#include "header.h"

int HOME=0, LOG_OUT=0;

void Nocursortype(){
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void gotoxy(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX - 1;
	Position.Y = posY - 1;

	SetConsoleCursorPosition(hStdout, Position);
}
void Textcolor(int x){
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

int convert_to_int(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++)
        res = res * 10 + (s[i] - '0');
    return res;
}
Semester* find_semester(Semester* pSem, string name) {
    if (!pSem) return nullptr;
    while (pSem && pSem->name != name)
        pSem = pSem->pNext_Semester;
    return pSem;
}
int count_sem(string student_id) {
    int cnt=0;
    ifstream fin("year_sem.csv");
    string s;
    if (fin.is_open()) {
        while (!fin.eof()) {
            getline(fin, s, ',');
            if (s.substr(2, 2)==student_id.substr(0,2)) break; 
            getline(fin, s,'\n');
        }
        while (!fin.eof()) {
            getline(fin, s, '\n');
            cnt+=convert_to_int(s);
            if (!fin.eof()) getline(fin, s, ',');
        }
    }
    fin.close();
    return cnt;
}
bool check_empty(ifstream& fin) {
    return (fin.peek() == ifstream::traits_type::eof());
}
bool isStaff(string username){
    if (username.find('@') != string::npos) // username co '@' la staff
        return true;
    else
        return false;
}
bool account_check(Account *head, User U){
    bool success = false;
    Account *cur = head;
    while (!success && cur){
        if (cur->username == U.username && cur->password == U.password)
            success = true;
        else
            cur = cur->next;
    }
    return success;
}
Account *load_account_list(){
    fstream inputFile("account.csv", ios::in);
    Account *head = new Account;
    getline(inputFile, head->username, ',');
    getline(inputFile, head->password, '\n');

    Account *cur = head;
    do{
        cur->next = new Account;
        cur = cur->next;
        getline(inputFile, cur->username, ',');
        getline(inputFile, cur->password, '\n');
        cur->next = nullptr;
    }while (inputFile.eof() == false);

    inputFile.close();
    return head;
}
void save_account_list(Account *head){
    fstream changeFile("account.csv", ios::out); // rewrite file
    Account *cur = head;
    changeFile << cur->username << ',' << cur->password;
    cur = cur->next;
    while (cur){
        changeFile << '\n'<< cur->username << ',' << cur->password;
        cur = cur->next;
    }
    changeFile.close();
}
void delete_account_list(Account *&head){
    Account *temp = nullptr;
    while (head){
        temp = head->next;
        delete head;
        head = temp;
    }
}
void change_password(Account *head, User U){
    Account *cur = head;
    bool found = false;
    while (cur && cur->username != U.username)
        cur = cur->next;
    if (cur == nullptr){
        cout << "ERROR!\n";
    }
    else
        cur->password = U.password;
    return;
}
// calculate overall GPA
void calcu_oGPA(Year* year, Student* student) {
    int ammout_sem = count_sem(student->StudentID);
    Cur_Course* cur = student->pCur_Cour;
    double total = 0;
    int cnt = 0;
    while (cur) {
        ++cnt;
        total += cur->mark.Total;
        cur=cur->pNext_Cur_Cour;
    }
    if(cnt) total = total*1.0/cnt; 
    if (ammout_sem>1) student->GPA = 1.0*((student->GPA)*(ammout_sem-1)+total)/ammout_sem;
    else student->GPA=total;
    student->GPA=int(student->GPA*10)/10.0;
}
void calcu_oGPA_main(Year* year) {
    while (year) {
        Class* _class = year->pClass;
        while (_class) {
            Student* st = _class->pStudent;
            while (st) {
                calcu_oGPA(year, st);
                st = st->pNext_Student;
            }
            _class = _class->pNext_Class;
        }
        year=year->pNext_Year;
    }
}
// create account
void Create_Account_For_new_Student(string student_id, Account* account_head) {
    Account* cur = account_head;
    Account* newAcc = new Account;
    newAcc->username = student_id;
    newAcc->password = "123456789";
    newAcc->next = nullptr;

    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;

    if (cur == nullptr) account_head = newAcc;
    else cur->next = newAcc;
}
void Create_Course(Year* year, Semester* sem) { 
    ifstream filein(year->name + "_" + sem->name + ".csv");
    if (!filein){
        cout << "Cannot open file \"" << year->name << "_" << sem->name + "\".csv\".\n";
        return;
    }

    Textcolor(SUCCESS);
    cout << "Courses added:\n";
    Textcolor(NORMAL);
    cout << setfill('_') << setw(148) << left << "_" << endl;
    cout << setfill(' ') << setw(10) << left << " ID" << " | ";
    cout << setw(7) << left << "Credits" << " | ";
    cout << setw(8) << left << "Capacity" << " | ";
    cout << setw(40) << left << "Course's name" << " | ";
    cout << setw(28) << left << "Teacher's name" << " | ";
    cout << setw(15) << left << "Time performing" << " | ";
    cout << setw(9) << left << "Start day" << " | ";
    cout << setw(8) << left << "End day" << '\n';
    
    cout << setfill('_') << setw(12) << right << "|";
    cout << setw(10) << right << "|";
    cout << setw(11) << right << "|";
    cout << setw(43) << right << "|";
    cout << setw(31) << right << "|";
    cout << setw(18) << right << "|";
    cout << setw(12) << right << "|";
    cout << setw(12) << right << '\n';

    string s = "";
    while(filein.eof() == false){
        Course* pCur_Course = sem->pCourse;
        Course* add_Course = new Course;

        getline(filein,add_Course->CourseID,',');           
        getline(filein,add_Course->Number_of_Credits,',');  
        getline(filein,add_Course->Max_Student,',');        
        getline(filein,add_Course->Course_Name,',');        
        getline(filein,add_Course->Teacher_Name,',');      
        getline(filein,add_Course->Day1,',');
        getline(filein,add_Course->Session1,',');
        getline(filein,add_Course->Day2,',');
        getline(filein,add_Course->Session2,',');
        getline(filein,add_Course->Start_Day,','); 
        getline(filein,add_Course->End_Day,'\n');

        cout << " " << setfill(' ') << setw(9) << left << add_Course->CourseID << " | ";
        cout << setw(7) << right << add_Course->Number_of_Credits << " | ";
        cout << setw(8) << right << add_Course->Max_Student << " | ";
        cout << setw(40) << left << add_Course->Course_Name << " | ";
        cout << setw(28) << left << add_Course->Teacher_Name << " | ";
        s = add_Course->Day1; s += " "; s += add_Course->Session1;
        cout << setw(15) << left << s << " | ";
        cout << setw(9) << left << add_Course->Start_Day << " | ";
        cout << setw(8) << left << add_Course->End_Day << '\n';
        s = add_Course->Day2; s += " "; s += add_Course->Session2;
        cout << setw(12) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(43) << right << "|";
        cout << setw(31) << right << "|";
        cout << ' ' << setw(15) << left << s << " |";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';

        add_Course->pNext_Course = nullptr;  
        add_Course->pStudent_Course = nullptr;

        if(sem->pCourse == NULL) sem->pCourse = add_Course;
        else{
            while(pCur_Course->pNext_Course != NULL) pCur_Course = pCur_Course->pNext_Course;
            pCur_Course->pNext_Course = add_Course;
        }
        // End of table
        cout << setfill('_') << setw(12) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(43) << right << "|";
        cout << setw(31) << right << "|";
        cout << setw(18) << right << "|";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';
    }
    filein.close();
}

void Print_Course(Year* year, Semester* sem) {
    cout << "List of courses of the school year " << year->name << " - semester " << sem->name << ":\n";  

    if (sem->pCourse == nullptr){
        cout << "\tNo course was added.\n";
    }
    else{
        Course* pCourse = sem->pCourse;
        cout << setfill('_') << setw(148) << "_" << endl;
        cout << setfill(' ') << setw(10) << left << " ID" << " | ";
        cout << setw(7) << left << "Credits" << " | ";
        cout << setw(8) << left << "Capacity" << " | ";
        cout << setw(40) << left << "Course's name" << " | ";
        cout << setw(28) << left << "Teacher's name" << " | ";
        cout << setw(15) << left << "Time performing" << " | ";
        cout << setw(9) << left << "Start day" << " | ";
        cout << setw(8) << left << "End day" << '\n';
        
        cout << setfill('_') << setw(12) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(43) << right << "|";
        cout << setw(31) << right << "|";
        cout << setw(18) << right << "|";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';
        string s = "";
        while (pCourse != NULL) {
            cout << " " << setfill(' ') << setw(9) << left << pCourse->CourseID << " | ";
            cout << setw(7) << right << pCourse->Number_of_Credits << " | ";
            cout << setw(8) << right << pCourse->Max_Student << " | ";
            cout << setw(40) << left << pCourse->Course_Name << " | ";
            cout << setw(28) << left << pCourse->Teacher_Name << " | ";
            s = pCourse->Day1; s += " "; s += pCourse->Session1;
            cout << setw(15) << left << s << " | ";
            cout << setw(9) << left << pCourse->Start_Day << " | ";
            cout << setw(8) << left << pCourse->End_Day << '\n';
            s = pCourse->Day2; s += " "; s += pCourse->Session2;
            cout << setw(12) << right << "|";
            cout << setw(10) << right << "|";
            cout << setw(11) << right << "|";
            cout << setw(43) << right << "|";
            cout << setw(31) << right << "|";
            cout << ' ' << setw(15) << left << s << " |";
            cout << setw(12) << right << "|";
            cout << setw(11) << right << '\n';

            pCourse = pCourse->pNext_Course;

            // End of table
            cout << setfill('_') << setw(12) << right << "|";  
            cout << setw(10) << right << "|";
            cout << setw(11) << right << "|";
            cout << setw(43) << right << "|";
            cout << setw(31) << right << "|";
            cout << setw(18) << right << "|";
            cout << setw(12) << right << "|";
            cout << setw(11) << right << '\n';
        }
    }
}
Course* find_Course(Course* pCourse, string name) { 
    if (!pCourse) return nullptr;
    if (pCourse->CourseID == name) return pCourse;
    while (pCourse->pNext_Course && pCourse->pNext_Course->CourseID != name)
        pCourse = pCourse->pNext_Course;
    if(pCourse->pNext_Course && pCourse->pNext_Course->CourseID == name)
        return pCourse->pNext_Course;
    else
        return nullptr;
}
// find student
Student* find_student_in_1_class(Class* classes, string Student_ID){
    if(classes->pStudent == NULL) return NULL;
    Student* pCur_Student = classes->pStudent;
    
    while(pCur_Student != NULL && pCur_Student->StudentID != Student_ID)
        pCur_Student = pCur_Student->pNext_Student;

    if(pCur_Student != NULL) return pCur_Student;
    return NULL;
}
Student* find_student_in_many_classes(Year* year, string Student_ID){ // of 1 year, not of all years
    if(year->pClass == NULL) return NULL;
    Class* pCur_Class = year->pClass;

    while(pCur_Class != NULL){
        Student* temp = find_student_in_1_class(pCur_Class,Student_ID);
        if(temp != NULL) return temp;
        pCur_Class = pCur_Class->pNext_Class;
    }
    return NULL;
}
//find course

// find student in course
Student_Course* find_student_in_a_course(Course* cour, string Student_ID) {
    Student_Course* pCur = cour->pStudent_Course;
    while (pCur != nullptr && pCur->StudentID != Student_ID) pCur = pCur->pNext_Student_Course;
    return pCur;
}
Course* find_course_in_many_subjects(Semester* semester, string course){ // course id
    if(semester->pCourse == NULL) return NULL;
    Course* pCur_Course = semester->pCourse;

    while(pCur_Course != NULL){
        if(pCur_Course->CourseID == course) return pCur_Course;
        pCur_Course = pCur_Course->pNext_Course;
    }
    return NULL;
}

void Delete_Course(Semester* sem) {
    string s;
    cout << "Enter course ID to delete: " ;
    cin >> s;
    Course* cour = find_Course(sem->pCourse, s);
    if (cour == nullptr){
        Textcolor(_ERROR);
        cout << "Invalid course.";
        Textcolor(NORMAL);
    }
    else{
        if (cour->CourseID == s) { // course id
            Course* pDel = sem->pCourse;
            sem->pCourse = sem->pCourse->pNext_Course;
            delete pDel;
        }
        else {
            Course* pDel = cour->pNext_Course;
            cour->pNext_Course = cour->pNext_Course->pNext_Course;
        }
        Textcolor(SUCCESS);
        cout << "Course has been deleted.\n";
        Textcolor(NORMAL);
    }
}
bool semExists(Year* year, string findSem){  
    Semester* pCurSem = year->pSemester;
    while (pCurSem && pCurSem->name != findSem)
        pCurSem = pCurSem->pNext_Semester;
    if (pCurSem == nullptr)
        return false;
    else 
        return true;
}
void Create_Semester(Year *&year){
    Semester *pCur_Semester = year->pSemester;

    Semester *Temp_Semester = new Semester;
    Temp_Semester->name = to_string(1);
    Temp_Semester->pNext_Semester = NULL;
    Temp_Semester->pCourse = nullptr;
    
    if (year->pSemester == NULL)
        year->pSemester = Temp_Semester;
    else{
        while (pCur_Semester->pNext_Semester != NULL)
            pCur_Semester = pCur_Semester->pNext_Semester;
        Temp_Semester->name=to_string(convert_to_int(pCur_Semester->name)+1);
        pCur_Semester->pNext_Semester = Temp_Semester;
    }
    Textcolor(SUCCESS);
    cout<<"Semester "<<Temp_Semester->name<<" has been added.\n";
    Textcolor(NORMAL);
    cin.ignore(1000, '\n');
    getchar();
}
void create_Registration_Session(Registration_Session &S){
    cout << "Create Registration Session: \n";
    cout << "Start time: \n";
    cout << "Date: ";
    cin >> S.start.date;
    cout << "Month: ";
    cin >> S.start.month;
    cout << "Year: ";
    cin >> S.start.year;
    do {
        cout<<"Hour: ";
        cin>>S.start.hour;
    } while(S.start.hour <0 || S.start.hour>23);
    do {
        cout<<"Minute: ";
        cin>>S.start.minute;
    } while(S.start.minute<0 || S.start.minute>59);

    cout << "End time: \n";
    cout << "Date: ";
    cin >> S.end.date;
    cout << "Month: ";
    cin >> S.end.month;
    cout << "Year: ";
    cin >> S.end.year;
    do {
        cout<<"Hour: ";
        cin>>S.end.hour;
    } while(S.end.hour <0 || S.end.hour>23);
    do {
        cout<<"Minute: ";
        cin>>S.end.minute;
    } while(S.end.minute<0 || S.end.minute>59);
    Textcolor(SUCCESS);
    cout << "Registration session created.";
    Textcolor(NORMAL);
}
bool Check_Regis_Time(Registration_Session S) {
    time_t now = time(0);
    tm* t = localtime(&now);
    int year = t->tm_year + 1900, mon = t->tm_mon + 1, day = t->tm_mday,
    hour = t->tm_hour, minute = t->tm_min;
    if (year != S.start.year) return 0;
    if (mon < S.start.month || mon > S.end.month) return 0;
    if (mon == S.start.month) {
        if (day < S.start.date) return 0;    // check day
        if (day == S.start.date) {
            if (hour < S.start.hour) return 0;// check hour
            if (hour == S.start.hour) {
                if (minute < S.start.minute) return 0;// check minute
            }
        }
    }
    if (mon == S.end.month) {
        if (day > S.end.date) return 0;    // check day
        if (day == S.end.date) {
            if (hour > S.end.hour) return 0;// check hour
            if (hour == S.end.hour) {
                if (minute > S.end.minute) return 0;// check minute
            }
        }
    }
    return 1;
}
void Update_Course(Semester* sem){
    string s = "";
    cout << "Enter course ID to update: " ;
    cin >> s;
    Course* cour = find_Course(sem->pCourse, s);
    if (cour == nullptr){
        Textcolor(_ERROR);
        cout << "Invalid course.";
        Textcolor(NORMAL);
    }
    else{
        cout << "Update the following details: " << endl;
        cout << "ID: ";
        cin >> cour->CourseID;
        cout << "Number of credits: ";
        cin >> cour->Number_of_Credits;
        cout << "Maximum number of students in Course: ";
        cin >> cour->Max_Student;
        cout << "Course name: ";
        cin.ignore(1000, '\n');
        getline(cin, cour->Course_Name, '\n');
        cout << "Teacher name: ";
        getline(cin, cour->Teacher_Name, '\n');
        cout << "Time performing: " << endl;
        cout << "\tDay of week: MON TUE WED THU FRI SAT\n";
        cout << "\tSession: S1 - 07:30\n";
        cout << "\t         S2 - 09:30\n";
        cout << "\t         S3 - 13:30\n";
        cout << "\t         S4 - 15:30\n";
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
        Textcolor(SUCCESS);
        cout << "Course has been updated.\n";
        Textcolor(NORMAL);
    }
}
void Print_Year(Year *year)
{
    cout << "List of school years:\n";
    if (year == NULL) {
        cout << "\tNo year was created.\n";
    }
    else{
        Year *pCur_Year = year;
        while (pCur_Year != NULL)
        {
            cout << '\t' << pCur_Year->name << endl;
            pCur_Year = pCur_Year->pNext_Year;
        }
    }
    cout << endl;
}
void Print_Class(Year *year)
{
    cout << "List of classes of the year " << year->name << ":\n";
    if(year->pClass == nullptr) {
        cout << "\tNo class was created.\n";
    }
    else{
        Class *pCur_Class = year->pClass;
        while (pCur_Class != NULL)
        {
            cout << '\t' << pCur_Class->name << endl;
            pCur_Class = pCur_Class->pNext_Class;
        }
    }
    cout << endl;
}
void Print_Student(Class *classes){
    cout << "List of students in class " << classes->name << ":\n";  
    if (classes->pStudent == nullptr){
        cout << "\tNo student was added.\n";
    }
    else{
        Student *pCur_Student = classes->pStudent;
        cout << "______________________________________________________________________________________________\n";
        cout << " No. | Student ID |       First name      | Last name | Gender | Date of Birth |   Social ID  \n";
        cout << "_____|____________|_______________________|___________|________|_______________|______________\n";
        cout << setfill(' ');
        while (pCur_Student != NULL)
        {
            //No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID
            cout<< ' ' << setw(3) << left << pCur_Student->No << " | ";
            cout<< setw(10) << left << pCur_Student->StudentID << " | ";
            cout<< setw(21) << left << pCur_Student->LastName << " | ";
            cout<< setw(9) << left << pCur_Student->FirstName << " | ";
            cout<< setw(6) << left << pCur_Student->Gender << " | ";
            cout<< setw(13) << left << pCur_Student->Date_of_Birth << " | ";
            cout<< setw(12) << right << pCur_Student->SocialID << " \n";
            pCur_Student = pCur_Student->pNext_Student;
            // cout << "_____|____________|_______________________|___________|________|_______________|______________\n";  
        }
    }
}
void Print_Semester(Year* year) {
    cout << "List of semesters of the year " << year->name << ":\n";
    if (year->pSemester == nullptr){
        cout << "\tNo semester was created.\n";
    }
    else{
        Semester* sem = year->pSemester;
        while (sem) {
            cout << "\tSemester " << sem->name << endl;
            sem = sem->pNext_Semester;
        }
    }
    cout << endl;
}
void Print_Cur_Course(Cur_Course* cur_course) {
    if (cur_course == nullptr)
        cout << "No course to display" << endl; 
    else {
        cout << setfill('_') << setw(147) << '\n';
        cout << setfill(' ') << setw(10) << left << " ID" << " | ";
        cout << setw(7) << left << "Credits" << " | ";
        cout << setw(8) << left << "Capacity" << " | ";
        cout << setw(40) << left << "Course name" << " | ";
        cout << setw(28) << left << "Teacher's name" << " | ";
        cout << setw(15) << left << "Time performing" << " | ";
        cout << setw(9) << left << "Start day" << " | ";
        cout << setw(8) << left << "End day" << '\n';
        
        cout << setfill('_') << setw(13) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(43) << right << "|";
        cout << setw(31) << right << "|";
        cout << setw(18) << right << "|";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';

        string s = "";
        while (cur_course != NULL) {
            cout << " " << setfill(' ') << setw(9) << left << cur_course->CourseID << " | ";
            cout << setw(7) << right << cur_course->Number_of_Credits << " | ";
            cout << setw(8) << right << cur_course->Max_Student << " | ";
            cout << setw(40) << left << cur_course->Course_Name << " | ";
            cout << setw(28) << left << cur_course->Teacher_Name << " | ";
            s = cur_course->Day1; s += " "; s += cur_course->Session1;
            cout << setw(15) << left << s << " | ";
            cout << setw(9) << left << cur_course->Start_Day << " | ";
            cout << setw(8) << left << cur_course->End_Day << '\n';

            cout << setw(13) << right << "|";
            cout << setw(10) << right << "|";
            cout << setw(11) << right << "|";
            cout << setw(43) << right << "|";
            cout << setw(31) << right << "|";
            s = cur_course->Day2; s += " "; s += cur_course->Session2;
            cout << ' ' << setw(15) << left << s << " |";
            cout << setw(12) << right << "|";
            cout << setw(11) << right << '\n';

            cur_course = cur_course->pNext_Cur_Cour;
        }  
        // End of table
        cout << setfill('_') << setw(13) << right << "|";
        cout << setw(10) << right << "|";
        cout << setw(11) << right << "|";
        cout << setw(43) << right << "|";
        cout << setw(31) << right << "|";
        cout << setw(18) << right << "|";
        cout << setw(12) << right << "|";
        cout << setw(11) << right << '\n';
    }
}
//18

// 20
void View_Student_In_Course(Semester* sem){
    string inCourse;
    Course* pCurCourse; 
    // bool courseExists()
    cout << "Enter course ID to view its students: ";
    cin >> inCourse;
    pCurCourse = sem->pCourse;
    while (pCurCourse && pCurCourse->CourseID != inCourse)
        pCurCourse = pCurCourse->pNext_Course;
    if (pCurCourse == nullptr){
        Textcolor(_ERROR);
        cout << "Invalid course.";
        Textcolor(NORMAL);
    }
    else{
        system("cls");
        cout << "List of students in course " << inCourse << ":\n";
        Student_Course *pCurStu = pCurCourse->pStudent_Course;
        if (pCurStu == nullptr){
            cout << "\tNo student has enrolled in this course.\n";
        }
        else{
            cout << setfill(' ');  
            cout << "______________________________________________________________________________________________\n";
            cout << " No. | Student ID |       First name      | Last name | Gender | Date of Birth |   Social ID  \n";
            cout << "_____|____________|_______________________|___________|________|_______________|______________\n";   
            while (pCurStu){
                cout<< " " << setw(3) << left << pCurStu->No << " | ";
                cout<< setw(10) << left << pCurStu->StudentID << " | ";
                cout<< setw(21) << left << pCurStu->LastName << " | ";
                cout<< setw(9) << left << pCurStu->FirstName << " | ";
                cout<< setw(6) << left << pCurStu->Gender << " | ";
                cout<< setw(13) << left << pCurStu->Date_of_Birth << " | ";
                cout<< setw(12) << right << pCurStu->SocialID << " \n";
                
                pCurStu = pCurStu->pNext_Student_Course;
                cout << "_____|____________|_______________________|___________|________|_______________|______________\n";  
            }
        }
    }
}
void View_Enrolled_Course(Year* year, Student* student) {
    string id=student->StudentID;
    string s;
    cout << setfill('_') << setw(147) << left << "_" << endl;
    cout << setfill(' ') << setw(10) << left << " ID" << " | ";
    cout << setw(7) << left << "Credits" << " | ";
    cout << setw(8) << left << "Capacity" << " | ";
    cout << setw(40) << left << "Course name" << " | ";
    cout << setw(28) << left << "Teacher's name" << " | ";
    cout << setw(15) << left << "Time performing" << " | ";
    cout << setw(9) << left << "Start day" << " | ";
    cout << setw(8) << left << "End day" << '\n';
    
    cout << setfill('_') << setw(12) << right << "|";
    cout << setw(10) << right << "|";
    cout << setw(11) << right << "|";
    cout << setw(43) << right << "|";
    cout << setw(31) << right << "|";
    cout << setw(18) << right << "|";
    cout << setw(12) << right << "|";
    cout << setw(11) << right << '\n';
    Semester* sem = year->pSemester;
    while (sem) {
        ifstream fin(year->name+"_HK"+sem->name+"_course.csv");
        string course_id, credits, capacity,name, teacher, d1, s1, d2, s2, sDay, eDay;
        while (fin.is_open() && !fin.eof()) {
            getline(fin, s, ',');
            if (s==".") {
                getline(fin, course_id, ',');
                getline(fin, credits, ',');
                getline(fin, capacity, ',');
                getline(fin, name, ',');
                getline(fin, teacher, ',');
                getline(fin, d1, ',');
                getline(fin, s1, ',');
                getline(fin, d2, ',');
                getline(fin, s2, ',');
                getline(fin, sDay, ',');
                getline(fin, eDay, '\n');
            }
            else {
                getline(fin, s, ',');
                if (s==id) {
                    string str="";
                    cout << " " << setfill(' ') << setw(9) << left << course_id << " | ";
                    cout << setw(7) << right << credits<< " | ";
                    cout << setw(8) << right << capacity << " | ";
                    cout << setw(40) << left << name << " | ";
                    cout << setw(28) << left << teacher << " | ";
                    str = d1; str += " "; str += s1;
                    cout << setw(15) << left << str << " | ";
                    cout << setw(9) << left << sDay << " | ";
                    cout << setw(8) << left << eDay << '\n';
                    str = d2; str += " "; str += s2;
                    cout << setw(12) << right << "|";
                    cout << setw(10) << right << "|";
                    cout << setw(11) << right << "|";
                    cout << setw(43) << right << "|";
                    cout << setw(31) << right << "|";
                    cout << ' ' << setw(15) << left << str << " |";
                    cout << setw(12) << right << "|";
                    cout << setw(11) << right << '\n';
                }
                getline(fin,s,'\n');
            }
        }
        fin.close();
        sem = sem->pNext_Semester;
    }
}
void View_Enrolled_Course_main(Year*& year, string studentID) {
    // string studentID;
    // cout << "Your student ID: ";
    // cin >> studentID;
    Student* student = find_student_in_many_classes(year, studentID);
    if (student == NULL) {
        Textcolor(_ERROR);
        cout << "Student ID not found!" << endl;
        Textcolor(NORMAL);
        return;
    }
    View_Enrolled_Course(year, student);
}
void Delete_Enrolled_Course(Student*& student, Course*& course) {
    Cur_Course* pCur1 = student->pCur_Cour;
    Student_Course* pCur2 = course->pStudent_Course;
    if (student->pCur_Cour == NULL || course->pStudent_Course == NULL) {
        cout << "You haven't enrolled in this course yet!";
        return;
    }
    if (pCur1->CourseID == course->CourseID) {
        Cur_Course* pTemp1 = pCur1;
        pCur1 = pCur1->pNext_Cur_Cour;
        student->pCur_Cour = pCur1;
        delete pTemp1;
    }
    else {
        Cur_Course* pTemp1 = pCur1;
        while (pTemp1->pNext_Cur_Cour->CourseID != course->CourseID) {
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
void Delete_Enrolled_Course_main(Year*& year, Semester*& semester, string studentID,Registration_Session &S) {
    if (Check_Regis_Time(S)) {
        // string studentID;
        // cout << "Your studentID: ";
        // cin >> studentID;
        Student* student = find_student_in_many_classes(year, studentID);
        if (student == NULL) {
            Textcolor(_ERROR);
            cout << "Student ID not found!" << endl;
            Textcolor(NORMAL);
            return;
        }
        // if having enrolled courses, delete ones
        string course_id;
        cout << "Enter course ID to delete: ";
        cin >> course_id;
        Course* Del_Cour = find_course_in_many_subjects(semester, course_id);
        if (Del_Cour == NULL) {
            Textcolor(_ERROR);
            cout << "Invalid course.\n";
            Textcolor(NORMAL);
            return;
        }
        Delete_Enrolled_Course(student, Del_Cour);
        Textcolor(SUCCESS);
        cout << "Course deleted.";
        Textcolor(NORMAL);
    }
    else{
        Textcolor(_ERROR);
        cout << "Registration session has expired!\n";
        Textcolor(NORMAL);
    }
}
bool yearExists(Year *year, string findYear){ // new
    Year *pCurYear = year;
    while (pCurYear && pCurYear->name != findYear)
        pCurYear = pCurYear->pNext_Year;
    if (pCurYear == nullptr)
        return false;
    else
        return true;
}
void Create_Year(Year* &year){
    Year* pCur_Year = year;

    Year* Temp_Year = new Year;
    Temp_Year->name = to_string(2019);
    Temp_Year->pNext_Year = NULL;
    Temp_Year->pClass = NULL;
    Temp_Year->pSemester = NULL;

    if(year == NULL) year = Temp_Year;
    else{
        while(pCur_Year->pNext_Year != NULL) pCur_Year = pCur_Year->pNext_Year;
        Temp_Year->name = to_string(convert_to_int(pCur_Year->name)+1);
        pCur_Year->pNext_Year = Temp_Year;
    }
    Textcolor(SUCCESS);
    cout << Temp_Year->name<<" year has been created.";
    Textcolor(NORMAL);    cin.ignore(1000, '\n');
    getchar();
}

bool classExists(Year* year, string findClass){ // new
    Class* pCurClass = year->pClass;
    while (pCurClass && pCurClass->name != findClass)
        pCurClass = pCurClass->pNext_Class;
    if (pCurClass == nullptr)
        return false;
    else
        return true;
}
void Create_Class(Year* &year){
    string name_class;
    cout<<"Create a new class of the year "<< year->name << " (ex:21CLC10) ";  
    cin >> name_class;

    if (classExists(year, name_class)){
        Textcolor(_ERROR);
        cout << "Class already exists.\n";
        Textcolor(NORMAL);
    }
    else{
        Class* pCur_Class = year->pClass;

        Class* Temp_Class = new Class;
        Temp_Class->name = name_class;
        Temp_Class->pNext_Class = NULL;
        Temp_Class->pStudent = NULL;

        if(year->pClass == NULL) year->pClass = Temp_Class;
        else{
            while(pCur_Class->pNext_Class != NULL) pCur_Class = pCur_Class->pNext_Class;
            pCur_Class->pNext_Class = Temp_Class;
        }
        Textcolor(SUCCESS);
        cout << "New class has been created.";
        Textcolor(NORMAL);
    }
}

Year* Import_Year(Year* year){
    if(year == NULL) return NULL;
    Year* pCur_Year;

    pCur_Year = year;
    string find_year;
    cout << "Enter a school year (ex: 2021) ";  
    cin >> find_year;
                    
    while(pCur_Year != NULL && find_year != pCur_Year->name)
        pCur_Year = pCur_Year->pNext_Year;
    // if (pCur_Year == nullptr){  
    //     Textcolor(_ERROR);
    //     cout << "Invalid year.";
    //     Textcolor(NORMAL);
    //     cin.ignore(1000, '\n');
    //     getchar();
    // }
    return pCur_Year;
}
Class* Import_Class(Class* classes){
    if(classes == NULL) return NULL;
    Class* pCur_class;

    pCur_class = classes;
    string find_class;
    cout << "Enter a class (ex:21CLC10) ";  
    cin >> find_class;

    while (pCur_class != NULL && find_class != pCur_class->name)
        pCur_class = pCur_class->pNext_Class;

    return pCur_class;
}
Semester* Import_Semester(Semester* sem){
    if(sem == NULL) return NULL;
    Semester* pCur_sem;
    do{
        pCur_sem = sem;
        string find_sem;
        cout<<"Enter a semester to view courses (ex: 1, 2, 3) ";  
        cin>>find_sem;   
        while(pCur_sem != NULL && find_sem != pCur_sem->name)
            pCur_sem = pCur_sem->pNext_Semester;
        if (pCur_sem == nullptr){  
            Textcolor(_ERROR);
            cout << "Invalid semester.\n";
            Textcolor(NORMAL);
        }
    }while(pCur_sem == NULL);
    return pCur_sem;
}

void Create_Student(Year* year, Class *&classes, Account* account_head){ 

    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    ifstream filein(classes->name+".csv");
    if (!filein.is_open()){  
        Textcolor(_ERROR);
        cout << "Cannot open file.\n";
        Textcolor(NORMAL);
        return;
    }
    Student* pCur_Student = nullptr;
    Student* Temp_Student = nullptr;

    Textcolor(SUCCESS);
    cout << "Students added:\n";
    Textcolor(NORMAL);

    cout << "______________________________________________________________________________________________\n";
    cout << " No. | Student ID |       First name      | Last name | Gender | Date of Birth |   Social ID  \n";
    cout << "_____|____________|_______________________|___________|________|_______________|______________\n";

    while(filein.eof() == false){
        pCur_Student = classes->pStudent;
        string No, id;
        getline(filein, No, ',');
        getline(filein, id, ',');
        cout << setfill(' ');
        if (find_student_in_many_classes(year, id)==nullptr) {
            Temp_Student = new Student;
            
            Temp_Student->No = No;                          cout<< ' ' << setw(3) << left << Temp_Student->No << " | ";
            Temp_Student->StudentID = id;                   cout<< setw(10) << left << Temp_Student->StudentID << " | ";
            getline(filein,Temp_Student->LastName,',');     cout<< setw(21) << left << Temp_Student->LastName << " | ";
            getline(filein,Temp_Student->FirstName,',');    cout<< setw(9) << left << Temp_Student->FirstName << " | ";
            getline(filein,Temp_Student->Gender,',');       cout<< setw(6) << left << Temp_Student->Gender << " | ";
            getline(filein,Temp_Student->Date_of_Birth,',');cout<< setw(13) << left << Temp_Student->Date_of_Birth << " | ";
            getline(filein,Temp_Student->SocialID,'\n');    cout<< setw(12) << right << Temp_Student->SocialID << " \n";

            Temp_Student->pNext_Student = NULL;
            Temp_Student->pCur_Cour = NULL;
            Create_Account_For_new_Student(Temp_Student->StudentID, account_head);

            if(classes->pStudent == NULL) classes->pStudent = Temp_Student;
            else{
                while(pCur_Student->pNext_Student != NULL) pCur_Student = pCur_Student->pNext_Student;
                pCur_Student->pNext_Student = Temp_Student;
            }
        }
        else {
            Textcolor(_ERROR);
            cout << id <<" already exists!\n";
            Textcolor(NORMAL);
            getline(filein, No, '\n');
        }
    }
    
    filein.close();
}
//convert_to_int
void Add_1_Student(Class* import_class, string student_id) {
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
void Add_1_Student_main(Year* year,Class *&classes, Account* account_head) {
    string student_id;
    Student* stu = nullptr;
    
    cout<<"Enter the new student's ID: "; cin>>student_id;
    stu = find_student_in_many_classes(year, student_id);

    if (stu != nullptr){
        Textcolor(_ERROR);
        cout << "ID already existed.\n";
        Textcolor(NORMAL);
    }
    else{
        Add_1_Student(classes, student_id);
        Textcolor(SUCCESS);  
        cout<<"Student added!"<<endl;
        Textcolor(NORMAL);

        Create_Account_For_new_Student(student_id, account_head);
    }
}

//check enroll
bool Check_Cur_Course(Course* course_regis,Student* student){
    Cur_Course* pCur = student->pCur_Cour;
    while(pCur != NULL){
        if(pCur->CourseID == course_regis->CourseID) return false;
        else pCur = pCur->pNext_Cur_Cour;
    }
    return true;
}
bool Check_quantity(Student* student){
    int count = 0;
    Cur_Course* pCur = student->pCur_Cour;
    while(pCur != NULL){
        count++;
        pCur = pCur->pNext_Cur_Cour;
    }
    if(count < 5) return true; // "< 3" --> 2 --> allow to enroll--> 3 course
    return false;   //"<= 3" --> 3 --> allow to enroll --> 4 course
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
Cur_Course* Copy_Course(Course* course_regis){
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
Student_Course* Copy_Student_Cour(Student* student){
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
        Textcolor(SUCCESS);
        cout << "Enroll successful.\n";
        Textcolor(NORMAL);
    }
    else {  
        Textcolor(_ERROR);

        if(Check_Cur_Course(course_regis,student) == false)
            cout<<"You have enrolled in this course.\n";
        else if (Check_quantity(student) == false)
            cout<<"This course has enough quantity.\n";
        else if(Check_Session(course_regis,student) == false)
            cout<<"The schedule has been overlapped.\n";
        
        Textcolor(NORMAL);
    }
}

//enroll main
void enroll_main(Year* &year, Semester* &semester,string studentID,Registration_Session &S){
    Year* tmp = year;
    while (tmp->pNext_Year) tmp = tmp->pNext_Year;
    if (tmp->name != year->name) {
        Textcolor(4);
        cout<<"Invalid time!"<<endl;
        Textcolor(11);
    }
    else if (Check_Regis_Time(S) && studentID.substr(0,2)<= year->name.substr(2,2)) {
        // string studentID;
        // cout<<"StudentID "; cin>>studentID;

        Student* student = find_student_in_many_classes(year, studentID);
        if(student == NULL){
            Textcolor(_ERROR);
            cout << "Invalid student.\n";
            Textcolor(NORMAL);
            return;
        }
        //view all course
        string course_id;
        cout << "Course ID you want to enroll in: "; cin >> course_id;
        Course* course_regis = find_course_in_many_subjects(semester,course_id);
        if(course_regis == NULL){
            Textcolor(_ERROR);
            cout << "Invalid course.\n";
            Textcolor(NORMAL);
            return;
        }

        Enroll_Course(course_regis, student);
    }
    else{
        Textcolor(_ERROR);
        cout << "Registration session has expired!\n";
        Textcolor(NORMAL);
    } 
}

//22
double rand_mark() {
    //srand(time(NULL));
    return min(10.0, (rand() % 11) * 1.0 + (rand() % 10) / 10.0);
}
void Assign_Mark(Year* year,string course_id, string Student_ID, double total, double final, double mid, double other) {
    Student* Std = find_student_in_many_classes(year, Student_ID);
    // Student id always exists in this case-->no check null
    Cur_Course* pCur_Cour = Std->pCur_Cour;
    while(pCur_Cour != NULL && pCur_Cour->CourseID != course_id) pCur_Cour = pCur_Cour->pNext_Cur_Cour;
    if(pCur_Cour != NULL){
        pCur_Cour->mark.Final = final;
        pCur_Cour->mark.Midterm = mid;
        pCur_Cour->mark.Other = other;
        pCur_Cour->mark.Total = total;
    }
}
void Create_Mark(Year* year, Semester* sem, Course* cour) {
    string s =  year->name + "_" + sem->name + "_" + cour->CourseID + ".csv";
    ofstream fout(s);
    fout << "No,ID,Full name,Total mark,Final mark,Midterm mark,Other mark";
    Student_Course* Stu_Cour = cour->pStudent_Course;
    int cnt = 1;
    while (Stu_Cour) {
        fout << endl;
        double total, final, mid, other;
        final = rand_mark(), mid = rand_mark(), other = (rand() % 10) / 10.0;
        total = min((final * 2.0 + mid) / 3.0 + other, 10.0);
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
    string s = cour->CourseID + ".csv";
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
        Assign_Mark(year,cour->CourseID, pCurStd->StudentID, pCurStd->mark.Total, pCurStd->mark.Final,
        pCurStd->mark.Midterm, pCurStd->mark.Other);
    }
    fin.close();
}
void View_Score_Board(Course *cour) {
    cout << "Scoreboard of " << cour->CourseID << " - " << cour->Course_Name << ":\n";  
    
    Student_Course* pCurStd = cour->pStudent_Course;
    if (pCurStd == nullptr){
        cout << "\tNo student has enrolled in this course.\n";
    }
    else{
        string s = "";
        cout << "___________________________________________________________________________________\n";
        cout << " Student ID |             Full name              | Midterm | Final | Other | Total \n";
        cout << "____________|____________________________________|_________|_______|_______|_______\n";
        cout << setfill(' ');  
        while (pCurStd != nullptr){
            cout << ' ' << setw(10) << left << pCurStd->StudentID << " | ";
            s = pCurStd->LastName + " " + pCurStd->FirstName;
            cout << setw(34) << left << s << " | ";
            cout << setw(7) << right << pCurStd->mark.Midterm << " | ";
            cout << setw(5) << right << pCurStd->mark.Final << " | ";
            cout << setw(5) << right << pCurStd->mark.Other << " | ";
            cout << setw(5) << right << pCurStd->mark.Total << '\n';
            pCurStd = pCurStd->pNext_Student_Course;
            cout << "____________|____________________________________|_________|_______|_______|_______\n"; 
        }
    }
}
// mark main & scoreboard in a course main 
void Create_mark_main(Year* year,Semester* sem){ // Import scoreboard
    string course_id;
    cout << "Enter course ID to import its scoreboard: "; cin>>course_id;
    Course* course_regis = find_course_in_many_subjects(sem,course_id);
    if(course_regis == NULL){
        Textcolor(_ERROR);
        cout<<"Invalid course.\n";
        Textcolor(NORMAL);
        return;                                      
    }
    Create_Mark(year, sem, course_regis);
    Import_Scoreboard(year, course_regis);
    Textcolor(SUCCESS);  
    cout << "Scoreboard imported.";
    Textcolor(NORMAL);
}
//23
void View_scoreboard_main(Semester* sem){
    string course_id;
    cout<<"Enter course ID to view its scoreboard: "; cin>>course_id;
    Course* course_regis = find_course_in_many_subjects(sem,course_id);
    if(course_regis == NULL){
        Textcolor(_ERROR);
        cout<<"Invalid course.\n";
        Textcolor(NORMAL);
        return;                                      
    }
    system("cls");
    View_Score_Board(course_regis);
}
//22 export
void Export_Course(Year* year, Semester* sem, Course* course) {
    Student_Course* stu_cour = course->pStudent_Course;
    ofstream fileout;
    int cnt = 1;
    string s = course->CourseID;
    fileout.open(year->name + "_HK" + sem->name + "_" + s + ".csv");  // export course new name
    fileout << "No" << "," << "ID" << "," << "Full name" << "," << "Total mark" << "," << "Final mark" << "," << "Midterm mark" << "," << "Other mark";
    while (stu_cour != nullptr) {
        fileout << endl;
        fileout << cnt++ << "," << stu_cour->StudentID << "," << stu_cour->FirstName + " " + stu_cour->LastName <<","
        << stu_cour->mark.Total << "," << stu_cour->mark.Final << ","
        << stu_cour->mark.Midterm << "," << stu_cour->mark.Other;
        stu_cour = stu_cour->pNext_Student_Course;
    }
    fileout.close();
}
void Export_Course_main(Year*& year, Semester*& semester) {
    string course_id;
    cout << "Enter course ID to export its scoreboard: ";
    cin >> course_id;
    Course* export_course = find_course_in_many_subjects(semester, course_id);
    if (export_course == NULL) {
        Textcolor(_ERROR);
        cout << "Invalid course.";
        Textcolor(NORMAL);
        return;
    }
    Export_Course(year, semester, export_course);
    Textcolor(SUCCESS);
    cout << "Scoreboard exported.\n";
    Textcolor(NORMAL);
}

//24
void update_student_result(Year* &year, Semester* &sem){
    //view all course
    //Print_Course(year, sem);
    //find course
    string course_id;
    cout << "Enter course ID to update its scoreboard: "; cin >> course_id;
    Course* course_update = find_course_in_many_subjects(sem,course_id);
    if(course_update == NULL){
        Textcolor(_ERROR);
        cout<<"Invalid course.\n";
        Textcolor(NORMAL);
        return;
    }
    system("cls");
    //view student in a course
    View_Score_Board(course_update);
    // find student
    if (course_update->pStudent_Course == nullptr){
        cout << "No student to update his/her result.\n";
    }
    else{
        string studentID;
        cout<<"Enter student ID (whose result you want to update): "; cin >> studentID;

        Student* student = find_student_in_many_classes(year, studentID);
        if(student == NULL){
            Textcolor(_ERROR);
            cout << "Invalid student ID.\n";
            Textcolor(NORMAL);
            return;
        }
        Student_Course* student_cour = find_student_in_a_course(course_update,student->StudentID);
        
        cout<<"Update the following scores:\n";
        cout<<"Midterm: ";cin>>student_cour->mark.Midterm;
        cout<<"Final: ";cin>>student_cour->mark.Final;
        cout<<"Other: ";cin>>student_cour->mark.Other;
        double a,b,c;
        a = student_cour->mark.Midterm;
        b = student_cour->mark.Final;
        c = student_cour->mark.Other;
        student_cour->mark.Total = min(int(((a + b* 2)/3 + c)* 10 )/10.0, 10.0);// lam tron 1 chu so thap phan

        Cur_Course* cur_cour = student->pCur_Cour;
        while(cur_cour != NULL){
            if(cur_cour->CourseID != course_update->CourseID) cur_cour = cur_cour->pNext_Cur_Cour;
            else break;
        }
        // copy student_course score into cur_course student
        cur_cour->mark.Midterm = student_cour->mark.Midterm;
        cur_cour->mark.Final = student_cour->mark.Final;
        cur_cour->mark.Other = student_cour->mark.Other;
        cur_cour->mark.Total = student_cour->mark.Total;
        Textcolor(SUCCESS);  
        cout << "Result updated.\n";
        Textcolor(NORMAL);
    }
}
//25
void View_Class_Scoreboard_main(Class* classes){ 
    if (classes->pStudent == NULL){
        cout << "No student has been added in the class.\n";
        return;
    }   
    cout<<"________________________________________________________________________________________________________________________________\n";
    cout<<" Student ID |             Full name              |                                    Marks                                     \n";
    cout<<"____________|____________________________________|______________________________________________________________________________\n";
    Student* pCurStudent = classes->pStudent;
    string s = ""; 
    cout << setfill(' ');  
    while (pCurStudent != NULL){
        cout << "            |                                    | ";
        // print title
        Cur_Course* pCur_Cour = NULL;
        if(pCurStudent->pCur_Cour != NULL){
            pCur_Cour = pCurStudent->pCur_Cour;
            while(pCur_Cour != NULL){
                // print course id
                cout<< setw(12) << left << pCur_Cour->CourseID << " | ";
                pCur_Cour = pCur_Cour->pNext_Cur_Cour;
            }
        }
        cout << setw(12) << left << "Sem GPA" << " | ";
        cout << setw(12) << left << "Overall GPA" << "\n";
    
        //print concept
        cout << ' ' << setw(10) << left << pCurStudent->StudentID << " | ";
        s = pCurStudent->LastName + " " + pCurStudent->FirstName;
        cout << setw(34) << left << s << " | ";

        double GPA_this_semester = 0;
        int count = 0;
        if (pCurStudent->pCur_Cour != NULL){
            pCur_Cour = pCurStudent->pCur_Cour;  // copy pCur_Cour = pCurStudent->pCur_Cour
            while(pCur_Cour != NULL){
                // calculate
                double a,b,c;
                a = pCur_Cour->mark.Midterm;
                b = pCur_Cour->mark.Final;
                c = pCur_Cour->mark.Other;
                GPA_this_semester += ((a + b* 2)/3 + c);
                // courses's quantity
                count++;
                // print each course's score          
                Textcolor(15);
                cout << setw(7) << right << pCur_Cour->mark.Final;
                Textcolor(NORMAL);
                cout << "      | ";
                pCur_Cour = pCur_Cour->pNext_Cur_Cour;
            }
            GPA_this_semester = int((GPA_this_semester / count )* 10)/10.0;
            Textcolor(SUCCESS);
            cout << setw(7) << right << GPA_this_semester;
            Textcolor(NORMAL);
            cout << "      | ";
            Textcolor(SUCCESS);
            cout << setw(7) << right << pCurStudent->GPA << endl;
            Textcolor(NORMAL);
        }
        else{
            Textcolor(SUCCESS);
            cout << setw(7) << right << GPA_this_semester;
            Textcolor(NORMAL);
            cout << "      | ";
            Textcolor(SUCCESS);
            cout << setw(7) << right << pCurStudent->GPA << endl;
            Textcolor(NORMAL);
        }
        pCurStudent = pCurStudent->pNext_Student;
    }
}
//26
void Student_View_Scoreboard(Year* year, string studentID){
    cout << "Your scoreboard:\n";
    Student* student = find_student_in_many_classes(year, studentID);
    if (student == nullptr){
        cout << "\tCannot find student ID.\n";
    }
    else if(student->pCur_Cour == NULL){
        cout << "\tYou haven't enrolled in any courses.\n";
    } 
    else{
        Cur_Course* pCur = student->pCur_Cour;
        cout << "____________________________________________________________________________\n";
        cout << "                Course name               | Midterm | Final | Other | Total \n";
        cout << "__________________________________________|_________|_______|_______|_______\n";
        cout << setfill(' ');  
        while(pCur != NULL){
            cout << ' ' << setw(40) << left << pCur->Course_Name << " | ";
            cout << setw(7)  << right << pCur->mark.Midterm << " | ";
            cout << setw(5)  << right << pCur->mark.Final << " | ";
            cout << setw(5)  << right << pCur->mark.Other << " | ";
            cout << setw(5)  << right << pCur->mark.Total << "\n";
            pCur = pCur->pNext_Cur_Cour;
            cout << "__________________________________________|_________|_______|_______|_______\n"; 
        }    
    }
}

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
void del_cur_course_last_sem(Year* year) {
    while (year) {
        Class* _class = year->pClass;
        while (_class) {
            Student* st = _class->pStudent;
            while (st) {
                delete_cur_course(st);
                st = st->pNext_Student;
            }
            _class = _class->pNext_Class;
        }
        year = year->pNext_Year;
    }
}
// Load data
Class* find_class(Year* year, string name) {
    if (year == nullptr) return nullptr;
    Class* _class = year->pClass;
    while (_class && _class->name != name) _class = _class->pNext_Class;
    return _class;
}
Year* load_year(Year* &year, string name) {
    Year* pNew = new Year;
    pNew->name = name;
    pNew->pNext_Year = nullptr;
    pNew->pClass = nullptr;
    pNew->pSemester = nullptr;
    if (year == nullptr) year = pNew;
    else {
        Year* tmp = year;
        while (tmp->pNext_Year) tmp = tmp->pNext_Year;
        tmp->pNext_Year = pNew;
    }
    return pNew;
}
Course* load_course(Semester* sem, ifstream &fin) {
    Course* course = sem->pCourse;
    Course* newCourse = new Course;
    getline(fin, newCourse->CourseID, ',');
    getline(fin, newCourse->Number_of_Credits, ',');
    getline(fin, newCourse->Max_Student, ',');
    getline(fin, newCourse->Course_Name, ',');
    getline(fin, newCourse->Teacher_Name, ',');
    getline(fin, newCourse->Day1, ',');
    getline(fin, newCourse->Session1, ',');
    getline(fin, newCourse->Day2, ',');
    getline(fin, newCourse->Session2, ',');
    getline(fin, newCourse->Start_Day, ',');
    getline(fin, newCourse->End_Day, '\n');
    newCourse->pStudent_Course = nullptr;
    newCourse->pNext_Course = nullptr;
    while (course && course->pNext_Course) course = course->pNext_Course;
    if (course) course->pNext_Course = newCourse;
    else sem->pCourse = newCourse;
    return newCourse;
}
void load_student_cur_course(Year* year, string StudentID, Course* course, Mark mark) {
    Student *st = find_student_in_many_classes(year, StudentID);
    if (st != nullptr) {
        Cur_Course* cur_course = st->pCur_Cour, *tmp = Copy_Course(course);
        tmp->mark = mark;
        while (cur_course && cur_course->pNext_Cur_Cour)  cur_course = cur_course->pNext_Cur_Cour;
        if (cur_course) cur_course->pNext_Cur_Cour = tmp;
        else st->pCur_Cour = tmp;
    }
}
void load_student_in_course(string No, ifstream &fin, Course* course, Year* year) {
    Student_Course* st_c = course->pStudent_Course;
    Student_Course* newSt_C = new Student_Course;
    newSt_C->No = No;
    getline(fin, newSt_C->StudentID, ',');
    getline(fin, newSt_C->LastName, ',');
    getline(fin, newSt_C->FirstName, ',');
    getline(fin, newSt_C->Gender, ',');
    getline(fin, newSt_C->Date_of_Birth, ',');
    getline(fin, newSt_C->SocialID, ',');
    string s;
    getline(fin, s, ',');
    newSt_C->mark.Final = convert_to_double(s);
    getline(fin, s, ',');
    newSt_C->mark.Midterm = convert_to_double(s);
    getline(fin, s, ',');
    newSt_C->mark.Other = convert_to_double(s);
    getline(fin, s, '\n');
    newSt_C->mark.Total = convert_to_double(s);
    newSt_C->pNext_Student_Course = nullptr;
    load_student_cur_course(year, newSt_C->StudentID, course, newSt_C->mark);
    while (st_c && st_c->pNext_Student_Course) st_c = st_c->pNext_Student_Course;
    if (st_c) st_c->pNext_Student_Course = newSt_C;
    else course->pStudent_Course = newSt_C;
}
void load_course_and_student(Year* year, Semester* sem) {
    ifstream fin(year->name+"_HK"+sem->name+"_course.csv");
    if (fin.is_open() == false || check_empty(fin) == true) {
        fin.close();
        return;
    }
    string s;
    Course* course = nullptr;
    while (!fin.eof()) {
        getline(fin, s, ',');
        if (s==".") course = load_course(sem, fin);
        else load_student_in_course(s, fin, course, year);
    }
    fin.close();
}
void load_semester(Year* year, ifstream &fin) {
    Semester* sem = nullptr;
    string s;
    getline(fin, s, '\n');
    int n = convert_to_int(s);
    if (n==0) return;
    for (int i=0; i<n; ++i) {
        if (sem == nullptr) {
            sem = new Semester;
            year->pSemester = sem;
        }
        else {
            sem->pNext_Semester = new Semester;
            sem = sem->pNext_Semester;
        }
        sem->name = to_string(i+1);
        sem->pCourse = nullptr;
        load_course_and_student(year, sem);
        sem->pNext_Semester = nullptr;
    }
}
void load_student(Class* _class, ifstream &fin) {
    Student* pCur_St = _class->pStudent;
    while (pCur_St && pCur_St->pNext_Student) pCur_St = pCur_St->pNext_Student; 
    Student* st = new Student;
    getline(fin, st->No, ',');
    getline(fin, st->StudentID, ',');
    getline(fin, st->LastName, ',');
    getline(fin, st->FirstName, ',');
    getline(fin, st->Gender, ',');
    string s;
    getline(fin, s, ',');
    st->GPA = convert_to_double(s);
    getline(fin, st->Date_of_Birth, ',');
    getline(fin, st->SocialID, '\n');
    st->pCur_Cour = nullptr;
    st->pNext_Student = nullptr;
    if (pCur_St) pCur_St->pNext_Student = st;
    else _class->pStudent = st;
}
void load_class(Year* year) {
    ifstream fin(year->name+"_class_student.csv");
    if (fin.is_open() == false || check_empty(fin) == true) {
        fin.close();
        return;
    }
    string s;
    year->pClass = nullptr;
    Class* _class = nullptr;
    while (!fin.eof()) {
        getline(fin, s, ',');
        if (find_class(year, s) == nullptr) {
            Class* newClass = new Class;
            newClass->name = s;
            newClass->pNext_Class = nullptr;
            newClass->pStudent = nullptr;
            if (!_class) {
                year->pClass = newClass;
                _class = newClass;
            }
            else {
                 _class->pNext_Class = newClass;
                 _class = _class->pNext_Class;
            }
        }
        load_student(_class, fin);
    }
    fin.close();
}
void load_regis_time(Registration_Session &S) {
    ifstream fin("Regis_Time.csv");
    if (fin.is_open() == false || check_empty(fin) == true) {
        fin.close();
        return;
    }
    string s;
    getline(fin, s, ',');
    S.start.date = convert_to_int(s);
    getline(fin, s, ',');
    S.start.month = convert_to_int(s);
    getline(fin, s, ',');
    S.start.year = convert_to_int(s);
    getline(fin, s, ',');
    S.start.hour = convert_to_int(s);
    getline(fin, s, '\n');
    S.start.minute = convert_to_int(s);
    getline(fin, s, ',');
    S.end.date = convert_to_int(s);
    getline(fin, s, ',');
    S.end.month = convert_to_int(s);
    getline(fin, s, ',');
    S.end.year = convert_to_int(s);
    getline(fin, s, ',');
    S.end.hour = convert_to_int(s);
    getline(fin, s, '\n');
    S.end.minute = convert_to_int(s);
    fin.close();
}
void load_main(Year* &year, Registration_Session &S) {
    ifstream fin("year_sem.csv");
    if (fin.is_open() == false || check_empty(fin) == true) {
        fin.close();
        return;
    }
    Year* Tmp_y = nullptr;
    while (!fin.eof()) {
        string s;
        getline(fin, s, ',');
        Tmp_y = load_year(year, s);
        load_class(Tmp_y);
        load_semester(Tmp_y, fin);
    }
    fin.close();
    
    load_regis_time(S);
}

//Save
void save_course(Year* year, Semester* sem) {
    Course* course = sem->pCourse;
    ofstream fout(year->name+"_HK"+sem->name+"_course.csv");
    while (course) {
        fout<<".,"<<course->CourseID<<","<<course->Number_of_Credits<<","<<course->Max_Student<<","<<course->Course_Name
        <<","<<course->Teacher_Name<<","<<course->Day1<<","<<course->Session1<<","<<course->Day2
        <<","<<course->Session2<<","<<course->Start_Day<<","<<course->End_Day;
        Student_Course* st = course->pStudent_Course;
        while (st) {
            fout<<"\n";
            fout<<st->No<<","<<st->StudentID<<","<<st->LastName<<","<<st->FirstName<<","<<st->Gender<<","<<st->Date_of_Birth
            <<","<<st->SocialID<<","<<st->mark.Final<<","<<st->mark.Midterm<<","
            <<st->mark.Other<<","<<st->mark.Total;
            st = st->pNext_Student_Course;
        }
        course = course->pNext_Course;
        if (course) fout<<"\n";
    }

    fout.close();
}
void save_course_main(Year* year) {
    while (year) {
        Semester* sem = year->pSemester;
        while (sem) {
            save_course(year, sem);
            sem = sem->pNext_Semester;
        }
        year = year->pNext_Year;
    }
}
void save_year_semester(Year* year) {
    while (year->pNext_Year) year=year->pNext_Year;
    ofstream fout;
    fout.open("year_sem1.csv");
    ifstream fin;
    fin.open("year_sem.csv");
    string s;
    while (!fin.eof()) {
        getline(fin, s, ',');
        if (s==year->name) break; 
        fout<<s<<",";
        getline(fin, s, '\n');
        fout<<s<<"\n";
    }
    Semester* sem=year->pSemester;
    string cnt="0";
    while (sem) {
        cnt=sem->name;
        sem=sem->pNext_Semester;
    }
    fout<<year->name<<","<<cnt;
    fin.close();
    fout.close();
    remove("year_sem.csv");
    rename("year_sem1.csv", "year_sem.csv");
}
void save_class_student(Year* year, Class* _class) {
    ofstream fout(year->name+"_class_student.csv");
    while(_class != nullptr) {
        Student* st = _class->pStudent;
        while(st != nullptr) {
            fout<<_class->name<<",";
            fout<<st->No<<","<<st->StudentID<<","<<st->LastName<<","<<st->FirstName
            <<","<<st->Gender<<","<<st->GPA<<","<<st->Date_of_Birth<<","<<st->SocialID;
            st = st->pNext_Student;
            if (st) fout<<"\n";
        }
        _class = _class->pNext_Class;
        if (_class != nullptr) fout<<"\n";
    }
    fout.close();
}
void save_class_student_main(Year* year) {
    while (year->pNext_Year) year=year->pNext_Year;
    save_class_student(year, year->pClass);
}
void save_regis_time(Registration_Session &S) {
    ofstream fout("Regis_Time.csv");
    fout<<S.start.date<<","<<S.start.month<<","<<S.start.year<<","<<S.start.hour<<","<<S.start.minute<<"\n";
    fout<<S.end.date<<","<<S.end.month<<","<<S.end.year<<","<<S.end.hour<<","<<S.end.minute;
    fout.close();
}
// copy class and student
void copy_file(Year* year1, Year* year2) {
    ifstream fin;
    fin.open(year1->name+"_class_student.csv", ios::binary);
    fin.seekg(0, ios::end);
    int size = fin.tellg();
    char* data = new char[size];
    fin.seekg(0, ios::beg);
    fin.read(data, size);
    fin.close();
    ofstream fout;
    fout.open(year2->name+"_class_student.csv", ios::binary);
    fout.write(data, size);
    fout.close();
    delete [] data;
}
void copy_class_student(Year* year1, Year* year2) {
    copy_file(year1, year2);
    load_class(year2);
}

// not add button of profile
// view profile
void Staff_profile(Staff* &staff){
    ifstream filein("staff_profile.csv");
    if(filein.is_open()){
        Staff* pCur_staff = NULL;
        while(filein.eof() == false){
            Staff* pTemp = new Staff;
            getline(filein,pTemp->Email,',');
            getline(filein,pTemp->Full_name,',');
            getline(filein,pTemp->Gender,',');
            getline(filein,pTemp->Birth_of_date,',');
            getline(filein,pTemp->Social_ID,'\n');
            pTemp->pNext_Staff = NULL;
            if(staff == NULL){
                staff = pTemp;
            }else{
                pCur_staff->pNext_Staff = pTemp;
            }
            pCur_staff = pTemp;
        }
    }
    filein.close();
}
void output_staff(Staff* staff, string username){
    cout << setfill(' ');
    Textcolor(10);
    gotoxy(52, 8); cout << setw(24) << right << "---PROFILE---";
    Textcolor(NORMAL);
    if(staff == NULL) {
        gotoxy(52, 10);
        cout << setw(20) << right << "No data.\n";
        return;
    }
    Staff* pCur = staff;
    while(pCur != NULL){
        if(username == pCur->Email){
            gotoxy(52, 10); cout << setw(14) << left << "Email" << " : " << pCur->Email << endl;
            gotoxy(52, 11); cout << setw(14) << left << "Full name" << " : " << pCur->Full_name << endl;
            gotoxy(52, 12); cout << setw(14) << left << "Gender" << " : " << pCur->Gender << endl;
            gotoxy(52, 13); cout << setw(14) << left << "Date of Birth" << " : " << pCur->Birth_of_date << endl;
            gotoxy(52, 14); cout << setw(14) << left << "Social ID" << " : " << pCur->Social_ID;
            break;
        }
        else pCur = pCur->pNext_Staff;
    }
}
//No, StudentID, Fullname, Gender, Date_of_Birth, SocialID
void Student_profile(Year* year,string username){
    cout << setfill(' ');
    Textcolor(10);
    gotoxy(52, 8); cout << setw(23) << right << "---PROFILE---\n\n";
    Textcolor(NORMAL);

    Student* student = nullptr;
    Year* curYear = year;
    while (curYear != nullptr && student == nullptr){
        student = find_student_in_many_classes(curYear, username);
        curYear = curYear->pNext_Year;
    }
    if(student == NULL){
        gotoxy(52, 10);
        cout << setw(20) << right << "No data.\n";
    }
    else{
        gotoxy(52, 10); cout << setw(14) << left << "No" << " : " << student->No << endl;
        gotoxy(52, 11); cout << setw(14) << left << "Student ID" << " : "<< student->StudentID << endl;
        gotoxy(52, 12); cout << setw(14) << left << "Full name" << " : " << student->LastName << " " << student->FirstName << endl;
        gotoxy(52, 13); cout << setw(14) << left << "Gender" << " : " << student->Gender << endl;
        gotoxy(52, 14); cout << setw(14) << left << "Date of Birth" << " : " << student->Date_of_Birth << endl;
        gotoxy(52, 15); cout << setw(14) << left << "SocialID" << " : " << student->SocialID;
    }
}

//logo portal
void logo_portal(int x,int y){
    Textcolor(10);
    gotoxy(x, y+0);cout << "    ____  ____  ____  _________    __" << endl;
    gotoxy(x, y+1);cout << "   / __ \\/ __ \\/ __ \\/_  __/   |  / /" << endl;
    gotoxy(x, y+2);cout << "  / /_/ / / / / /_/ / / / / /| | / /" << endl;
    gotoxy(x, y+3);cout << " / ____/ /_/ / _, _/ / / / ___ |/ /___" << endl;
    gotoxy(x, y+4);cout << "/_/    \\____/_/ |_| /_/ /_/  |_/_____ /" << endl;
}
//new
void box(int x,int y,int width, int height, int textcolor,int bcolor ,string text) {

	Textcolor(10);
	gotoxy(x + 1, y + 1);
	cout << text;
	
	Textcolor(BOX);
	for (int i = x; i <= x + width; i++) {
		gotoxy(i, y);
		cout << char(205);
		gotoxy(i, y + height);
		cout << char(205);
	}
	for (int i = y; i <= y + height; i++) {
		gotoxy(x, i);
		cout << char(186);
		gotoxy(x + width, i);
		cout << char(186);
	}
	gotoxy(x, y); cout << char(201);
	gotoxy(x + width, y); cout << char(187);
	gotoxy(x, y + height); cout << char(200);
	gotoxy(x + width, y + height); cout << char(188);
    Textcolor(NORMAL);
}

//staff
void COURSE_PAGE(Year* &year,Semester* &sem,int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[],Registration_Session &S) {

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1){
                    system("cls");
                    Print_Course(year, sem);
                    Create_Course(year, sem);
                    save_course_main(year);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 2){
                    system("cls");
                    Print_Course(year, sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if(cell == 3){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr)
                        cout << "You need to add a course to update it.";
                    else
                        Update_Course(sem);
                    save_course_main(year);
                    cin.ignore(1000, '\n');
                    getchar();
                    
                }else if(cell == 4){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr){
                        cout << "You need to add a course to delete it.";
                    }
                    else{
                        Delete_Course(sem);
                        save_course_main(year);
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                    save_course_main(year);
                }else if(cell == 5){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr){
                        cout << "You need to add a course to view its students.";
                    }
                    else{
                        View_Student_In_Course(sem);
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                }else if(cell == 6){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr)
                        cout << "You need to create a course to import its scoreboard.\n";
                    else
                        Create_mark_main(year,sem);
                    cin.ignore(1000, '\n');
                    getchar();
                    save_course_main(year);
                }else if(cell == 7){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr){
                        cout << "You need to create a course to view its scoreboard.\n";
                    }
                    else{
                        View_scoreboard_main(sem);
                    }
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 8){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr)
                        cout << "You need to create a course to export its scoreboard.\n";
                    else
                        Export_Course_main(year, sem);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 9){
                    system("cls");
                    Print_Course(year, sem);
                    if (sem->pCourse == nullptr)
                        cout << "You need to create a course to update its scoreboard.\n";
                    else{
                        update_student_result(year,sem);
                        calcu_oGPA_main(year);
                    }
                    cin.ignore(1000, '\n');
                    getchar();
                    save_class_student_main(year);
                    save_course_main(year);
                }else if(cell == 10){
                    system("cls");
                    create_Registration_Session(S);
                    cin.ignore(1000, '\n');
                    getchar();
                    save_regis_time(S);
                }
				else if (cell == 11) {
					HOME = 4;
					return;
				}
				else if (cell == 12) break;

                system("cls");  // print box for all
                for (int i = 0; i < number_of_cells; i++) {
		            box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
	            }        
			}
		}
	}
}
void SEMESTER_PAGE(Year* &year,int locate_x, int locate_y, int number_of_cells, string SEMESTER_name_list_of_boxs[],Registration_Session &S) {
    Semester* import_sem;

    // print chosen year
    gotoxy(62,6);
    Textcolor(10);
    cout << "SCHOOL YEAR " << year->name << endl;
    Textcolor(NORMAL);

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");
                    Print_Semester(year);
                    Create_Semester(year);
                    if (year->pSemester->pNext_Semester) {
                        calcu_oGPA_main(year);
                        save_class_student_main(year);
                    }
                    save_year_semester(year);
                    del_cur_course_last_sem(year);
                }else if (cell == 2){
                    system("cls");
                    Print_Semester(year);
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 3) {
                    system("cls");
                    Print_Semester(year);
                    if (year->pSemester == nullptr){
                        cout << "You need to create a semester to view courses.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                    else{
                        import_sem = Import_Semester(year->pSemester);

                        if(import_sem == NULL){
                            Textcolor(_ERROR);
                            cout<<"Invalid semester.";
                            Textcolor(NORMAL);
                            cin.ignore(1000, '\n');
                            getchar();                       
                        }else{
                            system("cls");
                            string COURSE_name_list_of_boxs[] = { "Create course","View course","Update course","Delete course","View student","Create mark","View scoreboard","Export course","Update result","Time registration","Home","Return" };
                            COURSE_PAGE(year,import_sem,locate_x, 2, 12, COURSE_name_list_of_boxs,S); // set locate_y = 2
                        }
                        
                        system("cls");
                        //
                        if (HOME == 4) return;
                        //
                        for (int i = 0; i < number_of_cells; i++) {
                            box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
                        }
                    }
				}
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;

                system("cls");
                // print chosen year
                gotoxy(62,6);
                Textcolor(10);
                cout << "SCHOOL YEAR " << year->name << endl;
                Textcolor(NORMAL);

                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_name_list_of_boxs[i]);
				}
			}
		}
	}
}


