#include <bits/stdc++.h>
using namespace std;

struct _time {
    char start[3], end[3], day[2][4];
};

struct course {
    int id, credits, capacity;
    string course_name, teacher_name;
    _time time_performed;
    course *pNext_Course;
};

struct student {
    string No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    student* pNext_Student;
    course* studied_course, current_course;
};

struct subject {
    string subject_name;
    course *pCourse;
    subject *pNext_Subject;
};

struct _class {
    string name;
    student* pStudent;
    _class* pNext_Class;
};

struct year_semes {
    string year, semes;
    subject *pSubject;
    // pointer to class
};

subject *find_subject(subject *pSubject, string subject_name) {
    if (!pSubject) return nullptr;
    while (pSubject && pSubject->subject_name != subject_name) 
        pSubject = pSubject->pNext_Subject;
    return pSubject;
}

year_semes current_ys; // current year & semester

void add_course() { 
    string s;
    cout << "Subject: ";
    cin >> s;
    subject *Sub = find_subject(current_ys.pSubject, s);
    while (!Sub) {
        cout << "Subject not found! Try again: ";
        cin >> s;
        Sub = find_subject(current_ys.pSubject, s);
    }
    course* add_course = nullptr;
    if (!Sub->pCourse) {
        Sub->pCourse = new course;
        add_course = Sub->pCourse;
    }
    else {
        while (Sub->pCourse->pNext_Course) 
            Sub->pCourse = Sub->pCourse->pNext_Course;
        Sub->pCourse->pNext_Course = new course;
        add_course = Sub->pCourse->pNext_Course;
    }
    cout << "Enter the following details: " << endl;
    cout << "ID: ";
    cin >> add_course->id;
    cout << "Number of credits: ";
    cin >> add_course->credits;
    cout << "Maximum number of students in course: ";
    cin >> add_course->capacity;
    cout << "Course name: ";
    cin >> add_course->course_name;
    cout << "Teacher name: ";
    cin >> add_course->teacher_name;
    cout << "Time performing: " << endl;
    cout << "Day 1: ";
    cin >> add_course->time_performed.day[0];
    cout << "Day 2: ";
    cin >> add_course->time_performed.day[1];
    cout << "Start time: ";
    cin >> add_course->time_performed.start;
    cout << "End time: ";
    cin >> add_course->time_performed.end;
    add_course->pNext_Course = nullptr;
    cout << "Course added!" << endl;
}