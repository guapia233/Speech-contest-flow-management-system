#include"speechManager.h"
using namespace std;

int main() {
	srand((unsigned int)time(NULL)); //随机数种子

	SpeechManager sm;
  
	int choice = 0;

	while (true) {
		sm.show_Menu();
		cout << "请输入你要选择的数字：" << endl;
		cin >> choice;

		switch (choice) {
		case 1: //开始比赛
			sm.startSpeech();
		case 2: //查看记录
			sm.showRecord();
		case 3: //清空记录
			sm.clearRecord();
		case 0: //退出程序
			sm.exitSystem();
		default:
			system("cls");
			break;
		}
	}
	system("pause");

	return 0;
}
