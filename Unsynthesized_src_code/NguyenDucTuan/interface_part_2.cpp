#include "lib.h"
#include<string>
using namespace std;
int HOME = 0;
struct Spec {
	int x = 60, y = 10;
	int width = 20, height = 2;
};
void box(int x,int y,int width, int height, int textcolor,int bcolor ,string text) {

	Textcolor(10);
	gotoxy(x + 1, y + 1);
	cout << text;
	
	Textcolor(11);
	for (int i = x; i <= x + width; i++) {
		gotoxy(i, y);
		cout << char(196);
		gotoxy(i, y + height);
		cout << char(196);
	}
	for (int i = y; i <= y + height; i++) {
		gotoxy(x, i);
		cout << char(179);
		gotoxy(x + width, i);
		cout << char(179);
	}
	gotoxy(x, y); cout << char(218);
	gotoxy(x + width, y); cout << char(191);
	gotoxy(x, y + height); cout << char(192);
	gotoxy(x + width, y + height); cout << char(217);
}


void STUDENT_COUR_PAGE(int locate_x, int locate_y, int number_of_cells, string STUDENT_COUR_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, STUDENT_COUR_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) cout << "A";
				else if (cell == 2) {
					cout << "B";
				}
				else if (cell == 3) {
					HOME = 4;
					return;
				}
				else if (cell == 4) break;
			}
		}


	}
}
void SEMESTER_PAGE(int locate_x, int locate_y, int number_of_cells, string SEMESTER_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) cout << "A";
				else if (cell == 2) {
					system("cls");
					string STUDENT_COUR_name_list_of_boxs[] = { "Create semester","View semester","Home","Return","n","n","n","n","n","n" };
					STUDENT_COUR_PAGE(60, 10, 10, STUDENT_COUR_name_list_of_boxs);
					system("cls");
					//
					if (HOME == 4) return;
					//
					for (int i = 0; i < number_of_cells; i++) {
						box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
					}
				}
				else if (cell == 3) cout << "C";
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;
			}
		}


	}
}


void STUDENT_PAGE(int locate_x, int locate_y, int number_of_cells, string STUDENT_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, STUDENT_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) cout << "A";
				else if (cell == 2) {
					HOME = 4;
					return;
				}
				else if (cell == 3) break;
			}
		}


	}
}
void CLASS_PAGE(int locate_x, int locate_y, int number_of_cells, string CLASS_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CLASS_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) cout << "A";
				else if (cell == 2) {
					system("cls"); // doi ten, doi so luong
					string STUDENT_name_list_of_boxs[] = { "Create student","Home","Return" }; // change
					STUDENT_PAGE(60, 10, 3, STUDENT_name_list_of_boxs); //change
					system("cls");
					//
					if (HOME == 4) return;
					//
					for (int i = 0; i < number_of_cells; i++) {
						box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CLASS_name_list_of_boxs[i]);
					}
				}
				else if (cell == 3) {
					HOME = 4;
					return;
				}
				else if (cell == 4) break;
			}
		}


	}
}
void YEAR_PAGE(int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) cout << "A";
				else if (cell == 2) {
					system("cls");
					string CLASS_name_list_of_boxs[] = { "Create class","View student","Home","Return" };
					CLASS_PAGE(60, 10, 4, CLASS_name_list_of_boxs);
					system("cls");
					//
					if (HOME == 4) return;
					//
					for (int i = 0; i < number_of_cells; i++) {
						box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
					}
				}
				else if (cell == 3) {
					system("cls");
					string SEMESTER_name_list_of_boxs[] = { "Create semester","View semester","Home","Return" };
					SEMESTER_PAGE(60, 10, 4, SEMESTER_name_list_of_boxs);
					system("cls");
					//
					if (HOME == 4) return;
					//
					for (int i = 0; i < number_of_cells; i++) {
						box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
					}
				}
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;
			}
		}


	}
}

void HOME_PAGE(int locate_x,int locate_y, int number_of_cells, string HOME_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, HOME_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		HOME = 0;
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
					system("cls");
					string YEAR_name_list_of_boxs[] = { "Create year","View classes","View semesters","Home","Return"};
					YEAR_PAGE(60, 10, 5, YEAR_name_list_of_boxs);
					system("cls");

					for (int i = 0; i < number_of_cells; i++) {
						box(locate_x, locate_y + i * 3, 20, 2, 10, 11, HOME_name_list_of_boxs[i]);
					}
				}
				else if (cell == 2) cout << "B";
				else if (cell == 3) break;
			}
		}


	}
}
int main() {
	Nocursortype();
	string HOME_name_list_of_boxs[] = { "HOME","CURRENT TIME","LOG OUT" };
	HOME_PAGE(60,10, 3, HOME_name_list_of_boxs);
	cout << "\n\n";
	_getch();
}
//180//188
/*
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
	int cell = 1; int text = 3;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == 60 && y == 10) {
					ycu = y;
					y += 3 * 3;
					cell = text;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == 60 && y == 16) {
					ycu = y;
					y -= 3 * 3;
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) cout << "A";
				else if (cell == 2) cout << "B";
			}
		}


	}
*/