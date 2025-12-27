#ifndef LOADACC_H_INCLUDED
#define LOADACC_H_INCLUDED

#include "account.h"
#include "add.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[1;37m"

account *loadaccounts(int *count)
{
    account *accounts = malloc(30 * sizeof(account));
    char x[300];
    *count = 0;

    if (accounts == NULL)
    {
        printf(COLOR_RED"Memory allocation failed\n"COLOR_RESET);
        return NULL;
    }

    FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL)
    {
        printf(COLOR_RED"error opening file"COLOR_RESET);
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
        sprintf(filename, "%lld.txt", accounts[*count].accountnumber);
        FILE *tfp = fopen(filename, "a");
        if (tfp != NULL)
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
    char temp[100];
    printf(COLOR_YELLOW"\n you need accounts to be sorted by:\n"COLOR_RESET);
    printf("1-name\n");
    printf("2-balance\n");
    printf("3-date opened\n");
    printf("4-status\n");
    printf("please input your choice\n");
            fgets(temp, sizeof(temp), stdin);
             if (strchr(temp, '\n') == NULL)
        {
            printf(COLOR_RED"invalid input\n"COLOR_RESET);
           clearbuffer();   
            asktocontinue();
            return;
        }
        temp[strcspn(temp, "\n")] = '\0';
        if (!checkint(temp))
        {
            printf(COLOR_RED"invalid input\n"COLOR_RESET);
            asktocontinue();
            return;
        }

       
        choice = atoi(temp);

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
        printf(COLOR_RED"invalid choice\n"COLOR_RESET);
        return;
    }
    printf(COLOR_YELLOW"\n accounts list\n"COLOR_RESET);
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
        return COLOR_RED"Invalid month"COLOR_RESET;
    }
}
void querySearch(account accounts[], int *count)
{
    long long searchnumber;
    int found = 0;
    char temp[100];
    printf("input account number to search\n");
    fgets(temp, sizeof(temp), stdin);
    if (strchr(temp, '\n') == NULL)
    {
        printf(COLOR_RED"Invalid input\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    temp[strcspn(temp, "\n")] = '\0';

    if (!checkint(temp))
    {
        printf(COLOR_RED"Invalid input\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    

    searchnumber = atoll(temp);
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
            break;
        }
    }
    if (!found)
    {
        printf(COLOR_YELLOW"\n account not found\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
    }
    asktocontinue();
}
void advancedSearch(account accounts[], int *count)
{
    char keyword[100];
    int found = 0;
    printf("input keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    if (strchr(keyword, '\n') == NULL)
    {
        printf(COLOR_RED"Invalid input\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    keyword[strcspn(keyword, "\n")] = '\0';

    for (int i = 0; i < *count; i++)
    {
        char accStr[50], mobileStr[50], balanceStr[50], dateStr[50];

        sprintf(accStr, "%lld", accounts[i].accountnumber);
        sprintf(mobileStr, "%lld", accounts[i].mobile);
        sprintf(balanceStr, "%.2f", accounts[i].balance);
        sprintf(dateStr, "%d-%d", accounts[i].dateopened.month, accounts[i].dateopened.year);
        if (strstr(accounts[i].name, keyword) != NULL ||
            strstr(accounts[i].address, keyword) != NULL ||
            strstr(accounts[i].status, keyword) != NULL ||
            strstr(accStr, keyword) != NULL ||
            strstr(mobileStr, keyword) != NULL ||
            strstr(balanceStr, keyword) != NULL ||
            strstr(dateStr, keyword) != NULL)
        {
            printf("\naccount number: %lld\n", accounts[i].accountnumber);
            printf("name: %s\n", accounts[i].name);
            printf("address: %s\n", accounts[i].address);
            printf("balance: %f\n", accounts[i].balance);
            printf("mobile: %lld\n", accounts[i].mobile);
            printf("date opened: %s %d\n", getMonthName(accounts[i].dateopened.month), accounts[i].dateopened.year);
            printf("status: %s\n", accounts[i].status);
            found = 1;
        }
    }

    if (!found)
    {
        printf(COLOR_YELLOW"\nthe keyword is not found in any account\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    asktocontinue();
}

void asktocontinue()
{

    char input[10];
    int *count = malloc(sizeof(int));
    if (count == NULL )
    {
        printf(COLOR_RED"Memory allocation failed!\n"COLOR_RESET);
        return;
    }
    *count = 0;

    printf(COLOR_YELLOW"Do you want to do any other operations ? :(Y/N)\n"COLOR_RESET);
    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
        {
            printf(COLOR_RED"invalid input\n"COLOR_RESET);
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove newline
        if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0)
        {
            account *accounts = loadaccounts(count);
            menu(accounts, count);
            free(count);
            free(accounts);
            break;
        }
        else if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0)
        {

            printf(COLOR_YELLOW"Thank you!\nQUITTING.\n"COLOR_RESET);
            exit(0);
        }
        else
        {
            printf(COLOR_RED"invalid input , try again\n"COLOR_RESET);
        }
    }
}
void saveaccounts(account accounts[], int *count)
{
    char input[10];
    printf(COLOR_YELLOW"Do you want to save changes to file? (Y/N): "COLOR_RESET);

    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
        {
            printf(COLOR_RED"Invalid input\n"COLOR_RESET);
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0)
        {
            FILE *fp = fopen("accounts.txt", "w");
            if (fp == NULL)
            {
                printf(COLOR_RED"Error opening file for writing\n"COLOR_RESET);
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
            printf(COLOR_GREEN"Changes saved successfully!\n"COLOR_RESET);
            break;
        }
        else if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0)
        {
            printf(COLOR_YELLOW"Changes not saved.\n"COLOR_RESET);
            break;
        }
        else
        {
            printf(COLOR_RED"Invalid input, try again (Y/N): "COLOR_RESET);
        }
    }
}
void menu(account accounts[], int *count)
{
    char select[1000];
    printf(COLOR_CYAN"- ADD\n- DELETE \n- MODIFY\n- SEARCH\n- ADVANCED SEARCH\n- CHANGE STATUS\n- WITHDRAW\n- DEPOSIT\n- TRANSFER\n- REPORT\n- PRINT\n- QUIT\n"COLOR_RESET);
    while (1)
    {
        if (!fgets(select, sizeof(select), stdin))
        {
            printf(COLOR_RED"Error reading input\n"COLOR_RESET);
            continue;
        }

        select[strcspn(select, "\n")] = '\0';
        if (stricmp(select, "ADD") == 0)
        {
            printf(COLOR_GREEN"ADD SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            addAccount(accounts, count);
            break;
        }
        else if (stricmp(select, "DELETE") == 0)
        {
            printf(COLOR_GREEN"DELETE SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el functioN
            printf(COLOR_YELLOW"1 - MULTI-DELETE\n2 - DELETE"COLOR_RESET);
            int choice;
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                    ;

                printf(COLOR_RED"Invalid input\n"COLOR_RESET);
                return;
            }
            while (getchar() != '\n')
                ;

            if (choice == 1)
            {
                multidelete(accounts, count);
            }
            else if (choice == 2)
            {
                deleteAccount(accounts, count);
            }
            break;
        }
        else if (stricmp(select, "MODIFY") == 0)
        {
            printf(COLOR_GREEN"MODIFY SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            modifyAccount(accounts, count);
            break;
        }
        else if (stricmp(select, "SEARCH") == 0)
        {
            printf(COLOR_GREEN"SEARCH SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            querySearch(accounts, count);
            break;
        }
        else if (stricmp(select, "ADVANCED SEARCH") == 0)
        {
            printf(COLOR_GREEN"ADVANCED SEARCH , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            advancedSearch(accounts, count);
            break;
        }
        else if (stricmp(select, "CHANGE STATUS") == 0)
        {
            printf(COLOR_GREEN"CHANGE_STATUS , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            changeStatus(accounts, count);
            break;
        }
        else if (stricmp(select, "WITHDRAW") == 0)
        {
            printf(COLOR_GREEN"WITHDRAW SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            withDraw(accounts, count);
            break;
        }
        else if (stricmp(select, "DEPOSIT") == 0)
        {
            printf(COLOR_GREEN"DEPOSIT SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            deposit(accounts, count);
            break;
        }
        else if (stricmp(select, "TRANSFER") == 0)
        {
            printf(COLOR_GREEN"TRANSFER SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            transfer(accounts, count);
            break;
        }
        else if (stricmp(select, "REPORT") == 0)
        {
            printf(COLOR_GREEN"REPORT SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            report(accounts, count);
            break;
        }
        else if (stricmp(select, "QUIT") == 0)
        {
            printf(COLOR_GREEN"QUIT SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            printf(COLOR_YELLOW"Thank you!\nQUITTING.\n"COLOR_RESET);
            exit(0);
            break;
        }
        else if (stricmp(select, "PRINT") == 0)
        {
            printf(COLOR_GREEN"PRINT SELECTED , PROCCESSING\n"COLOR_RESET); // matensash t7ot el function
            printAccounts(accounts, count);
            break;
        }
        else
            printf(COLOR_RED"invalid input, try again\n"COLOR_RESET);
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
            printf(COLOR_RED"username too long\n"COLOR_RESET);
            clearbuffer(); // consume remaining chars
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
            printf(COLOR_RED"password too long\n"COLOR_RESET);
            clearbuffer();
            continue;
        }

        in_pass[strcspn(in_pass, "\n")] = '\0';
        break;
    }

    fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf(COLOR_RED"error occurred\n"COLOR_RESET);
        return 0;
    }

    while (fscanf(fp, "%49s %49s", f_user, f_pass) == 2)
    {
        if (strcmp(in_user, f_user) == 0 &&
            strcmp(in_pass, f_pass) == 0)
        {
            fclose(fp);
            printf(COLOR_GREEN"login successful\n"COLOR_RESET);
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
    char temp[100];
    int *count = malloc(sizeof(int));

    if (count == NULL)
    {
        printf(COLOR_RED"Memory allocation failed!\n"COLOR_RESET);
        exit(1);
    }
    *count = 0;
    printf(COLOR_GREEN"====BANK MANAGMENT===="COLOR_RESET);
    while (1)
    {
        printf("\n1: LOGIN\n0: QUIT\n");

        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0';
        if (!checkint(temp))
        {
            printf(COLOR_RED"invalid input\n"COLOR_RESET);
            return;
        }

        if (strlen(temp) == sizeof(temp) - 1)
        {
            printf(COLOR_RED"invalid input\n"COLOR_RESET);
            clearbuffer();
            asktocontinue();
            return;
        }
        x = atoi(temp);

        if (x == 0)
        {
            printf(COLOR_YELLOW"THANK YOU\nGOODBYE!!"COLOR_RESET);
            exit(0);
        }
        else if (x == 1)
        {
            int login_result = login(); // de feeha value el result 3shan mancallsh el func kaza mara

            if (login_result == 0)
            { // bro forgot his password :p
                printf(COLOR_RED"UNAUTHORIZED USER SYSTEM WILL CLOSE\n"COLOR_RESET);
                free(count);
                exit(0);
            }
            if (login_result == 1)
            {
                printf(COLOR_GREEN"USER CONFIRMED\n"COLOR_RESET);

                account *accounts = loadaccounts(count);

                menu(accounts, count);
                free(count);
                free(accounts);

                break;
            }
        }
        else
        {
            printf(COLOR_RED"Invalid\n"COLOR_RESET);
        }
    }
}
void clearbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void report(account accounts[], int *count)
{
    int num = *count;
    long long accNum;
    char filename[50];
    int found = 0;
    char transactions[100][200];
    int lineCount = 0;
    printf("enter your account number");
    if (scanf("%lld", &accNum) != 1)
    {
        printf(COLOR_RED"invalid input \n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    for (int i = 0; i < num; i++)
    {
        if (accounts[i].accountnumber == accNum)
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf(COLOR_YELLOW"account number doesn't exist\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    sprintf(filename, "%lld.txt", accNum);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf(COLOR_YELLOW"no transaction history found"COLOR_RESET);
        asktocontinue();
        return;
    }
    while (fgets(transactions[lineCount], sizeof(transactions[lineCount]), fp))
    {
        if (transactions[lineCount][0] == '\n')
            continue;

        lineCount++;
    }
    fclose(fp);
    if (lineCount == 0)
    {
        printf(COLOR_YELLOW"no transactions found"COLOR_RESET);
        asktocontinue();
        return;
    }
    printf("\n----last transactions in account number %lld----\n", accNum);
    int start = lineCount - 5;
    if (start < 0)
        start = 0;
    for (int j = start; j < lineCount; j++)
    {
        printf("%s\n", transactions[j]);
    }
    clearbuffer();
    asktocontinue();
    return;
}

#endif
