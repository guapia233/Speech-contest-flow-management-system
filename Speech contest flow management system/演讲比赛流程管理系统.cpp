#include"speechManager.h"
using namespace std;

int main() {
	srand((unsigned int)time(NULL)); //���������

	SpeechManager sm;
  
	int choice = 0;

	while (true) {
		sm.show_Menu();
		cout << "��������Ҫѡ������֣�" << endl;
		cin >> choice;

		switch (choice) {
		case 1: //��ʼ����
			sm.startSpeech();
		case 2: //�鿴��¼
			sm.showRecord();
		case 3: //��ռ�¼
			sm.clearRecord();
		case 0: //�˳�����
			sm.exitSystem();
		default:
			system("cls");
			break;
		}
	}
	system("pause");

	return 0;
}
