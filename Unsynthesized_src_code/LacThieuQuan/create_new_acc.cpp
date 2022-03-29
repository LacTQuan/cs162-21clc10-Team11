void Create_Account_For_new_Student(string student_id) {
    Account* head = load_account_list(), *cur = head;
    Account* newAcc = new Account;
    newAcc->username = student_id;
    newAcc->password = "123456789";
    newAcc->next = nullptr;

    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;

    if (cur == nullptr) cur = newAcc;
    else cur->next = newAcc;
    save_account_list(head);
}
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
        pNew_Student->No = to_string(convert_to_int(pCur_Student->No) + 1);
        pCur_Student->pNext_Student = pNew_Student;
    }
}
void Add_1_Student_main(Year* year) {
    string student_id;
    Class* import_class = nullptr;
    
    do {
        import_class = Import_Class(year->pClass);
    } while (import_class == nullptr);
    
    Student* stu = nullptr;
    
    do {
        cout<<"Enter the new student's id, (existed id is not allowed): "; cin>>student_id;
        stu = find_student_in_many_classes(year, student_id);
    } while (stu != nullptr);
    
    Add_1_Student(import_class, student_id);
    cout<<"Added!"<<endl;
    cin.ignore();
    getchar();
    Create_Account_For_new_Student(student_id);
    cin.ignore();
    getchar();
}