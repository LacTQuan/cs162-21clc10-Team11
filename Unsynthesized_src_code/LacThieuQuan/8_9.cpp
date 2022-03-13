#include <bits/stdc++.h>
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

void add_Course(Year* &year) { 
    string s;
    cout << "Semester: ";
    cin >> s;
    Semester* sem = find_semester(year->pSemester, s);
    while (!sem) {
        cout << "Semester not found! Try again: ";
        cin >> s;
        sem = find_semester(year->pSemester, s);
    }
    cout << "Subject: ";
    cin >> s;
    Subject* Sub = find_Subject(sem->pSubject, s);
    while (!Sub) {
        cout << "Subject not found! Try again: ";
        cin >> s;
        Sub = find_Subject(sem->pSubject, s);
    }
    Course* add_Course = nullptr;
    if (!Sub->pCourse) {
        Sub->pCourse = new Course;
        add_Course = Sub->pCourse;
    }
    else {
        while (Sub->pCourse->pNext_Course) 
            Sub->pCourse = Sub->pCourse->pNext_Course;
        Sub->pCourse->pNext_Course = new Course;
        add_Course = Sub->pCourse->pNext_Course;
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
    cin >> add_Course->Teacher_Name;
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

void view_list_courses(Course* pCourse) {
    string s = "";
    while (pCourse) {
        cout << setw(5) << left << pCourse->CourseID;
        cout << setw(10) << left << pCourse->Number_of_Credits;
        cout << setw(10) << left << pCourse->Max_Student;
        cout << setw(20) << left << pCourse->Course_Name;
        cout << setw(20) << left << pCourse->Teacher_Name;
        s = pCourse->Day1; s += pCourse->Session1;
        cout << setw(10) << left << s;
        cout << setw(7) << left << pCourse->Start_Day;
        cout << setw(7) << left << pCourse->End_Day;
        s = pCourse->Day2; s += pCourse->Session2;
        cout << endl << setw(75) << left << s << endl;
        pCourse = pCourse->pNext_Course;
    }
}

void view_list_Courses(Year* year) {
    string s;
    cout << "Semester: ";
    cin >> s;
    Semester* sem = find_semester(year->pSemester, s);
    while (!sem) {
        cout << "Semester not found! Try again: ";
        cin >> s;
        sem = find_semester(year->pSemester, s);
    }
    cout << "Subject: ";
    cin >> s;
    Subject* Sub = find_Subject(sem->pSubject, s);
    while (!Sub) {
        cout << "Subject not found! Try again: ";
        cin >> s;
        Sub = find_Subject(sem->pSubject, s);
    }
    cout << endl;
    cout << setw(5) << left << "ID";
    cout << setw(10) << left << "Credits";
    cout << setw(10) << left << "Capacity";
    cout << setw(20) << left << "Course's name";
    cout << setw(20) << left << "Teacher's name";
    cout << setw(10) << left << "Time performing: ";
    cout << setw(7) << left << "Start day: ";
    cout << setw(7) << left << "End day: " << endl;
    view_list_courses(Sub->pCourse);
}