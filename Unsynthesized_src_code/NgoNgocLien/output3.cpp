#include<iostream>
#include<cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include<cmath>
#include<string.h>
#include <conio.h>
#include <Windows.h>
//#include<bits/stdc++.h>
using namespace std;

#define nullptr 0
int HOME = 0;
int LOG_OUT = 0;

//right
struct Mark{ // new
    double Total = 0, Final = 0, Midterm = 0, Other = 0;
};
struct Cur_Course{ //new
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Mark mark;      
    Cur_Course* pNext_Cur_Cour;
    //Temp_Course* pTemp_Cour;
};
struct Student{
    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    double GPA = 0;  // new
    Student* pNext_Student;
    Cur_Course* pCur_Cour;
};
struct Class{
    string name;
    Student* pStudent;
    Class* pNext_Class;
};
//left
struct Student_Course{
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    Mark mark;
    Student_Course* pNext_Student_Course;
};
struct Course{
    //Course id, Course name, teacher name, number of credits, 
    //the maximum number of students (default 50), day, and the session
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Course* pNext_Course;
    Student_Course* pStudent_Course;
};
struct Semester{
    string name;
    Semester* pNext_Semester;
    Course* pCourse;
};
//main
struct Year{
    string name;
    Class* pClass;
    Year* pNext_Year;
    Semester* pSemester;
};
// Time
struct Time{
    int date;
    int month;
    int year;
};
struct Registration_Session{
    Time start;
    Time end;
};
struct Account{
    string username, password;
    Account *next;
};
struct User{ // new
// hold current user
// Purpose: avoid a user change another user's password
    string username;
    string password;
};
Registration_Session S;
Account *account_head;
User U;

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

Semester* find_semester(Semester* pSem, string name) {
    if (!pSem) return nullptr;
    while (pSem && pSem->name != name)
        pSem = pSem->pNext_Semester;
    return pSem;
}

Year* Current_Year = nullptr;

bool account_check(Account *head, User U){
    bool success = false;
    Account *cur = head;
    while (!success && cur){
        if (cur->username == U.username && cur->password == U.password)
            success = true;
        else
            cur = cur->next;
    }
    return success;
}
// Load all usernames and passwords to a linked list
Account *load_account_list(){
    fstream inputFile("account.csv", ios::in);
    Account *head = new Account;
    getline(inputFile, head->username, ',');
    getline(inputFile, head->password, '\n');

    Account *cur = head;
    do{
        cur->next = new Account;
        cur = cur->next;
        getline(inputFile, cur->username, ',');
        getline(inputFile, cur->password, '\n');
        cur->next = nullptr;
    }while (inputFile.eof() == false);

    inputFile.close();
    return head;
}
void save_account_list(Account *head){
    fstream changeFile("account.csv", ios::out); // rewrite file
    Account *cur = head;
    changeFile << cur->username << ',' << cur->password;
    cur = cur->next;
    while (cur){
        changeFile << '\n'<< cur->username << ',' << cur->password;
        cur = cur->next;
    }
    changeFile.close();
}
void delete_account_list(Account *&head){
    Account *temp = nullptr;
    while (head){
        temp = head->next;
        delete head;
        head = temp;
    }
}
void change_password(Account *head, User U){
    Account *cur = head;
    bool found = false;
    while (cur && cur->username != U.username)
        cur = cur->next;
    if (cur == nullptr){
        cout << "ERROR!\n";
    }
    else
        cur->password = U.password;
    return;
}
// create account
void Create_Account_For_new_Student(string student_id) {
    Account* cur = account_head;
    Account* newAcc = new Account;
    newAcc->username = student_id;
    newAcc->password = "123456789";
    newAcc->next = nullptr;

    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;

    if (cur == nullptr) account_head = newAcc;
    else cur->next = newAcc;
}

// void Add_New_Account(Account* head) {
//     Account* cur = head;
//     while (cur != nullptr && cur->next != nullptr) cur = cur->next;
//     if ()
// }
void Create_Course(Semester* sem) { 
    cout << setfill('_') << setw(127) << '\n';
    cout << setfill(' ') << setw(9) << left << " ID" << " | ";
    cout << setw(7) << left << "Credits" << " | ";
    cout << setw(8) << left << "Capacity" << " | ";
    cout << setw(20) << left << "Course's name" << " | ";
    cout << setw(28) << left << "Teacher's name" << " | ";
    cout << setw(15) << left << "Time performing" << " | ";
    cout << setw(9) << left << "Start day" << " | ";
    cout << setw(8) << left << "End day" << '\n';
    
    cout << setfill('_') << setw(11) << right << "|";
    cout << setw(10) << right << "|";
    cout << setw(11) << right << "|";
    cout << setw(23) << right << "|";
    cout << setw(31) << right << "|";
    cout << setw(18) << right << "|";
    cout << setw(12) << right << "|";
    cout << setw(11) << right << '\n';

    ifstream filein("course.csv");
    string s = "";
    while(filein.eof() == false){
        Course* pCur_Course = sem->pCourse;
        Course* add_Course = new Course;

        getline(filein,add_Course->CourseID,',');           
        getline(filein,add_Course->Number_of_Credits,',');  
        getline(filein,add_Course->Max_Student,',');        
        getline(filein,add_Course->Course_Name,',');        
        getline(filein,add_Course->Teacher_Name,',');      
        getline(filein,add_Course->Day1,',');
        getline(filein,add_Course->Session1,',');
        getline(filein,add_Course->Day2,',');
        getline(filein,add_Course->Session2,',');
        getline(filein,add_Course->Start_Day,','); 
        getline(filein,add_Course->End_Day,'\n');

        cout << " " << setfill(' ') << setw(8) << left << add_Course->CourseID << " | ";
        cout << setw(7) << right << add_Course->Number_of_Credits << " | ";
        cout << setw(8) << right << add_Course->Max_Student << " | ";
        cout << setw(20) << left << add_Course->Course_Name << " | ";
        cout << setw(28) << left << add_Course->Teacher_Name << " | ";
        s = add_Course->Day1; s += " "; s += add_Course->Session1;
        cout << setw(15) << left << s << " | ";
        cout << setw(9) << left << add_Course->Start_Day << " | ";
        cout << setw(8) << left << add_Course->End_Day << '\n';
        s = add_Course->Day2; s += " "; s += add_Course->Session2;
        cout << setw(11) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(23) << right << "|";
        cout << setw(31) << right << "|";
        cout << ' ' << setw(15) << left << s << " |";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';

        add_Course->pNext_Course = nullptr;  
        add_Course->pStudent_Course = nullptr;

        if(sem->pCourse == NULL) sem->pCourse = add_Course;
        else{
            while(pCur_Course->pNext_Course != NULL) pCur_Course = pCur_Course->pNext_Course;
            pCur_Course->pNext_Course = add_Course;
        }
          
    }
    filein.close();
    
}

