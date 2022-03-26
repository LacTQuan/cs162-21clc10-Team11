struct Account{
    string username, password;
    Account *next;
};
struct User{
    string username, password;
};
bool isStaff(string username){
    if (username.find('@') != string::npos) // username co '@' la staff
        return true;
    else
        return false;
}
bool account_check(Account *head, string username, string password){
    bool success = false;
    Account *cur = head;
    while (!success && cur){
        if (cur->username == username && cur->password == password)
            success = true;
        else
            cur = cur->next;
    }
    return success;
}
/*******************************************************
 * Load all usernames and passwords to a pointer array *
 * for futher rewriting file                           *
 *******************************************************/
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
//************************************************************
// If new students have been added in the general profile,   *
// before the program ends, a number of new student accounts * 
// are created with default password 123456789.              *
//                                                           *
// Note: new students must be added to the end of profile    *
//************************************************************
void create_student_account(Account *head){
    if (head == nullptr)
        return;
    
    Account *cur = head;
    while (cur->next && isStaff(cur->next->username))
        cur = cur->next;
    
    string line, trash;
    fstream infile("profile.csv", ios::in);

    // find the farthest position in the profile where a student already has an account.
    while (infile.eof() == false && cur->next && line == cur->username){
        getline(infile, trash, ',');
        getline(infile, line, ',');
        getline(infile, trash, '\n');
        cur = cur->next;
    }

    if (infile.eof() == false){
        do{
            getline(infile, trash, ',');
            getline(infile, line, ',');
            getline(infile, trash, '\n');
            cur->next = new Account;
            cur = cur->next;
            cur->username = line;
            cur->password = "123456789";
            cur->next = nullptr;
        }while (infile.eof() == false);
    }
    infile.close();
}

