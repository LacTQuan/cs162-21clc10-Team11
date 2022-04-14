#include "header.h"
int main() {
    system("cls");
    User U;  
    Account* account_head;  
    Registration_Session S;
    Staff* staff = NULL;
    Year* year = NULL;
    
    load_main(year,S);

    Nocursortype();
    string LOGIN_name_list_of_boxs[] = { "LOGIN","EXIT" };
	LOGIN_PAGE(year, account_head, U, 60, 10, 2, LOGIN_name_list_of_boxs,S,staff); 

    delete_account_list(account_head);
    delete_all_node(year);
    //Staff_profile(staff);
    //output_staff(staff,"httu@fit.hcmus.edu.vn");


    return 0;
}
