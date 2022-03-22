#include "lib.h"
#include<string>
using namespace std;
struct Spec {
	int x = 60, y = 10;
	int width = 20, height = 2;
};
void box(int x,int y,int width, int height, int textcolor,int bcolor ,string text) {
	//backgroundcolor(75);
	//Textcolor(180);
	/*for (int i = x; i <= x + width; i++) {
		for (int j = y; j <= y + height; j++) {
			gotoxy1(i,j);
			cout << " ";
		}
	}*/
	Textcolor(10);
	gotoxy(x + 1, y + 1);
	cout << text;
	//backgroundcolor(1);
	Textcolor(11);
	for (int i = x; i <= x + width; i++) {
		gotoxy1(i, y);
		cout << char(196);
		gotoxy1(i, y + height);
		cout << char(196);
	}
	for (int i = y; i <= y + height; i++) {
		gotoxy1(x, i);
		cout << char(179);
		gotoxy1(x + width, i);
		cout << char(179);
	}
	gotoxy(x, y); cout << char(218);
	gotoxy(x + width, y); cout << char(191);
	gotoxy(x, y + height); cout << char(192);
	gotoxy(x + width, y + height); cout << char(217);
}
int main() {
	//Spec spec = { 60,10,20,2};
	box(60, 10, 20, 2,10,11,"HOME");
	//Spec spec1 = { 60,13,20,2};
	box(60, 13, 20, 2, 10, 11, "CURRENT TIME");
	//Spec spec2 = { 60,16,20,2};
	box(60, 16, 20, 2, 10, 11, "LOG OUT");
	
	int x = 59, y = 11;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	char var;
	
	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
		}
		var = _getch();
		//if (var == 13 && x == 60 && y == 10) {
		//	//HOME
		//}
		//else if (var == 13 && x == 60 && y == 13) {

		//}

		if (var == 72) {
			if (x == 60 && y == 10) {
				ycu = y;
				y += 3 * 3;
			}
			else {
				ycu = y;
				y -= 3;
			}
			
		}
		else if (var == 80) {
			if (x == 60 && y == 16) {
				ycu = y;
				y += 3 * 3;
			}
			else {
				ycu = y;
				y -= 3;
			}
		}

	}
	cout << "\n\n";
	_getch();
}
//180//188