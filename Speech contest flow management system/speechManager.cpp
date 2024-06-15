#include"speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
SpeechManager::~SpeechManager() {

}
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->mp.clear();
	this->m_Record.clear();
	this->round = 1;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_Score[i] = 0;
		}
		this->v1.push_back(i + 10001);
		this->mp.insert(make_pair(i + 10001, sp));
	}
	
}

void SpeechManager::startSpeech() {
	//第一轮比赛
	this->speechDraw(); //1、抽签

	this->speechContest(); //2、比赛

	this->showScore(); //3、显示晋级结果

	//第二轮比赛
	this->round++;
	this->speechDraw(); //1、抽签

	this->speechContest(); //2、比赛

	this->showScore(); //3、显示最终结果

	this->saveRecord(); //4、保存分数
	
	//重置比赛，更新数据
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	cout << "第 << " << this->round << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (round == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest() {
	cout << "------------- 第" << this->round << "轮正式比赛开始：------------- " << endl;
	multimap<double, int, greater<int>> groupScore;
	int num = 0;
	vector<int> v;
	if (round == 1) v = v1;
	else v = v2;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->mp[*it].m_Score[round - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号: " << it->second << " 姓名： " << this->mp[it->second].m_Name << " 成绩： " << this->mp[it->second].m_Score[this->round - 1] << endl;
			}

			int cnt = 0; //取前三名		
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && cnt < 3; it++, cnt++) {
				if (this->round == 1) {
					v2.push_back((*it).second);
				}
				else {
					victory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------- 第" << this->round << "轮比赛完毕  ------------- " << endl;
	system("pause");
}

void SpeechManager::showScore() {
	cout << "---------第" << this->round << "轮晋级选手信息如下：-----------" << endl;
	vector<int> v;
	if (this->round == 1) v = v2;
	else v = victory;
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号：" << *it << " 姓名： " << mp[*it].m_Name << " 得分： " << mp[*it].m_Score[this->round - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++) {
		ofs << *it << "," << mp[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();

	this->fileIsEmpty = false;
	cout << "记录已经保存" << endl;
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);  

	//文件不存在
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl; //测试用
		ifs.close();
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); //把读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string> v;                        

		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",", start); //从0开始查找逗号
			if (pos == -1) {
				break; //找不到break返回
			}
			string tmp = data.substr(start, pos - start); //找到逗号后后进行分割 
			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();
}

void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件为空或者不存在" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
		system("pause");
		system("cls");
	}
}

void SpeechManager::clearRecord() {
	cout << "确认清空吗？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//打开模式为ios::trunc，如果文件存在则删除文件并重新创建空文件
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}