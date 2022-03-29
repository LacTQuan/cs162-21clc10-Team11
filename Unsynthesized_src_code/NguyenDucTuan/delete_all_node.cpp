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
// continue