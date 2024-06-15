#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include <numeric>
#include <algorithm>
#include <ctime>
#include"speaker.h"
using namespace std;

class SpeechManager {
public:
	SpeechManager();
	~SpeechManager();  
	void show_Menu(); //��ʾ�˵�
	void startSpeech(); //��ʼ����
	void exitSystem(); //�˳�ϵͳ
	void initSpeech(); //��ʼ������   
	void createSpeaker(); //����ѡ��
	void speechDraw(); //��ǩ
	void speechContest(); //����
	void showScore(); //��ʾ�������
	void saveRecord(); //�������
	void loadRecord(); //��ȡ��¼
	void showRecord(); //�鿴��¼
	void clearRecord(); //��ռ�¼

	vector<int> v1; //��һ��ѡ������
	vector<int> v2; //�ڶ���ѡ������
	vector<int> victory; //ʤ��ѡ������
	map<int, Speaker> mp; //ѡ������Ӧ���
	int round; //��������
	bool fileIsEmpty; //�ļ�Ϊ�յı�־
	map<int, vector<string>> m_Record; //�����¼
};
 