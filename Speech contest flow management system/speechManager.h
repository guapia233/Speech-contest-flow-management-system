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
	void show_Menu(); //显示菜单
	void startSpeech(); //开始比赛
	void exitSystem(); //退出系统
	void initSpeech(); //初始化容器   
	void createSpeaker(); //创建选手
	void speechDraw(); //抽签
	void speechContest(); //比赛
	void showScore(); //显示晋级情况
	void saveRecord(); //保存分数
	void loadRecord(); //读取记录
	void showRecord(); //查看记录
	void clearRecord(); //清空记录

	vector<int> v1; //第一轮选手容器
	vector<int> v2; //第二轮选手容器
	vector<int> victory; //胜利选手容器
	map<int, Speaker> mp; //选手所对应编号
	int round; //比赛轮数
	bool fileIsEmpty; //文件为空的标志
	map<int, vector<string>> m_Record; //往届记录
};
 