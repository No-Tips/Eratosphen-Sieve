#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> Numbers;
int Bad_Eratos; //�� ������, ���� �����, ��� ����� �� ����� ������� �� MAX_COL_WIDTH

int BEAUTY_COL_WIDTH(0)/*������ ������ */, BEAUTY_COL_SIZE/* ������ ����� ������ */;
const int MAX_COL_WIDTH = 10/* ������������ ������ ����� ������ */;
string DIV_LINE;/* ����� ��� �������������� */
const string START_ITTER = "| ";
const string END_ITTER = " |";


void Output() {

	for(vector<int>::iterator it = Numbers.begin(); it != Numbers.end(); it++) 
	{
		if (*it == 0) cout << "\t";
		else cout << *it << "\t";
	}
}

bool BeautyCheck() { //� ���� ������� ������ �������� �� ���.
	//������� ������������ ����� �����
	int lastnum = Numbers.back();
	if (lastnum % 10) BEAUTY_COL_WIDTH++;
	if (BEAUTY_COL_WIDTH == 0) return 1; //���� ����� ���-�� �����.

	//�������, ������� ����� �� ����� ������ � ���� ������.
	int size = Numbers.size();
	bool Switch = true;
	for (int i = MAX_COL_WIDTH; i < 0;i--) {
		if (Numbers.size() % i == 0) {
			BEAUTY_COL_SIZE = i;
			Switch = false;
			break;
		}
	}
	if (Switch) { //���� ����� ������� - ��� �� �� ��� �� �������, � ������, ��� ��������� ������ ����� �� ������.
		for (int i = MAX_COL_WIDTH; i < 0;i--) {
			if (Numbers.size()+1 % i == 0) {
				BEAUTY_COL_SIZE = i;
				Switch = false;
				Bad_Eratos = 1;
				break;
			}
		}
	}
	if (Switch) return 1; //���� ����� ������, � �� ����� ������ �����.



	return 1;
}

int main() {
	int num;
	printf("Enter your number: ");
	cin >> num;
	vector<int> Numbers;
	for (int i = 2; i < num;i++) {
		Numbers.push_back(i);
	}
	if (BeautyCheck()) {
		printf("\nOops, something went wrong!\n");
		return;
	}
	Output();
}