#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;

#define nullptr 0
// color
#define _ERROR 4
#define SUCCESS 14
#define NORMAL 11
#define BOX 11


extern int HOME;
extern int LOG_OUT;
//right
struct Mark{ // new
    double Total = 0, Final = 0, Midterm = 0, Other = 0;
};
struct Cur_Course{ //new
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Mark mark;      
    Cur_Course* pNext_Cur_Cour = nullptr;
    //Temp_Course* pTemp_Cour;
};
struct Student{
    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    double GPA = 0;  // new
    Student* pNext_Student = nullptr;
    Cur_Course* pCur_Cour = nullptr;
};
struct Class{
    string name;
    Student* pStudent = nullptr;
    Class* pNext_Class = nullptr;
};
//left
struct Student_Course{
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    Mark mark;
    Student_Course* pNext_Student_Course = nullptr;
};
struct Course{
    //Course id, Course name, teacher name, number of credits, 
    //the maximum number of students (default 50), day, and the session
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Course* pNext_Course = nullptr;
    Student_Course* pStudent_Course = nullptr;
};
struct Semester{
    string name;
    Semester* pNext_Semester = nullptr;
    Course* pCourse = nullptr;
};
//main
struct Year{
    string name;
    Class* pClass = nullptr;
    Year* pNext_Year = nullptr;
    Semester* pSemester = nullptr;
};
// Time
struct Time{
    int date, month, year, minute, hour;
};
struct Registration_Session{
    Time start = {20,3,2022,0,0};
    Time end = {30,4,2022,0,0};
};
struct Account{
    string username, password;
    Account *next = nullptr;
};
struct User{ // new
// hold current user
// Purpose: avoid a user change another user's password
    string username;
    string password;
};
struct Staff{
    string Email;
    string Full_name;
    string Gender;
    string Birth_of_date;
    string Social_ID;
    Staff* pNext_Staff = nullptr;
};

void Nocursortype();
void gotoxy(SHORT posX, SHORT posY);
void Textcolor(int x);
int convert_to_int(string s);
Semester* find_semester(Semester* pSem, string name);
int count_sem(string student_id);
bool check_empty(ifstream& fin);
bool isStaff(string username);
bool account_check(Account *head, User U);
Account *load_account_list();
void save_account_list(Account *head);
void delete_account_list(Account *&head);
void change_password(Account *head, User U);
// calculate overall GPA
void calcu_oGPA(Year* year, Student* student);
void calcu_oGPA_main(Year* year);
// create account
void Create_Account_For_new_Student(string student_id, Account* account_head);
void Create_Course(Year* year, Semester* sem);
void Print_Course(Year* year, Semester* sem);
Course* find_Course(Course* pCourse, string name);
// find student
Student* find_student_in_1_class(Class* classes, string Student_ID);
Student* find_student_in_many_classes(Year* year, string Student_ID);
// find student in course
Student_Course* find_student_in_a_course(Course* cour, string Student_ID);
Course* find_course_in_many_subjects(Semester* semester, string course);
void Delete_Course(Semester* sem);
bool semExists(Year* year, string findSem);
void Create_Semester(Year *&year);
void create_Registration_Session(Registration_Session &S);
bool Check_Regis_Time(Registration_Session S);
void Update_Course(Semester* sem);
void Print_Year(Year *year);
void Print_Class(Year *year);
void Print_Student(Class *classes);
void Print_Semester(Year* year);
void Print_Cur_Course(Cur_Course* cur_course);

//20
void View_Student_In_Course(Semester* sem);
void View_Enrolled_Course(Year* year, Student* student);
void View_Enrolled_Course_main(Year*& year, string studentID);
void Delete_Enrolled_Course(Student*& student, Course*& course);
void Delete_Enrolled_Course_main(Year*& year, Semester*& semester, string studentID,Registration_Session &S);
bool yearExists(Year *year, string findYear);
void Create_Year(Year* &year);
bool classExists(Year* year, string findClass);
void Create_Class(Year* &year);

Year* Import_Year(Year* year);
Class* Import_Class(Class* classes);
Semester* Import_Semester(Semester* sem);

void Create_Student(Year* year, Class *&classes, Account* account_head);
//convert_to_int
void Add_1_Student(Class* import_class, string student_id);
void Add_1_Student_main(Year* year,Class *&classes, Account* account_head);