void Print_Course(Semester* sem) {
    Course* pCourse = sem->pCourse;
    cout << endl;
    cout << setfill('_') << setw(127) << '\n';
    cout << setfill(' ') << setw(9) << left << " ID" << " | ";
    cout << setw(7) << left << "Credits" << " | ";
    cout << setw(8) << left << "Capacity" << " | ";
    cout << setw(20) << left << "Course's name" << " | ";
    cout << setw(28) << left << "Teacher's name" << " | ";
    cout << setw(15) << left << "Time performing" << " | ";
    cout << setw(9) << left << "Start day" << " | ";
    cout << setw(8) << left << "End day" << '\n';
    
    cout << setfill('_') << setw(11) << right << "|";
    cout << setw(10) << right << "|";
    cout << setw(11) << right << "|";
    cout << setw(23) << right << "|";
    cout << setw(31) << right << "|";
    cout << setw(18) << right << "|";
    cout << setw(12) << right << "|";
    cout << setw(11) << right << '\n';
    string s = "";
    while (pCourse != NULL) {
        cout << " " << setfill(' ') << setw(8) << left << pCourse->CourseID << " | ";
        cout << setw(7) << right << pCourse->Number_of_Credits << " | ";
        cout << setw(8) << right << pCourse->Max_Student << " | ";
        cout << setw(20) << left << pCourse->Course_Name << " | ";
        cout << setw(28) << left << pCourse->Teacher_Name << " | ";
        s = pCourse->Day1; s += " "; s += pCourse->Session1;
        cout << setw(15) << left << s << " | ";
        cout << setw(9) << left << pCourse->Start_Day << " | ";
        cout << setw(8) << left << pCourse->End_Day << '\n';
        s = pCourse->Day2; s += " "; s += pCourse->Session2;
        cout << setw(11) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(23) << right << "|";
        cout << setw(31) << right << "|";
        cout << ' ' << setw(15) << left << s << " |";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';
        pCourse = pCourse->pNext_Course;
    }
}
Course* find_Course(Course* pCourse, string name) {
    if (!pCourse) return nullptr;
    if (pCourse->Course_Name == name) return pCourse;
    while (pCourse->pNext_Course && pCourse->pNext_Course->Course_Name != name)
        pCourse = pCourse->pNext_Course;
    if(pCourse->pNext_Course && pCourse->pNext_Course->Course_Name == name)
        return pCourse;
    else   
        return nullptr;
}
// find student
Student* find_student_in_1_class(Class* classes, string Student_ID){
    if(classes->pStudent == NULL) return NULL;
    Student* pCur_Student = classes->pStudent;
    
    while(pCur_Student != NULL && pCur_Student->StudentID != Student_ID)
        pCur_Student = pCur_Student->pNext_Student;

    if(pCur_Student != NULL) return pCur_Student;
    return NULL;
}
Student* find_student_in_many_classes(Year* year, string Student_ID){
    if(year->pClass == NULL) return NULL;
    Class* pCur_Class = year->pClass;

    while(pCur_Class != NULL){
        Student* temp = find_student_in_1_class(pCur_Class,Student_ID);
        if(temp != NULL) return temp;
        pCur_Class = pCur_Class->pNext_Class;
    }
    return NULL;
}
//find course

// find student in course
Student_Course* find_student_in_a_course(Course* cour, string Student_ID) {
    Student_Course* pCur = cour->pStudent_Course;
    while (pCur != nullptr && pCur->StudentID != Student_ID) pCur = pCur->pNext_Student_Course;
    return pCur;
}
Course* find_course_in_many_subjects(Semester* semester, string course){
    if(semester->pCourse == NULL) return NULL;
    Course* pCur_Course = semester->pCourse;

    while(pCur_Course != NULL){
        if(pCur_Course->Course_Name == course) return pCur_Course;
        pCur_Course = pCur_Course->pNext_Course;
    }
    return NULL;
}

