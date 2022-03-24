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

#define nullptr 0
int HOME = 0;
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
    int hour;
    int minute;
};
struct Registration_Session{
    Time start;
    Time end;
};
Semester* find_semester(Semester* pSem, string name) {
    if (!pSem) return nullptr;
    while (pSem && pSem->name != name)
        pSem = pSem->pNext_Semester;
    return pSem;
}
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

void Create_Course(Semester* sem) { 
    ifstream filein("course.csv");
    while(filein.eof() == false){
        Course* pCur_Course = sem->pCourse;
        Course* add_Course = new Course;
        cout << "ID: ";
        getline(filein,add_Course->CourseID,','); cout<<add_Course->CourseID<<" | ";
        cout << "Number of credits: ";
        getline(filein,add_Course->Number_of_Credits,','); cout<<add_Course->Number_of_Credits<<" | ";
        cout << "Maximum number of students in Course: ";
        getline(filein,add_Course->Max_Student,','); cout<<add_Course->Max_Student<<" | ";
        cout << "Course name: ";
        getline(filein,add_Course->Course_Name,','); cout<<add_Course->Course_Name<<" | ";
        cout << "Teacher name: ";
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
Registration_Session create_Registration_Session(){
    Registration_Session S;
    cout << "Create Registration Session: \n";
    cout << "Start time: \n";
    cout << "Date: ";
    cin >> S.start.date;
    cout << "Month: ";
    cin >> S.start.month;
    cout << "Year: ";
    cin >> S.start.year;
    cout << "Hour: ";
    cin >> S.start.hour;
    cout << "Minute: ";
    cin >> S.start.minute;

    cout << "End time: \n";
    cout << "Date: ";
    cin >> S.end.date;
    cout << "Month: ";
    cin >> S.end.month;
    cout << "Year: ";
    cin >> S.end.year;
    cout << "Hour: ";
    cin >> S.end.hour;
    cout << "Minute: ";
    cin >> S.end.minute;

    return S;
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
void View_Enrolled_Course(Student* student){
    if(student->pCur_Cour == NULL){
        cout<<"No subjects is enrolled"<<endl;
        cin.ignore();
        getchar();
        return;
    }
    Cur_Course* pCur_st = student->pCur_Cour;
    cout<<"Courses enrolled: ";
    while(pCur_st != NULL){
        cout<<pCur_st->Course_Name<<" ";
        pCur_st = pCur_st->pNext_Cur_Cour;
    }
}
void view_enrolled_main(Year* &year, Semester* &semester){
    string studentID;
    cout<<"StudentID "; cin>>studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if(student == NULL){
        cout<<"invalid student"<<endl;
        cin.ignore();
        getchar();
        return;
    }
    
    View_Enrolled_Course(student);
    cin.ignore();
    getchar();
}
void Delete_Enrolled_Course(Student* &student, Course* &course){
    if(student->pCur_Cour == NULL || course->pStudent_Course == NULL){
        cout<<"No courses is to delete"<<endl;
        return;
    }
    Cur_Course* pCur_Head = student->pCur_Cour;
    Student_Course* pStu_Head = course->pStudent_Course;

    if(student->pCur_Cour->Course_Name == course->Course_Name){
        //delete current course
        Cur_Course* pTemp = student->pCur_Cour;
        pCur_Head = pCur_Head->pNext_Cur_Cour;
        student->pCur_Cour = pCur_Head;
        delete pTemp;

    }else{
        //delete current course
        Cur_Course* pTemp = pCur_Head;
        while(pTemp->pNext_Cur_Cour->Course_Name != course->Course_Name)
            pTemp = pTemp->pNext_Cur_Cour;

        Cur_Course* pDel = pTemp->pNext_Cur_Cour;
        pTemp->pNext_Cur_Cour = pTemp->pNext_Cur_Cour->pNext_Cur_Cour;
        delete pDel;
        
    }
    
    if(course->pStudent_Course->StudentID == student->StudentID){
        //delete student in course
        Student_Course* pTemp2 = course->pStudent_Course;
        pStu_Head = pStu_Head->pNext_Student_Course;
        course->pStudent_Course = pStu_Head;
        delete pTemp2;
    }else{
        //delete student in course

        Student_Course* pTemp2 = pStu_Head;
        while(pTemp2->pNext_Student_Course->StudentID != student->StudentID)
            pTemp2 = pTemp2->pNext_Student_Course;

        Student_Course* pDel2 = pTemp2->pNext_Student_Course;
        pTemp2->pNext_Student_Course = pTemp2->pNext_Student_Course->pNext_Student_Course;
        delete pDel2;
    }
}
void delete_enrolled_main(Year* &year, Semester* &semester){
    string studentID;
    cout<<"StudentID "; cin>>studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if(student == NULL){
        cout<<"invalid student"<<endl;
        cin.ignore();
        getchar();
        return;
    }
    //view all course
    View_Enrolled_Course(student);

    string course_name;
    cout<<endl<<"Course you choose to delete "; cin>>course_name;
    Course* course_del = find_course_in_many_subjects(semester,course_name);
    if(course_del == NULL){
        cout<<"invalid course_register"<<endl;
        cin.ignore();
        getchar();
        return;
    }
    cout<<"This course is" <<course_del->Course_Name<<endl;

    Delete_Enrolled_Course(student,course_del);
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
void Create_Student(Class *&classes){

    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    
    ifstream filein("profile.csv");
    while(filein.eof() == false){
        Student* pCur_Student = classes->pStudent;
        Student* Temp_Student = new Student;
        cout<<"Import student: "<<endl;
        cout<<"No ";getline(filein,Temp_Student->No,',');cout<<Temp_Student->No<<" | ";
        cout<<"StudentID ";getline(filein,Temp_Student->StudentID,',');cout<<Temp_Student->StudentID<<" | ";
        cout<<"FirstName ";getline(filein,Temp_Student->FirstName,',');cout<< " " << setw(20) << left << Temp_Student->FirstName;
        cout<<"LastName ";getline(filein,Temp_Student->LastName,',');cout<< " " << setw(15) << left << Temp_Student->LastName<<" | ";
        cout<<"Gender ";getline(filein,Temp_Student->Gender,',');cout<<setw(7) << left << Temp_Student->Gender<<" | ";
        cout<<"Date_of_Birth ";getline(filein,Temp_Student->Date_of_Birth,',');cout<<Temp_Student->Date_of_Birth<<" | ";
        cout<<"SocialID ";getline(filein,Temp_Student->SocialID,'\n');cout<<Temp_Student->SocialID<<endl;
        Temp_Student->pNext_Student = NULL;
        Temp_Student->pCur_Cour = NULL;

        if(classes->pStudent == NULL) classes->pStudent = Temp_Student;
        else{
            while(pCur_Student->pNext_Student != NULL) pCur_Student = pCur_Student->pNext_Student;
            pCur_Student->pNext_Student = Temp_Student;
        }    
    }
    
    filein.close();
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
    if(count <= 3) return true;
    return false;
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
            cin.ignore();
            getchar();
        }else if (Check_quantity(student) == false){
            cout<<"This course has enough quantity\n";
            cin.ignore();
            getchar();
        }else if(Check_Session(course_regis,student) == false){
            cout<<"The schedule has been overlapped\n";
            cin.ignore();
            getchar();
        }
    }
}

//enroll main
void enroll_main(Year* &year, Semester* &semester){
    string studentID;
    cout<<"StudentID "; cin>>studentID;

    Student* student = find_student_in_many_classes(year, studentID);
    if(student == NULL){
        cout<<"invalid student"<<endl;
    cin.ignore();
    getchar();
        return;
    }
    //view all course
    string course_name;
    cout<<"Course you want to choose "; cin>>course_name;
    Course* course_regis = find_course_in_many_subjects(semester,course_name);
    if(course_regis == NULL){
        cout<<"invalid course_register"<<endl;
        cin.ignore();
        getchar();
        return;
    }

    Enroll_Course(course_regis,student);
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
int convert_to_int(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++)
        res = res * 10 + (s[i] - '0');
    return res;
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
        cin.ignore();
        getchar();
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
        cin.ignore();
        getchar();
        return;                                      
    }
    system("cls");
    View_Score_Board(course_regis);
}
void update_student_result(Year* year, Semester* sem){
    //view all course
    //Print_Course(sem);
    //find course
    string course_name;
    cout<<"Course you want to choose "; cin>>course_name;
    Course* course_update = find_course_in_many_subjects(sem,course_name);
    if(course_update == NULL){
        cout<<"invalid course_update"<<endl;
        cin.ignore();
        getchar();
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
        cin.ignore();
        getchar();
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


void Interface_Student(Year* year, Semester* sem, string Student_ID) {
    int choose_1;
    do {
        HOME:
        // system("cls");
        cout << "1.Home" << endl;
        cout << "2.Log out" << endl;
        cout << "Enter choose "; cin >> choose_1;
        if (choose_1 == 1) {
            int choose_2;
            do {
                // if course registration is active
                // system("cls");
                cout << "1.Enroll a course" << endl;
                cout << "2.View my course" << endl;
                cout << "3.Remove a course from my list" << endl;
                cout << "4.Return" << endl;
                cout << "5.Home" << endl;
                cout << "Enter choose " << endl; cin >> choose_2;
                if (choose_2 == 1) {
                    // system("cls");
                    Print_Course(sem);
                    enroll_main(year,sem);
                }
                else if (choose_2 == 2) {
                    // system("cls");
                    Print_Cur_Course(find_student_in_many_classes(year, Student_ID)->pCur_Cour);
                    cout << endl;
                    getchar();
                }
                else if (choose_2 == 3) {
                    // Remove course
                }
                if (choose_2 == 5) goto HOME;
            } while (choose_2 != 4);
        }
    } while (choose_1 != 2);
}
void Interface_Staff(Year* &year){
    int choose_1;
    do{
        HOME:
        system("cls");
        cout<<"1.Home"<<endl;
        cout<<"2.Log out"<<endl;
        cout<<"->Enter choose ";cin>>choose_1;
        if(choose_1 == 1){
            
            int choose_2;
            do{
                valid_year:
                system("cls");
                cout<<"--------YEARS LIST--------"<<endl;
                Print_Year(year);
                cout<<"--------------------------"<<endl;
                cout<<"1.Create year"<<endl;
                cout<<"2.Choose year to view classes"<<endl;
                cout<<"3.Choose year to view semesters"<<endl;
                cout<<"4.Home"<<endl;
                cout<<"5.Return"<<endl;              
                cout<<"->Enter choose "; cin>>choose_2;

                if(choose_2 == 1){
                    system("cls");
                    Print_Year(year);

                    Create_Year(year); 
                }   

                if(choose_2 == 2){
                    system("cls");
                    Print_Year(year);

                    int choose_3;
                    Year* import_year = Import_Year(year);

                    if(import_year == NULL){
                        cout<<"no years was created ";
                        cin.ignore();
                        getchar();
                        goto valid_year;
                    }
                    do{
                        valid_class:
                        system("cls");
                        cout<<"--------CLASSES LIST--------"<<endl;
                        Print_Class(import_year);
                        cout<<"----------------------------"<<endl;                  
                        cout<<"1.Create class"<<endl;
                        cout<<"2.Choose class to view student"<<endl;
                        cout<<"3.Home"<<endl;
                        cout<<"4.Return"<<endl; 
                        cout<<"->Enter choose "; cin>>choose_3;
                        if(choose_3 == 1){
                            system("cls");
                            Print_Class(import_year);

                            Create_Class(import_year);
                        }
                        if(choose_3 == 2) {
                            system("cls");
                            Print_Class(import_year);

                            int choose_4;
                            Class* import_class = Import_Class(import_year->pClass);

                            if(import_class == NULL){
                                cout<<"no classes was created ";
                                cin.ignore();
                                getchar();
                                goto valid_class;
                            }
                            do{
                                system("cls");
                                cout<<"--------STUDENTS LIST--------"<<endl;
                                Print_Student(import_class);
                                cout<<"-----------------------------"<<endl;                                
                                cout<<"1.Create student"<<endl;                            
                                cout<<"2.Home"<<endl;
                                cout<<"3.Return"<<endl; 
                                cout<<"->Enter choose "; cin>>choose_4;
                                if(choose_4 == 1){
                                    system("cls");
                                    Print_Student(import_class);
                                    Create_Student(import_class);
                                } 
                                else if(choose_4 == 2) goto HOME;

                            }while(choose_4 != 3);
                        }
                        if(choose_3 == 3) goto HOME;

                    }while(choose_3 != 4);
                }
                else if (choose_2 == 3) {
                    system("cls");
                    Print_Year(year);

                    int choose_3;
                    Year* import_year = Import_Year(year);

                    if(import_year == NULL){
                        cout<<"no years was created ";
                        cin.ignore();
                        getchar();
                        goto valid_year;
                    }
                    do{
                        valid_semester:
                        system("cls");
                        cout<<"--------SEMESTERS LIST--------"<<endl;
                        Print_Semester(import_year);
                        cout<<"------------------------------"<<endl;                  
                        cout<<"1.Create semester"<<endl;
                        cout<<"2.Choose semester to view courses"<<endl;
                        cout<<"3.Home"<<endl;
                        cout<<"4.Return"<<endl; 
                        cout<<"->Enter choose "; cin>>choose_3;
                        if(choose_3 == 1){
                            system("cls");
                            Print_Semester(import_year);
                            Create_Semester(import_year);
                        }
                        if(choose_3 == 2) {
                            system("cls");
                            Print_Semester(import_year);

                            int choose_4;
                            Semester* import_sem = Import_Semester(import_year->pSemester);

                            if(import_sem == NULL){
                                cout<<"no semesters was created ";
                                cin.ignore();
                                getchar();
                                goto valid_semester;
                            }
                            do{
                                system("cls");
                                cout<<"--------COURSES LIST---------"<<endl;
                                Print_Course(import_sem);
                                cout<<"-----------------------------"<<endl;                                
                                cout<<"1.Create course"<<endl;                            
                                cout<<"2.Update course"<<endl;
                                cout<<"3.Delete course"<<endl;
                                cout<<"4.Home"<<endl; 
                                cout<<"5.Return"<<endl;
                                cout<<"6.Enroll"<<endl;
                                cout<<"7.View student in course"<<endl;
                                cout<<"8.Create mark"<<endl;
                                cout<<"9.View scoreboard in a course"<<endl;
                                cout<<"10.Update student result"<<endl;
                                cout<<"->Enter choose "; cin>>choose_4;
                                if(choose_4== 1){
                                    system("cls");
                                    Print_Course(import_sem);
                                    Create_Course(import_sem);
                                } 
                                else if (choose_4 == 2) {
                                    system("cls");
                                    Print_Course(import_sem);
                                    Update_Course(import_sem);
                                }
                                else if (choose_4 == 3) {
                                    system("cls");
                                    Print_Course(import_sem);
                                    Delete_Course(import_sem);
                                }
                                else if (choose_4 == 6){
                                    system("cls");
                                    Print_Course(import_sem);                        
                                    enroll_main(import_year,import_sem);
                                }
                                else if (choose_4 == 7) {
                                    system("cls");
                                    View_Student_In_Course(import_sem);
                                    cin.ignore();
                                    getchar();
                                }
                                else if (choose_4 == 8) {
                                    system("cls");
                                    Print_Course(import_sem);
                                    Create_mark_main(import_year,import_sem);
                                    // Import_Scoreboard(year, cour);
                                    // View_Score_Board(cour);
                                    // cin.ignore(1000, '\n');
                                    // getchar();
                                }else if (choose_4 == 9){
                                    system("cls");
                                    Print_Course(import_sem);
                                    View_scoreboard_main(import_sem);
                                    cin.ignore();
                                    getchar();
                                }else if(choose_4 == 10){
                                    system("cls");
                                    Print_Course(import_sem);
                                    update_student_result(import_year,import_sem);
                                    cin.ignore();
                                    getchar();
                                }
                                if(choose_4 == 4) goto HOME;
                            } while (choose_4 != 5);
                        }
                        if(choose_3 == 3) goto HOME;
                    }while(choose_3 != 4);
                }
                if(choose_2 == 4) goto HOME;
            }while(choose_2 != 5);
        }
    }while(choose_1 != 2);
}
void Interface() {
    cout << "1.Log in" << endl;
    cout << "2.Exit" << endl;
    // student account ---> Interface_Student
    // staff account ---> Interface_Staff
}
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
					string STUDENT_COUR_name_list_of_boxs[] = { "Create course","Update course","Delete course","Home","Return","Enroll","View student","Create mark","View scoreboard","Update result" };
					STUDENT_COUR_PAGE(locate_x, locate_y, 10, STUDENT_COUR_name_list_of_boxs);
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
					STUDENT_PAGE(locate_x, locate_y, 3, STUDENT_name_list_of_boxs); //change
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
					CLASS_PAGE(locate_x, locate_y, 4, CLASS_name_list_of_boxs);
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
					YEAR_PAGE(locate_x, locate_y, 5, YEAR_name_list_of_boxs);
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
    system("cls");
    Year* year = NULL;
    //test(year);
    Nocursortype();
	string HOME_name_list_of_boxs[] = { "HOME","CURRENT TIME","LOG OUT" };
	HOME_PAGE(60,10, 3, HOME_name_list_of_boxs);
    //Interface_Staff(year);
}