#include "loadacc.h"
#include "add.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"

account *loadaccounts(int *count)
{
    account *accounts = malloc(30 * sizeof(account));
    char x[300];
    *count = 0;

    if (accounts == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL)
    {
        printf("error opening file");
        free(accounts);
        return NULL;
    }
    while (fgets(x, sizeof(x), fp) != NULL)
    {
        x[strcspn(x, "\n")] = '\0';   // da by3ed l7ad ma yla2y \n melakher by3ed char.s el line
        char *token = strtok(x, ","); // byfsel el lines b kol comma
        if (token == NULL)
            continue;
        accounts[*count].accountnumber = atoll(token); // el atoi bethawel mn string le long long
        char filename[50];
        sprintf(filename,"%lld.txt",accounts[*count].accountnumber);
        FILE *tfp=fopen(filename,"a");
        if(tfp!=NULL)
            fclose(tfp);
        token = strtok(NULL, ",");
        strcpy(accounts[*count].name, token);

        token = strtok(NULL, ",");
        strcpy(accounts[*count].address, token);
        token = strtok(NULL, ",");
        accounts[*count].balance = atof(token); // el atof bethawel mn string le float
        token = strtok(NULL, ",");
        accounts[*count].mobile = atoll(token);
        token = strtok(NULL, ",");
        sscanf(token, "%d-%d", &accounts[*count].dateopened.month, &accounts[*count].dateopened.year);
        token = strtok(NULL, "\n");
        if (token[0] == ' ')
            token++;
        strcpy(accounts[*count].status, token);
        (*count)++;
    }
    fclose(fp);
    return accounts;
}
void sortByName(account accounts[], int *count)
{
    account temp;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = i + 1; j < *count; j++)
            if (_stricmp(accounts[i].name, accounts[j].name) > 0)
            {
                temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
    }
}
void sortByBalance(account accounts[], int *count)
{
    account temp;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = i + 1; j < *count; j++)
            if (accounts[i].balance > accounts[j].balance)
            {
                temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
    }
}
void sortByDate(account accounts[], int *count)
{
    account temp;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = i + 1; j < *count; j++)
            if (accounts[i].dateopened.year > accounts[j].dateopened.year || (accounts[i].dateopened.year == accounts[j].dateopened.year && accounts[i].dateopened.month > accounts[j].dateopened.month))
            {
                temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
    }
}
void sortByStatus(account accounts[], int *count)
{
    account temp;
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = i + 1; j < *count; j++)
            if (strcmp(accounts[i].status, accounts[j].status) > 0)
            {
                temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
    }
}
void printAccounts(account accounts[], int *count)
{
    int choice;
    printf("\n you need accounts to be sorted by:\n");
    printf("1-name\n");
    printf("2-balance\n");
    printf("3-date opened\n");
    printf("4-status\n");
    printf("please input your choice\n");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        sortByName(accounts, count);
        break;
    case 2:
        sortByBalance(accounts, count);
        break;
    case 3:
        sortByDate(accounts, count);
        break;
    case 4:
        sortByStatus(accounts, count);
        break;
    default:
        printf("invalid choice\n");
        return;
    }
    printf("\n accounts list\n");
    for (int i = 0; i < *count; i++)
    {
        printf("account number: %lld\n", accounts[i].accountnumber);
        printf("name: %s\n", accounts[i].name);
        printf("address: %s\n", accounts[i].address);
        printf("balance: %f\n", accounts[i].balance);
        printf("mobile: %lld\n", accounts[i].mobile);
        printf("date opened: %d-%d\n", accounts[i].dateopened.month, accounts[i].dateopened.year);
        printf("status: %s\n\n\n\n\n", accounts[i].status);
    }
    asktocontinue();
}
const char *getMonthName(int month)
{
    switch (month)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Invalid month";
    }
}
void querySearch(account accounts[], int *count, int *accFound)
{
    long long searchnumber;
    int found = 0;
    printf("input account number to search\n");
    scanf("%lld", &searchnumber);
    getchar();
    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == searchnumber)
        {
            printf("\naccount number: %lld\n", accounts[i].accountnumber);
            printf("name: %s\n", accounts[i].name);
            printf("address: %s\n", accounts[i].address);
            printf("balance: %f\n", accounts[i].balance);
            printf("mobile: %lld\n", accounts[i].mobile);
            printf("date opened: %s %d\n", getMonthName(accounts[i].dateopened.month), accounts[i].dateopened.year);
            printf("status: %s\n", accounts[i].status);
            found = 1;
            (*accFound)++;
            break;
        }
    }
    if (!found)
        printf("\n account not found\n");
    asktocontinue();
}
void advancedSearch(account accounts[], int *count, int *accFound)
{
    char keyword[100];
    int found = 0;
    *accFound = 0;
    printf("input keyword: ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    for (int i = 0; i < *count; i++)
    {
        if (strstr(accounts[i].name, keyword) != NULL)
        {
            printf("\naccount number: %lld\n", accounts[i].accountnumber);
            printf("name: %s\n", accounts[i].name);
            printf("address: %s\n", accounts[i].address);
            printf("balance: %f\n", accounts[i].balance);
            printf("mobile: %lld\n", accounts[i].mobile);
            printf("date opened: %s %d\n", getMonthName(accounts[i].dateopened.month), accounts[i].dateopened.year);
            printf("status: %s\n\n\n\n", accounts[i].status);
            found = 1;
            (*accFound)++;
        }
    }

    if (!found)
        printf("\nthe keyword is not found in any account\n");
    asktocontinue();
}

void asktocontinue()
{

    char input[10];
    int *count = malloc(sizeof(int));
    int *accFound = malloc(sizeof(int));
    if (count == NULL || accFound == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    *count = 0;
    *accFound = 0;
    
    printf("Do you want to do any other operations ? :(Y/N)\n");
    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("invalid input\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove newline
        if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0)
        {
            account *accounts = loadaccounts(count);
            menu(accounts, count, accFound);
            free(count);
            free(accFound);
            free(accounts);
            break;
        }
        else if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0)
        {

            printf("Thank you!\nQUITTING.\n");
            exit(0);
        }
        else
        {
            printf("invalid input , try again\n");
        }
    }
}
void saveaccounts(account accounts[], int *count)
{
    char input[10];
    printf("Do you want to save changes to file? (Y/N): ");

    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("Invalid input\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0)
        {
            FILE *fp = fopen("accounts.txt", "w");
            if (fp == NULL)
            {
                printf("Error opening file for writing\n");
                return;
            }

            for (int i = 0; i < *count; i++)
            {
                fprintf(fp, "%lld,%s,%s,%.2f,%lld,%d-%d,%s\n",
                        accounts[i].accountnumber,
                        accounts[i].name,
                        accounts[i].address,
                        accounts[i].balance,
                        accounts[i].mobile,
                        accounts[i].dateopened.month,
                        accounts[i].dateopened.year,
                        accounts[i].status);
            }

            fclose(fp);
            printf("Changes saved successfully!\n");
            break;
        }
        else if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0)
        {
            printf("Changes not saved.\n");
            break;
        }
        else
        {
            printf("Invalid input, try again (Y/N): ");
        }
    }
}
void 
menu(account accounts[], int *count, int *accFound)
{
    char select[100];
    printf("- ADD\n- DELETE \n- MODIFY\n- SEARCH\n- ADVANCED SEARCH\n- CHANGE STATUS\n- WITHDRAW\n- DEPOSIT\n- TRANSFER\n- REPORT\n- PRINT\n- QUIT\n");
    while (1)
    {
        if (!fgets(select, sizeof(select), stdin))
        {
            printf("Error reading input\n");
            continue;
        }

        select[strcspn(select, "\n")] = '\0';
        if (strcmp(select, "ADD") == 0)
        {
            printf("ADD SELECTED , PROCCESSING\n"); // matensash t7ot el function
            addAccount(accounts, count);
            break;
        }
        else if (strcmp(select, "DELETE") == 0)
        {
            printf("DELETE SELECTED , PROCCESSING\n"); // matensash t7ot el functioN
            printf("1 - MULTI-DELETE\n2 - DELETE");
            int choice;
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n');
                    
                printf("Invalid input\n");
                return;
            }
            while (getchar() != '\n');
                
            if (choice == 1){
                multidelete(accounts,count);}
            else if(choice ==2){
            deleteAccount(accounts, count);
        }
            break;
        }
        else if (strcmp(select, "MODIFY") == 0)
        {
            printf("MODIFY SELECTED , PROCCESSING\n"); // matensash t7ot el function
            modifyAccount(accounts, count);
            break;
        }
        else if (strcmp(select, "SEARCH") == 0)
        {
            printf("SEARCH SELECTED , PROCCESSING\n"); // matensash t7ot el function
            querySearch(accounts, count, accFound);
            break;
        }
        else if (strcmp(select, "ADVANCED SEARCH") == 0)
        {
            printf("ADVANCED SEARCH , PROCCESSING\n"); // matensash t7ot el function
            advancedSearch(accounts, count, accFound);
            break;
        }
        else if (strcmp(select, "CHANGE STATUS") == 0)
        {
            printf("CHANGE_STATUS , PROCCESSING\n"); // matensash t7ot el function
            changeStatus(accounts, count);
            break;
        }
        else if (strcmp(select, "WITHDRAW") == 0)
        {
            printf("WITHDRAW SELECTED , PROCCESSING\n"); // matensash t7ot el function
            break;
        }
        else if (strcmp(select, "DEPOSIT") == 0)
        {
            printf("DEPOSIT SELECTED , PROCCESSING\n"); // matensash t7ot el function
            deposit(accounts,count);
            break;
        }
        else if (strcmp(select, "TRANSFER") == 0)
        {
            printf("TRANSFER SELECTED , PROCCESSING\n"); // matensash t7ot el function
            break;
        }
        else if (strcmp(select, "REPORT") == 0)
        {
            printf("REPORT SELECTED , PROCCESSING\n"); // matensash t7ot el function
            break;
        }
        else if (strcmp(select, "QUIT") == 0)
        {
            printf("QUIT SELECTED , PROCCESSING\n"); // matensash t7ot el function
            printf("Thank you!\nQUITTING.\n");
            exit(0);
            break;
        }
        else if (strcmp(select, "PRINT") == 0)
        {
            printf("PRINT SELECTED , PROCCESSING\n"); // matensash t7ot el function
            printAccounts(accounts, count);
            break;
        }
        else
            printf("invalid input, try again\n");
    }
}