void Delete_Course(Semester* sem) {
    string s;
    cout << "Course name: " ;
    cin >> s;
    Course* cour = find_Course(sem->pCourse, s);
    while (!cour || (cour->Course_Name != s && !cour->pNext_Course)) {
        cout << "Course not found! Try again: ";
        cin >> s;
        cour = find_Course(sem->pCourse, s);
    }
    if (cour->Course_Name == s) {
        Course* pDel = sem->pCourse;
        sem->pCourse = sem->pCourse->pNext_Course;
        delete pDel;
    }
    else {
        Course* pDel = cour->pNext_Course;
        cour->pNext_Course = cour->pNext_Course->pNext_Course;
    }
    cout << "Deleted!" << endl;
}
void Create_Semester(Year *&year){
    string name_semester;
    cout << "Import semester (ex: 1, 2, 3): ";
    cin >> name_semester;
    Semester *pCur_Semester = year->pSemester;

    Semester *Temp_Semester = new Semester;
    Temp_Semester->name = name_semester;
    Temp_Semester->pNext_Semester = NULL;
    Temp_Semester->pCourse = nullptr;

    if (year->pSemester == NULL)
        year->pSemester = Temp_Semester;
    else{
        while (pCur_Semester->pNext_Semester != NULL)
            pCur_Semester = pCur_Semester->pNext_Semester;
        pCur_Semester->pNext_Semester = Temp_Semester;
    }
}
void create_Registration_Session(){
    cout << "Create Registration Session: \n";
    cout << "Start time: \n";
    cout << "Date: ";
    cin >> S.start.date;
    cout << "Month: ";
    cin >> S.start.month;
    cout << "Year: ";
    cin >> S.start.year;

    cout << "End time: \n";
    cout << "Date: ";
    cin >> S.end.date;
    cout << "Month: ";
    cin >> S.end.month;
    cout << "Year: ";
    cin >> S.end.year;
}
bool Check_Regis_Time() {
    time_t now = time(0);
    tm* t = localtime(&now);
    int year = t->tm_year + 1900, mon = t->tm_mon + 1, day = t->tm_mday;
    if (year != S.start.year) return 0;
    if (mon < S.start.month || mon > S.end.month) return 0;
    if (mon == S.start.month && day < S.start.date) return 0;
    if (mon == S.end.month && day > S.end.date) return 0;
    return 1;
}
void Update_Course(Semester* sem){
    string s = "";
    cout << "Course name: " ;
    cin >> s;
    Course* cour = find_Course(sem->pCourse, s);
    while (!cour || (cour->Course_Name != s && !cour->pNext_Course)) {
        cout << "Course not found! Try again: ";
        cin >> s;
        cour = find_Course(sem->pCourse, s);
    }
    if (cour->pNext_Course && cour->pNext_Course->Course_Name == s) cour = cour->pNext_Course;

    cout << "Update the following details: " << endl;
    cout << "ID: ";
    cin >> cour->CourseID;
    cout << "Number of credits: ";
    cin >> cour->Number_of_Credits;
    cout << "Maximum number of students in Course: ";
    cin >> cour->Max_Student;
    cout << "Course name: ";
    cin >> cour->Course_Name;
    cout << "Teacher name: ";
    cin.ignore(1000, '\n');
    getline(cin, cour->Teacher_Name, '\n');
    cout << "Time performing: " << endl;
    cout << "Day 1: ";
    cin >> cour->Day1;
    cout << "Session 1: ";
    cin >> cour->Session1;
    cout << "Day 2: ";
    cin >> cour->Day2;
    cout << "Session 2: ";
    cin >> cour->Session2;
    cout << "Start day: ";
    cin >> cour->Start_Day;
    cout << "End day: ";
    cin >> cour->End_Day;
    cout << "Course added!" << endl;
}
void Print_Year(Year *year)
{
    if(year == NULL) {
        return;
    }
    Year *pCur_Year = year;
    while (pCur_Year != NULL)
    {
        cout << pCur_Year->name <<" ";
        pCur_Year = pCur_Year->pNext_Year;
    }
    cout<<endl;
}
void Print_Class(Year *year)
{
    Class *pCur_Class = year->pClass;
    while (pCur_Class != NULL)
    {
        cout << pCur_Class->name << " ";
        pCur_Class = pCur_Class->pNext_Class;
    }
    cout<<endl;
}
void Print_Student(Class *classes) // updated
{
    Student *pCur_Student = classes->pStudent;
    cout << "______________________________________________________________________________________________\n";
    cout << " No. | Student ID |       First name      | Last name | Gender | Date of Birth |   Social ID  \n";
    cout << "_____|____________|_______________________|___________|________|_______________|______________\n";
    while (pCur_Student != NULL)
    {
        //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
        cout<< " " << setw(3) << left << pCur_Student->No << " | ";
        cout<< setw(10) << left << pCur_Student->StudentID << " | ";
        cout<< setw(21) << left << pCur_Student->LastName << " | ";
        cout<< setw(9) << left << pCur_Student->FirstName << " | ";
        cout<< setw(6) << left << pCur_Student->Gender << " | ";
        cout<< setw(13) << left << pCur_Student->Date_of_Birth << " | ";
        cout<< setw(12) << right << pCur_Student->SocialID << " \n";
        pCur_Student = pCur_Student->pNext_Student;
    }
    // cout << "_____|____________|_______________________|___________|________|_______________|______________\n";
}
void Print_Semester(Year* year) {
    Semester* sem = year->pSemester;
    while (sem) {
        cout << "Semester " << sem->name << endl;
        sem = sem->pNext_Semester;
    }
}
void Print_Cur_Course(Cur_Course* cur_course) {
    if (cur_course == nullptr)
        cout << "No course to display" << endl;
    else {
        cout << setw(5) << left << "ID";
        cout << setw(10) << left << "Credits";
        cout << setw(10) << left << "Capacity";
        cout << setw(20) << left << "Course's name";
        cout << setw(20) << left << "Teacher's name";
        cout << setw(20) << left << "Time performing";
        cout << setw(15) << left << "Start day";
        cout << setw(15) << left << "End day" << endl;
        string s = "";
        while (cur_course != NULL) {
            cout << setw(5) << left << cur_course->CourseID;
            cout << setw(10) << left << cur_course->Number_of_Credits;
            cout << setw(10) << left << cur_course->Max_Student;
            cout << setw(20) << left << cur_course->Course_Name;
            cout << setw(20) << left << cur_course->Teacher_Name;
            s = cur_course->Day1; s += " "; s += cur_course->Session1;
            cout << setw(20) << left << s;
            cout << setw(15) << left << cur_course->Start_Day;
            cout << setw(15) << left << cur_course->End_Day;
            s = cur_course->Day2; s += " "; s += cur_course->Session2;
            cout << endl << setw(70) << right << s << endl;
            cur_course = cur_course->pNext_Cur_Cour;
        }  
    }
}
//18
void View_Student_In_Class(Year *year){ // updated
	string inClass;
	string findYear = ""; 
	Year *pCurYear = NULL;
	bool exist = true;
	do{
		exist = true;
		cout << "Enter class: ";
		cin >> inClass;
		
		// Enter '0' to stop this function
		if (inClass == "0")
			return;
		
		findYear = inClass.substr(0, 2); // strname.substr(start_point, number_of_character)
		pCurYear = year;
		// find year
		while (pCurYear && (pCurYear->name).substr(0, 2) != findYear)
			pCurYear = pCurYear->pNext_Year;
		if (pCurYear == NULL){
			cout << "Class does not exist.\n";
			exist = false;
		}
		else{
			Class *pCurClass = pCurYear->pClass;
			// find class
			while (pCurClass && pCurClass->name != inClass)
				pCurClass = pCurClass->pNext_Class;
			if (pCurClass == NULL){
				cout << "Class does not exist.\n";
				exist = false;
			}
			else{
				cout << "______________________________________________________________________________________________\n";
                cout << " No. | Student ID |       First name      | Last name | Gender | Date of Birth |   Social ID  \n";
                cout << "_____|____________|_______________________|___________|________|_______________|______________\n";   
				Student *pCurStudent = pCurClass->pStudent;
				while (pCurStudent){
					cout<< " " << setw(3) << left << pCurStudent->No << " | ";
                    cout<< setw(10) << left << pCurStudent->StudentID << " | ";
                    cout<< setw(21) << left << pCurStudent->LastName << " | ";
                    cout<< setw(9) << left << pCurStudent->FirstName << " | ";
                    cout<< setw(6) << left << pCurStudent->Gender << " | ";
                    cout<< setw(13) << left << pCurStudent->Date_of_Birth << " | ";
                    cout<< setw(12) << right << pCurStudent->SocialID << " \n";
					pCurStudent = pCurStudent->pNext_Student;
				}
                cout << "_____|____________|_______________________|___________|________|_______________|______________\n";
			}
		}
	} while (!exist);
}
// 20
void View_Student_In_Course(Semester* sem){ // updated
    string inCourse;
    cout << "Enter course's name ";
    cin >> inCourse;
    Find_Course:
        Course* pCurCourse = sem->pCourse;
        while (pCurCourse && pCurCourse->Course_Name != inCourse)
            pCurCourse = pCurCourse->pNext_Course;
    while (pCurCourse == NULL){
        cout << "Course does not exist. Try again \n";
        cin >> inCourse;
        goto Find_Course;
    }
    Student_Course *pCurStu = pCurCourse->pStudent_Course;
    
    cout << "______________________________________________________________________________________________\n";
    cout << " No. | Student ID |       First name      | Last name | Gender | Date of Birth |   Social ID  \n";
    cout << "_____|____________|_______________________|___________|________|_______________|______________\n";   
    while (pCurStu){
        cout<< " " << setw(3) << left << pCurStu->No << " | ";
        cout<< setw(10) << left << pCurStu->StudentID << " | ";
        cout<< setw(21) << left << pCurStu->LastName << " | ";
        cout<< setw(9) << left << pCurStu->FirstName << " | ";
        cout<< setw(6) << left << pCurStu->Gender << " | ";
        cout<< setw(13) << left << pCurStu->Date_of_Birth << " | ";
        cout<< setw(12) << right << pCurStu->SocialID << " \n";
        
        pCurStu = pCurStu->pNext_Student_Course;
    }
    cout << "_____|____________|_______________________|___________|________|_______________|______________\n";
}
void View_Enrolled_Course(Student* student) {
    if (student->pCur_Cour == NULL) {
        cout << "You haven't enrolled any courses yet!" << endl;
    }
    else {
        Cur_Course* pEnroll = student->pCur_Cour;
        cout << "Courses have been enrolled: ";
        while (pEnroll != NULL) {
            cout << pEnroll->Course_Name << " | ";
            pEnroll = pEnroll->pNext_Cur_Cour;
        }
    }
}
void View_Enrolled_Course_main(Year*& year, string studentID) {
    // string studentID;
    // cout << "Your student ID: ";
    // cin >> studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if (student == NULL) {
        cout << "Student ID not found!" << endl;
        return;
    }
    View_Enrolled_Course(student);
}
void Delete_Enrolled_Course(Student*& student, Course*& course) {
    Cur_Course* pCur1 = student->pCur_Cour;
    Student_Course* pCur2 = course->pStudent_Course;
    if (student->pCur_Cour == NULL || course->pStudent_Course == NULL) {
        cout << "You haven't enrolled this course yet!";
        return;
    }
    if (pCur1->Course_Name == course->Course_Name) {
        Cur_Course* pTemp1 = pCur1;
        pCur1 = pCur1->pNext_Cur_Cour;
        student->pCur_Cour = pCur1;
        delete pTemp1;
    }
    else {
        Cur_Course* pTemp1 = pCur1;
        while (pTemp1->pNext_Cur_Cour->Course_Name != course->Course_Name) {
            pTemp1 = pTemp1->pNext_Cur_Cour;
        }
        Cur_Course* pDel1 = pTemp1->pNext_Cur_Cour;
        pTemp1->pNext_Cur_Cour = pTemp1->pNext_Cur_Cour->pNext_Cur_Cour;
        delete pDel1;
    }
    if (pCur2->StudentID == student->StudentID) {
        Student_Course* pTemp2 = pCur2;
        pCur2 = pCur2->pNext_Student_Course;
        course->pStudent_Course = pCur2;
        delete pTemp2;
    }
    else {
        Student_Course* pTemp2 = pCur2;
        while (pTemp2->pNext_Student_Course->StudentID != student->StudentID) {
            pTemp2 = pTemp2->pNext_Student_Course;
        }
        Student_Course* pDel2 = pTemp2->pNext_Student_Course;
        pTemp2->pNext_Student_Course = pTemp2->pNext_Student_Course->pNext_Student_Course;
        delete pDel2;
    }
}
void Delete_Enrolled_Course_main(Year*& year, Semester*& semester, string studentID) {
    if (Check_Regis_Time()) {
    // string studentID;
    // cout << "Your studentID: ";
    // cin >> studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if (student == NULL) {
        cout << "Student ID not found!" << endl;
        cin.ignore(1000, '\n');
        getchar();
        return;
    }
    //view all course
    if (student->pCur_Cour == NULL) {
        cout << "You haven't enrolled any courses yet!" << endl;
        return;
    }
    else {
        Cur_Course* pEnroll = student->pCur_Cour;
        cout << "Courses have been enrolled: ";
        while (pEnroll != NULL) {
            cout << pEnroll->Course_Name << " | ";
            pEnroll = pEnroll->pNext_Cur_Cour;
        }
    }
    cout<<endl;
    // if having enrolled courses, delete ones
    string course_name;
    cout << "Course you want to delete: ";
    cin >> course_name;
    Course* Del_Cour = find_course_in_many_subjects(semester, course_name);
    if (Del_Cour == NULL) {
        cout << "Course name not found!" << endl;
        cin.ignore(1000, '\n');
        getchar();
        return;
    }
    Delete_Enrolled_Course(student, Del_Cour);

    }else cout<<"Over time!";
}
bool yearExists(Year *year, string findYear){ // new
    Year *pCurYear = year;
    while (pCurYear && pCurYear->name != findYear)
        pCurYear = pCurYear->pNext_Year;
    if (pCurYear == nullptr)
        return false;
    else
        return true;
}
void Create_Year(Year* &year){ // fixed
    string name_year;
    bool exist = false;
    do{
        exist = false;
        cout<<"Import academic year (ex: 2021) ";
        cin >> name_year;
        if (yearExists(year, name_year)){
            exist = true;
            Textcolor(4);
            cout << "Year already exists.\n";
            Textcolor(11);
        }
    } while (exist);
    
    Year* pCur_Year = year;

    Year* Temp_Year = new Year;
    Temp_Year->name = name_year;
    Temp_Year->pNext_Year = NULL;
    Temp_Year->pClass = NULL;
    Temp_Year->pSemester = NULL;

    if(year == NULL) year = Temp_Year;
    else{
        while(pCur_Year->pNext_Year != NULL) pCur_Year = pCur_Year->pNext_Year;
        pCur_Year->pNext_Year = Temp_Year;
    }
}
bool classExists(Year* year, string findClass){ // new
    Class* pCurClass = year->pClass;
    while (pCurClass && pCurClass->name != findClass)
        pCurClass = pCurClass->pNext_Class;
    if (pCurClass == nullptr)
        return false;
    else
        return true;
}
void Create_Class(Year* &year){ // fixed
    string name_class;
    bool exist = false;
    do{
        exist = false;
        cout<<"Import class (ex:21CLC10) ";
        cin >> name_class;
        if (classExists(year, name_class)){
            exist = true;
            Textcolor(4);
            cout << "Class already exists.\n";
            Textcolor(11);
        }
    } while (exist);

    Class* pCur_Class = year->pClass;

    Class* Temp_Class = new Class;
    Temp_Class->name = name_class;
    Temp_Class->pNext_Class = NULL;
    Temp_Class->pStudent = NULL;

    if(year->pClass == NULL) 
        year->pClass = Temp_Class;
    else{
        while(pCur_Class->pNext_Class != NULL) 
            pCur_Class = pCur_Class->pNext_Class;
        pCur_Class->pNext_Class = Temp_Class;
    }
}

