#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define nullptr 0

struct Account{
    string username, password;
    Account *next;
};


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

int login_main(){
    Account *account_head = load_account_list();
    int choice;
    do{
        LOGIN:
        cout << "1. Log in\n";
        cout << "2. Change password\n";
        cout << "3. Exit\n";
        cout << "-> Enter choice: "; cin >> choice;
        string username, password;
        if (choice == 1){
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (account_check(account_head, username, password)){
                cout << "Log in successfully.\n";
                cin.ignore();
                getchar();
                //do{...}
                goto LOGIN; ////////////////////////////////////////////////////////////////////////
            }
            else{
                cout << "Username or password is incorrect.\n";
                cin.ignore();
                getchar();
                goto LOGIN;
            }
        }
        if (choice == 2){
            string newPassword;
            cout << "Enter username: "; cin >> username;
            cout << "Enter old password: "; cin >> password;
            if (account_check(account_head, username, password)){
                cout << "Enter new password: "; cin >> newPassword;
                change_password(account_head, username, newPassword);
                cout << "Password has been changed.\n";
                cin.ignore();
                getchar();
                goto LOGIN; //////////////////////////////////////////////////////////////////
            }
            else{
                cout << "Username or password is incorrect";
                cin.ignore();
                getchar();
                goto LOGIN;
            }
        }
    }while (choice != 3);
    save_account_list(account_head);
    delete_account_list(account_head);
    return 0;
}


int main(){
    login_main();
    // Account *head = load_account_list();
    // Account *cur = head;
    // while (cur){
    //     cout << cur->username << " " << cur->password << endl;
    //     cur = cur->next;
    // }
    // delete_account_list(head);
    // if (head == nullptr)
    //     cout << "Nothing.\n";
    // else{
    //     cout << "Something.\n";
    // }
    return 0;
}

