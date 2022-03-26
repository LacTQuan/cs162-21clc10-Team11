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