Year* Import_Year(Year* year){
    if(year == NULL) return NULL;
    Year* pCur_Year;
    do{
    pCur_Year = year;
    string find_year;
    cout<<"academic year to import class (ex: 2021) ";
    cin>>find_year;
                        
        while(pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;

    }while(pCur_Year == NULL);
    return pCur_Year;
}
Class* Import_Class(Class* classes){
    if(classes == NULL) return NULL;
    Class* pCur_class;
    do{
        pCur_class = classes;
        string find_class;
        cout<<"class to import student (ex:21CLC10) ";
        cin>>find_class;
        while(pCur_class != NULL && find_class != pCur_class->name)
            pCur_class = pCur_class->pNext_Class;
    }while(pCur_class == NULL);
    return pCur_class;
}
Semester* Import_Semester(Semester* sem){
    if(sem == NULL) return NULL;
    Semester* pCur_sem;
    do{
        pCur_sem = sem;
        string find_sem;
        cout<<"semester to import student (ex: 1, 2, 3) ";
        cin>>find_sem;                 
        while(pCur_sem != NULL && find_sem != pCur_sem->name)
            pCur_sem = pCur_sem->pNext_Semester;
    }while(pCur_sem == NULL);
    return pCur_sem;
}

void Create_Student(Class *&classes){

    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    
    ifstream filein(classes->name+".csv");
    Student* pCur_Student = nullptr;
    Student* Temp_Student = nullptr;

    while(filein.eof() == false){
        pCur_Student = classes->pStudent;
        Temp_Student = new Student;
        // cout<<"Import student: "<<endl;
        getline(filein,Temp_Student->No,',');           cout<< " " << setw(3) << left << Temp_Student->No << " | ";
        getline(filein,Temp_Student->StudentID,',');    cout<< setw(10) << left << Temp_Student->StudentID << " | ";
        getline(filein,Temp_Student->LastName,',');     cout<< setw(21) << left << Temp_Student->LastName << " | ";
        getline(filein,Temp_Student->FirstName,',');    cout<< setw(9) << left << Temp_Student->FirstName << " | ";
        getline(filein,Temp_Student->Gender,',');       cout<< setw(6) << left << Temp_Student->Gender << " | ";
        getline(filein,Temp_Student->Date_of_Birth,',');cout<< setw(13) << left << Temp_Student->Date_of_Birth << " | ";
        getline(filein,Temp_Student->SocialID,'\n');    cout<< setw(12) << right << Temp_Student->SocialID << " \n";

        Temp_Student->pNext_Student = NULL;
        Temp_Student->pCur_Cour = NULL;
        Create_Account_For_new_Student(Temp_Student->StudentID);

        if(classes->pStudent == NULL) classes->pStudent = Temp_Student;
        else{
            while(pCur_Student->pNext_Student != NULL) pCur_Student = pCur_Student->pNext_Student;
            pCur_Student->pNext_Student = Temp_Student;
        }
    }
    
    filein.close();
}
//convert_to_int
int convert_to_int(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++)
        res = res * 10 + (s[i] - '0');
    return res;
}
void Add_1_Student(Class* import_class, string student_id) {
    Student* pCur_Student = import_class->pStudent;
    Student* pNew_Student = new Student;
    pNew_Student->StudentID = student_id;
    
    cin.ignore(1000, '\n');
    cout<<"Enter last name: "; getline(cin, pNew_Student->LastName, '\n');
    cout<<"Enter first name: "; getline(cin, pNew_Student->FirstName, '\n');
    cout<<"Enter date of birth: "; cin>>pNew_Student->Date_of_Birth;
    cout<<"Enter gender: "; cin>>pNew_Student->Gender;
    cout<<"Enter social ID: "; cin>>pNew_Student->SocialID;
    pNew_Student->pCur_Cour = nullptr;
    pNew_Student->pNext_Student = nullptr;
    
    while (pCur_Student != nullptr && pCur_Student->pNext_Student != nullptr) 
        pCur_Student = pCur_Student->pNext_Student;
    
    if (pCur_Student == nullptr) {
        pNew_Student->No = "1";
        import_class->pStudent = pNew_Student;
    }
    else {
        pNew_Student->No = to_string(convert_to_int(pCur_Student->No) + 1); // continue
        pCur_Student->pNext_Student = pNew_Student;
    }
}
void Add_1_Student_main(Year* year,Class *&classes ) {
    string student_id;
    Student* stu = nullptr;
    bool exist = false;
    do {
        exist = false;
        system("cls");
        cout<<"Enter the new student's ID: "; cin>>student_id;
        stu = find_student_in_many_classes(year, student_id);

        if (stu != nullptr){
            exist = true;
            Textcolor(4);
            cout << "ID already existed.\n";
            Textcolor(11);
            cin.ignore(1000, '\n');
            getchar();
        }
    } while (exist);
    
    Add_1_Student(classes, student_id);
    cout<<"Added!"<<endl;

    Create_Account_For_new_Student(student_id);
}

