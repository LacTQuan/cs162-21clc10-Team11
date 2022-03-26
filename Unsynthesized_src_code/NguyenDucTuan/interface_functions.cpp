#include<iostream>
#include<cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include<cmath>
#include<string>
#include <conio.h>
#include <Windows.h>
//#include<bits/stdc++.h>
using namespace std;
void Nocursortype(){
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void gotoxy(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX - 1;
	Position.Y = posY - 1;

	SetConsoleCursorPosition(hStdout, Position);
}
void Textcolor(int x){
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);

}