void STUDENT_PAGE(Year* &year,Class* &classes, Account* account_head, int locate_x, int locate_y, int number_of_cells, string STUDENT_name_list_of_boxs[]) {
    // print chosen class
    gotoxy(64,6);
    Textcolor(10);
    cout << "CLASS " << classes->name << endl;
    Textcolor(NORMAL);

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, STUDENT_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");
                    Print_Student(classes);
                    Create_Student(year, classes, account_head);
                    save_account_list(account_head); // save account
                    save_class_student_main(year);
                    cin.ignore(1000, '\n');
                    getchar();
                }   
                else if (cell == 2){
                    system("cls");
                    Print_Student(classes);
                    Add_1_Student_main(year, classes, account_head);
                    save_class_student_main(year);
                    save_account_list(account_head); // save account
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if (cell == 3){
                    system("cls");
                    Print_Student(classes);
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 4) {
					HOME = 4;
					return;
				}
				else if (cell == 5) break;

                system("cls");
                // print chosen class
                gotoxy(64,6);
                Textcolor(10);
                cout << "CLASS " << classes->name << endl;
                Textcolor(NORMAL);
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, STUDENT_name_list_of_boxs[i]);
				}
			}
		}
	}
}
void CLASS_PAGE(Year* &year, Account* account_head, int locate_x, int locate_y, int number_of_cells, string CLASS_name_list_of_boxs[]) {
    // print chosen year
    gotoxy(62,6);
    Textcolor(10);
    cout << "SCHOOL YEAR " << year->name << endl;
    Textcolor(NORMAL);

    Class* import_class;
	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CLASS_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");
                    Print_Class(year);
                    Create_Class(year);
                    cin.ignore(1000,'\n');
                    getchar();
                    save_class_student_main(year);
                }else if (cell == 2){
                    system("cls");
                    Print_Class(year);
                    cin.ignore(1000,'\n');
                    getchar();
                }
				else if (cell == 3) {
					system("cls");
                    Print_Class(year);
                    if (year->pClass == nullptr){
                        cout << "You need to create a class to view students.";
                        cin.ignore(1000,'\n');
                        getchar();
                    }
                    else{
                        import_class = Import_Class(year->pClass);

                        if(import_class == NULL){
                            Textcolor(_ERROR);
                            cout<<"Invalid class.";
                           Textcolor(_ERROR);
                            cin.ignore(1000, '\n');
                            getchar();
                        }
                        else{
                            system("cls");
                            string STUDENT_name_list_of_boxs[] = { "Create student","Add 1 student","View students","Home","Return" }; 
                            STUDENT_PAGE(year,import_class,account_head, locate_x, locate_y, 5, STUDENT_name_list_of_boxs);
                        }
                        //
                        if (HOME == 4) return;
                        //
                    }
				}else if (cell == 4){
                    // continue //gan ham 25
                    system("cls");
                    Print_Class(year);
                    if (year->pClass == nullptr){
                        cout << "You need to create a class to view scoreboard.";
                        cin.ignore(1000,'\n');
                        getchar();
                    }
                    else{
                        import_class = Import_Class(year->pClass);

                        if(import_class == NULL){
                            Textcolor(_ERROR);
                            cout<<"Invalid class.";
                            Textcolor(NORMAL);
                            cin.ignore(1000, '\n');
                            getchar();
                        }
                        else{
                            system("cls");
                            View_Class_Scoreboard_main(import_class);	
                        }
                        cin.ignore(1000, '\n');  // test 25 vs 26
                        getchar();
                    }
                }
				else if (cell == 5) {
					HOME = 4;
					return;
				}
				else if (cell == 6) break;
                system("cls");

                // print chosen year
                gotoxy(62,6);
                Textcolor(10);
                cout << "SCHOOL YEAR " << year->name << endl;
                Textcolor(NORMAL);

                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CLASS_name_list_of_boxs[i]);
				}
			}
		}


	}
}
void YEAR_PAGE(Year* &year, Account* account_head, int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[],Registration_Session &S) {
    Year* import_year;

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");

                    Print_Year(year);
                    if (year) {
                        calcu_oGPA_main(year);
                        save_class_student_main(year);
                    }
                    Year* tmpYear = year, *tmp2Year = year;
                    while (tmpYear->pNext_Year) tmpYear = tmpYear->pNext_Year;
                    Create_Year(year);
                    while (tmp2Year->pNext_Year) tmp2Year = tmp2Year->pNext_Year;
                    copy_class_student(tmpYear, tmp2Year);
                    save_class_student_main(year);
                    save_year_semester(year);
                }else if (cell == 2){
                    system("cls");
                    Print_Year(year);
                    cin.ignore(1000, '\n');
                    getchar();
                }
				else if (cell == 3) {
                    system("cls");
                    Print_Year(year);
                    if (year == nullptr){
                        cout << "You need to create a new school year.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                    else{
                        import_year = Import_Year(year); // import year

                        if(import_year == NULL){
                            Textcolor(_ERROR);
                            cout<<"Invalid year.";
                            Textcolor(NORMAL);
                            cin.ignore(1000, '\n');
                            getchar();
                        }
                        else{
                            system("cls");
                            string CLASS_name_list_of_boxs[] = { "Create class","View classes","View student","View scoreboard","Home","Return" };
                            CLASS_PAGE(import_year, account_head, locate_x, locate_y, 6, CLASS_name_list_of_boxs);
                        }							
                        //
                        if (HOME == 4) return;
                        //
                    }
				}
				else if (cell == 4) {
                    system("cls");
                    Print_Year(year);
                    if (year == nullptr){
                        cout << "You need to create a new school year.\n";
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                    else{
                        import_year = Import_Year(year); // import year

                        if(import_year == NULL){
                            Textcolor(_ERROR);
                            cout<<"Invalid year.";
                            Textcolor(NORMAL);
                            cin.ignore(1000, '\n');
                            getchar();
                        }
                        else{
                            system("cls");
                            string SEMESTER_name_list_of_boxs[] = { "Create semester","View semester","View course","Home","Return" };
                            SEMESTER_PAGE(import_year,60, 10, 5, SEMESTER_name_list_of_boxs,S);
                        }	
                        //
                        if (HOME == 4) return;
                        //
                    }
				}
				else if (cell == 5) {
					// enter HOME -> nothing happens because here is HOME
				}
				else if (cell == 6) break;
                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
				}
			}
		}


	}
}

