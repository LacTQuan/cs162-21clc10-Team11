struct Semester{
    string name;
    Semester* pNext_Semester;
    Course* pCourse;
};

// 18
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
