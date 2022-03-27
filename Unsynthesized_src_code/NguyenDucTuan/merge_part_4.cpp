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
    double GPA;
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
Registration_Session S;
Account *account_head;

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

bool account_check(Account *head, string username, string password){
    bool success = false;
    Account *cur = head;
    while (!success && cur){
        if (cur->username == username && cur->password == password)
            success = true;
        else
            cur = cur->next;
    }
    return success;
}
/*******************************************************
 * Load all usernames and passwords to a pointer array *
 * for further rewriting file                           *
 *******************************************************/
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
void change_password(Account *head, string username, string newPassword){
    Account *cur = head;
    bool found = false;
    while (cur && cur->username != username)
        cur = cur->next;
    if (cur == nullptr){
        cout << "ERROR!\n";
    }
    else
        cur->password = newPassword;
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
    ifstream filein("course.csv");
    while(filein.eof() == false){
        Course* pCur_Course = sem->pCourse;
        Course* add_Course = new Course;
        cout << "ID: ";
        getline(filein,add_Course->CourseID,','); cout<<add_Course->CourseID<<" | ";
        cout << "Credits: ";
        getline(filein,add_Course->Number_of_Credits,','); cout<<add_Course->Number_of_Credits<<" | ";
        cout << "Capacity: ";
        getline(filein,add_Course->Max_Student,','); cout<<add_Course->Max_Student<<" | ";
        cout << "Course's name: ";
        getline(filein,add_Course->Course_Name,','); cout<<add_Course->Course_Name<<" | ";
        cout << "Teacher's name: ";
        getline(filein,add_Course->Teacher_Name,',');cout<<add_Course->Teacher_Name<<" | ";
        cout << "Day 1: ";
        getline(filein,add_Course->Day1,','); cout<<add_Course->Day1<<" | ";
        cout << "Session 1: ";
        getline(filein,add_Course->Session1,','); cout<<add_Course->Session1<<" | ";
        cout << "Day 2: ";
        getline(filein,add_Course->Day2,','); cout<<add_Course->Day2<<" | ";
        cout << "Session 2: ";
        getline(filein,add_Course->Session2,','); cout<<add_Course->Session2<<" | ";
        cout << "Start day: ";
        getline(filein,add_Course->Start_Day,','); cout<<add_Course->Start_Day<<" | ";
        cout << "End day: ";
        getline(filein,add_Course->End_Day,'\n'); cout<<add_Course->End_Day<<endl<<" | ";
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
    cout << setw(5) << left << "ID";
    cout << setw(10) << left << "Credits";
    cout << setw(10) << left << "Capacity";
    cout << setw(20) << left << "Course's name";
    cout << setw(20) << left << "Teacher's name";
    cout << setw(20) << left << "Time performing";
    cout << setw(15) << left << "Start day";
    cout << setw(15) << left << "End day" << endl;
    string s = "";
    while (pCourse != NULL) {
        cout << setw(5) << left << pCourse->CourseID;
        cout << setw(10) << left << pCourse->Number_of_Credits;
        cout << setw(10) << left << pCourse->Max_Student;
        cout << setw(20) << left << pCourse->Course_Name;
        cout << setw(20) << left << pCourse->Teacher_Name;
        s = pCourse->Day1; s += " "; s += pCourse->Session1;
        cout << setw(20) << left << s;
        cout << setw(15) << left << pCourse->Start_Day;
        cout << setw(15) << left << pCourse->End_Day;
        s = pCourse->Day2; s += " "; s += pCourse->Session2;
        cout << endl << setw(70) << right << s << endl;
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
void Print_Student(Class *classes)
{
    Student *pCur_Student = classes->pStudent;
    while (pCur_Student != NULL)
    {
        //No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID
        cout <<"No."<< pCur_Student->No << " | ";
        cout<< pCur_Student->StudentID << " | ";
        cout<< pCur_Student->FirstName << " | ";
        cout<< pCur_Student->LastName << " | ";
        cout<< pCur_Student->Gender << " | ";
        cout<< pCur_Student->Date_of_Birth << " | ";
        cout<< pCur_Student->SocialID << " \n";
        pCur_Student = pCur_Student->pNext_Student;
    }
    cout<<endl;
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
        cout << "No courses to display" << endl;
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
void View_Student_In_Class(Year *year){
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
				cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tSocial ID\n";
				Student *pCurStudent = pCurClass->pStudent;
				while (pCurStudent){
					cout << pCurStudent->No << '\t';
					cout << pCurStudent->StudentID << '\t';
					cout << pCurStudent->FirstName << '\t';
					cout << pCurStudent->LastName << '\t';
					cout << pCurStudent->Gender << '\t';
					cout << pCurStudent->SocialID << '\n';
					pCurStudent = pCurStudent->pNext_Student;
				}
			}
		}
	} while (!exist);
}
// 20
void View_Student_In_Course(Semester* sem){
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
    
    cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of Birth\tSocial ID\n";
    while (pCurStu){
        cout << pCurStu->No << '\t';
        cout << pCurStu->StudentID << '\t';
        cout << pCurStu->FirstName << '\t';
        cout << pCurStu->LastName << '\t';
        cout << pCurStu->Gender << '\t';
        cout << pCurStu->Date_of_Birth << '\t';
        cout << pCurStu->SocialID << '\n';
        
        pCurStu = pCurStu->pNext_Student_Course;
    }
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
        //cin.ignore(1000, '\n');
        //getchar();
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
        //cin.ignore(1000, '\n');
        //getchar();
        return;
    }
    Delete_Enrolled_Course(student, Del_Cour);

    }else cout<<"Over time!";
}
void Create_Year(Year* &year){
    string name_year;
    cout<<"Import academic year (ex: 2021) ";
    cin >> name_year;
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
void Create_Class(Year* &year){
    string name_class;
    cout<<"Import class (ex:21CLC10) ";
    cin >> name_class;
    Class* pCur_Class = year->pClass;

    Class* Temp_Class = new Class;
    Temp_Class->name = name_class;
    Temp_Class->pNext_Class = NULL;
    Temp_Class->pStudent = NULL;

    if(year->pClass == NULL) year->pClass = Temp_Class;
    else{
        while(pCur_Class->pNext_Class != NULL) pCur_Class = pCur_Class->pNext_Class;
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
    while(filein.eof() == false){
        Student* pCur_Student = classes->pStudent;
        Student* Temp_Student = new Student;
        cout<<"Import student: "<<endl;
        cout<<"No ";getline(filein,Temp_Student->No,',');cout<<Temp_Student->No<<" | ";
        cout<<"StudentID ";getline(filein,Temp_Student->StudentID,',');cout<<Temp_Student->StudentID<<" | ";
        cout<<"FirstName ";getline(filein,Temp_Student->FirstName,',');cout<< " " << setw(20) << left << Temp_Student->FirstName<<" | ";
        cout<<"LastName ";getline(filein,Temp_Student->LastName,',');cout<< " " << setw(15) << left << Temp_Student->LastName<<" | ";
        cout<<"Gender ";getline(filein,Temp_Student->Gender,',');cout<<setw(7) << left << Temp_Student->Gender<<" | ";
        cout<<"Date_of_Birth ";getline(filein,Temp_Student->Date_of_Birth,',');cout<<Temp_Student->Date_of_Birth<<" | ";
        cout<<"SocialID ";getline(filein,Temp_Student->SocialID,'\n');cout<<Temp_Student->SocialID<<endl;
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
    cout<<"Enter first name: "; getline(cin, pNew_Student->FirstName, '\n');
    cout<<"Enter last name: "; getline(cin, pNew_Student->LastName, '\n');
    cout<<"Enter date of birth: "; cin>>pNew_Student->Date_of_Birth;
    cout<<"Enter gender: "; cin>>pNew_Student->Gender;
    cout<<"Enter social id: "; cin>>pNew_Student->SocialID;
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
    
    do {
        cout<<"Enter the new student's id, (existed id is not allowed): "; cin>>student_id;
        stu = find_student_in_many_classes(year, student_id);
    } while (stu != nullptr);
    
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
            cout<<"invalid student"<<endl;
            return;
        }
        //view all course
        string course_name;
        cout<<"Course you want to choose "; cin>>course_name;
        Course* course_regis = find_course_in_many_subjects(semester,course_name);
        if(course_regis == NULL){
            cout<<"invalid course_register"<<endl;
            return;
        }

        Enroll_Course(course_regis,student);
    }
    else cout<<"Over time!"<<endl;
}


double rand_mark() {
    //srand(time(NULL));
    return min(10.0, (rand() % 11) * 1.0 + (rand() % 10) / 10.0);
}
void Assign_Mark(Year* year, string Student_ID, double total, double final, double mid, double other) {
    Student* Std = find_student_in_many_classes(year, Student_ID);
    // Student id always exists in this case-->no check null
    Std->pCur_Cour->mark.Final = final,
    Std->pCur_Cour->mark.Midterm = mid,
    Std->pCur_Cour->mark.Other = other,
    Std->pCur_Cour->mark.Total = total;
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
        Assign_Mark(year, pCurStd->StudentID, pCurStd->mark.Total, pCurStd->mark.Final,
        pCurStd->mark.Midterm, pCurStd->mark.Other);
    }
    fin.close();
}
void View_Score_Board(Course *cour) {
    cout << "ID\tFull name\t\tMidterm mark\tFinal mark\tOther\tTotal" << endl;
    Student_Course* pCurStd = cour->pStudent_Course;
    while (pCurStd != nullptr) {
        cout << pCurStd->StudentID << "\t" << pCurStd->LastName + " " + pCurStd->FirstName
        << "\t" << pCurStd->mark.Midterm << "\t" << pCurStd->mark.Final << "\t" << pCurStd->mark.Other
        << "\t" << pCurStd->mark.Total << endl;
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
}


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
        cout<<"invalid student"<<endl;
        //cin.ignore();
        //getchar();
        return;
    }
    Student_Course* student_cour = find_student_in_a_course(course_update,student->StudentID);
    
    cout<<"Update score\n";
    cout<<"Midterm ";cin>>student_cour->mark.Midterm;
    cout<<"Final ";cin>>student_cour->mark.Final;
    cout<<"Other ";cin>>student_cour->mark.Other;
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
//logo portal
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
                    if(sem->pCourse == NULL) cout<<"no courses was created ";
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if(cell == 3){
                    system("cls");
                    Print_Course(sem);
                    Update_Course(sem);
                }else if(cell == 4){
                    system("cls");
                    Print_Course(sem);
                    Delete_Course(sem);
                }else if(cell == 5){
                    system("cls");
                    View_Student_In_Course(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 6){
                    system("cls");
                    Print_Course(sem);
                    Create_mark_main(year,sem);
                }else if(cell == 7){
                    system("cls");
                    View_scoreboard_main(sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 8){
                    system("cls");
                    Export_Course_main(year, sem);
                }else if(cell == 9){
                    system("cls");
                    Print_Course(sem);
                    update_student_result(year,sem);
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
                    if(year->pSemester == NULL) cout<<"no semesters was created ";
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 3) {
                    system("cls");
                    Print_Semester(year);

                    import_sem = Import_Semester(year->pSemester);

                    if(import_sem == NULL){
                        cout<<"no semesters was created ";
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
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if (cell == 3){
                    system("cls");
                    Print_Student(classes);
                    if(classes->pStudent == NULL) cout<<"no students was created ";
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
                    if(year->pClass == NULL) cout<<"no classes was created ";
                    cin.ignore(1000,'\n');
                    getchar();
                }
				else if (cell == 3) {
					system("cls");
                    Print_Class(year);

                    import_class = Import_Class(year->pClass);

                    if(import_class == NULL){
                        cout<<"no classes was created ";
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
				}
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;
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
                    if(year == NULL) cout<<"no years was created ";
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 3) {
                    system("cls");
                    Print_Year(year);

                    import_year = Import_Year(year); // import year

                    if(import_year == NULL){
                        cout<<"no years was created ";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
					    string CLASS_name_list_of_boxs[] = { "Create class","View classes","View student","Home","Return" };
					    CLASS_PAGE(import_year,locate_x, locate_y, 5, CLASS_name_list_of_boxs);
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
                        cout<<"no years was created ";
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

// student
void COURSE_STU_PAGE(string username,Year* &year,Semester* &sem,int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[]) {

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
                    enroll_main(year,sem,username);  // continue
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 2){
                    system("cls");
                    View_Enrolled_Course_main(year,username);

                    //Student* temp = find_student_in_many_classes(year,username);  // find student to check Cur_Course
                    //if(temp->pCur_Cour == NULL) cout<<"no courses was enrolled ";

                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 3){
                    system("cls");
                    Print_Course(sem);
                    Delete_Enrolled_Course_main(year,sem,username);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;

                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
				}
			}
		}


	}
}
void SEMESTER_STU_PAGE(string username,Year* &year,int locate_x, int locate_y, int number_of_cells, string SEMESTER_STU_name_list_of_boxs[]) {
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
                        cout<<"no semesters was created ";
                        cin.ignore(1000, '\n');
                        getchar();                       
                    }else{
                        system("cls");
					    string COURSE_STU_name_list_of_boxs[] = { "Enroll course","View my course","Remove course","Home","Return"};
					    COURSE_STU_PAGE(username,year,import_sem,locate_x, locate_y, 5, COURSE_STU_name_list_of_boxs);
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
void YEAR_STU_PAGE(string username,Year* &year,int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[]) {
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
                        cout<<"no years was created ";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
					    string SEMESTER_name_list_of_boxs[] = {"View semester","Home","Return" };
					    SEMESTER_STU_PAGE(username,import_year,locate_x, locate_y, 3, SEMESTER_name_list_of_boxs);
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

void CHANGE_PASS_PAGE(string username,Year* &year, int locate_x,int locate_y, int number_of_cells, string CHANGE_PASS_name_list_of_boxs[],Account *account_head) {

    string newPassword,user_change, password;
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
                    if (username.back() == 'n'){
                        system("cls"); //staff
					    string YEAR_name_list_of_boxs[] = { "Create year","View list of years","View classes","View semesters","Home","Return"};
					    YEAR_PAGE(year, locate_x, locate_y, 6, YEAR_name_list_of_boxs);
	
                    }else{
                        system("cls"); //student
                        string YEAR_STU_name_list_of_boxs[] = {"View year","Home","Return"};
                        YEAR_STU_PAGE(username,year, locate_x, locate_y, 3, YEAR_STU_name_list_of_boxs);
                        
                    }				
				}else if(cell == 2){
                    system("cls");
                    cout << "Enter username: "; cin >> user_change;
                    cout << "Enter old password: "; cin >> password;
                    if (account_check(account_head, user_change, password)){
                        cout << "Enter new password: "; cin >> newPassword;
                        change_password(account_head, user_change, newPassword);
                        save_account_list(account_head); // save account
                        cout << "Password has been changed.\n";
                        cin.ignore(1000, '\n');
                        getchar();                        
                    }
                    else{
                        cout << "Username or password is incorrect";
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
    string username, password;

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
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    if (account_check(account_head, username, password)){
                        cout << "Log in successfully.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                        system("cls");
                        string CHANGE_PASS_name_list_of_boxs[] = { "HOME","CHANGE PASSWORD","LOG OUT"};
                        CHANGE_PASS_PAGE(username,year, locate_x, locate_y, 3, CHANGE_PASS_name_list_of_boxs,account_head);
                                  
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
	LOGIN_PAGE(year,60,10, 2, LOGIN_name_list_of_boxs);
    
}