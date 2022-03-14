#include "header.h"

Subject* find_Subject(Subject *pSubject, string Subject_name) {
    if (!pSubject) return nullptr;
    while (pSubject && pSubject->name != Subject_name) 
        pSubject = pSubject->pNext_Subject;
    return pSubject;
}

Semester* find_semester(Year* year, string name) {
    if (!year) return nullptr;
    while (year && year->pSemester->name != name)
        year = year->pNext_Year;
    return year->pSemester;
}
Course* find_Course(Course* pCourse, string ID){
    if (!pCourse)
        return nullptr;
    
    while (pCourse && pCourse->CourseID != ID)
        pCourse = pCourse->pNext_Course;
    if(!pCourse)
        return nullptr;
    else if (pCourse->CourseID == ID)
        return pCourse;
}

void add_Course(Year* year) { 
    string s;
    cout << "Semester: ";
    cin >> s;
    Semester* sem = find_semester(year, s);
    while (!sem) {
        cout << "Semester not found! Try again: ";
        cin >> s;
        sem = find_semester(year, s);
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

void view_list_Courses(Year* year) {
    string s;
    cout << "Semester: ";
    cin >> s;
    Semester* sem = find_semester(year, s);
    while (!sem) {
        cout << "Semester not found! Try again: ";
        cin >> s;
        sem = find_semester(year, s);
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
    while (Sub->pCourse) {
        cout << setw(5) << left << Sub->pCourse->CourseID;
        cout << setw(10) << left << Sub->pCourse->Number_of_Credits;
        cout << setw(10) << left << Sub->pCourse->Max_Student;
        cout << setw(20) << left << Sub->pCourse->Course_Name;
        cout << setw(20) << left << Sub->pCourse->Teacher_Name;
        s = Sub->pCourse->Day1; s += Sub->pCourse->Session1;
        cout << setw(10) << left << s;
        cout << setw(7) << left << Sub->pCourse->Start_Day;
        cout << setw(7) << left << Sub->pCourse->End_Day;
        s = Sub->pCourse->Day2; s += Sub->pCourse->Session2;
        cout << endl << setw(75) << left << s << endl;
        Sub->pCourse = Sub->pCourse->pNext_Course;
    }
}

void add_Subject(Year* year) {
    string s;
    cout << "Semester: ";
    cin >> s;
    Semester* sem = find_semester(year, s);
    while (!sem) {
        cout << "Semester not found! Try again: ";
        cin >> s;
        sem = find_semester(year, s);
    }
    Subject* add_Subject = nullptr;
    if (!sem->pSubject) add_Subject = sem->pSubject;
    else {
        while (sem->pSubject->pNext_Subject) sem->pSubject = sem->pSubject->pNext_Subject;
        sem->pSubject->pNext_Subject = new Subject;
        add_Subject = sem->pSubject->pNext_Subject;
    }
    cout << "Enter the following detail: " << endl;
    cout << "Subject name: ";
    cin >> add_Subject->name;
    add_Subject->pCourse = nullptr;
    add_Subject->pNext_Subject = nullptr;

}

void delete_Course(Year* year){
    string s;
    cout << "Semester: ";
    cin >> s;
    Semester* sem = find_semester(year, s);
    while (!sem) {
        cout << "Semester not found! Try again: ";
        cin >> s;
        sem = find_semester(year, s);
    }
    cout << "Subject: ";
    cin >> s;
    Subject* Sub = find_Subject(sem->pSubject, s);
    while (!Sub) {
        cout << "Subject not found! Try again: ";
        cin >> s;
        Sub = find_Subject(sem->pSubject, s);
    }  
    cout << "Course ID: " ;
    cin >> s;
    Course* cour = find_Course(year->pSemester->pSubject->pCourse, s);
    while (!cour || (cour->CourseID != s && !cour->pNext_Course)) {
        cout << "Course not found! Try again: ";
        cin >> s;
        cour = find_Course(year->pSemester->pSubject->pCourse, s);
    }
    if (cour->CourseID == s) {
        Course** tmp = &(year->pSemester->pSubject->pCourse);
        Course* pDel = cour;
        (*tmp) = (*tmp)->pNext_Course;
        delete pDel;
    }
    else {
        Course* pDel = cour->pNext_Course;
        cour->pNext_Course = cour->pNext_Course->pNext_Course;
    }
    cout << "Deleted!" << endl;
}

void create_Semester(Year *year){
    Year *pCur_Year;
    string find_year;
    do{
        pCur_Year = year;
        cout << "academic year to import semester (ex:2020-2021): ";
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

    cout << "End time: \n";
    cout << "Date: ";
    cin >> S.end.date;
    cout << "Month: ";
    cin >> S.end.month;
    cout << "Year: ";
    cin >> S.end.year;

    return S;
}

// only able to update course for latest semester
void Update_Course(Year *year){
	while (year->pNext_Year)
		year = year->pNext_Year;
	Semester *pCurSem = year->pSemester;
	while (pCurSem->pNext_Semester)
		pCurSem = pCurSem->pNext_Semester;
	
	
	bool exist = true;
	Subject *pCurSub = NULL;
	string inSub = "";
	do{
		exist = true;
		cout << "Enter subject: ";
		cin >> inSub;
		
		if (inSub == "0")
			return;
		
		pCurSub = pCurSem->pSubject;
		// find subject
		while (pCurSub && pCurSub->name != inSub)
			pCurSub = pCurSub->pNext_Subject;
		if (pCurSub == NULL){
			cout << "Subject does not exist.\n";
			exist = false;
		}
		else{
			exist = true;
			string inCourse;
			Course *pCurCourse = NULL; ////////
			do{
				cout << "Enter course ID: ";
				cin >> inCourse;
				if (inCourse == "0")
					return;
				
				pCurCourse = pCurSub->pCourse;
				// find course
				while (pCurCourse && pCurCourse->CourseID != inCourse)
					pCurCourse = pCurCourse->pNext_Course;
				if (pCurCourse == NULL){
					cout << "Course does not exist.\n";
					exist = false;
				}
				else{
					cout << "Update the following information: \n";
					cout << "Course ID: "; cin >> pCurCourse->CourseID; 
					cout << "Course name: "; cin >> pCurCourse->Course_Name;
					cout << "Teacher name: "; cin >> pCurCourse->Teacher_Name;
					cout << "Number of credits: "; cin >> pCurCourse->Number_of_Credits;
					cout << "Maximum students: "; cin >> pCurCourse->Max_Student;
					cout << "Start day: "; cin >> pCurCourse->Start_Day;
					cout << "End day: "; cin >> pCurCourse->End_Day;
					cout << "Day 1: "; cin >> pCurCourse->Day1;
					cout << "Session 1: "; cin >> pCurCourse->Session1;
					cout << "Day 2: "; cin >> pCurCourse->Day2;
					cout << "Session 2: "; cin >> pCurCourse->Session2;
				}
			}while (!exist);
		}
	}while (!exist);
}

void Print_Year(Year *year)
{
    if(year == NULL) {
        return;
    }
    Year *pCur_Year = year;
    while (pCur_Year != NULL)
    {
        cout << pCur_Year->name << " ";
        pCur_Year = pCur_Year->pNext_Year;
    }
    cout<<endl;
}
void Print_Class(Year *year)
{
    Year* pCur_Year;
    do{
        pCur_Year = year;
        string find_year;
        cout<<"academic year export (ex:2020-2021) ";
        cin>>find_year;
        
        while(pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;

    }while(pCur_Year == NULL);

    if(pCur_Year->pClass == NULL) {
        return;
    }
    Class *pCur_Class = pCur_Year->pClass;
    while (pCur_Class != NULL)
    {
        cout << pCur_Class->name << " ";
        pCur_Class = pCur_Class->pNext_Class;
    }
    cout<<endl;
}
void Print_Student(Year *year){
    Year* pCur_Year;
    do{
        pCur_Year = year;
        string find_year;
        cout<<"academic year export (ex:2020-2021) ";
        cin>>find_year;
        
        while(pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;

    }while(pCur_Year == NULL);

    Class* pCur_Class;
    do{
        pCur_Class = pCur_Year->pClass;
        string find_class;
        cout<<"class export (ex:21CLC10) ";
        cin>>find_class;
        
        while(pCur_Class != NULL && find_class != pCur_Class->name)
            pCur_Class = pCur_Class->pNext_Class;

    }while(pCur_Class == NULL);

    if(pCur_Class->pStudent == NULL) {
        return;
    }
    Student *pCur_Student = pCur_Class->pStudent;
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
void Create_Year(Year* &year){
    string name_year;
    cout<<"Import academic year (ex:2020-2021) ";
    cin >> name_year;
    Year* pCur_Year = year;

    Year* Temp_Year = new Year;
    Temp_Year->name = name_year;
    Temp_Year->pNext_Year = NULL;
    Temp_Year->pClass = NULL;

    if(year == NULL) year = Temp_Year;
    else{
        while(pCur_Year->pNext_Year != NULL) pCur_Year = pCur_Year->pNext_Year;
        pCur_Year->pNext_Year = Temp_Year;
    }
}
void Create_Class(Year* &year){
    Year* pCur_Year;
    do{
        pCur_Year = year;
        string find_year;
        cout<<"academic year to import class (ex:2020-2021) ";
        cin>>find_year;
        
        while(pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;

    }while(pCur_Year == NULL);

    string name_class;
    cout<<"Import class (ex:21CLC10) ";
    cin >> name_class;
    Class* pCur_Class = pCur_Year->pClass;

    Class* Temp_Class = new Class;
    Temp_Class->name = name_class;
    Temp_Class->pNext_Class = NULL;

    if(pCur_Year->pClass == NULL) pCur_Year->pClass = Temp_Class;
    else{
        while(pCur_Class->pNext_Class != NULL) pCur_Class = pCur_Class->pNext_Class;
        pCur_Class->pNext_Class = Temp_Class;
    }
}


void Create_Student(Year* &year){
    Year* pCur_Year;
    do{
        pCur_Year = year;
        string find_year;
        cout<<"academic year to import class (ex:2020-2021) ";
        cin>>find_year;
        
        while(pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;

    }while(pCur_Year == NULL);

    Class* pCur_Class;
    do{
        pCur_Class = pCur_Year->pClass;
        string find_class;
        cout<<"class to import student (ex:21CLC10) ";
        cin>>find_class;
        
        while(pCur_Class != NULL && find_class != pCur_Class->name)
            pCur_Class = pCur_Class->pNext_Class;

    }while(pCur_Class == NULL);

    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    
    ifstream filein("profile.csv");
    while(filein.eof() == false){
        Student* pCur_Student = pCur_Class->pStudent;
        Student* Temp_Student = new Student;
        cout<<"Import student: "<<endl;
        cout<<"No ";getline(filein,Temp_Student->No,',');cout<<Temp_Student->No<<" | ";
        cout<<"StudentID ";getline(filein,Temp_Student->StudentID,',');cout<<Temp_Student->StudentID<<" | ";
        cout<<"FirstName ";getline(filein,Temp_Student->FirstName,',');cout<<Temp_Student->FirstName<<" ";
        cout<<"LastName ";getline(filein,Temp_Student->LastName,',');cout<<Temp_Student->LastName<<" | ";
        cout<<"Gender ";getline(filein,Temp_Student->Gender,',');cout<<Temp_Student->Gender<<" | ";
        cout<<"Date_of_Birth ";getline(filein,Temp_Student->Date_of_Birth,',');cout<<Temp_Student->Date_of_Birth<<" | ";
        cout<<"SocialID ";getline(filein,Temp_Student->SocialID,'\n');cout<<Temp_Student->SocialID<<endl;
        Temp_Student->pNext_Student = NULL;

        if(pCur_Class->pStudent == NULL) pCur_Class->pStudent = Temp_Student;
        else{
            while(pCur_Student->pNext_Student != NULL) pCur_Student = pCur_Student->pNext_Student;
            pCur_Student->pNext_Student = Temp_Student;
        }    
    }
    
    filein.close();
}

// function 18
void View_Student_In_Class(Year *year){ 
	string inClass;
	string findYear = ""; 
	Year *pCurYear = NULL;
	bool exist = true;
	do{
		exist = true;
		cout << "Enter class: ";
		cin >> inClass;
		
		if (inClass == "0")
			return;
		
		findYear = inClass.substr(0, 2); // strname.substr(start_point, number_of_character)
		pCurYear = year;
		// find year from class. Ex: 20CLC >>> 2020-2021
		while (pCurYear && (pCurYear->name).substr(0, 2) != findYear)
			pCurYear = pCurYear->pNext_Year;
		if (pCurYear == NULL){
			cout << "Class does not exist.\n";
			exist = false;
		}
		else{
			Class *pCurClass = pCurYear->pClass;
			// find class from its name
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

struct Semester{
    string name;
    Semester* pNext_Semester;
    Course* pCourse;
};

// 20
void View_Student_In_Course(Year *year){
	string inYear = "";
	Year *pCurYear = NULL;
	bool exist;
	do{
		exist = true;
		cout << "Enter school year: ";
		cin >> inYear;
		
		if (inYear == "0")
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

void solve() {
    Year* year = NULL;
    int choose;
    do{
        cout << "1. Create Year\n";
        cout << "2. Create Class\n";
        cout << "3. Create Student\n";
        cout << "4. Print Year\n";
        cout << "5. Print Class\n";
        cout << "6. Print Student\n";
        cout << "7. Create Semester\n";
        cout << "8. Create Registration Session\n";
        cout << "9. Add Subject\n";
        cout << "10. Add Course\n";
        cout << "11. View Courses\n";
        cout << "12. Update Course\n";
        cout << "13. Delete COurse\n";

        cout << "14.Exit\n";
        cout << "->Your choose ";
        cin >> choose;
        if (choose == 1) Create_Year(year);
        if (choose == 2) Create_Class(year);
        if (choose == 3) Create_Student(year);
        if (choose == 4) Print_Year(year);
        if (choose == 5) Print_Class(year);
        if (choose == 6) Print_Student(year);
        if (choose == 7) create_Semester(year);
        if (choose == 8) create_Registration_Session();
        if (choose == 9) add_Subject(year);
        if (choose == 10) add_Course(year);
        if (choose == 11) view_list_Courses(year);
        if (choose == 12) Update_Course(year);
        if (choose == 13) delete_Course(year);

    }while(choose != 14);
}