//check enroll
bool Check_Cur_Course(Course* course_regis,Student* student);
bool Check_quantity(Student* student);
bool Check_Session(Course* course_regis,Student* student);
//enroll
Cur_Course* Copy_Course(Course* course_regis);
//No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
Student_Course* Copy_Student_Cour(Student* student);
void Enroll_Course(Course* &course_regis, Student* &student);

//enroll main
void enroll_main(Year* &year, Semester* &semester,string studentID,Registration_Session &S);

//22
double rand_mark();
void Assign_Mark(Year* year,string course_id, string Student_ID, double total, double final, double mid, double other);
void Create_Mark(Year* year, Semester* sem, Course* cour);

double convert_to_double(string s);
void Import_Scoreboard(Year* year, Course* cour);
void View_Score_Board(Course *cour);
// mark main & scoreboard in a course main 
void Create_mark_main(Year* year,Semester* sem);
//23
void View_scoreboard_main(Semester* sem);
//22 export
void Export_Course(Year* year, Semester* sem, Course* course);
void Export_Course_main(Year*& year, Semester*& semester);

//24
void update_student_result(Year* &year, Semester* &sem);
//25
void View_Class_Scoreboard_main(Class* classes);
//26
void Student_View_Scoreboard(Year* year, string studentID);
void delete_cur_course(Student* &student);
void delete_student(Class* &classes);
void delete_student_cour(Course* &course);
void delete_course(Semester* &sem);
void delete_all_node(Year* &year);
void del_cur_course_last_sem(Year* &year);
// Load data
Class* find_class(Year* year, string name);
Year* load_year(Year* &year, string name);
Course* load_course(Semester* sem, ifstream &fin);
void load_student_cur_course(Year* year, string StudentID, Course* course, Mark mark);
void load_student_in_course(string No, ifstream &fin, Course* course, Year* year);
void load_course_and_student(Year* year, Semester* sem);
void load_semester(Year* year, ifstream &fin);
void load_student(Class* _class, ifstream &fin);
void load_class(Year* year);
void load_regis_time(Registration_Session &S);
void load_main(Year* &year, Registration_Session &S);
//Save
void save_course(Year* year, Semester* sem);
void save_course_main(Year* year);
void save_year_semester(Year* year);
void save_class_student(Year* year, Class* _class);
void save_class_student_main(Year* year);
// copy class and student
void copy_file(Year* year1, Year* year2);
void copy_class_student(Year* year1, Year* year2);

// not add button of profile
// view profile
void Staff_profile(Staff* &staff);
void output_staff(Staff* staff, string username);
//No, StudentID, Fullname, Gender, Date_of_Birth, SocialID
void Student_profile(Year* year,string username);


//logo portal
void logo_portal(int x,int y);
//new
void box(int x,int y,int width, int height, int textcolor,int bcolor ,string text);

//staff
void COURSE_PAGE(Year* &year,Semester* &sem,int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[],Registration_Session &S);
void SEMESTER_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string SEMESTER_name_list_of_boxs[],Registration_Session &S);


void STUDENT_PAGE(Year* &year,Class* &classes, Account* account_head, int locate_x, int locate_y, int number_of_cells, string STUDENT_name_list_of_boxs[]);
void CLASS_PAGE(Year* &year, Account* account_head, int locate_x, int locate_y, int number_of_cells, string CLASS_name_list_of_boxs[]);
void YEAR_PAGE(Year* &year, Account* account_head, int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[],Registration_Session &S);

// student
void COURSE_STU_PAGE(Year* &year,Semester* &sem, User U, int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[],Registration_Session &S);
void SEMESTER_STU_PAGE(Year* &year, User U, int locate_x, int locate_y, int number_of_cells, string SEMESTER_STU_name_list_of_boxs[],Registration_Session &S);
void YEAR_STU_PAGE(Year* &year, User U, int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[],Registration_Session &S);

void CHANGE_PASS_PAGE(Year* &year, Account* account_head, User &U, int locate_x,int locate_y, int number_of_cells, string CHANGE_PASS_name_list_of_boxs[],Registration_Session &S, Staff* &staff);
void LOGIN_PAGE(Year* &year, Account* account_head, User U, int locate_x,int locate_y, int number_of_cells, string LOGIN_name_list_of_boxs[],Registration_Session &S, Staff* &staff);

#endif
