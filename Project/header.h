#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include<iostream>
#include<cstring>
#include <iomanip>
#include <fstream>

using namespace std;

#define nullptr 0
//right
struct Student{
    //No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    Student* pNext_Student;
};
struct Class{
    string name;
    Student* pStudent;
    Class* pNext_Class;
};
//left
struct Student_Course{
    Student_Course* pNext_Student_Course;
    Student* pStudent;
};
struct Course{
    //Course id, Course name, teacher name, number of credits, 
    //the maximum number of students (default 50), day, and the session
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Course* pNext_Course;
    Student_Course* pStudent_Course;
};
struct Subject{
    string name;
    Subject* pNext_Subject;
    Course* pCourse;
};
struct Semester{
    string name;
    Semester* pNext_Semester;
    Subject* pSubject;
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


Subject* find_Subject(Subject *pSubject, string Subject_name);
Semester* find_semester(Year* year, string name);
void add_Course(Year* year);
void view_list_Courses(Year* year);
void add_Subject(Year* year);
Course* find_Course(Course* pCourse, string ID);
void delete_Course(Year* year);
void create_Semester(Year *year);
Registration_Session create_Registration_Session();
void update_Course(Year *year);
void Print_Year(Year *year);
void Print_Class(Year *year);
void Print_Student(Year *year);
void Create_Year(Year* &year);
void Create_Class(Year* &year);
void Create_Student(Year* &year);


void solve();

#endif