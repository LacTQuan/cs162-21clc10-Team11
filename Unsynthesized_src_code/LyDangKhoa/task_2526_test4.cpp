#include <string>
#include<iostream>
#include<cstring>
#include <iomanip>
#include <fstream>
#include <math.h>
//#include<bits/stdc++.h>
using namespace std;

#define nullptr 0
//right
struct Mark { // new
    double Total = 0, Final = 0, Midterm = 0, Other = 0;
};
struct Cur_Course { //new
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Mark mark;
    Cur_Course* pNext_Cur_Cour;
    //Temp_Course* pTemp_Cour;
};
struct Student {
    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    double GPA;
    Student* pNext_Student;
    Cur_Course* pCur_Cour;
};
struct Student_Course {
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    Mark mark;
    Student_Course* pNext_Student_Course;
    Student* pStudent;
};
struct Class {
    string name;
    Student* pStudent;
    Class* pNext_Class;
};
//left
struct Course {
    //Course id, Course name, teacher name, number of credits, 
    //the maximum number of students (default 50), day, and the session
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Course* pNext_Course;
    Student_Course* pStudent_Course;
};
struct Semester {
    string name;
    Semester* pNext_Semester;
    Course* pCourse;
};
//main
struct Year {
    string name;
    Class* pClass;
    Year* pNext_Year;
    Semester* pSemester;
};
// Time
struct Time {
    int date;
    int month;
    int year;
    int hour;
    int minute;
};
struct Registration_Session {
    Time start;
    Time end;
};
Semester* find_semester(Semester* pSem, string name) {
    if (!pSem) return nullptr;
    while (pSem && pSem->name != name)
        pSem = pSem->pNext_Semester;
    return pSem;
}
void Create_Course(Semester* sem) {
    ifstream filein("course.csv");
    while (filein.eof() == false) {
        Course* pCur_Course = sem->pCourse;
        Course* add_Course = new Course;
        cout << "ID: ";
        getline(filein, add_Course->CourseID, ','); cout << add_Course->CourseID << " | ";
        cout << "Number of credits: ";
        getline(filein, add_Course->Number_of_Credits, ','); cout << add_Course->Number_of_Credits << " | ";
        cout << "Maximum number of students in Course: ";
        getline(filein, add_Course->Max_Student, ','); cout << add_Course->Max_Student << " | ";
        cout << "Course name: ";
        getline(filein, add_Course->Course_Name, ','); cout << add_Course->Course_Name << " | ";
        cout << "Teacher name: ";
        getline(filein, add_Course->Teacher_Name, ',');cout << add_Course->Teacher_Name << " | ";
        cout << "Day 1: ";
        getline(filein, add_Course->Day1, ','); cout << add_Course->Day1 << " | ";
        cout << "Session 1: ";
        getline(filein, add_Course->Session1, ','); cout << add_Course->Session1 << " | ";
        cout << "Day 2: ";
        getline(filein, add_Course->Day2, ','); cout << add_Course->Day2 << " | ";
        cout << "Session 2: ";
        getline(filein, add_Course->Session2, ','); cout << add_Course->Session2 << " | ";
        cout << "Start day: ";
        getline(filein, add_Course->Start_Day, ','); cout << add_Course->Start_Day << " | ";
        cout << "End day: ";
        getline(filein, add_Course->End_Day, '\n'); cout << add_Course->End_Day << endl << " | ";
        add_Course->pNext_Course = nullptr;

        if (sem->pCourse == NULL) sem->pCourse = add_Course;
        else {
            while (pCur_Course->pNext_Course != NULL) pCur_Course = pCur_Course->pNext_Course;
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
    if (pCourse->pNext_Course && pCourse->pNext_Course->Course_Name == name)
        return pCourse;
    else
        return nullptr;
}
void Delete_Course(Semester* sem) {
    string s;
    cout << "Course name: ";
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
void Create_Semester(Year*& year) {
    string name_semester;
    cout << "Import semester (ex: 1, 2, 3): ";
    cin >> name_semester;
    Semester* pCur_Semester = year->pSemester;

    Semester* Temp_Semester = new Semester;
    Temp_Semester->name = name_semester;
    Temp_Semester->pNext_Semester = NULL;
    Temp_Semester->pCourse = nullptr;

    if (year->pSemester == NULL)
        year->pSemester = Temp_Semester;
    else {
        while (pCur_Semester->pNext_Semester != NULL)
            pCur_Semester = pCur_Semester->pNext_Semester;
        pCur_Semester->pNext_Semester = Temp_Semester;
    }
}
Registration_Session create_Registration_Session() {
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
void Update_Course(Semester* sem) {
    string s = "";
    cout << "Course name: ";
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
void Print_Year(Year* year)
{
    if (year == NULL) {
        return;
    }
    Year* pCur_Year = year;
    while (pCur_Year != NULL)
    {
        cout << pCur_Year->name << " ";
        pCur_Year = pCur_Year->pNext_Year;
    }
    cout << endl;
}
void Print_Class(Year* year)
{
    Class* pCur_Class = year->pClass;
    while (pCur_Class != NULL)
    {
        cout << pCur_Class->name << " ";
        pCur_Class = pCur_Class->pNext_Class;
    }
    cout << endl;
}
void Print_Student(Class* classes)
{
    Student* pCur_Student = classes->pStudent;
    while (pCur_Student != NULL)
    {
        //No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID
        cout << "No." << pCur_Student->No << " | ";
        cout << pCur_Student->StudentID << " | ";
        cout << pCur_Student->FirstName << " | ";
        cout << pCur_Student->LastName << " | ";
        cout << pCur_Student->Gender << " | ";
        cout << pCur_Student->Date_of_Birth << " | ";
        cout << pCur_Student->SocialID << " \n";
        pCur_Student = pCur_Student->pNext_Student;
    }
    cout << endl;
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
void View_Student_In_Class(Year* year) {
    string inClass;
    string findYear = "";
    Year* pCurYear = NULL;
    bool exist = true;
    do {
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
        if (pCurYear == NULL) {
            cout << "Class does not exist.\n";
            exist = false;
        }
        else {
            Class* pCurClass = pCurYear->pClass;
            // find class
            while (pCurClass && pCurClass->name != inClass)
                pCurClass = pCurClass->pNext_Class;
            if (pCurClass == NULL) {
                cout << "Class does not exist.\n";
                exist = false;
            }
            else {
                cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tSocial ID\n";
                Student* pCurStudent = pCurClass->pStudent;
                while (pCurStudent) {
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
void View_Student_In_Course(Year* year) {
    string inYear = "";
    Year* pCurYear = NULL;
    bool exist;
    do {
        exist = true;
        cout << "Enter school year: ";
        cin >> inYear;

        if (inYear == "0")  // Enter 0 to stop
            return;

        pCurYear = year;
        while (pCurYear && pCurYear->name != inYear)
            pCurYear = pCurYear->pNext_Year;
        if (pCurYear == NULL) {
            cout << "School year does not exist.\n";
            exist = false;
        }
        else {
            string inSem = "";
            Semester* pCurSem = NULL;
            do {
                exist = true;
                cout << "Enter semester: ";
                cin >> inSem;

                if (inSem == "0")
                    return;

                pCurSem = pCurYear->pSemester;
                while (pCurSem && pCurSem->name != inSem)
                    pCurSem = pCurSem->pNext_Semester;
                if (pCurSem == NULL) {
                    cout << "Semester does not exist.\n";
                    exist = false;
                }
                else {
                    string inCourse = "";
                    Course* pCurCourse = NULL;
                    do {
                        exist = true;
                        cout << "Enter course ID: ";
                        cin >> inCourse;

                        if (inCourse == "0")
                            return;

                        pCurCourse = pCurSem->pCourse;
                        while (pCurCourse && pCurCourse->CourseID != inCourse)
                            pCurCourse = pCurCourse->pNext_Course;
                        if (pCurCourse == NULL) {
                            cout << "Course does not exist.\n";
                            exist = false;
                        }
                        else {
                            Student_Course* pCurStu = pCurCourse->pStudent_Course;
                            Student* pStuTemp = NULL;

                            cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of Birth\tSocial ID\n";
                            while (pCurStu) {
                                pStuTemp = pCurStu->pStudent;
                                cout << pStuTemp->No << '\t';
                                cout << pStuTemp->StudentID << '\t';
                                cout << pStuTemp->FirstName << '\t';
                                cout << pStuTemp->LastName << '\t';
                                cout << pStuTemp->Gender << '\t';
                                cout << pStuTemp->Date_of_Birth << '\t';
                                cout << pStuTemp->SocialID << '\n';

                                pCurStu = pCurStu->pNext_Student_Course;
                            }
                        }
                    } while (!exist);
                }
            } while (!exist);
        }
    } while (!exist);
}
void Create_Year(Year*& year) {
    string name_year;
    cout << "Import academic year (ex: 2021) ";
    cin >> name_year;
    Year* pCur_Year = year;

    Year* Temp_Year = new Year;
    Temp_Year->name = name_year;
    Temp_Year->pNext_Year = NULL;
    Temp_Year->pClass = NULL;
    Temp_Year->pSemester = NULL;

    if (year == NULL) year = Temp_Year;
    else {
        while (pCur_Year->pNext_Year != NULL) pCur_Year = pCur_Year->pNext_Year;
        pCur_Year->pNext_Year = Temp_Year;
    }
}
void Create_Class(Year*& year) {
    string name_class;
    cout << "Import class (ex:21CLC10) ";
    cin >> name_class;
    Class* pCur_Class = year->pClass;

    Class* Temp_Class = new Class;
    Temp_Class->name = name_class;
    Temp_Class->pNext_Class = NULL;
    Temp_Class->pStudent = NULL;

    if (year->pClass == NULL) year->pClass = Temp_Class;
    else {
        while (pCur_Class->pNext_Class != NULL) pCur_Class = pCur_Class->pNext_Class;
        pCur_Class->pNext_Class = Temp_Class;
    }
}
void Create_Student(Class*& classes) {

    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID

    ifstream filein("profile.csv");
    while (filein.eof() == false) {
        Student* pCur_Student = classes->pStudent;
        Student* Temp_Student = new Student;
        cout << "Import student: " << endl;
        cout << "No ";getline(filein, Temp_Student->No, ',');cout << Temp_Student->No << " | ";
        cout << "StudentID ";getline(filein, Temp_Student->StudentID, ',');cout << Temp_Student->StudentID << " | ";
        cout << "FirstName ";getline(filein, Temp_Student->FirstName, ',');cout << " " << setw(20) << left << Temp_Student->FirstName;
        cout << "LastName ";getline(filein, Temp_Student->LastName, ',');cout << " " << setw(15) << left << Temp_Student->LastName << " | ";
        cout << "Gender ";getline(filein, Temp_Student->Gender, ',');cout << setw(7) << left << Temp_Student->Gender << " | ";
        cout << "Date_of_Birth ";getline(filein, Temp_Student->Date_of_Birth, ',');cout << Temp_Student->Date_of_Birth << " | ";
        cout << "SocialID ";getline(filein, Temp_Student->SocialID, '\n');cout << Temp_Student->SocialID << endl;
        Temp_Student->pNext_Student = NULL;
        Temp_Student->pCur_Cour = NULL;

        if (classes->pStudent == NULL) classes->pStudent = Temp_Student;
        else {
            while (pCur_Student->pNext_Student != NULL) pCur_Student = pCur_Student->pNext_Student;
            pCur_Student->pNext_Student = Temp_Student;
        }
    }

    filein.close();
}
Year* Import_Year(Year* year) {
    if (year == NULL) return NULL;
    Year* pCur_Year;
    do {
        pCur_Year = year;
        string find_year;
        cout << "academic year to import class (ex: 2021) ";
        cin >> find_year;

        while (pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;

    } while (pCur_Year == NULL);
    return pCur_Year;
}
Class* Import_Class(Class* classes) {
    if (classes == NULL) return NULL;
    Class* pCur_class;
    do {
        pCur_class = classes;
        string find_class;
        cout << "class to import student (ex:21CLC10) ";
        cin >> find_class;
        while (pCur_class != NULL && find_class != pCur_class->name)
            pCur_class = pCur_class->pNext_Class;
    } while (pCur_class == NULL);
    return pCur_class;
}
Semester* Import_Semester(Semester* sem) {
    if (sem == NULL) return NULL;
    Semester* pCur_sem;
    do {
        pCur_sem = sem;
        string find_sem;
        cout << "semester to import student (ex: 1, 2, 3) ";
        cin >> find_sem;
        while (pCur_sem != NULL && find_sem != pCur_sem->name)
            pCur_sem = pCur_sem->pNext_Semester;
    } while (pCur_sem == NULL);
    return pCur_sem;
}
Student* find_student_in_1_class(Class* classes, string Student_ID){
    if(classes->pStudent == NULL) return NULL;
    Student* pCur_Student = classes->pStudent;
    
    while(pCur_Student != NULL && pCur_Student->StudentID != Student_ID)
        pCur_Student = pCur_Student->pNext_Student;

    if(pCur_Student != NULL) return pCur_Student;
    return NULL;
}
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
int convert_to_int(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++)
        res = res * 10 + (s[i] - '0');
    return res;
}
/*void Add_1_Student(Class* import_class, string student_id) {
    Student* pCur_Student = import_class->pStudent;
    Student* pNew_Student = new Student;
    pNew_Student->StudentID = student_id;
    
    cin.ignore(1000, '\n');
    cout<<"Enter last name: "; getline(cin, pNew_Student->LastName, '\n');
    cout<<"Enter first name: "; getline(cin, pNew_Student->FirstName, '\n');
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
}*/
bool Check_Cur_Course(Course* course_regis, Student* student) {
    Cur_Course* pCur = student->pCur_Cour;
    while (pCur != NULL) {
        if (pCur->Course_Name == course_regis->Course_Name) return false;
        else pCur = pCur->pNext_Cur_Cour;
    }
    return true;
}
bool Check_quantity(Student* student) {
    int count = 0;
    Cur_Course* pCur = student->pCur_Cour;
    while (pCur != NULL) {
        count++;
        pCur = pCur->pNext_Cur_Cour;
    }
    if (count <= 3) return true;
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
Cur_Course* Copy_Course(Course* course_regis) {
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
Student_Course* Copy_Student_Cour(Student* student) {
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

void View_Enrolled_Course(Student* student) {
    Cur_Course* pCur_Cour = new Cur_Course;
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
void Delete_Enrolled_Course(Student*& student, Course*& course) {
    Cur_Course* pCur1 = student->pCur_Cour;
    Student_Course* pCur2 = course->pStudent_Course;
    while (student->pCur_Cour == NULL || course->pStudent_Course == NULL) {
        cout << "You haven't enrolled this course yet!";
        cin.ignore();
        getchar();
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
//enroll main
void View_Enrolled_Course_main(Year*& year, Semester*& semester) {
    string studentID;
    cout << "Your student ID: ";
    cin >> studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if (student == NULL) {
        cout << "Student ID not found!" << endl;
        cin.ignore();
        getchar();
        return;
    }
    View_Enrolled_Course(student);
    cin.ignore();
    getchar();
}
void Delete_Enrolled_Course_main(Year*& year, Semester*& semester) {
    string studentID;
    cout << "Your studentID: ";
    cin >> studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if (student == NULL) {
        cout << "Student ID not found!" << endl;
        cin.ignore();
        getchar();
        return;
    }
    //view all course
    //View_Enrolled_Course(student);
    string course_name;
    cout << "Course you want to delete: ";
    cin >> course_name;
    Course* Del_Cour = find_course_in_many_subjects(semester, course_name);
    if (Del_Cour == NULL) {
        cout << "Course name not found!" << endl;
        cin.ignore();
        getchar();
        return;
    }
    Delete_Enrolled_Course(student, Del_Cour);
}
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
void Export_Course(Course* course) {
    Student_Course* stu_cour = course->pStudent_Course;
    ofstream fileout;
    int cnt = 1;
    string s = course->Course_Name;
    fileout.open(s + ".csv");
    fileout << "No" << "," << "ID" << "," << "Full name" << "," << "Total mark" << "," << "Final mark" << "," << "Midterm mark" << "," << "Other mark";
    while (stu_cour != nullptr) {
        fileout << endl;
        fileout << cnt++ << "," << stu_cour->StudentID << "," << stu_cour->FirstName + " " + stu_cour->LastName << stu_cour->mark.Total << "," << stu_cour->mark.Final << ","
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
        cin.ignore();
        getchar();
        return;
    }
    Export_Course(export_course);
}
Class* find_class_in_many_classes(Year* year, string class_name){
    if (year->pClass == NULL) return NULL;
    Class* pCur_Class = year->pClass;

    while(pCur_Class != NULL){
        if (pCur_Class->name == class_name) return pCur_Class;
        pCur_Class = pCur_Class->pNext_Class;
    }
    return NULL;
}
void View_Class_Scoreboard(Class* class_name, Course* course){
    cout << "Student ID\tFull Name\t   Midterm Mark\tFinal Mark\tOther Marks\tTotal mark" << endl;
    Student_Course* pStu_Cour = course->pStudent_Course;
    while (pStu_Cour != NULL){
        cout << pStu_Cour->StudentID << "\t" << pStu_Cour->FirstName + " " + pStu_Cour->LastName
        << "\t" << pStu_Cour->mark.Midterm << "\t   " << pStu_Cour->mark.Final << "\t   " << pStu_Cour->mark.Other << pStu_Cour->mark.Total << endl;
        pStu_Cour = pStu_Cour->pNext_Student_Course;
    }
}
void View_Class_Scoreboard_main(Year*& year, Semester*& semester){
    string class_name;
    cout << "Class you want to view scoreboard: ";
    cin >> class_name;
    string course_name;
    cout << "Course you want to view in " << class_name << endl;
    cin >> course_name;
    Class* class_check = find_class_in_many_classes(year, class_name);
    Course* course_check = find_course_in_many_subjects(semester, course_name);
    if (class_check != find_class_in_many_classes(year, class_name)){
        cout << "Class name not found!" << endl;
        cin.ignore();
        getchar();
        return;
    }
    View_Class_Scoreboard(class_check, course_check);
    cin.ignore();
    getchar();
}

void Student_View_Scoreboard(Student* student, Course* course){
    Cur_Course* pCur = student->pCur_Cour;
    Student_Course* pStu_Cour = course->pStudent_Course;
    if(pStu_Cour == NULL){
        cout << "The staff member haven't inputted your scores yet!" << endl;
    }
    cout << "Midterm mark\tFinal mark\tOther\tTotal" << endl;
    while(pStu_Cour != NULL && pCur != NULL){
            cout << "\t" << pStu_Cour->mark.Midterm << "\t\t" << pStu_Cour->mark.Final << "\t"
            << pStu_Cour->mark.Other << "\t" << pStu_Cour->mark.Total << endl;
            pStu_Cour = pStu_Cour->pNext_Student_Course;
        }    
}
void Student_View_Scoreboard_main(Year*& year, Semester*& semester) {
    string studentID;
    cout << "Your student ID: ";
    cin >> studentID;
    string course_name;
    cout << "Course you want to choose: ";
    cin >> course_name;
    Student* student = find_student_in_many_classes(year, studentID);
    Course* course = find_course_in_many_subjects(semester, course_name);
    if (student == NULL || course == NULL) {
        cout << "Student ID not found!" << endl;
        cin.ignore();
        getchar();
        return;
    }
    Student_View_Scoreboard(student, course);
    cin.ignore();
    getchar();
}
void Interface(Year*& year) {
    int choose_1;
    do {
    HOME:
        system("cls");
        cout << "1.Home" << endl;
        cout << "2.Log out" << endl;
        cout << "->Enter choose ";cin >> choose_1;
        if (choose_1 == 1) {

            int choose_2;
            do {
            valid_year:
                system("cls");
                cout << "--------YEARS LIST--------" << endl;
                Print_Year(year);
                cout << "--------------------------" << endl;
                cout << "1.Create year" << endl;
                cout << "2.Choose year to view classes" << endl;
                cout << "3.Choose year to view semesters" << endl;
                cout << "4.Home" << endl;
                cout << "5.Return" << endl;
                cout << "->Enter choose "; cin >> choose_2;

                if (choose_2 == 1) {
                    system("cls");
                    Print_Year(year);

                    Create_Year(year);
                }

                if (choose_2 == 2) {
                    system("cls");
                    Print_Year(year);

                    int choose_3;
                    Year* import_year = Import_Year(year);

                    if (import_year == NULL) {
                        cout << "no years was created ";
                        cin.ignore();
                        getchar();
                        goto valid_year;
                    }
                    do {
                    valid_class:
                        system("cls");
                        cout << "--------CLASSES LIST--------" << endl;
                        Print_Class(import_year);
                        cout << "----------------------------" << endl;
                        cout << "1.Create class" << endl;
                        cout << "2.Choose class to view student" << endl;
                        cout << "3.Home" << endl;
                        cout << "4.Return" << endl;
                        cout << "->Enter choose "; cin >> choose_3;
                        if (choose_3 == 1) {
                            system("cls");
                            Print_Class(import_year);

                            Create_Class(import_year);
                        }
                        if (choose_3 == 2) {
                            system("cls");
                            Print_Class(import_year);

                            int choose_4;
                            Class* import_class = Import_Class(import_year->pClass);

                            if (import_class == NULL) {
                                cout << "no classes was created ";
                                cin.ignore();
                                getchar();
                                goto valid_class;
                            }
                            do {
                                system("cls");
                                cout << "--------STUDENTS LIST--------" << endl;
                                Print_Student(import_class);
                                cout << "-----------------------------" << endl;
                                cout << "1.Create student" << endl;
                                cout << "2.Home" << endl;
                                cout << "3.Return" << endl;
                                cout << "->Enter choose "; cin >> choose_4;
                                if (choose_4 == 1) {
                                    system("cls");
                                    Print_Student(import_class);
                                    Create_Student(import_class);
                                }
                                else if (choose_4 == 2) goto HOME;

                            } while (choose_4 != 3);
                        }
                        if (choose_3 == 3) goto HOME;

                    } while (choose_3 != 4);
                }
                else if (choose_2 == 3) {
                    system("cls");
                    Print_Year(year);

                    int choose_3;
                    Year* import_year = Import_Year(year);

                    if (import_year == NULL) {
                        cout << "no years was created ";
                        cin.ignore();
                        getchar();
                        goto valid_year;
                    }
                    do {
                    valid_semester:
                        system("cls");
                        cout << "--------SEMESTERS LIST--------" << endl;
                        Print_Semester(import_year);
                        cout << "------------------------------" << endl;
                        cout << "1.Create semester" << endl;
                        cout << "2.Choose semester to view courses" << endl;
                        cout << "3.Home" << endl;
                        cout << "4.Return" << endl;
                        cout << "->Enter choose "; cin >> choose_3;
                        if (choose_3 == 1) {
                            system("cls");
                            Print_Semester(import_year);
                            Create_Semester(import_year);
                        }
                        if (choose_3 == 2) {
                            system("cls");
                            Print_Semester(import_year);

                            int choose_4;
                            Semester* import_sem = Import_Semester(import_year->pSemester);

                            if (import_sem == NULL) {
                                cout << "no semesters was created ";
                                cin.ignore();
                                getchar();
                                goto valid_semester;
                            }
                            do {
                                system("cls");
                                cout << "--------COURSES LIST---------" << endl;
                                Print_Course(import_sem);
                                cout << "-----------------------------" << endl;
                                cout << "1.Create course" << endl;
                                cout << "2.Update course" << endl;
                                cout << "3.Delete course" << endl;
                                cout << "4.Home" << endl;
                                cout << "5.Return" << endl;
                                cout << "6.Enroll" << endl;
                                cout << "7.View enrolled course" << endl;
                                cout << "8.Delete enrolled course" << endl;
                                cout << "9.Export student list in a course" << endl;
                                cout << "10.View a class's scoreboard" << endl;
                                cout << "11.Student views his/her scoreboard" << endl;
                                cout << "12.Input mark" << endl;
                                cout << "13.View scoreboard of a course" << endl;
                                cout << "->Enter choose "; cin >> choose_4;
                                if (choose_4 == 1) {
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
                                else if (choose_4 == 6) {
                                    system("cls");
                                    Print_Course(import_sem);
                                    enroll_main(import_year, import_sem);
                                }
                                else if (choose_4 == 7) {
                                    system("cls");
                                    View_Enrolled_Course_main(import_year, import_sem);
                                }
                                else if (choose_4 == 8) {
                                    system("cls");
                                    Delete_Enrolled_Course_main(import_year, import_sem);
                                }
                                else if (choose_4 == 9) {
                                    system("cls");
                                    Export_Course_main(import_year, import_sem);
                                }
                                else if (choose_4 == 10){
                                    system("cls");
                                    View_Class_Scoreboard_main(import_year, import_sem);
                                }
                                else if (choose_4 == 11){
                                    system("cls");
                                    Student_View_Scoreboard_main(import_year, import_sem);
                                }
                                else if (choose_4 == 12){
                                    system("cls");
                                    Create_mark_main(import_year, import_sem);
                                }
                                else if (choose_4 == 13){
                                    system("cls");
                                    View_scoreboard_main(import_sem);
                                }
                                if (choose_4 == 4) goto HOME;
                            } while (choose_4 != 5);
                        }
                        if (choose_3 == 3) goto HOME;
                    } while (choose_3 != 4);
                }
                if (choose_2 == 4) goto HOME;
            } while (choose_2 != 5);
        }
    } while (choose_1 != 2);
}
int main() {
    Year* year = NULL;
    //test(year);

    Interface(year);
}