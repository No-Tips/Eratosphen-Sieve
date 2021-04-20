#pragma once
#include <iostream>
#include <vector>
#include <string>
#include<windows.h>

using namespace std;

vector<int> Numbers;

int Bad_Eratos(0); //�� ������, ���� �����, ��� ����� �� ����� ������� �� MAX_COL_WIDTH

int BEAUTY_COL_WIDTH(1)/*������ ������ */, BEAUTY_COL_SIZE/* ������ ����� ������ */;
const int MAX_COL_WIDTH(10)/* ������������ ������ ����� ������ */, MIN_COL_WIDTH(4)/* ����������� ������ ������*/;
const int DELAY = 5*100; //�������� ����� ��������. (0,5 ������)

string DIV_LINE = "";/* �������������� */
string DIV_CHAR = "=";
string START_ITTER = "|";
string END_ITTER = "|";

bool BeautySetup() { //� ���� ������� ������ �������� �� ���.

	//END_ITTER += "\n";
	START_ITTER += " ";

	//������� ������������ ����� �����
	BEAUTY_COL_WIDTH = (to_string (Numbers.back())).length();

	//�������, ������� ����� �� ����� ������ � ���� ������.
	int size = Numbers.size();
	bool Switch = true;
	for (int i = MAX_COL_WIDTH; i >= MIN_COL_WIDTH;i--) {
		if ((Numbers.size()) % i == 0) {
			BEAUTY_COL_SIZE = i;
			Switch = false;
			break;
		}
	}
	if (Switch) { //���� ����� ������� - ��� �� �� ��� �� �������, � ������, ��� ��������� ������ ����� �� ������.
		for (int badnums = 1; badnums < MAX_COL_WIDTH-1;badnums++) {
			for (int i = MAX_COL_WIDTH; i >= MIN_COL_WIDTH;i--) {
				if ((Numbers.size() + badnums) % i == 0) {
					BEAUTY_COL_SIZE = i;
					Switch = false;
					Bad_Eratos = badnums;
					break;
				}
			}
		}
	}
	if (Switch) {//���� ����� ������, � �� ����� ������ �����.
		printf("MAX_COL_WIDTH setup error!\n");
		return 1; 
	}
	//������ ��� ��������������.
	int tempsize = BEAUTY_COL_WIDTH + 4; //������ ������� ����� �������� ���� ������.
	for (int i = 1; i <= BEAUTY_COL_SIZE;i++) {
		for (int j = 1;j < tempsize;j++) {
			DIV_LINE.append(DIV_CHAR);
		}
	}
	DIV_LINE.append(DIV_CHAR + "\n");

	return 0;
}

string AddSpace(string str, bool Switch) {
	if (Switch) str += " ";
	else str = " " + str;
	return str;
}

string OutNum(int number) {
	string out = to_string(number);
	int temp = out.length();
	bool Switch = true;
	while(temp < BEAUTY_COL_WIDTH) {
		temp++;
		out = AddSpace(out, Switch);
		if (Switch) Switch = false;
		else Switch = true;
	}
	out = START_ITTER + out + " ";
	return out;
}




string* GenSieve(string* sieve, int columns) { //��������� ������� ������. ������ ����� ������� ������� - ����� ������.
	for(int i = 0; i< columns;i++) sieve[i] = ""; //������� ���� ������
	int itter = 0;
	int curcolumn = 0;
	for (vector<int>::iterator it = Numbers.begin(); it != Numbers.end(); it++, itter++)
	{
		string out = "";
		if (*it) out = OutNum(*it);
		if (itter == BEAUTY_COL_SIZE) { sieve[curcolumn] += END_ITTER; itter = 0; curcolumn++; }
		sieve[curcolumn] += out;
	}
	while (Bad_Eratos) {
		string out = "";
		for (int i = 0; i < BEAUTY_COL_WIDTH;i++) {
			out += " ";
		}
		sieve[curcolumn] += START_ITTER + out + " ";
		Bad_Eratos--;
	}
	sieve[curcolumn] += END_ITTER;
	return sieve;
}

void Output(string* Sieve, int column) { //������ ����� ������
	cout << DIV_LINE;
	for (int i = 0;i < column; i++) cout << Sieve[i] << "\n";
	cout << DIV_LINE;
}



string replace(string findstr, string data) {
	string newstr = " ";
	for (int i = 1; i < findstr.length();i++) {
		newstr += " ";
	}
	
	data.replace(data.find(findstr), (findstr.length()), newstr);
	return data;
}

string* EratospenSieve(string* Sieve, int num, int column) {
	cout << DIV_LINE;
	int curcolumn = 0;
	Sieve[curcolumn];
	for (curcolumn; curcolumn < column;curcolumn++) {
		cout << Sieve[curcolumn];
		for (int itter = 2; itter * itter < num; itter++) {
			int pos = (BEAUTY_COL_SIZE * curcolumn);
			while (pos != (BEAUTY_COL_SIZE * (curcolumn + 1))) {
				if (Numbers[pos] % itter == 0 and itter!=Numbers[pos]) {
					//�������� ��� ������� �� �������	
					Sieve[curcolumn]=replace((to_string(Numbers[pos])), Sieve[curcolumn]);
					cout <<"\r"<< Sieve[curcolumn] << flush;
					Sleep(DELAY);
					Numbers[pos] = 1;
				}
				pos++;
			}
		}
		cout << "\n";
	}
	cout << DIV_LINE;
	return Sieve;
}

int main() {
	int num;
	printf("Enter your number: ");
	cin >> num;
	for (int i = 2; i < num+1;i++) {
		Numbers.push_back(i);
	}
	if (BeautySetup()) {
		printf("\nOops, something went wrong!\n");
		return 0;
	}

	//� �����, ��� ���� ����� � ���� ����� ��� �� � ���� ������, ����� �� ������� � ��� ��������.
	int column = (Numbers.size() + Bad_Eratos) / BEAUTY_COL_SIZE;
	string* Sieve = new string[column];			//������� ���� ������ ����������
	Sieve = GenSieve(Sieve, column);
	Output(Sieve, column);
	Sieve = EratospenSieve(Sieve, num, column);
	Output(Sieve, column);


}