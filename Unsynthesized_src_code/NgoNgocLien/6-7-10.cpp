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

// 6
void create_Semester(Year *year){
    Year *pCur_Year;
    string find_year;
    do{
        pCur_Year = year;
        cout << "Academic year to import semester (ex:2020-2021): ";
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

// 7
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

// 10
// only able to update course of latest semester
void Update_Course(Year *year){
	// find latest year & semester
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
