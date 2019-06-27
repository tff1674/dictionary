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
	cout << "�������ֵ���ĵ���" << endl;
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
	cout << "����ɹ� ��" << endl;
}

void Add() {
	res result;
	string word;
	int cnt = 0;
	cout << "�����뵥�ʣ�" << endl;
	cin >> word;
	cout << "���������꣺" << endl;
	cin >> result.pron;
	cout << "�м������ͣ�" << endl;
	cin >> cnt;
	result.cnt = cnt;
	result.det = new detail[cnt];
	for (int i = 0; i < cnt; i++) {
		cout << "��" << i + 1 << "�ֵĴ��ԣ�";
		cin >> result.det[i].a;
		cout << "��" << i + 1 << "�ֵ���˼��";
		cin >> result.det[i].b;
	}
	if (dictmap.find(word) != dictmap.end())
		cout << "�˴��Ѿ����ڣ�" << endl;
	else {
		dictmap.insert(make_pair(word, result));
		t = true;
	}
}

void Search() {
	cout << "��������Ҫ���ҵĵ��ʣ�" << endl;
	cin >> buffer;
	map<string, res>::iterator mapIter;
	if ((mapIter = dictmap.find(buffer)) != dictmap.end()) {
		cout << "\"" << buffer << "\"" << "  ���ֵ���Ϊ�� " << endl;
		cout << "���꣺" << mapIter->second.pron << "\n";
		for (int i = 0; i < mapIter->second.cnt; i++)
			cout << "��" << i + 1 << "�֣�" << mapIter->second.det[i].a << " ��˼��" << mapIter->second.det[i].b << endl;
	}
	else {
		cout << "�˴ʲ������ֵ��У�" << endl;
	}
}

void Menu()
{
	system("cls");
	cout << "\t================================================" << endl;
	cout << "\t*                                              *" << endl;
	cout << "\t*              1����ʾ�ֵ�                     *" << endl;
	cout << "\t*              2����ӵ���                     *" << endl;
	cout << "\t*              3�����ҵ���                     *" << endl;
	cout << "\t*              4���޸��ֵ�                     *" << endl;
	cout << "\t*              5��ɾ������                     *" << endl;
	cout << "\t*              0����    ��                     *" << endl;
	cout << "\t*                                              *" << endl;
	cout << "\t================================================" << endl;
	cout << "����������ѡ�";
	cin >> choice;
	while (choice < -1 || choice>5)
	{
		cout << "�������" << endl << "���������룺" << endl;
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
			cout << "�Ƿ񱣴� ��Y/N����" << endl;
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
	cout << "��������Ҫ�滻�ĵ��ʣ�" << endl;
	cin >> chgf;
	map<string, res>::iterator mapIter;
	if ((mapIter = dictmap.find(chgf)) != dictmap.end())
	{
		delete[] mapIter->second.det;
		cout << "�м������壺";
		cin >> cnt;
		mapIter->second.det = new detail[cnt];
		for (int i = 0; i < cnt; i++) {
			cout << "��" << i + 1 << "�ִ��ԣ�";
			cin >> buf;
			mapIter->second.det[i].a = buf;
			cout << "��˼��";
			cin >> buf;
			mapIter->second.det[i].b = buf;
		}
		cout << "�޸ĳɹ���" << endl;
		cout << "���꣺" << mapIter->second.pron << "\n";
		for (int i = 0; i < mapIter->second.cnt; i++)
			cout << "��" << i + 1 << "�֣�" << mapIter->second.det[i].a << " ��˼��" << mapIter->second.det[i].b << endl;
		t = true;
	}
	else
	{
		cout << "�˴ʲ������ֵ��У�" << endl;
		return;
	}
}
void Delete()
{
	cout << "��������Ҫɾ���ĵ��ʣ�" << endl;
	cin >> buffer;
	map<string, res>::iterator mapIter;
	if ((mapIter = dictmap.find(buffer)) != dictmap.end()) {
		delete[] mapIter->second.det;
		dictmap.erase(buffer);
		t = true;
		cout << "ɾ���ɹ�" << endl;
	}
	else {
		cout << "�˴ʲ������ֵ��У�" << endl;
		return;
	}
}
int main()
{
	Menu();
	system("pause");
	return 0;
}