//check enroll
bool Check_Cur_Course(Course* course_regis,Student* student){
    Cur_Course* pCur = student->pCur_Cour;
    while(pCur != NULL){
        if(pCur->Course_Name == course_regis->Course_Name) return false;
        else pCur = pCur->pNext_Cur_Cour;
    }
    return true;
}
bool Check_quantity(Student* student){
    int count = 0;
    Cur_Course* pCur = student->pCur_Cour;
    while(pCur != NULL){
        count++;
        pCur = pCur->pNext_Cur_Cour;
    }
    if(count < 3) return true; // "< 3" --> 2 --> allow to enroll--> 3 course
    return false;   //"<= 3" --> 3 --> allow to enroll --> 4 course
}
bool Check_Session(Course* course_regis,Student* student){
    Cur_Course* pCur = student->pCur_Cour;
    while(pCur != NULL){
        if((pCur->Day1 == course_regis->Day1 && pCur->Session1 == course_regis->Session1) || 
        (pCur->Day2 == course_regis->Day2 && pCur->Session2 == course_regis->Session2)) return false;
        else pCur = pCur->pNext_Cur_Cour;
    }
    return true;
}
//enroll
Cur_Course* Copy_Course(Course* course_regis){
    Cur_Course* Cur_Cour = new Cur_Course;
    Cur_Cour->CourseID = course_regis->CourseID;
    Cur_Cour->Course_Name = course_regis->Course_Name;
    Cur_Cour->Teacher_Name = course_regis->Teacher_Name;
    Cur_Cour->Number_of_Credits = course_regis->Number_of_Credits;
    Cur_Cour->Max_Student = course_regis->Max_Student;
    Cur_Cour->Day1 = course_regis->Day1;
    Cur_Cour->Session1 = course_regis->Session1;
    Cur_Cour->Day2 = course_regis->Day2;
    Cur_Cour->Session2 = course_regis->Session2;
    Cur_Cour->Start_Day = course_regis->Start_Day;
    Cur_Cour->End_Day = course_regis->End_Day;
    return Cur_Cour;
}
//No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
Student_Course* Copy_Student_Cour(Student* student){
    Student_Course* Student_Cour = new Student_Course;
    Student_Cour->No = student->No;
    Student_Cour->StudentID = student->StudentID;
    Student_Cour->FirstName = student->FirstName;
    Student_Cour->LastName = student->LastName;
    Student_Cour->Gender = student->Gender;
    Student_Cour->Date_of_Birth = student->Date_of_Birth;
    Student_Cour->SocialID = student->SocialID;
    return Student_Cour;
}
void Enroll_Course(Course* &course_regis, Student* &student){
    if(Check_Cur_Course(course_regis,student) == true && Check_quantity(student) == true &&
       Check_Session(course_regis,student) == true ){
        //add course_regis into student_course
        Cur_Course* cur_course = Copy_Course(course_regis);
        cur_course->pNext_Cur_Cour = NULL;
        Cur_Course* pCur = student->pCur_Cour;

        if(student->pCur_Cour == NULL){
            student->pCur_Cour = cur_course;
        }
        else{
            while(pCur->pNext_Cur_Cour != NULL) pCur = pCur->pNext_Cur_Cour;
            pCur->pNext_Cur_Cour = cur_course;
        }

        //add inf SV into student_course
        Student_Course* Student_cour = Copy_Student_Cour(student);
        Student_cour->pNext_Student_Course = NULL;
        Student_Course* pCur_Student_cour = course_regis->pStudent_Course;

        if(course_regis->pStudent_Course == NULL){
            course_regis->pStudent_Course = Student_cour;
        }
        else {
            while(pCur_Student_cour->pNext_Student_Course != NULL)
                pCur_Student_cour = pCur_Student_cour->pNext_Student_Course;
            pCur_Student_cour->pNext_Student_Course = Student_cour;
        }
    
    }else {
        if(Check_Cur_Course(course_regis,student) == false){
            cout<<"This course has been registering\n";
        }else if (Check_quantity(student) == false){
            cout<<"This course has enough quantity\n";
        }else if(Check_Session(course_regis,student) == false){
            cout<<"The schedule has been overlapped\n";
        }
    }
}

//enroll main
void enroll_main(Year* &year, Semester* &semester,string studentID){
    if (Check_Regis_Time()) {
        // string studentID;
        // cout<<"StudentID "; cin>>studentID;

        Student* student = find_student_in_many_classes(year, studentID);
        if(student == NULL){
            cout<<"Invalid student"<<endl;
            return;
        }
        //view all course
        string course_name;
        cout<<"Course you want to choose "; cin>>course_name;
        Course* course_regis = find_course_in_many_subjects(semester,course_name);
        if(course_regis == NULL){
            cout<<"Invalid course_register"<<endl;
            return;
        }

        Enroll_Course(course_regis,student);
    }
    else cout<<"Over time!"<<endl;
}

//22
double rand_mark() {
    //srand(time(NULL));
    return min(10.0, (rand() % 11) * 1.0 + (rand() % 10) / 10.0);
}
void Assign_Mark(Year* year,string course_name, string Student_ID, double total, double final, double mid, double other) {
    Student* Std = find_student_in_many_classes(year, Student_ID);
    // Student id always exists in this case-->no check null
    Cur_Course* pCur_Cour = Std->pCur_Cour;
    while(pCur_Cour != NULL && pCur_Cour->Course_Name != course_name) pCur_Cour = pCur_Cour->pNext_Cur_Cour;
    if(pCur_Cour != NULL){
        pCur_Cour->mark.Final = final;
        pCur_Cour->mark.Midterm = mid;
        pCur_Cour->mark.Other = other;
        pCur_Cour->mark.Total = total;
    }
}
void Create_Mark(Course* cour) {
    string s = cour->Course_Name + ".csv";
    ofstream fout(s);
    fout << "No,ID,Full name,Total mark,Final mark,Midterm mark,Other mark";
    Student_Course* Stu_Cour = cour->pStudent_Course;
    int cnt = 1;
    while (Stu_Cour) {
        fout << endl;
        double total, final, mid, other;
        final = rand_mark(), mid = rand_mark(), other = (rand() % 10) / 10.0;
        total = (final * 2.0 + mid) / 3.0 + other;
        final = int(final * 10) / 10.0;
        fout << cnt++ << "," << Stu_Cour->StudentID << "," << Stu_Cour->FirstName + " " + Stu_Cour->LastName << ","
        << total << "," << final << "," << mid << "," << other;
        Stu_Cour = Stu_Cour->pNext_Student_Course;
    }
    fout.close();
}

