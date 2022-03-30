//save
void Save_Course(Year* year, Semester* sem) {
    Course* course = sem->pCourse;
    ofstream fout(year->name+sem->name+"_course.csv");
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
void Save_Course_main(Year* year) {
    while (year) {
        Semester* sem = year->pSemester;
        while (sem) {
            Save_Course(year, sem);
            sem = sem->pNext_Semester;
        }
        year = year->pNext_Year;
    }
}
void Save_Year_Semester(Year* year) {
    ofstream fout("year_sem.csv");
    while (year) {
        fout<<year->name;
        Semester* sem = year->pSemester;
        int max_sem = 1;
        while(sem) {
            max_sem = max(max_sem, convert_to_int(sem->name));
            sem = sem->pNext_Semester;
        }
        fout<<","<<max_sem;
        if (year->pNext_Year != nullptr) fout<<"\n";
        year = year->pNext_Year;
    }
    fout.close();
}
void Save_Class_Student(Year* year, Class* _class) {
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
void Save_Class_Student_main(Year* year) {
    while (year) {
        Save_Class_Student(year, year->pClass);
        year = year->pNext_Year;
    }
}
void Save_Reigis_Time() {
    ofstream fout("Regis_Time.csv");
    fout<<S.start.date<<","<<S.start.month<<","<<S.start.year<<"\n";
    fout<<S.end.date<<","<<S.end.month<<","<<S.end.year;
    fout.close();
}
void Save_main(Year* year) {
    while (year) {
        Save_Year_Semester(year);
        Save_Class_Student_main(year);
        Save_Course_main(year);
        year = year->pNext_Year;
    }
}