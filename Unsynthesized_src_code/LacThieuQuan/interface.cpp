void Interface(Year* &year){
    int choose_1;
    do{
        HOME:
        system("cls");
        cout<<"1.Home"<<endl;
        cout<<"2.Log out"<<endl;
        cout<<"->Enter choose ";cin>>choose_1;
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
                        cout<<"2.Choose semester to view subject"<<endl;
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
                                valid_subject:
                                system("cls");
                                cout<<"--------SUBJECTS LIST--------"<<endl;
                                Print_Subject(import_sem);
                                cout<<"-----------------------------"<<endl;                                
                                cout<<"1.Create subject"<<endl;                            
                                cout<<"2.Choose subject to view courses"<<endl;
                                cout<<"3.Home"<<endl; 
                                cout<<"4.Return"<<endl;
                                cout<<"->Enter choose "; cin>>choose_4;
                                if(choose_4 == 1){
                                    system("cls");
                                    Print_Subject(import_sem);
                                    Create_Subject(import_sem);
                                } 
                                else if (choose_4 == 2) {
                                    system("cls");
                                    Print_Subject(import_sem);

                                    int choose_5;
                                    Subject* import_sub = Import_Subject(import_sem->pSubject);

                                    if(import_sub == NULL){
                                        cout<<"no subjects was created ";
                                        cin.ignore();
                                        getchar();
                                        goto valid_subject;
                                    }
                                    do {
                                        system("cls");
                                        cout<<"--------COURSES LIST---------"<<endl;
                                        Print_Course(import_sub);
                                        cout<<"-----------------------------"<<endl;                                
                                        cout<<"1.Create course"<<endl;                            
                                        cout<<"2.Update course"<<endl;
                                        cout<<"3.Delete course"<<endl;
                                        cout<<"4.Home"<<endl; 
                                        cout<<"5.Return"<<endl;
                                        cout<<"6.Enroll"<<endl;
                                        cout<<"->Enter choose "; cin>>choose_5;
                                        if(choose_5 == 1){
                                            system("cls");
                                            Print_Course(import_sub);
                                            Create_Course(import_sub);
                                        } 
                                        else if (choose_5 == 2) {
                                            system("cls");
                                            Print_Course(import_sub);
                                            Update_Course(import_sub);
                                        }
                                        else if (choose_5 == 3) {
                                            system("cls");
                                            Print_Course(import_sub);
                                            Delete_Course(import_sub);
                                        }
                                        else if (choose_5 == 6){
                                            //string studentID;
                                            //cout<<"StudentID "<<studentID;
                                            //enroll_main(import_year,import_sem,studentID);
                                        }
                                        if(choose_5 == 4) goto HOME;
                                    } while (choose_5 != 5);
                                }
                                else if(choose_4 == 3) goto HOME;
                            }while(choose_4 != 4);
                        }
                        if(choose_3 == 3) goto HOME;
                    }while(choose_3 != 4);
                }
                if(choose_2 == 4) goto HOME;
            }while(choose_2 != 5);
        }
    }while(choose_1 != 2);
}