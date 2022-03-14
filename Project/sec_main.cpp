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

void update_Course(Year *year){
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
    cin >> cour->Teacher_Name;
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
    cour->pNext_Course = nullptr;
    cout << "Course added!" << endl;

/*
    Year *pCur_Year;
    string find_year = "";
    do{
        pCur_Year = year;
        cout << "academic year to import semester (ex:2020-2021): ";
        cin >> find_year;

        while (pCur_Year != NULL && find_year != pCur_Year->name)
            pCur_Year = pCur_Year->pNext_Year;
    } while (pCur_Year == NULL);

    Semester *pCur_Semester;
    string find_Semester;
    do{
        pCur_Semester = pCur_Year->pSemester;
        cout << "semester to import subject (ex: 1, 2, 3): ";
        cin >> find_Semester;

        while (pCur_Semester != NULL && find_Semester != pCur_Semester->name)
            pCur_Semester = pCur_Semester->pNext_Semester;
    } while (pCur_Semester == NULL);

    Subject *pCur_Subject;
    string find_Subject;
    do{
        pCur_Subject = pCur_Semester->pSubject;
        cout << "subject to update course: ";
        cin >> find_Subject;

        while (pCur_Subject != NULL && find_Subject != pCur_Subject->name)
            pCur_Subject = pCur_Subject->pNext_Subject;
    } while (pCur_Subject == NULL);

    Course *pCur_Course;
    string find_Course = "";
    
    do{
        pCur_Course = pCur_Subject->pCourse;
        cout << "course to update: ";
        cin >> find_Course;

        while (pCur_Course != NULL && find_Course != pCur_Course->Course_Name){
            pCur_Course = pCur_Course->pNext_Course;
        }
    }while (pCur_Course == NULL);
    
    //course id, course name, teacher name, number of credits, 
    //the maximum number of students (default 50), day, and the session
    cout << "Update course: " << endl;
    cout << "Course ID: "; 
    cin >> pCur_Course->CourseID;
    cout << "Course name: ";
    cin >> pCur_Course->Course_Name;
    cout << "Teacher name: ";
    cin >> pCur_Course->Teacher_Name;
    cout << "Number of credit: ";
    cin >> pCur_Course->Number_of_Credits;
    cout << "Maximum student: ";
    cin >> pCur_Course->Max_Student;
    // sao lai phai co start day, end day cho course?
    cout << "Start day: ";
    cin >> pCur_Course->Start_Day;
    cout << "End day: ";
    cin >> pCur_Course->End_Day;
    cout << "First weekday (MON/TUE...): ";
    cin >> pCur_Course->Day1;
    cout << "Session for first weekday (S1/ S2/ S3/ S4): ";
    cin >> pCur_Course->Session1;
    cout << "Second weekday (MON/TUE...): : ";
    cin >> pCur_Course->Day2;
    cout << "Session for second weekday (S1/ S2/ S3/ S4): ";
    cin >> pCur_Course->Session2;
*/
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
        if (choose == 12) update_Course(year);
        if (choose == 13) delete_Course(year);

    }while(choose != 14);
}
