#include "loadacc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu()
{
    char select[100];
    printf("- ADD\n- DELETE \n- MODIFY\n- SEARCH\n- ADVANCED SEARCH\n- CHANGE_STATUS\n- WIRHDRAW\n- DEPOSIT\n- TRANSFER\n- REPORT\n- PRINT\n- QUIT\n");
    fflush(stdout);
    while (1)
    {
        if (!fgets(select, sizeof(select), stdin))
        {
            printf("Error reading input\n");
            continue;
        }

        // remove trailing newline
        select[strcspn(select, "\n")] = '\0';
        if (strcmp(select, "ADD") == 0)
        {
            printf("ADD SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "DELETE") == 0)
        {
            printf("DELETE SELECTED , PROCCESSING"); // matensash t7ot el functioN
            break;
        }
        if (strcmp(select, "MODIFY") == 0)
        {
            printf("MODIFY SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "SEARCH") == 0)
        {
            printf("SEARCH SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "ADVANCED SEARCH") == 0)
        {
            printf("ADVANCED SEARCH , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "CHANGE_STATUS") == 0)
        {
            printf("CHANGE_STATUS , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "WHITHDRAW") == 0)
        {
            printf("WHITHDRAW SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "DEPOSIT") == 0)
        {
            printf("DEPOSIT SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "TRANSFER") == 0)
        {
            printf("TRANSFER SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "REPORT") == 0)
        {
            printf("REPORT SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "QUIT") == 0)
        {
            printf("QUIT SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        if (strcmp(select, "PRINT") == 0)
        {
            printf("PRINT SELECTED , PROCCESSING"); // matensash t7ot el function
            break;
        }
        else
            printf("invalid input, try again");
    }
}

int login()
{

    FILE *fp;
    char f_user[50], f_pass[50], in_user[50], in_pass[50];
    printf("Enter username :\n");
    fgets(in_user, sizeof(in_user), stdin);
    in_user[strcspn(in_user, "\n")] = '\0';
    printf("Enter password :\n");
    fgets(in_pass, sizeof(in_pass), stdin);
    in_pass[strcspn(in_pass, "\n")] = '\0';

    fp = fopen("users.txt", "r"); // 3ayez a read el data
    if (fp == NULL)
    {
        printf("error occured "); // law el file hasal error
        return 0;
    }
    while (fscanf(fp, "%49s %49s", f_user, f_pass) == 2)
    { // ==2 yaany while it reads ONLY 2 words
        if (strcmp(in_user, f_user) == 0 && strcmp(in_pass, f_pass) == 0)
        { // input = data
            fclose(fp);
            printf("login successfull\n");
            return 1; // login success
        }
    }
    fclose(fp);
    return 0; // login failed
}

void startmenu(void)
{
    int x;
    int result;

    while (1)
    {
        printf("\n1: LOGIN\n0: QUIT\n");

        result = scanf("%d", &x); // law akhad rakam haykoon 1 law akhad ay haga tanya hayb2a 0
        while (getchar() != '\n')
            ;
        if (result != 1)
        {
            printf("Invalid\nenter a number\n");

            while (getchar() != '\n')
                ; // i used this to remove the wrong input from the scanf so i can get new input so it does not get into an infinite loop
            continue;
        }

        if (x == 0)
        {
            exit(0);
        }
        else if (x == 1)
        {
            int login_result = login(); // de feeha value el result 3shan mancallsh el func kaza mara

            if (login_result == 0)
            { // bro forgot his password :p
                printf("UNAUTHORIZED USER SYSTEM WILL CLOSE\n");
                exit(0);
            }
            if (login_result == 1)
            {
                printf("USER CONFIRMED\n");
                loadaccounts();

                menu();
                break;
            }
        }
        else
        {
            printf("Invalid\n");
        }
    }
}

int main(void)
{
    startmenu();
    return 0;
}
