#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> Numbers;

int Bad_Eratos(0); //На случай, если число, что ввели не ровно делится на MAX_COL_WIDTH

int BEAUTY_COL_WIDTH(1)/*Ширина ячейки */, BEAUTY_COL_SIZE/* Ширина одной строки */;
const int MAX_COL_WIDTH(10)/* Максимальная ширина одной строки */, MIN_COL_WIDTH(4)/* Минимальная ширина строки*/;


string DIV_LINE = "";/* Разграничитель */
string DIV_CHAR = "=";
string START_ITTER = "|";
string END_ITTER = "|";

bool BeautySetup() { //Я хочу сделать решето красивым на вид.

	END_ITTER += "\n";
	START_ITTER += " ";

	//Считаем максимальную длину числа
	BEAUTY_COL_WIDTH = (to_string (Numbers.back())).length();

	//Считаем, сколько чисел мы будем лепить в одну строку.
	int size = Numbers.size();
	bool Switch = true;
	for (int i = MAX_COL_WIDTH; i >= MIN_COL_WIDTH;i--) {
		if ((Numbers.size()) % i == 0) {
			BEAUTY_COL_SIZE = i;
			Switch = false;
			break;
		}
	}
	if (Switch) { //Если число простое - оно ни на что не делится, а значит, что последняя строка будет не ровная.
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
	if (Switch) {//Если прямо пиздец, и не нашло такого числа.
		printf("MAX_COL_WIDTH setup error!\n");
		return 1; 
	}
	//Делаем наш разграничитель.
	int tempsize = BEAUTY_COL_WIDTH + 4; //Именно столько будет занимать одна ячейка.
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


void Output() {

	int itter = 0;
	cout << DIV_LINE;
	for(vector<int>::iterator it = Numbers.begin(); it != Numbers.end(); it++,itter++) 
	{
		string out = "";
		if(*it) out = OutNum(*it);
		else {//Если мы "удалили" элемент.
			for (int i = 0; i < BEAUTY_COL_WIDTH;i++) {
				out += " ";
			}
			out = START_ITTER + out + " ";
		}
		if (itter == BEAUTY_COL_SIZE) {out = END_ITTER + out; itter = 0;}
		cout << out;
	}
	while (Bad_Eratos) {
		string out = "";
		for (int i = 0; i < BEAUTY_COL_WIDTH;i++) {
			out += " ";
		}
		cout << START_ITTER + out + " ";
		Bad_Eratos--;
	}
	cout << END_ITTER + DIV_LINE;
}

void EratospenSieve(int num) {
	for (int itter = 2; itter * itter < num; itter++) {
		int pos = itter;
		while(pos != Numbers.size()){
			if (Numbers[pos] % itter == 0) {
				Numbers[pos] = 0;
			}
			pos++;
		}
	}
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

	//Я решил, что весь вывод у меня будет все же в виде текста, чтобы по красоте с ним работать.
	int column = (Numbers.size() + Bad_Eratos) / BEAUTY_COL_SIZE;
	string** Sieve = new string*[column];			//Создаем
	for (int temp = 0; temp < column;temp++) {		//Наше решето Эратосфена
		Sieve[temp] = new string[DIV_LINE.length()];//Как прекрасный двумерный массив
	}
	Output();
	EratospenSieve(num);
	Output();
}