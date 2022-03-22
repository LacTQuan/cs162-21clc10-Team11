double rand_mark() {
    //srand(time(NULL));
    return min(10.0, (rand() % 11) * 1.0 + (rand() % 10) / 10.0);
}
void Assign_Mark(Year* year, string Student_ID, double total, double final, double mid, double other) {
    Student* Std = find_student_in_many_classes(year, Student_ID);
    // Student id always exists in this case-->no check null
    Std->pCur_Cour->mark.Final = final,
    Std->pCur_Cour->mark.Midterm = mid,
    Std->pCur_Cour->mark.Other = other,
    Std->pCur_Cour->mark.Total = total;
}
void Create_Mark(Semester* sem) {
    string s;
    cout << "Course name: ";
    cin >> s;
    Course* cour = find_Course(sem->pCourse, s);
    while (cour == nullptr || (cour->Course_Name != s && cour->pNext_Course == nullptr)) {
        cout << "Course not found. Try again: ";
        cin >> s;
        cour = find_Course(sem->pCourse, s);
    }
    if (cour->Course_Name != s) cour = cour->pNext_Course;
    if (cour->pStudent_Course == nullptr) {
        cout << "No student in this course!" << endl;
        return;
    }
    ofstream fout(s + ".csv");
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
int convert_to_int(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++)
        res = res * 10 + (s[i] - '0');
    return res;
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
        Assign_Mark(year, pCurStd->StudentID, pCurStd->mark.Total, pCurStd->mark.Final,
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
    cin.ignore(1000, '\n');
    getchar();
}