void delete_account_list(Account *&head){
    Account *temp = nullptr;
    while (head){
        temp = head->next;
        delete head;
        head = temp;
    }
}
void change_password(Account *head, string username, string newPassword){
    Account *cur = head;
    bool found = false;
    while (cur && cur->username != username)
        cur = cur->next;
    if (cur == nullptr){
        cout << "ERROR!\n";
    }
    else
        cur->password = newPassword;
    return;
}
// new
void view_profile(User U){
    system("cls");

    ifstream infile;
    string line;
    if (isStaff(U.username)){
        cout << "PROFILE:\n";
        cout << "Email: ";
        cout << U.username << endl;
        infile.open("staff_profile.csv");
        while (infile.eof() == false){
            getline(infile, line, ',');
            if (line != U.username)
                getline(infile, line, '\n');
            else
                break;
        }
        getline(infile, line, ',');     cout << "Full name: " << line << endl;
        getline(infile, line, ',');     cout << "Gender: " << line << endl;
        getline(infile, line, ',');     cout << "Date of birth: " << line << endl;
        getline(infile, line, '\n');    cout << "Social ID: " << line << endl;
    }
    else{
        cout << "Student ID: ";
        cout << U.username << endl;
        infile.open("profile.csv");
        while (infile.eof() == false){
            getline(infile, line, ',');
            if (line != U.username)
                getline(infile, line, '\n');
            else
                break;
        }
        getline(infile, line, ',');     cout << "Full name: " << line << endl;
        getline(infile, line, ',');     cout << "Gender: " << line << endl;
        getline(infile, line, ',');     cout << "Date of birth: " << line << endl;
        getline(infile, line, '\n');    cout << "Social ID: " << line << endl;
    }
    getchar();
    infile.close();
}
void Interface_Staff(Year* &year, User U){
    int choose_1;
    do{
        HOME:
        system("cls");
        cout << "1.Home\n";
        cout << "2.View profile\n";
        cout << "3.Log out\n";
        cout << "->Enter choice "; cin>>choose_1;
        if(choose_1 == 1){
            
            int choose_2;
            do{
                valid_year:
                system("cls");
                cout<<"--------YEARS LIST--------"<<endl;
                Print_Year(year);
                cout<<"--------------------------"<<endl;
                cout<<"1.Create year"<<endl;
                cout<<"2.Choose year to view classes"<<endl;
                cout<<"3.Choose year to view semesters"<<endl;
                cout<<"4.Home"<<endl;
                cout<<"5.Return"<<endl;              
                cout<<"->Enter choose "; cin>>choose_2;

                if(choose_2 == 1){
                    system("cls");
                    Print_Year(year);
                    Create_Year(year); 
                }   

                if(choose_2 == 2){
                    system("cls");
                    Print_Year(year);

                    int choose_3;
                    Year* import_year = Import_Year(year);

                    if(import_year == NULL){
                        cout<<"no years was created ";
                        cin.ignore();
                        getchar();
                        goto valid_year;
                    }
                    do{
                        valid_class:
                        system("cls");
                        cout<<"--------CLASSES LIST--------"<<endl;
                        Print_Class(import_year);
                        cout<<"----------------------------"<<endl;                  
                        cout<<"1.Create class"<<endl;
                        cout<<"2.Choose class to view student"<<endl;
                        cout<<"3.Home"<<endl;
                        cout<<"4.Return"<<endl; 
                        cout<<"->Enter choose "; cin>>choose_3;
                        if(choose_3 == 1){
                            system("cls");
                            Print_Class(import_year);

                            Create_Class(import_year);
                        }
                        if(choose_3 == 2) {
                            system("cls");
                            Print_Class(import_year);

                            int choose_4;
                            Class* import_class = Import_Class(import_year->pClass);

                            if(import_class == NULL){
                                cout<<"no classes was created ";
                                cin.ignore();
                                getchar();
                                goto valid_class;
                            }
                            do{
                                system("cls");
                                cout<<"--------STUDENTS LIST--------"<<endl;
                                Print_Student(import_class);
                                cout<<"-----------------------------"<<endl;                                
                                cout<<"1.Create student"<<endl;                            
                                cout<<"2.Home"<<endl;
                                cout<<"3.Return"<<endl; 
                                cout<<"->Enter choose "; cin>>choose_4;
                                if(choose_4 == 1){
                                    system("cls");
                                    Print_Student(import_class);
                                    Create_Student(import_class);
                                } 
                                else if(choose_4 == 2) goto HOME;

                            }while(choose_4 != 3);
                        }
                        if(choose_3 == 3) goto HOME;

                    }while(choose_3 != 4);
                }
                else if (choose_2 == 3) {
                    system("cls");
                    Print_Year(year);

                    int choose_3;
                    Year* import_year = Import_Year(year);

                    if(import_year == NULL){
                        cout<<"no years was created ";
                        cin.ignore();
                        getchar();
                        goto valid_year;
                    }
                    do{
                        valid_semester:
                        system("cls");
                        cout<<"--------SEMESTERS LIST--------"<<endl;
                        Print_Semester(import_year);
                        cout<<"------------------------------"<<endl;                  
                        cout<<"1.Create semester"<<endl;
                        cout<<"2.Choose semester to view courses"<<endl;
                        cout<<"3.Home"<<endl;
                        cout<<"4.Return"<<endl; 
                        cout<<"->Enter choose "; cin>>choose_3;
                        if(choose_3 == 1){
                            system("cls");
                            Print_Semester(import_year);
                            Create_Semester(import_year);
                        }
                        if(choose_3 == 2) {
                            system("cls");
                            Print_Semester(import_year);

                            int choose_4;
                            Semester* import_sem = Import_Semester(import_year->pSemester);

                            if(import_sem == NULL){
                                cout<<"no semesters was created ";
                                cin.ignore();
                                getchar();
                                goto valid_semester;
                            }
                            do{
                                system("cls");
                                cout<<"--------COURSES LIST---------"<<endl;
                                Print_Course(import_sem);
                                cout<<"-----------------------------"<<endl;                                
                                cout<<"1.Create course"<<endl;                            
                                cout<<"2.Update course"<<endl;
                                cout<<"3.Delete course"<<endl;
                                cout<<"4.Home"<<endl; 
                                cout<<"5.Return"<<endl;
                                cout<<"6.Enroll"<<endl;
                                cout<<"7.View student in course"<<endl;
                                cout<<"->Enter choose "; cin>>choose_4;
                                if(choose_4== 1){
                                    system("cls");
                                    Print_Course(import_sem);
                                    Create_Course(import_sem);
                                } 
                                else if (choose_4 == 2) {
                                    system("cls");
                                    Print_Course(import_sem);
                                    Update_Course(import_sem);
                                }
                                else if (choose_4 == 3) {
                                    system("cls");
                                    Print_Course(import_sem);
                                    Delete_Course(import_sem);
                                }
                                else if (choose_4 == 6){
                                    system("cls");
                                    Print_Course(import_sem);
                                    string studentID;
                                    cout<<"StudentID "; cin>>studentID;
                                    enroll_main(import_year,import_sem,studentID);
                                }
                                else if (choose_4 == 7) {
                                    system("cls");
                                    View_Student_In_Course(import_sem);
                                    getchar();
                                }
                                if(choose_4 == 4) goto HOME;
                            } while (choose_4 != 5);
                        }
                        if(choose_3 == 3) goto HOME;
                    }while(choose_3 != 4);
                }
                if(choose_2 == 4) goto HOME;
            }while(choose_2 != 5);
        }
        else if (choose_1 == 2){
            view_profile(U);
            getchar();
        }
    }while(choose_1 != 3);
}
void Interface(Year* &year) {
    User U;
    Account *account_head = load_account_list();
    int choice;
    do{
        LOGIN:
        system("cls");
        cout << "1. Log in\n";
        cout << "2. Change password\n";
        cout << "3. Exit\n";
        cout << "-> Enter choice: "; cin >> choice;
        if (choice == 1){
            system("cls");
            cout << "Enter username: ";
            cin >> U.username;
            cout << "Enter password: ";
            cin >> U.password;
            if (account_check(account_head, U.username, U.password)){
                cout << "Log in successfully.\n";
                cin.ignore();
                getchar();
                if (isStaff(U.username)) // staff
                    Interface_Staff(year, U);
                else // student
                    Interface_Staff(year, U); //Interface_Student();
                goto LOGIN;
            }
            else{
                cout << "Username or password is incorrect.\n";
                cin.ignore();
                getchar();
                goto LOGIN;
            }
        }
        if (choice == 2){
            system("cls");
            string newPassword;
            cout << "Enter username: "; cin >> U.username;
            cout << "Enter old password: "; cin >> U.password;
            if (account_check(account_head, U.username, U.password)){
                cout << "Enter new password: "; cin >> U.password;
                change_password(account_head, U.username, U.password);
                save_account_list(account_head);
                cout << "Password has been changed.\n";
                cin.ignore();
                getchar();
                goto LOGIN;
            }
            else{
                cout << "Username or password is incorrect";
                cin.ignore();
                getchar();
                goto LOGIN;
            }
        }

    }while (choice != 3);
    create_student_account(account_head);
    save_account_list(account_head);
    delete_account_list(account_head);
    return;
}