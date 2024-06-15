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
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
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
		string name = "ѡ��";
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
	//��һ�ֱ���
	this->speechDraw(); //1����ǩ

	this->speechContest(); //2������

	this->showScore(); //3����ʾ�������

	//�ڶ��ֱ���
	this->round++;
	this->speechDraw(); //1����ǩ

	this->speechContest(); //2������

	this->showScore(); //3����ʾ���ս��

	this->saveRecord(); //4���������
	
	//���ñ�������������
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	cout << "�� << " << this->round << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

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
	cout << "------------- ��" << this->round << "����ʽ������ʼ��------------- " << endl;
	multimap<double, int, greater<int>> groupScore;
	int num = 0;
	vector<int> v;
	if (round == 1) v = v1;
	else v = v2;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		num++;
		//��ί���
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
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "���: " << it->second << " ������ " << this->mp[it->second].m_Name << " �ɼ��� " << this->mp[it->second].m_Score[this->round - 1] << endl;
			}

			int cnt = 0; //ȡǰ����		
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
	cout << "------------- ��" << this->round << "�ֱ������  ------------- " << endl;
	system("pause");
}

void SpeechManager::showScore() {
	cout << "---------��" << this->round << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	vector<int> v;
	if (this->round == 1) v = v2;
	else v = victory;
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << mp[*it].m_Name << " �÷֣� " << mp[*it].m_Score[this->round - 1] << endl;
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
	cout << "��¼�Ѿ�����" << endl;
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);  

	//�ļ�������
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl; //������
		ifs.close();
		return;
	}

	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ��!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch); //�Ѷ�ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string> v;                        

		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",", start); //��0��ʼ���Ҷ���
			if (pos == -1) {
				break; //�Ҳ���break����
			}
			string tmp = data.substr(start, pos - start); //�ҵ����ź����зָ� 
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
		cout << "�ļ�Ϊ�ջ��߲�����" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}
		system("pause");
		system("cls");
	}
}

void SpeechManager::clearRecord() {
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//��ģʽΪios::trunc������ļ�������ɾ���ļ������´������ļ�
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}