int login()
{

    FILE *fp;
    char f_user[50], f_pass[50], in_user[50], in_pass[50];
    while (1)
    {
        printf("Enter username:\n");

        if (!fgets(in_user, sizeof(in_user), stdin))
            return 0;

        if (strchr(in_user, '\n') == NULL)
        {
            printf("username too long\n");
            clearbuffer();   // consume remaining chars
            continue;
        }

        in_user[strcspn(in_user, "\n")] = '\0';
        break;
    }

    while (1)
    {
        printf("Enter password:\n");

        if (!fgets(in_pass, sizeof(in_pass), stdin))
            return 0;

        if (strchr(in_pass, '\n') == NULL)
        {
            printf("password too long\n");
            clearbuffer();
            continue;
        }

        in_pass[strcspn(in_pass, "\n")] = '\0';
        break;
    }

    fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf("error occurred\n");
        return 0;
    }

    while (fscanf(fp, "%49s %49s", f_user, f_pass) == 2)
    {
        if (strcmp(in_user, f_user) == 0 &&
            strcmp(in_pass, f_pass) == 0)
        {
            fclose(fp);
            printf("login successful\n");
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void startmenu(void)
{
    int x;
    int result;
    int *count = malloc(sizeof(int));
    int *accFound = malloc(sizeof(int));

    if (count == NULL || accFound == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    *count = 0;
    *accFound = 0;

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
                free(accFound);
                free(count);
                exit(0);
            }
            if (login_result == 1)
            {
                printf("USER CONFIRMED\n");

                account *accounts = loadaccounts(count);

                menu(accounts, count, accFound);
                free(accFound);
                free(count);
                free(accounts);

                break;
            }
        }
        else
        {
            printf("Invalid\n");
        }
    }
}
void clearbuffer(){
    int c;
while ((c = getchar()) != '\n' && c != EOF);
}