// #include<iostream>
// #include<cstring>
// #include <iomanip>
// #include <fstream>
#include<bits/stdc++.h>
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
    int hour;
    int minute;
};
struct Registration_Session{
    Time start;
    Time end;
};
Subject* find_Subject(Subject *pSubject, string Subject_name) {
    if (!pSubject) return nullptr;
    while (pSubject && pSubject->name != Subject_name) 
        pSubject = pSubject->pNext_Subject;
    return pSubject;
}
Semester* find_semester(Semester* pSem, string name) {
    if (!pSem) return nullptr;
    while (pSem && pSem->name != name)
        pSem = pSem->pNext_Semester;
    return pSem;
}
void Create_Course(Subject* sub) { 
    string s;
    Course* add_Course = sub->pCourse;
    if (!sub->pCourse) {
        sub->pCourse = new Course;
        add_Course = sub->pCourse;
    }
    else {
        while (add_Course->pNext_Course) 
            add_Course = add_Course->pNext_Course;
        add_Course->pNext_Course = new Course;
        add_Course = add_Course->pNext_Course;
    }
    cout << "Enter the following details: " << endl;
    cout << "ID: ";
    cin >> add_Course->CourseID;
    cout << "Number of credits: ";
    cin >> add_Course->Number_of_Credits;
    cout << "Maximum number of students in Course: ";
    cin >> add_Course->Max_Student;
    cout << "Course name: ";
    cin >> add_Course->Course_Name;
    cout << "Teacher name: ";
    cin.ignore(1000, '\n');
    getline(cin, add_Course->Teacher_Name, '\n');
    cout << "Time performing: " << endl;
    cout << "Day 1: ";
    cin >> add_Course->Day1;
    cout << "Session 1: ";
    cin >> add_Course->Session1;
    cout << "Day 2: ";
    cin >> add_Course->Day2;
    cout << "Session 2: ";
    cin >> add_Course->Session2;
    cout << "Start day: ";
    cin >> add_Course->Start_Day;
    cout << "End day: ";
    cin >> add_Course->End_Day;
    add_Course->pNext_Course = nullptr;
    cout << "Course added!" << endl;
}
void Print_Course(Subject* sub) {
    Course* pCourse = sub->pCourse;
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
    while (pCourse) {
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
void Create_Subject(Semester* sem) {
    string sub_name;
    cout << "Subject name: ";
    cin.ignore(1000, '\n');
    getline(cin, sub_name, '\n');
    Subject* pNew = new Subject;
    pNew->name = sub_name;
    pNew->pCourse = nullptr;
    pNew->pNext_Subject = nullptr;
    if (!sem->pSubject)
        sem->pSubject = pNew;
    else {
        Subject* pCur_sub = sem->pSubject;
        while (pCur_sub->pNext_Subject) pCur_sub = pCur_sub->pNext_Subject;
        pCur_sub->pNext_Subject = pNew;
    }
}
Course* find_Course(Course* pCourse, string name) {
    if (!pCourse) return nullptr;
    if (pCourse->Course_Name == name) return pCourse;
    while (pCourse->pNext_Course && pCourse->pNext_Course->Course_Name != name)
        pCourse = pCourse->pNext_Course;
    if(pCourse->pNext_Course->Course_Name == name)
        return pCourse;
    else   
        return nullptr;
}
void Delete_Course(Subject* Sub) {
    string s;
    cout << "Course name: " ;
    cin >> s;
    Course* cour = find_Course(Sub->pCourse, s);
    while (!cour || (cour->Course_Name != s && !cour->pNext_Course)) {
        cout << "Course not found! Try again: ";
        cin >> s;
        cour = find_Course(Sub->pCourse, s);
    }
    if (cour->Course_Name == s) {
        Course* pDel = Sub->pCourse;
        Sub->pCourse = Sub->pCourse->pNext_Course;
        delete pDel;
    }
    else {
        Course* pDel = cour->pNext_Course;
        cour->pNext_Course = cour->pNext_Course->pNext_Course;
    }
    cout << "Deleted!" << endl;
}
void Create_Semester(Year *&year){
    Year *pCur_Year;
    string find_year;
    do{
        pCur_Year = year;
        cout << "academic year to import semester (ex: 2021): ";
        cin >> find_year;

        while (pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;
    } while (pCur_Year == NULL);

    string name_semester;
    cout << "Import semester (ex: 1, 2, 3): ";
    cin >> name_semester;
    Semester *pCur_Semester = pCur_Year->pSemester;

    Semester *Temp_Semester = new Semester;
    Temp_Semester->name = name_semester;
    Temp_Semester->pNext_Semester = NULL;
    Temp_Semester->pSubject = nullptr;

    if (pCur_Year->pSemester == NULL)
        pCur_Year->pSemester = Temp_Semester;
    else{
        while (pCur_Semester->pNext_Semester != NULL)
            pCur_Semester = pCur_Semester->pNext_Semester;
        pCur_Semester->pNext_Semester = Temp_Semester;
    }
}