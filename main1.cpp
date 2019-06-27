#include <iostream>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <map>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

typedef struct _detail {
	string a, b;
} detail;

typedef struct _res {
	string pron;
	int cnt;
	detail *det;
} res;

int choice;
bool t = false;
string buffer;
string str2, str3;
map<string, res> dictmap;
string str;
const char *p;

int Read();
void Menu();
void Do();
int main();
//void Translate();
void Add();
void Search();
void Change();
void Save(const char *p);
void Delete();

std::pair<string, res> readline(char * Line) {
	int cnt = 0;
	res result;
	char *tokbuf;
	char *tmp = strtok(Line, "|");
	string word = tmp;
	tmp = strtok(nullptr, "|");
	result.pron = tmp;
	tmp = strtok(nullptr, "|");
	result.cnt = cnt = atoi(tmp);
	result.det = new detail[cnt];
	for (int i = 0; i < cnt; i++) {
		tmp = strtok(nullptr, "|");
		result.det[i].a = tmp;
		tmp = strtok(nullptr, "|");
		result.det[i].b = tmp;
	}
	return make_pair(word, result);
}

int Read() {
	cout << "请输入字典的文档：" << endl;
	cin >> str;
	p = str.c_str();
	FILE *fp = fopen(p, "r");
	char Line[1024];
	while (fgets(Line, 1024, fp) != NULL) {
		if (strchr(Line, '|') == nullptr) continue;
		if (Line[strlen(Line) - 1] == '\n') Line[strlen(Line) - 1] = '\0';
		pair<string, res> tmp = readline(Line);
		map<string, res>::iterator it;
		if ((it = dictmap.find(tmp.first)) != dictmap.end())
			dictmap.erase(tmp.first);
		dictmap.insert(tmp);
	}
	for (auto r : dictmap) {
		cout << r.first << '\t' << r.second.pron << '\n';
		for (int i = 0; i < r.second.cnt; i++)
			cout << '\t' << r.second.det[i].a << '\t' << r.second.det->b;
		cout << "\n";
	}
	system("pause");
	fclose(fp);
	return 0;
}

void Save(const char *p) {
	ofstream fout(p);
	for (auto r : dictmap) {
		fout << r.first << '|';
		fout << r.second.pron << '|' << r.second.cnt;
		for (int i = 0; i < r.second.cnt; i++)
			fout << '|' << r.second.det[i].a << '|' << r.second.det->b;
		fout << "\n";
	}
	fout.close();
	cout << "保存成功 ！" << endl;
}

void Add() {
	res result;
	string word;
	int cnt = 0;
	cout << "请输入单词：" << endl;
	cin >> word;
	cout << "请输入音标：" << endl;
	cin >> result.pron;
	cout << "有几个解释：" << endl;
	cin >> cnt;
	result.cnt = cnt;
	result.det = new detail[cnt];
	for (int i = 0; i < cnt; i++) {
		cout << "第" << i + 1 << "种的词性：";
		cin >> result.det[i].a;
		cout << "第" << i + 1 << "种的意思：";
		cin >> result.det[i].b;
	}
	if (dictmap.find(word) != dictmap.end())
		cout << "此词已经存在！" << endl;
	else {
		dictmap.insert(make_pair(word, result));
		t = true;
	}
}

void Search() {
	cout << "请输入需要查找的单词：" << endl;
	cin >> buffer;
	map<string, res>::iterator mapIter;
	if ((mapIter = dictmap.find(buffer)) != dictmap.end()) {
		cout << "\"" << buffer << "\"" << "  在字典中为： " << endl;
		cout << "音标：" << mapIter->second.pron << "\n";
		for (int i = 0; i < mapIter->second.cnt; i++)
			cout << "第" << i + 1 << "种：" << mapIter->second.det[i].a << " 意思：" << mapIter->second.det[i].b << endl;
	}
	else {
		cout << "此词不存在字典中！" << endl;
	}
}

void Menu()
{
	system("cls");
	cout << "\t================================================" << endl;
	cout << "\t*                                              *" << endl;
	cout << "\t*              1、显示字典                     *" << endl;
	cout << "\t*              2、添加单词                     *" << endl;
	cout << "\t*              3、查找单词                     *" << endl;
	cout << "\t*              4、修改字典                     *" << endl;
	cout << "\t*              5、删除单词                     *" << endl;
	cout << "\t*              0、退    出                     *" << endl;
	cout << "\t*                                              *" << endl;
	cout << "\t================================================" << endl;
	cout << "请输入您的选项：";
	cin >> choice;
	while (choice < -1 || choice>5)
	{
		cout << "输入错误！" << endl << "请重新输入：" << endl;
		cin >> choice;
	}
	Do();
}

void Do()
{
	char a;
	switch (choice)
	{
	case 1:
		system("cls");
		Read();
		system("pause");
		system("cls");
		Menu();
		break;
	case 2:
		system("cls");
		Add();
		system("pause");
		system("cls");
		Menu();
		break;
	case 3:
		system("cls");
		Search();
		system("pause");
		system("cls");
		Menu();
		break;
	case 4:
		system("cls");
		Change();
		system("pause");
		system("cls");
		Menu();
		break;
	case 5:
		system("cls");
		Delete();
		system("pause");
		system("cls");
		Menu();
		break;
	case 0:
		if (t) {
			cout << "是否保存 （Y/N）？" << endl;
			cin >> a;
			if (a == 'Y' || a == 'y')
				Save(p);
		}
		exit(0);
		break;
	}
}

void Change()
{
	string chgf, buf;
	int cnt = 0;
	cout << "请输入您要替换的单词：" << endl;
	cin >> chgf;
	map<string, res>::iterator mapIter;
	if ((mapIter = dictmap.find(chgf)) != dictmap.end())
	{
		delete[] mapIter->second.det;
		cout << "有几个释义：";
		cin >> cnt;
		mapIter->second.det = new detail[cnt];
		for (int i = 0; i < cnt; i++) {
			cout << "第" << i + 1 << "种词性：";
			cin >> buf;
			mapIter->second.det[i].a = buf;
			cout << "意思：";
			cin >> buf;
			mapIter->second.det[i].b = buf;
		}
		cout << "修改成功！" << endl;
		cout << "音标：" << mapIter->second.pron << "\n";
		for (int i = 0; i < mapIter->second.cnt; i++)
			cout << "第" << i + 1 << "种：" << mapIter->second.det[i].a << " 意思：" << mapIter->second.det[i].b << endl;
		t = true;
	}
	else
	{
		cout << "此词不存在字典中！" << endl;
		return;
	}
}
void Delete()
{
	cout << "请输入需要删除的单词：" << endl;
	cin >> buffer;
	map<string, res>::iterator mapIter;
	if ((mapIter = dictmap.find(buffer)) != dictmap.end()) {
		delete[] mapIter->second.det;
		dictmap.erase(buffer);
		t = true;
		cout << "删除成功" << endl;
	}
	else {
		cout << "此词不存在字典中！" << endl;
		return;
	}
}
int main()
{
	Menu();
	system("pause");
	return 0;
}