double convert_to_double(string s) {
    string s1 = "", s2 = ""; // s1 la phan nguye, s2 la phan thap phan
    double res;
    bool t = 0; // neu t = 0 thi la phan nguyen, = 1 thi la phan thap phan
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') t = 1;
        else {
            if (t == 0) s1 += s[i]; 
            else s2 += s[i];
        }
    }
    res = convert_to_int(s1) + convert_to_int(s2) / pow(10, s2.length()) * 1.0; // cong phan nguyen va phan thap phan
    res = int(res * 10) / 10.0; // lam tron 1 chu so thap phan
    return res;
}
void Import_Scoreboard(Year* year, Course* cour) {
    string s = cour->Course_Name + ".csv";
    ifstream fin(s);
    fin.ignore(1000, '\n');
    while (fin.eof() == false) {
        getline(fin, s, ',');
        getline(fin, s, ',');
        Student_Course* pCurStd = find_student_in_a_course(cour, s);
        getline(fin, s, ',');
        getline(fin, s, ',');
        pCurStd->mark.Total = convert_to_double(s);
        getline(fin, s, ',');
        pCurStd->mark.Final = convert_to_double(s);
        getline(fin, s, ',');
        pCurStd->mark.Midterm = convert_to_double(s);
        getline(fin, s, '\n');
        pCurStd->mark.Other = convert_to_double(s);
        Assign_Mark(year,cour->Course_Name, pCurStd->StudentID, pCurStd->mark.Total, pCurStd->mark.Final,
        pCurStd->mark.Midterm, pCurStd->mark.Other);
    }
    fin.close();
}
void View_Score_Board(Course *cour) {
    cout << "__________________________________________________________________________________\n";
    cout << " Student ID |             Full name             | Midterm | Final | Other | Total \n";
    cout << "____________|___________________________________|_________|_______|_______|_______\n";
    Student_Course* pCurStd = cour->pStudent_Course;
    string s = "";
    while (pCurStd != nullptr) {
        cout << ' ' << setw(10) << left << pCurStd->StudentID << " | ";
        s = pCurStd->LastName + " " + pCurStd->FirstName;
        cout << setw(34) << left << s << " | ";
        cout << setw(7) << right << pCurStd->mark.Midterm << " | ";
        cout << setw(5) << right << pCurStd->mark.Final << " | ";
        cout << setw(5) << right << pCurStd->mark.Other << " | ";
        cout << setw(5) << right << pCurStd->mark.Total << '\n';
        pCurStd = pCurStd->pNext_Student_Course;
    }
}
// mark main & scoreboard in a course main
void Create_mark_main(Year* year,Semester* sem){
    string course_name;
    cout<<"Course you want to choose "; cin>>course_name;
    Course* course_regis = find_course_in_many_subjects(sem,course_name);
    if(course_regis == NULL){
        cout<<"invalid course_register"<<endl;
        //cin.ignore();
        //getchar();
        return;                                      
    }
    Create_Mark(course_regis);
    Import_Scoreboard(year, course_regis);
}
//23
void View_scoreboard_main(Semester* sem){
    string course_name;
    cout<<"Course you want to choose "; cin>>course_name;
    Course* course_regis = find_course_in_many_subjects(sem,course_name);
    if(course_regis == NULL){
        cout<<"invalid course_register"<<endl;
        //cin.ignore();
        //getchar();
        return;                                      
    }
    system("cls");
    View_Score_Board(course_regis);
}
//22 export
void Export_Course(Course* course) {
    Student_Course* stu_cour = course->pStudent_Course;
    ofstream fileout;
    int cnt = 1;
    string s = course->Course_Name;
    fileout.open(s + ".csv");
    fileout << "No" << "," << "ID" << "," << "Full name" << "," << "Total mark" << "," << "Final mark" << "," << "Midterm mark" << "," << "Other mark";
    while (stu_cour != nullptr) {
        fileout << endl;
        fileout << cnt++ << "," << stu_cour->StudentID << "," << stu_cour->FirstName + " " + stu_cour->LastName <<","
        << stu_cour->mark.Total << "," << stu_cour->mark.Final << ","
        << stu_cour->mark.Midterm << "," << stu_cour->mark.Other;
        stu_cour = stu_cour->pNext_Student_Course;
    }
    fileout.close();
}
void Export_Course_main(Year*& year, Semester*& semester) {
    string course_name;
    cout << "Choose a course you want to get students' data: ";
    cin >> course_name;
    Course* export_course = find_course_in_many_subjects(semester, course_name);
    if (export_course == NULL) {
        cout << "Course name not found!";
        //cin.ignore();
        //getchar();
        return;
    }
    Export_Course(export_course);
    cout << "Exported.\n";
}

//24
void update_student_result(Year* &year, Semester* &sem){
    //view all course
    //Print_Course(sem);
    //find course
    string course_name;
    cout<<"Course you want to choose "; cin>>course_name;
    Course* course_update = find_course_in_many_subjects(sem,course_name);
    if(course_update == NULL){
        cout<<"invalid course_update"<<endl;
        //cin.ignore();
        //getchar();
        return;
    }
    system("cls");
    //view student in a course
    View_Score_Board(course_update);
    // find student

    string studentID;
    cout<<"StudentID "; cin>>studentID;

    Student* student = find_student_in_many_classes(year, studentID);
    if(student == NULL){
        cout<<"Invalid student"<<endl;
        //cin.ignore();
        //getchar();
        return;
    }
    Student_Course* student_cour = find_student_in_a_course(course_update,student->StudentID);
    
    cout<<"Update score\n";
    cout<<"Midterm: ";cin>>student_cour->mark.Midterm;
    cout<<"Final: ";cin>>student_cour->mark.Final;
    cout<<"Other: ";cin>>student_cour->mark.Other;
    double a,b,c;
    a = student_cour->mark.Midterm;
    b = student_cour->mark.Final;
    c = student_cour->mark.Other;
    student_cour->mark.Total = int(((a + b* 2)/3 + c)* 10 )/10.0;// lam tron 1 chu so thap phan

    Cur_Course* cur_cour = student->pCur_Cour;
    while(cur_cour != NULL){
        if(cur_cour->Course_Name != course_update->Course_Name) cur_cour = cur_cour->pNext_Cur_Cour;
        else break;
    }
    // copy student_course score into cur_course student
    cur_cour->mark.Midterm = student_cour->mark.Midterm;
    cur_cour->mark.Final = student_cour->mark.Final;
    cur_cour->mark.Other = student_cour->mark.Other;
    cur_cour->mark.Total = student_cour->mark.Total;
    cout << "Result updated.\n";

}
//25
// void View_Class_Scoreboard(Class* class_name, Course* course){
//     cout << "Student ID\tFull Name\tFinal Mark" << endl;
//     Student_Course* pStu_Cour = course->pStudent_Course;
//     while (pStu_Cour != NULL){
//         cout << pStu_Cour->StudentID << "\t" << pStu_Cour->LastName + " " + pStu_Cour->FirstName
//         << "\t" << pStu_Cour->mark.Final << endl;
//         pStu_Cour = pStu_Cour->pNext_Student_Course;
//     }
// }
void View_Class_Scoreboard_main(Class* classes){ // chua chinh output
    if (classes->pStudent == NULL){
        cout << "No student is in this class!" << endl;
        return;
    }
    Student* pStudent = classes->pStudent;
    string s = "";
    // print title
    cout << "________________________________________________\n";
    cout << " Student ID |             Full name             \n";
    cout << "____________|___________________________________\n";
    while (pStudent != NULL){
                                                              
        Cur_Course* pCur_Cour;
        if(pStudent->pCur_Cour != NULL){
            pCur_Cour = pStudent->pCur_Cour;
            while(pCur_Cour != NULL){
                cout<<pCur_Cour->Course_Name<<"\t";
            }  
        }
        cout<<endl;
        //print concept
        s = pStudent->LastName + " " + pStudent->FirstName;
        cout << " " << setw(10) << left << pStudent->StudentID << " | ";
        cout << setw(34) << left << s << "\t";

        if(pStudent->pCur_Cour != NULL){
            pCur_Cour = pStudent->pCur_Cour;  // copy pCur_Cour = pStudent->pCur_Cour
            double GPA_this_semester = 0;
            int count = 0;
            while(pCur_Cour != NULL){
                // calculate
                double a,b,c;
                a = pCur_Cour->mark.Midterm;
                b = pCur_Cour->mark.Final;
                c = pCur_Cour->mark.Other;
                GPA_this_semester += ((a + b* 2)/3 + c);
                // courses's quantity
                count++;
                // print each course's score          
                cout<<pCur_Cour->mark.Final<<"\t";
            }
            GPA_this_semester = int(GPA_this_semester* 10)/10.0;
            cout<<GPA_this_semester<<"\t"<<pStudent->GPA<<endl;
        }
        pStudent = pStudent->pNext_Student;
        cout<<endl<<endl;
    }
}
//26
void Student_View_Scoreboard(Year* year,string studentID){ // fixed
    Student* student = find_student_in_many_classes(year, studentID);
    if(student->pCur_Cour == NULL){
        cout << "No course is enrolled.\n";
    }

    Cur_Course* pCur = student->pCur_Cour;
    cout << setw(28) << left << "Course name" << " | Midterm | Final | Other | Total\n";
    while(pCur != NULL){
        cout << setw(28) << left << pCur->Course_Name << " | ";
        cout << setw(7)  << right << pCur->mark.Midterm << " | ";
        cout << setw(5)  << right << pCur->mark.Final << " | ";
        cout << setw(5)  << right << pCur->mark.Other << " | ";
        cout << setw(5)  << right << pCur->mark.Total << "\n";
        pCur = pCur->pNext_Cur_Cour;
    } 
}