// student
void COURSE_STU_PAGE(Year* &year,Semester* &sem, User U, int locate_x, int locate_y, int number_of_cells, string COURSE_name_list_of_boxs[],Registration_Session &S) {
    Textcolor(10);
    gotoxy(62,6); cout << "SCHOOL YEAR " << year->name << endl;
    gotoxy(62,7); cout << "   SEMESTER " << sem->name << endl;
    Textcolor(NORMAL);

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1){
                    system("cls");
                    Print_Course(year, sem); // ko in ra cac mon hoc
                    enroll_main(year, sem, U.username, S);  // continue
                    save_course_main(year);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 2){
                    system("cls");
                    View_Enrolled_Course_main(year, U.username);

                    //Student* temp = find_student_in_many_classes(year,username);  // find student to check Cur_Course
                    //if(temp->pCur_Cour == NULL) cout<<"no courses was enrolled ";

                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 3){
                    system("cls");
                    // Print_Course(year, sem);
                    View_Enrolled_Course_main(year, U.username);
                    Delete_Enrolled_Course_main(year, sem, U.username, S);
                    save_course_main(year);
                    cin.ignore(1000, '\n');
                    getchar();
                }else if(cell == 4){
                    system("cls");
                    Student_View_Scoreboard(year, U.username);
                    cin.ignore(1000, '\n');
                    getchar();
                }
                else if (cell == 5) {
					HOME = 4;
					return;
				}
				else if (cell == 6) break;

                system("cls");
                Textcolor(10);
                gotoxy(62,6); cout << "SCHOOL YEAR " << year->name << endl;
                gotoxy(62,7); cout << "   SEMESTER " << sem->name << endl;
                Textcolor(NORMAL);

                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, COURSE_name_list_of_boxs[i]);
				}
			}
		}
	}
}
void SEMESTER_STU_PAGE(Year* &year, User U, int locate_x, int locate_y, int number_of_cells, string SEMESTER_STU_name_list_of_boxs[],Registration_Session &S) {
    gotoxy(62,6);
    Textcolor(10);
    cout << "SCHOOL YEAR " << year->name << endl;
    Textcolor(NORMAL);
    
    Semester* import_sem;

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_STU_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");
                    Print_Semester(year);

                    import_sem = Import_Semester(year->pSemester);

                    if(import_sem == NULL){
                        cout<<"No semester was created.";
                        cin.ignore(1000, '\n');
                        getchar();                       
                    }else{
                        system("cls");
					    string COURSE_STU_name_list_of_boxs[] = { "Enroll course","View my course","Remove course","View scoreboard","Home","Return"};
					    COURSE_STU_PAGE(year,import_sem,U,locate_x, locate_y, 6, COURSE_STU_name_list_of_boxs,S);
                    }
					
					//
					if (HOME == 4) return;
					//
					
				}
				else if (cell == 2) {
					HOME = 4;
					return;
				}
				else if (cell == 3) break;

                system("cls");

                gotoxy(62,6);
                Textcolor(10);
                cout << "SCHOOL YEAR " << year->name << endl;
                Textcolor(NORMAL);

                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, SEMESTER_STU_name_list_of_boxs[i]);
				}
			}
		}
	}
}
void YEAR_STU_PAGE(Year* &year, User U, int locate_x, int locate_y, int number_of_cells, string YEAR_name_list_of_boxs[],Registration_Session &S) {
    Year* import_year;

	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");
                    Print_Year(year);

                    import_year = Import_Year(year); // import year

                    if(import_year == NULL){
                        cout<<"No year was created.";
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
					    string SEMESTER_name_list_of_boxs[] = {"View semester","Home","Return" };
					    SEMESTER_STU_PAGE(import_year, U, locate_x, locate_y, 3, SEMESTER_name_list_of_boxs,S);
                    }	
					//
					if (HOME == 4) return;
					//
					
				}
				else if (cell == 2) {
					HOME = 4;
					return;
				}
				else if (cell == 3) break;
                system("cls");
                for (int i = 0; i < number_of_cells; i++) {
					box(locate_x, locate_y + i * 3, 20, 2, 10, 11, YEAR_name_list_of_boxs[i]);
				}
			}
		}
	}
}

