// #include<iostream>
// #include<cstring>
// #include <iomanip>
// #include <fstream>
#include<bits/stdc++.h>
using namespace std; 

#define nullptr 0
//right
struct Mark{ // new
    double Total = 0, Final = 0, Midterm = 0, Other = 0;
};
struct Temp_Course{ //new
    string CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
    string Start_Day, End_Day;
    Mark mark;
};
struct Cur_Course{ //new
    Cur_Course* pNext_Cur_Cour;
    Temp_Course* pTemp_Cour;
};
struct Student{
    //No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
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

        if(sem->pCourse == NULL) sem->pCourse = add_Course;
        else{
            while(pCur_Course->pNext_Course != NULL) pCur_Course = pCur_Course->pNext_Course;
            pCur_Course->pNext_Course = add_Course;
        }
          
    }
    filein.close();
    
}

/*
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
    cin.ignore(1000, '\n');
    getline(cin, s, '\n');
    Subject* Sub = find_Subject(sem->pSubject, s);
    while (!Sub) {
        cout << "Subject not found! Try again: ";
        cin.ignore(1000, '\n');
        getline(cin, s, '\n');
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
    ifstream filein("course.csv");
    while(filein.eof() == false){
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
    }
    filein.close();
    add_Course->pNext_Course = nullptr;
}
*/

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
    Temp_Semester->pCourse = nullptr;

    if (pCur_Year->pSemester == NULL)
        pCur_Year->pSemester = Temp_Semester;
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
    if (cur_course == nullptr || cur_course->pTemp_Cour == nullptr)
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
        while (cur_course->pTemp_Cour != NULL) {
            cout << setw(5) << left << cur_course->pTemp_Cour->CourseID;
            cout << setw(10) << left << cur_course->pTemp_Cour->Number_of_Credits;
            cout << setw(10) << left << cur_course->pTemp_Cour->Max_Student;
            cout << setw(20) << left << cur_course->pTemp_Cour->Course_Name;
            cout << setw(20) << left << cur_course->pTemp_Cour->Teacher_Name;
            s = cur_course->pTemp_Cour->Day1; s += " "; s += cur_course->pTemp_Cour->Session1;
            cout << setw(20) << left << s;
            cout << setw(15) << left << cur_course->pTemp_Cour->Start_Day;
            cout << setw(15) << left << cur_course->pTemp_Cour->End_Day;
            s = cur_course->pTemp_Cour->Day2; s += " "; s += cur_course->pTemp_Cour->Session2;
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
void View_Student_In_Course(Year *year){
	string inYear = "";
	Year *pCurYear = NULL;
	bool exist;
	do{
		exist = true;
		cout << "Enter school year: ";
		cin >> inYear;
		
		if (inYear == "0")  // Enter 0 to stop
			return;
		
		pCurYear = year;
		while (pCurYear && pCurYear->name != inYear)
			pCurYear = pCurYear->pNext_Year;
		if (pCurYear == NULL){
			cout << "School year does not exist.\n";
			exist = false;
		}
		else{
			string inSem = "";
			Semester *pCurSem = NULL;
			do{
				exist = true;
				cout << "Enter semester: ";
				cin >> inSem;
				
				if (inSem == "0")
					return;
				
				pCurSem = pCurYear->pSemester;
				while (pCurSem && pCurSem->name != inSem)
					pCurSem = pCurSem->pNext_Semester;
				if (pCurSem == NULL){
					cout << "Semester does not exist.\n";
					exist = false;
				}
				else{
					string inCourse = "";
					Course *pCurCourse = NULL; 
					do{
						exist = true;
						cout << "Enter course ID: ";
						cin >> inCourse;
						
						if (inCourse == "0")
							return;
						
						pCurCourse = pCurSem->pCourse;
						while (pCurCourse && pCurCourse->CourseID != inCourse)
							pCurCourse = pCurCourse->pNext_Course;
						if (pCurCourse == NULL){
							cout << "Course does not exist.\n";
							exist = false;
						}
						else{
							Student_Course *pCurStu = pCurCourse->pStudent_Course;
							Student *pStuTemp = NULL;
							
							cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of Birth\tSocial ID\n";
							while (pCurStu){
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
void Create_Year(Year* &year){
    string name_year;
    cout<<"Import academic year (ex: 2021) ";
    cin >> name_year;
    Year* pCur_Year = year;

    Year* Temp_Year = new Year;
    Temp_Year->name = name_year;
    Temp_Year->pNext_Year = NULL;
    Temp_Year->pClass = NULL;
    Temp_Year->pSemester = nullptr;

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

    if(year->pClass == NULL) year->pClass = Temp_Class;
    else{
        while(pCur_Class->pNext_Class != NULL) pCur_Class = pCur_Class->pNext_Class;
        pCur_Class->pNext_Class = Temp_Class;
    }
}
void Create_Student(Class *classes){

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

/*
bool Check_Cur_Course(Course* course_regis,Student* student){
    Cur_Course* pCur = student->pCur_Cour;
    while(pCur != NULL){
        if(pCur->pTemp_Cour->Course_Name == course_regis->Course_Name) return false;
        else pCur = pCur->pNext_Cur_Cour;
    }
    return true;
}

//CourseID, Course_Name, Teacher_Name, Number_of_Credits, Max_Student, Day1, Session1, Day2, Session2;
// Start_Day, End_Day;


//enroll
Temp_Course* Copy_Course(Course* course_regis){
    Temp_Course* Temp_Cour;
    Temp_Cour->CourseID = course_regis->CourseID;
    Temp_Cour->Course_Name = course_regis->Course_Name;
    Temp_Cour->Teacher_Name = course_regis->Teacher_Name;
    Temp_Cour->Number_of_Credits = course_regis->Number_of_Credits;
    Temp_Cour->Max_Student = course_regis->Max_Student;
    Temp_Cour->Day1 = course_regis->Day1;
    Temp_Cour->Session1 = course_regis->Session1;
    Temp_Cour->Day2 = course_regis->Day2;
    Temp_Cour->Session2 = course_regis->Session2;
    Temp_Cour->Start_Day = course_regis->Start_Day;
    Temp_Cour->End_Day = course_regis->End_Day;
    return Temp_Cour;
}
void Enroll_Course(Course* course_regis, Student* student){
    if(Check_Cur_Course(course_regis,student) == true){
        //add course into cur_course
        Temp_Course* Temp_Cour = Copy_Course(course_regis);

        Cur_Course* cur_course = new Cur_Course;
        cur_course->pNext_Cur_Cour = NULL;
        cur_course->pTemp_Cour = NULL;
        Cur_Course* pCur = student->pCur_Cour;

        if(student->pCur_Cour == NULL){
            student->pCur_Cour = cur_course;
            student->pCur_Cour->pTemp_Cour = Temp_Cour;
        }
        else{
            while(pCur->pNext_Cur_Cour != NULL) pCur = pCur->pNext_Cur_Cour;
            pCur->pNext_Cur_Cour = cur_course;
            pCur->pNext_Cur_Cour->pTemp_Cour = Temp_Cour;
        }
        //add inf SV into student_course
        Student_Course* Student_cour = new Student_Course;
        Student_Course* pCur_Student_cour = course_regis->pStudent_Course;
        if(course_regis->pStudent_Course == NULL) course_regis->pStudent_Course = Student_cour;
        else {
            while(pCur_Student_cour->pNext_Student_Course != NULL)
                pCur_Student_cour = pCur_Student_cour->pNext_Student_Course;
            pCur_Student_cour->pNext_Student_Course->pStudent = student;
        }

    } else cout<<"This subject has been registering\n";
    
    //else
    //da hoc , da dki cout<<thong bao
    // khi doi hoc ki dua vao chuc nang thay doi time he thong thi luc do cur->stu
    //** khi enroll thi dua inf sv vao course_student
}

// find student
Student* find_student_in_1_class(Class* classes, string StudentID){
    if(classes->pStudent == NULL) return NULL;
    Student* pCur_Student = classes->pStudent;
    
    while(pCur_Student != NULL && pCur_Student->StudentID == StudentID)
        pCur_Student = pCur_Student->pNext_Student;

    if(pCur_Student != NULL) return pCur_Student;
    return NULL;
}
Student* find_student_in_many_classes(Year* year, string StudentID){
    if(year->pClass == NULL) return NULL;
    Class* pCur_Class = year->pClass;

    while(pCur_Class != NULL){
        Student* temp = find_student_in_1_class(pCur_Class,StudentID);
        if(temp != NULL) return temp;
        pCur_Class = pCur_Class->pNext_Class;
    }
    return NULL;
}
//find course
Course* find_course_in_1_subject(Subject* subject, string course){
    if(subject->pCourse == NULL) return NULL;
    Course* pCur_Course = subject->pCourse;
    
    while(pCur_Course != NULL && pCur_Course->Course_Name == course)
        pCur_Course = pCur_Course->pNext_Course;

    if(pCur_Course != NULL) return pCur_Course;
    return NULL;
}
Course* find_course_in_many_subjects(Semester* semester, string course){
    if(semester->pSubject == NULL) return NULL;
    Subject* pCur_Subject = semester->pSubject;

    while(pCur_Subject != NULL){
        Course* temp = find_course_in_1_subject(pCur_Subject,course);
        if(temp != NULL) return temp;
        pCur_Subject = pCur_Subject->pNext_Subject;
    }
    return NULL;
}
//enroll main
void enroll_main(Year* &year, Semester* &semester, string StudentID){
    Student* student = find_student_in_many_classes(year, StudentID);
    
    //view all course
    string course_name;
    cout<<"Course you want to choose "; cin>>course_name;
    Course* course_regis = find_course_in_many_subjects(semester,course_name);
    Enroll_Course(course_regis,student);
}
*/

void Interface(Year* &year){
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
                                // else if (choose_4 == 6){
                                //     //string studentID;
                                //     //cout<<"StudentID "<<studentID;
                                //     //enroll_main(import_year,import_sem,studentID);
                                // }
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
int main(){
    Year* year = NULL;
    //test(year);

    Interface(year);
}
