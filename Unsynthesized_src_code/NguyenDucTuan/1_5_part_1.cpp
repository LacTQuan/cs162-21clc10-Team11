#include<iostream>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;
//right
struct Student{
    //No, StudentID, Year_Student, FirstName, LastName, Gender, Date_of_Birth, SocialID
    string No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID;
    Student* pNext_Student;
};
struct Class{
    string name;
    Student* pStudent;
    Class* pNext_Class;
};
//left
struct Semester{
    string name;
    Semester* pNext_Semester;
};
//main
struct Year{
    string name;
    Class* pClass;
    Year* pNext_Year;
    Semester* pSemester;
};
void Create_Year(Year* &year){
    string name_year;
    cout<<"Import academic year (ex: 2021) ";
    cin >> name_year;
    Year* pCur_Year = year;

    Year* Temp_Year = new Year;
    Temp_Year->name = name_year;
    Temp_Year->pNext_Year = NULL;
    Temp_Year->pClass = NULL;
    Temp_Year->pSemester = nullptr;

    if(year == NULL) year = Temp_Year;
    else{
        while(pCur_Year->pNext_Year != NULL) pCur_Year = pCur_Year->pNext_Year;
        pCur_Year->pNext_Year = Temp_Year;
    }
}
void Create_Class(Year* &year){
    string name_class;
    cout<<"Import class (ex:21CLC10) ";
    cin >> name_class;
    Class* pCur_Class = year->pClass;

    Class* Temp_Class = new Class;
    Temp_Class->name = name_class;
    Temp_Class->pNext_Class = NULL;

    if(year->pClass == NULL) year->pClass = Temp_Class;
    else{
        while(pCur_Class->pNext_Class != NULL) pCur_Class = pCur_Class->pNext_Class;
        pCur_Class->pNext_Class = Temp_Class;
    }
}
void Create_Student(Class *classes){

    //No, StudentID, FirstName, LastName, Gender, Date_of_Birth, SocialID
    
    ifstream filein("profile.csv");
    while(filein.eof() == false){
        Student* pCur_Student = classes->pStudent;
        Student* Temp_Student = new Student;
        cout<<"Import student: "<<endl;
        cout<<"No ";getline(filein,Temp_Student->No,',');cout<<Temp_Student->No<<" | ";
        cout<<"StudentID ";getline(filein,Temp_Student->StudentID,',');cout<<Temp_Student->StudentID<<" | ";
        cout<<"FirstName ";getline(filein,Temp_Student->FirstName,',');cout<< " " << setw(20) << left << Temp_Student->FirstName;
        cout<<"LastName ";getline(filein,Temp_Student->LastName,',');cout<< " " << setw(15) << left << Temp_Student->LastName<<" | ";
        cout<<"Gender ";getline(filein,Temp_Student->Gender,',');cout<<setw(7) << left << Temp_Student->Gender<<" | ";
        cout<<"Date_of_Birth ";getline(filein,Temp_Student->Date_of_Birth,',');cout<<Temp_Student->Date_of_Birth<<" | ";
        cout<<"SocialID ";getline(filein,Temp_Student->SocialID,'\n');cout<<Temp_Student->SocialID<<endl;
        Temp_Student->pNext_Student = NULL;

        if(classes->pStudent == NULL) classes->pStudent = Temp_Student;
        else{
            while(pCur_Student->pNext_Student != NULL) pCur_Student = pCur_Student->pNext_Student;
            pCur_Student->pNext_Student = Temp_Student;
        }    
    }
    
    filein.close();
}