//delete all node
void delete_cur_course(Student* &student){
    if(student->pCur_Cour == NULL) return;
    while(student->pCur_Cour != NULL){
        Cur_Course* pCur = student->pCur_Cour;
        student->pCur_Cour = student->pCur_Cour->pNext_Cur_Cour;
        delete pCur;
    }
}
void delete_student(Class* &classes){
    if(classes->pStudent == NULL) return;
    while(classes->pStudent != NULL){
        Student* pCur = classes->pStudent;
        classes->pStudent = classes->pStudent->pNext_Student;
        delete_cur_course(pCur);
        delete pCur;
    }
}
void delete_student_cour(Course* &course){
    if(course->pStudent_Course == NULL) return;
    while(course->pStudent_Course != NULL){
        Student_Course* pCur = course->pStudent_Course;
        course->pStudent_Course = course->pStudent_Course->pNext_Student_Course;
        delete pCur;
    }
}
void delete_course(Semester* &sem){
    if(sem->pCourse == NULL) return;
    while(sem->pCourse != NULL){
        Course* pCur = sem->pCourse;
        sem->pCourse = sem->pCourse->pNext_Course;
        delete_student_cour(pCur);
        delete pCur;
    }
}
void delete_all_node(Year* &year){
    if(year == NULL) return;
    while(year->pClass != NULL){
        Class* pCur_Class = year->pClass;
        year->pClass = year->pClass->pNext_Class;
        delete_student(pCur_Class);
        delete pCur_Class;
    }

    while(year->pSemester != NULL){
        Semester* pCur_Sem = year->pSemester;
        year->pSemester = year->pSemester->pNext_Semester;
        delete_course(pCur_Sem);
        delete pCur_Sem;
    }
    while(year != NULL){
        Year *pCur_Year = year;
        year = year->pNext_Year;
        delete pCur_Year;
    }
}
/// LOGO PORTAL ///
void logo_portal(int x,int y){
    Textcolor(10);
    gotoxy(x, y+0);cout << "    ____  ____  ____  _________    __" << endl;
    gotoxy(x, y+1);cout << "   / __ \\/ __ \\/ __ \\/_  __/   |  / /" << endl;
    gotoxy(x, y+2);cout << "  / /_/ / / / / /_/ / / / / /| | / /" << endl;
    gotoxy(x, y+3);cout << " / ____/ /_/ / _, _/ / / / ___ |/ /___" << endl;
    gotoxy(x, y+4);cout << "/_/    \\____/_/ |_| /_/ /_/  |_/_____ /" << endl;
}
//new
void box(int x,int y,int width, int height, int textcolor,int bcolor ,string text) {

	Textcolor(10);
	gotoxy(x + 1, y + 1);
	cout << text;
	
	Textcolor(11);
	for (int i = x; i <= x + width; i++) {
		gotoxy(i, y);
		cout << char(205);
		gotoxy(i, y + height);
		cout << char(205);
	}
	for (int i = y; i <= y + height; i++) {
		gotoxy(x, i);
		cout << char(186);
		gotoxy(x + width, i);
		cout << char(186);
	}
	gotoxy(x, y); cout << char(201);
	gotoxy(x + width, y); cout << char(187);
	gotoxy(x, y + height); cout << char(200);
	gotoxy(x + width, y + height); cout << char(188);
}

//staff
void COURSE_PAGE(Year* &year,Semester* &sem,int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
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
				if (cell == 1){
                    system("cls");
                    Create_Course(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 2){
                    system("cls");
                    Print_Course(sem);
                    if(sem->pCourse == NULL) cout<<"No course was created.";
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if(cell == 3){
                    system("cls");
                    Print_Course(sem);
                    Update_Course(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 4){
                    system("cls");
                    Print_Course(sem);
                    Delete_Course(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 5){
                    system("cls");
                    View_Student_In_Course(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 6){
                    system("cls");
                    Print_Course(sem);
                    Create_mark_main(year,sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 7){
                    system("cls");
                    View_scoreboard_main(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 8){
                    system("cls");
                    Export_Course_main(year, sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 9){
                    system("cls");
                    Print_Course(sem);
                    update_student_result(year,sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 10){
                    system("cls");
                    create_Registration_Session();
                }
				else if (cell == 11) {
                    HOME = 4;
					return;
				}
				else if (cell == 12) break;

                system("cls");  // print box for all
                for (int i = 0; i < number_of_cells; i++) {
		            box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
	            }        
			}
		}
	}
}
void SEMESTER_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string SEMESTER_name_list_of_boxs[]) {
    Semester* import_sem;

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
				if (cell == 1) {
                    system("cls");
                    Print_Semester(year);
                    Create_Semester(year);
                }else if (cell == 2){
                    system("cls");
                    Print_Semester(year);
                    if(year->pSemester == NULL) cout<<"No semester was created.";
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 3) {
                    system("cls");
                    Print_Semester(year);

                    import_sem = Import_Semester(year->pSemester);

                    if(import_sem == NULL){
                        cout<<"No semester was created.";
                        cin.ignore(1000, '\n');
                        getchar();                       
                    }else{
                        system("cls");
					    string COURSE_name_list_of_boxs[] = { "Create course","View course","Update course","Delete course","View student","Create mark","View scoreboard","Export course","Update result","Time registration","Home","Return" };
					    COURSE_PAGE(year,import_sem,locate_x, 2, 12, COURSE_name_list_of_boxs); // set locate_y = 2
                    }
					
					system("cls");
					//
					if (HOME == 4) return;
					//
					for (int i = 0; i < number_of_cells; i++) {
						box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
					}
				}
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;

                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
				}
			}
		}
	}
}

void STUDENT_PAGE(Year* &year,Class* &classes,int locate_x, int locate_y, int number_of_cells, string STUDENT_name_list_of_boxs[]) {

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
				if (cell == 1) {
                    system("cls");
                    Print_Student(classes);
                    Create_Student(classes);
                    save_account_list(account_head); // save account
                    cin.ignore(1000, '\n');
                    getchar();
                }   
                else if (cell == 2){
                    system("cls");
                    Print_Student(classes);
                    Add_1_Student_main(year,classes);
                    save_account_list(account_head); // save account
                    //
                    getchar();
                }
                else if (cell == 3){
                    system("cls");
                    Print_Student(classes);
                    if(classes->pStudent == NULL) cout<<"No student was created.";
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;

                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, STUDENT_name_list_of_boxs[i]);
				}
			}
		}
	}
}
void CLASS_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string CLASS_name_list_of_boxs[]) {
    Class* import_class;

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
				if (cell == 1) {
                    
                    system("cls");
                    Print_Class(year);

                    Create_Class(year);
                            
                }else if (cell == 2){
                    system("cls");
                    Print_Class(year);
                    if(year->pClass == NULL) cout<<"No class was created.";
                    cin.ignore(1000,'\n');
                    getchar();
                }
				else if (cell == 3) {
					system("cls");
                    Print_Class(year);

                    import_class = Import_Class(year->pClass);

                    if(import_class == NULL){
                        cout<<"No class was created.";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
                        string STUDENT_name_list_of_boxs[] = { "Create student","Add 1 student","View students","Home","Return" }; 

					    STUDENT_PAGE(year,import_class,locate_x, locate_y, 5, STUDENT_name_list_of_boxs);
					    
                    }
					//
					if (HOME == 4) return;
					//
				}else if (cell == 4){
                    // continue //gan ham 25
                    system("cls");
                    Print_Class(year);

                    import_class = Import_Class(year->pClass);

                    if(import_class == NULL){
                        cout<<"No class was created.";
                    }else{
                        system("cls");
                        View_Class_Scoreboard_main(import_class);			    
                    }
                    cin.ignore(1000, '\n');  // test 25 vs 26
                    getchar();
                }
				else if (cell == 5) {
					HOME = 4;
					return;
				}
				else if (cell == 6) break;
                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CLASS_name_list_of_boxs[i]);
				}
			}
		}


	}
}
void YEAR_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[]) {
    Year* import_year;

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
				if (cell == 1) {
                    system("cls");
                    Print_Year(year);
                    Create_Year(year);
                    
                }else if (cell == 2){
                    system("cls");
                    Print_Year(year);
                    if(year == NULL) cout<<"No year was created.";
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 3) {
                    system("cls");
                    Print_Year(year);

                    import_year = Import_Year(year); // import year

                    if(import_year == NULL){
                        cout<<"No year was created.";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
					    string CLASS_name_list_of_boxs[] = { "Create class","View classes","View student","View scoreboard","Home","Return" };
					    CLASS_PAGE(import_year,locate_x, locate_y, 6, CLASS_name_list_of_boxs);
                    }							
					//
					if (HOME == 4) return;
					//
					
				}
				else if (cell == 4) {
                    system("cls");
                    Print_Year(year);

                    import_year = Import_Year(year); // import year

                    if(import_year == NULL){
                        cout<<"No year was created.";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
					    string SEMESTER_name_list_of_boxs[] = { "Create semester","View semester","View course","Home","Return" };
					    SEMESTER_PAGE(import_year,60, 10, 5, SEMESTER_name_list_of_boxs);
                    }	
					//
					if (HOME == 4) return;
					//
				}
				else if (cell == 5) {
					// enter HOME -> nothing happens because here is HOME
				}
				else if (cell == 6) break;
                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
				}
			}
		}
	}
}