void CHANGE_PASS_PAGE(Year* &year, Account* account_head, User &U, int locate_x,int locate_y, int number_of_cells, string CHANGE_PASS_name_list_of_boxs[],Registration_Session &S, Staff* &staff){  

    string user_change, password;
	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CHANGE_PASS_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
        HOME = 0;
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
                if (cell == 1) {
                    if (isStaff(U.username)){
                        system("cls"); //staff
					    string YEAR_name_list_of_boxs[] = { "Create year","View list of years","View classes","View semesters","Home","Return"};
					    YEAR_PAGE(year, account_head, locate_x, locate_y, 6, YEAR_name_list_of_boxs,S);
	
                    }else{
                        system("cls"); //student
                        string YEAR_STU_name_list_of_boxs[] = {"View year","Home","Return"};
                        YEAR_STU_PAGE(year, U, locate_x, locate_y, 3, YEAR_STU_name_list_of_boxs,S);
                    }				
				}else if(cell == 2){
                    if(isStaff(U.username)){
                        system("cls");
                        output_staff(staff,U.username);
                        cin.ignore(1000, '\n');
                        getchar();
                    }else{
                        system("cls");
                        Student_profile(year,U.username);
                        cin.ignore(1000, '\n');
                        getchar();
                    }
                }
                else if(cell == 3){
                    system("cls");    
                   
                    Textcolor(10);
                    gotoxy(52, 8); cout << setfill(' ') << setw(30) << right << "---CHANGE PASSWORD---";
                    Textcolor(NORMAL);   

                    gotoxy(52, 10); cout << "Enter your username: "; cin >> user_change;
                    gotoxy(52, 11); cout << "Enter old password: "; cin >> password;
                    
                    if (user_change == U.username && password == U.password){
                        gotoxy(52, 12); cout << "Enter new password: ";
                        cin >> U.password;

                        change_password(account_head, U);
                        save_account_list(account_head); // save account
                        Textcolor(SUCCESS);
                        gotoxy(52, 14); cout << "Password has been changed.\n";
                        Textcolor(NORMAL);
                        cin.ignore(1000, '\n');
                        getchar();
                    } 
                    else{
                        Textcolor(_ERROR);
                        gotoxy(52, 13); cout << "Username or password is incorrect.\n";
                        Textcolor(NORMAL);
                        cin.ignore(1000, '\n');
                        getchar();                            
                    }
                                        
                }			                    
				else if (cell == 4) break;
                system("cls");

                for (int i = 0; i < number_of_cells; i++) {
                    box(locate_x, locate_y + i * 3, 20, 2, 10, 11, CHANGE_PASS_name_list_of_boxs[i]);
                }
			}
		}
	}
}
void LOGIN_PAGE(Year* &year, Account* account_head, User U, int locate_x,int locate_y, int number_of_cells, string LOGIN_name_list_of_boxs[],Registration_Session &S, Staff* &staff) { 
    account_head = load_account_list();
    Staff_profile(staff);
    logo_portal(51,4);
	for (int i = 0; i < number_of_cells; i++) {
		box(locate_x, locate_y + i * 3, 20, 2, 10, 11, LOGIN_name_list_of_boxs[i]);
	}
	int x = locate_x - 1, y = locate_y + 1;
	gotoxy(x, y);
	cout << char(26);
	int xcu = x, ycu = y;
	bool hold = true;
	int cell = 1;

	while (true) {
        LOG_OUT = 0;
		if (hold == true) {
			gotoxy(xcu, ycu);
			cout << " ";
			gotoxy(x, y);
			cout << char(26);
			
			hold = false;
		}
		if (_kbhit()) {
			hold = true; // da bam
			char var = _getch();

			if (var == 72) { //len
				if (x == locate_x - 1 && y == locate_y + 1) {
					ycu = y;
					y += 3 * (number_of_cells - 1);
					cell = number_of_cells;
				}
				else {
					ycu = y;
					y -= 3;
					cell -= 1;
				}
			}
			else if (var == 80) { //xuong
				if (x == locate_x - 1 && y == (locate_y + 1) + (number_of_cells - 1) * 3) {
					ycu = y;
					y -= 3 * (number_of_cells - 1);
					cell = 1;
				}
				else {
					ycu = y;
					y += 3;
					cell += 1;
				}
			}
			else if (var == 13) {
				if (cell == 1) {
                    system("cls");

                    gotoxy(52, 8);
                    Textcolor(10);
                    cout << setfill(' ') << setw(23) << right << "---LOG IN---";
                    Textcolor(NORMAL);

                    gotoxy(52, 10);
                    cout << "Enter username: ";
                    cin >> U.username;

                    gotoxy(52, 11);
                    cout << "Enter password: ";
                    cin >> U.password;

                    if (account_check(account_head, U)){
                        Textcolor(SUCCESS);
                        gotoxy(52, 13); cout << "Log in successfully.\n";
                        Textcolor(NORMAL);

                        cin.ignore(1000, '\n');
                        getchar();
                        system("cls");
                        string CHANGE_PASS_name_list_of_boxs[] = { "HOME","VIEW PROFILE","CHANGE PASSWORD","LOG OUT"};
                        CHANGE_PASS_PAGE(year, account_head, U, locate_x, locate_y, 4, CHANGE_PASS_name_list_of_boxs,S,staff);
                    }
                    else{
                        Textcolor(_ERROR);
                        gotoxy(52, 13); cout << "Username or password is incorrect.\n";
                        Textcolor(NORMAL);

                        cin.ignore(1000, '\n');
                        getchar();
                    }
                } else if (cell == 2) break;

                system("cls");
                logo_portal(51,4);
                for (int i = 0; i < number_of_cells; i++) {
                    box(locate_x, locate_y + i * 3, 20, 2, 10, 11, LOGIN_name_list_of_boxs[i]);
                }   
			}
		}
	}
    gotoxy(1,20);
}