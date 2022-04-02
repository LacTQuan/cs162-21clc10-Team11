// Load
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
    ifstream fin(year->name+sem->name+"_course.csv");
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
void load_regis_time() {
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
    getline(fin, s, '\n');
    S.start.year = convert_to_int(s);
    getline(fin, s, ',');
    S.end.date = convert_to_int(s);
    getline(fin, s, ',');
    S.end.month = convert_to_int(s);
    getline(fin, s, '\n');
    S.end.year = convert_to_int(s);
    fin.close();
}
void load_main(Year* &year) {
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
    
    load_regis_time();
}