/// STUDENT ///
void COURSE_STU_PAGE(Year* &year,Semester* &sem,int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[]) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
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
				if (cell == 1){
                    system("cls");
                    Print_Course(sem); // ko in ra cac mon hoc
                    enroll_main(year, sem, U.username);  // continue
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 2){
                    system("cls");
                    View_Enrolled_Course_main(year, U.username);

                    //Student* temp = find_student_in_many_classes(year,username);  // find student to check Cur_Course
                    //if(temp->pCur_Cour == NULL) cout<<"no courses was enrolled ";

                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 3){
                    system("cls");
                    Print_Course(sem);
                    Delete_Enrolled_Course_main(year, sem, U.username);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 4){
                    system("cls");
                    Student_View_Scoreboard(year, U.username);
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if (cell == 5) {
					HOME = 4;
					return;
				}
				else if (cell == 6) break;

                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
				}
			}
		}
	}
}
void SEMESTER_STU_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string SEMESTER_STU_name_list_of_boxs[]) {
    Semester* import_sem;

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_STU_name_list_of_boxs[i]);
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
				if (cell == 1) {
                    system("cls");
                    Print_Semester(year);

                    import_sem = Import_Semester(year->pSemester);

                    if(import_sem == NULL){
                        cout<<"No semester was created.";
                        cin.ignore(1000, '\n');
                        getchar();                       
                    }else{
                        system("cls");
					    string COURSE_STU_name_list_of_boxs[] = { "Enroll course","View my course","Remove course","View scoreboard","Home","Return"};
					    COURSE_STU_PAGE(year,import_sem,locate_x, locate_y, 6, COURSE_STU_name_list_of_boxs);
                    }
					
					//
					if (HOME == 4) return;
					//
					
				}
				else if (cell == 2) {
					HOME = 4;
					return;
				}
				else if (cell == 3) break;

                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_STU_name_list_of_boxs[i]);
				}
			}
		}
	}
}
void YEAR_STU_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[]) {
    Year* import_year;

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
				if (cell == 1) {
                    system("cls");
                    Print_Year(year);

                    import_year = Import_Year(year); // import year

                    if(import_year == NULL){
                        cout<<"No year was created.";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
					    string SEMESTER_name_list_of_boxs[] = {"View semester","Home","Return" };
					    SEMESTER_STU_PAGE(import_year,locate_x, locate_y, 3, SEMESTER_name_list_of_boxs);
                    }	
					//
					if (HOME == 4) return;
					//
					
				}
				else if (cell == 2) {
					HOME = 4;
					return;
				}
				else if (cell == 3) break;
                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
				}
			}
		}
	}
}
/// ACCOUNT ///
void CHANGE_PASS_PAGE(Year* &year, int locate_x,int locate_y, int number_of_cells, string CHANGE_PASS_name_list_of_boxs[],Account *account_head) {

    string user_change, password = "";
	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CHANGE_PASS_name_list_of_boxs[i]);
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
                    if (U.username.find('@') != string::npos){
                        system("cls"); //staff
					    string YEAR_name_list_of_boxs[] = { "Create year","View list of years","View classes","View semesters","Home","Return"};
					    YEAR_PAGE(year, locate_x, locate_y, 6, YEAR_name_list_of_boxs);
	
                    }else{
                        system("cls"); //student
                        string YEAR_STU_name_list_of_boxs[] = {"View year","Home","Return"};
                        YEAR_STU_PAGE(year, locate_x, locate_y, 3, YEAR_STU_name_list_of_boxs);
                        
                    }				
				}else if(cell == 2){
                    system("cls");           
                    cout << "Enter your username: "; cin >> user_change;
                    cout << "Enter old password: ";
                    cin >> password;
                    
                    if (user_change == U.username && password == U.password){
                        cout << "Enter new password: ";
                        cin >> U.password;

                        change_password(account_head, U);
                        save_account_list(account_head); // save account
                        cout << "Password has been changed.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                    else{
                        cout << "Username or password is incorrect.\n";
                        cin.ignore(1000, '\n');
                        getchar();                            
                    }
                                        
                }			                    
				else if (cell == 3) break;
                system("cls");

                for (int i = 0; i < number_of_cells; i++) {
                    box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CHANGE_PASS_name_list_of_boxs[i]);
                }
			}
		}
	}
}
void LOGIN_PAGE(Year* &year, int locate_x,int locate_y, int number_of_cells, string LOGIN_name_list_of_boxs[]) {
    account_head = load_account_list();

    logo_portal(51,4);
	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, LOGIN_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
        LOG_OUT = 0;
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
                    cout << "Enter username: ";
                    cin >> U.username;
                    cout << "Enter password: ";
                    cin >> U.password;

                    if (account_check(account_head, U)){
                        cout << "Log in successfully.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                        system("cls");
                        string CHANGE_PASS_name_list_of_boxs[] = { "HOME","CHANGE PASSWORD","LOG OUT"};
                        CHANGE_PASS_PAGE(year, locate_x, locate_y, 3, CHANGE_PASS_name_list_of_boxs, account_head);
                                  
                    }
                    else{
                        cout << "Username or password is incorrect.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                } else if (cell == 2) break;

                system("cls");
                logo_portal(51,4);
                for (int i = 0; i < number_of_cells; i++) {
                    box(locate_x, locate_y + i * 3, 20, 2, 10, 11, LOGIN_name_list_of_boxs[i]);
                }   
			}
		}
	}
    delete_account_list(account_head); // delete account
    delete_all_node(year);
    gotoxy(1,20);
}

int main() {
    system("cls");
    Year* year = NULL;
    
    Nocursortype();
    string LOGIN_name_list_of_boxs[] = { "LOGIN","EXIT" };
	LOGIN_PAGE(year, 60, 10, 2, LOGIN_name_list_of_boxs);
    return 0;
}

