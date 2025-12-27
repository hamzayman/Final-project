#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED

#include "account.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TRANSACTION_LIMIT 10000.0
#define DAILY_LIMIT 50000.0
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[1;37m"

int isDuplicateAccount(account accounts[], int *count, long long accNo)
{
    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == accNo)
        {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicate
}
void addAccount(account accounts[], int *count)
{

    if (accounts == NULL)
    {
        printf(COLOR_RED"Error loading accounts\n"COLOR_RESET);
        return;
    }

    long long accNo;
    char name[50];
    char address[100];
    float balance;
    char status[] = "active";
    long long mobile;
    int month, year;
    int flag = 0;
    char temp[100];

    SYSTEMTIME st;
    GetLocalTime(&st);
    month = st.wMonth;
    year = st.wYear;

    printf(COLOR_GREEN"\n--- ADD NEW ACCOUNT ---\n"COLOR_RESET);
    printf("Enter Account Number: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkint(temp))
    {
        printf(COLOR_RED"Invalid input \n"COLOR_RESET);
        asktocontinue();
        return;
    }
    if (strlen(temp) == sizeof(temp) - 1)
    {
        printf(COLOR_RED"Invalid input \n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    accNo = atoll(temp);

    if (isDuplicateAccount(accounts, count, accNo))
    {
        printf(COLOR_RED"Error: Account number already exists!\n"COLOR_RESET);

        asktocontinue();
        return;
    }

    printf("Enter Account Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (!checkstring(name))
    {
        printf(COLOR_RED"invalid input\n\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    if (strlen(name) == sizeof(name) - 1)
    {
        printf(COLOR_RED"invalid input\n\n"COLOR_RESET);
        while (getchar() != '\n')
            ;
        asktocontinue();
        return;
    }

    printf("Enter Initial Balance: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkint(temp))
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        asktocontinue();
        return;
    }

    if (strlen(temp) == sizeof(temp) - 1)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        while (getchar() != '\n')
            ;
        asktocontinue();
        return;
    }
    balance = atof(temp);

    printf("Enter Phone Number: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkint(temp))
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    if (strlen(temp) == sizeof(temp) - 1)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        while (getchar() != '\n')
            ;
        asktocontinue();
        return;
    }
    mobile = atoll(temp);
    printf("Enter Address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';
    if (!valid_email(address))
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    if (strlen(address) == sizeof(address) - 1)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        while (getchar() != '\n')
            ;
        asktocontinue();
        return;
    }
    // Add new account to array
    if (*count >= 100)
    {
        printf(COLOR_RED"Error: Maximum account limit reached!\n"COLOR_RESET);
        free(accounts);
        asktocontinue();
        return;
    }

    accounts[*count].accountnumber = accNo;
    strcpy(accounts[*count].name, name);
    strcpy(accounts[*count].address, address);
    accounts[*count].balance = balance;
    accounts[*count].mobile = mobile;
    accounts[*count].dateopened.month = month;
    accounts[*count].dateopened.year = year;
    strcpy(accounts[*count].status, status);
    (*count)++;

    printf(COLOR_GREEN"\nAccount added successfully on %d-%d\n"COLOR_RESET, month, year);

    // Save to file
    saveaccounts(accounts, count);
    // Ask to continue
    asktocontinue();
}
void deleteAccount(account accounts[], int *count)
{
    if (accounts == NULL)
    {
        printf(COLOR_GREEN"Error: No accounts loaded\n"COLOR_RESET);
        return;
    }

    if (*count == 0)
    {
        printf(COLOR_YELLOW"No accounts found in the system.\n"COLOR_RESET);
        return;
    }

    long long accToDelete;
    int found = 0;
    char temp[50];

    printf("\n--- DELETE ACCOUNT ---\n");
    printf("Enter account number to delete: ");
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

    accToDelete = atoll(temp);
    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == accToDelete)
        {
            found = 1;

            if (accounts[i].balance > 0.0)
            {
                printf(COLOR_RED"Deletion rejected, balance must be zero.\n"COLOR_RESET);
                printf(COLOR_YELLOW"Current balance: %.2f\n"COLOR_RESET, accounts[i].balance);
                asktocontinue();
                return;
            }
            else
            {
                // Shift all accounts after this one to the left
                for (int j = i; j < *count - 1; j++)
                {
                    accounts[j] = accounts[j + 1];
                }
                (*count)--; // Decrease the *count
                printf(COLOR_GREEN"Account deleted successfully.\n"COLOR_RESET);
                saveaccounts(accounts, count);
                asktocontinue();
                break;
            }
        }
    }

    if (!found)
    {
        printf(COLOR_RED"Error: Account number not found.\n"COLOR_RESET);
        return;
    }

    // Save changes to file
    saveaccounts(accounts, count);
    asktocontinue();
}
void multidelete(account accounts[], int *count)
{
    int choice;
    int deleted = 0;

    printf("\n--- MULTI DELETE ---\n");
    printf("1 - Delete by date (YYYY/MM)\n");
    printf("2 - Delete by status (inactive > 3 months & balance = 0)\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf(COLOR_RED"invalid input"COLOR_RESET);
        asktocontinue();
        return;
    }
    while (getchar() != '\n')
        ;

    if (choice == 1)
    {
        int year, month;
        SYSTEMTIME st;
        GetLocalTime(&st);

        printf("Enter year: ");
        if (scanf("%d", &year) != 1)
        {
            while (getchar() != '\n')
                ;
            printf(COLOR_RED"Invalid year input\n"COLOR_RESET);
            asktocontinue();
            return;
        }

        if (year < 1900 || year > st.wYear)
        {
            printf(COLOR_RED"Year out of valid range\n"COLOR_RESET);
            asktocontinue();
            return;
        }

        printf("Enter month (1-12): ");
        if (scanf("%d", &month) != 1)
        {
            while (getchar() != '\n')
                ;
            printf(COLOR_RED"Invalid month input\n"COLOR_RESET);
            asktocontinue();
            return;
        }
        while (getchar() != '\n')
            ;

        if (month < 1 || month > 12)
        {
            printf(COLOR_RED"Invalid month (must be 1-12)\n"COLOR_RESET);
            asktocontinue();
            return;
        }

        for (int i = 0; i < *count;)
        {
            if (accounts[i].dateopened.year == year &&
                accounts[i].dateopened.month == month && accounts[i].balance == 0)
            {
                for (int j = i; j < *count - 1; j++)
                    accounts[j] = accounts[j + 1];

                (*count)--;
                deleted++;
            }
            else
            {
                i++;
            }
        }
    }

    else if (choice == 2)
    {
        SYSTEMTIME st;
        GetLocalTime(&st);

        int currentMonth = st.wMonth;
        int currentYear = st.wYear;

        for (int i = 0; i < *count;)
        {
            int monthsInactive =
                (currentYear - accounts[i].dateopened.year) * 12 +
                (currentMonth - accounts[i].dateopened.month);

            if (accounts[i].balance == 0 &&
                strcmp(accounts[i].status, "inactive") == 0 &&
                monthsInactive > 3)
            {
                for (int j = i; j < *count - 1; j++)
                    accounts[j] = accounts[j + 1];

                (*count)--;
                deleted++;
            }
            else
            {
                i++;
            }
        }
    }
    else
    {
        printf(COLOR_RED"Invalid choice\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }

    if (deleted > 0)
    {
        saveaccounts(accounts, count);
        printf(COLOR_GREEN"\n%d account(s) deleted successfully.\n"COLOR_RESET, deleted);
    }
    else
    {
        printf(COLOR_YELLOW"no accounts deleted\n"COLOR_RESET);
    }

    asktocontinue();
}

void modifyAccount(account accounts[], int *count)
{
    long long accnum;
    int found = 0;
    printf("input account number to modify\n");
    scanf("%lld", &accnum);
    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == accnum)
        {
            found = 1;
            printf(COLOR_YELLOW"\n----modifying account %lld----\n"COLOR_RESET, accnum);
            getchar(); // aashan takhod el enter ely dostaha baad ma katabt el acc number

            printf("current name: %s\n", accounts[i].name);
            printf("enter new name(or press enter to keep current name):\n");
            char newname[100];
            fgets(newname, sizeof(newname), stdin);
            newname[strcspn(newname, "\n")] = '\0';
            if (strlen(newname) > 0) // aashan law el user karar y-keep current name haydos enter fa ma3mlsh copy lel enter fi el name
                strcpy(accounts[i].name, newname);

            printf("current e-mail: %s\n", accounts[i].address);
            printf("enter new e-mail(or press enter to keep current e-mail):\n");
            char newEmail[100];
            fgets(newEmail, sizeof(newEmail), stdin);
            newEmail[strcspn(newEmail, "\n")] = '\0';
            if (strlen(newEmail) > 0)
                strcpy(accounts[i].address, newEmail);

            printf("current mobile number: %lld\n", accounts[i].mobile);
            printf("enter new mobile number(or press enter to keep current mobile number):\n");
            char newMobile[30];
            fgets(newMobile, sizeof(newMobile), stdin);
            newMobile[strcspn(newMobile, "\n")] = '\0';
            if (strlen(newMobile) > 0)
                accounts[i].mobile = atoll(newMobile);
                saveaccounts(accounts,count);
            break; // aashan el loop awel ma tela2y el acc number ely el user medakhloh tewa2af mato3odsh tedawar fi el ba2y
        }
    }
    if (!found)
        printf(COLOR_RED"couldn't find account %lld to be modified\n"COLOR_RESET, accnum);
    asktocontinue();
}
void changeStatus(account accounts[], int *count)
{
    char temp[100];
    long long accNum;
    int found = 0;
    printf("\nenter account number to change status\n");
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
        printf(COLOR_RED"Invalid input \n"COLOR_RESET);
        asktocontinue();
        return;
    }

    accNum = atoll(temp);

    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == accNum)
        {
            found = 1;
            printf("\ncurrent status of your account %lld is %s\n", accNum, accounts[i].status);
            printf("enter new status(active or inactive):\n");
            char newStatus[20];
            while (1)
            {
                fgets(newStatus, sizeof(newStatus), stdin);

                if (strchr(newStatus, '\n') == NULL)
                {
                    printf(COLOR_RED"invalid input\n"COLOR_RESET);
                    clearbuffer();
                
                    
                }
                newStatus[strcspn(newStatus, "\n")] = '\0';

                if (!checkstring(newStatus))
                {
                    printf(COLOR_RED"Invalid input \n"COLOR_RESET);
                    continue;
                }

                if ((strcmp(newStatus, "active") == 0 || strcmp(newStatus, "inactive") == 0))
                {
                    break;
                }
                else
                {
                    printf(COLOR_RED"invalid input , try again.\n"COLOR_RESET);
                }
            }
            if (strcmp(newStatus, accounts[i].status) == 0)
                printf(COLOR_YELLOW"attention! the account already have the status of %s .no changes made\n"COLOR_RESET, accounts[i].status);
            else
            {
                strcpy(accounts[i].status, newStatus);
                saveaccounts(accounts, count);
                printf(COLOR_YELLOW"account status updated successfully to %s\n"COLOR_RESET, accounts[i].status);
            }
            break;
        }
    }

    if (!found)
        printf(COLOR_YELLOW"account number %lld is not found\n"COLOR_RESET, accNum);

    asktocontinue();
}
void deposit(account accounts[], int *count)
{
    int num = *count;
    long long accNum;
    float amount;
    int found = 0;
    char filename[50];
    printf("\nenter the account number\n");
    if (scanf("%lld", &accNum) != 1)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    for (int i = 0; i < num; i++)
    {
        if (accounts[i].accountnumber == accNum)
        {
            found = 1;
            if (strcmp(accounts[i].status, "active") != 0)
            {
                printf(COLOR_YELLOW"\nwarning!! the account status is inactive,transaction cannot be done"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }
            printf("\nenter the amount you want to deposit");
            if (scanf("%f", &amount) != 1 || amount <= 0)
            {
                printf(COLOR_RED"\ninvalid input,transaction cannot be done\n"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }
            clearbuffer();
            if (amount > TRANSACTION_LIMIT)
            {
                printf(COLOR_RED"\nmax deposit per transaction is %.2f ,transaction cannot be done\n"COLOR_RESET, TRANSACTION_LIMIT);
                asktocontinue();
                return;
            }

            accounts[i].balance = accounts[i].balance + amount;
            sprintf(filename, "./%lld.txt", accounts[i].accountnumber);

            FILE *fp = fopen(filename, "a");
            if (fp != NULL)
            {
                fprintf(fp, "\ndeposit %.2f\n", amount);
                fclose(fp);
            }
            else
            {
                printf(COLOR_RED"\nerror in opening transaction file\n"COLOR_RESET);
                asktocontinue();
                return;
            }
            printf(COLOR_GREEN"\n---deposit completed successfully---\n"COLOR_RESET);
            printf(COLOR_YELLOW"current balance is: %.2f"COLOR_RESET, accounts[i].balance);
            saveaccounts(accounts, count);
            asktocontinue();
            return;
        }
    }
    if (!found)
        printf(COLOR_YELLOW"\naccount number cannot be found"COLOR_RESET);
    asktocontinue();
    return;
}
int valid_email(const char *email)
{
    if (!email)
        return 0;

    char *at = strchr(email, '@');
    if (!at || at == email)
        return 0; // No @ or @ at start

    char *dot = strchr(at + 1, '.');
    if (!dot || dot[1] == '\0')
        return 0; // No . or . at end

    if (strchr(email, ','))
        return 0;

    return 1; // Good enough for bank system!
}
int checkint(char s[])
{

    for (int i = 0; s[i]; i++)
    {
        if (!isdigit(s[i]))
            return 0;
    }
    return 1;
}
int checkstring(char s[])
{

    for (int i = 0; s[i]; i++)
    {
        if (!isalpha(s[i]) && s[i] != ' ')
            return 0;
    }
    return 1;
}
int dailylimit(long long accNum, float newAmount)
{
    char filename[50];
    char line[200];
    float totalWithdrawn = 0.0;
    float amount;
    sprintf(filename, "%lld.txt", accNum);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return 1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "withdraw", 8) == 0)
        {
            sscanf(line, "withdraw %f", &amount);
            totalWithdrawn = totalWithdrawn + amount;
        }
    }
    fclose(fp);
    if (totalWithdrawn + newAmount > DAILY_LIMIT)
        return 0; // limit exceeded
    return 1;
}

void withDraw(account accounts[], int *count)
{
    int num = *count;
    long long accNum;
    int found = 0;
    float amount;
    char filename[50];
    printf("\nenter your account number\n");
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
        { // check law el account exist
            found = 1;
            if (strcmp(accounts[i].status, "active") != 0)
            { // check law el account active wala la
                printf(COLOR_YELLOW"\nwarning!! the status of your account is inactive,transaction cannot be completed\n"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }
            printf("\nenter the amount you want to withdraw:\n");
            if (scanf("%f", &amount) != 1 || amount <= 0)
            {
                printf(COLOR_RED"\ninvalid input,transaction cannot be done\n"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }
            clearbuffer();
            if (amount > TRANSACTION_LIMIT)
            {
                printf(COLOR_RED"\nwarning!! max per transaction is 10000\n"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }
            if (amount > accounts[i].balance)
            {
                printf(COLOR_RED"\ninsufficent balance\n"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }
            sprintf(filename, "%lld.txt", accounts[i].accountnumber);

            if (!dailylimit(accNum, amount))
            {
                printf(COLOR_RED"\n--daily limit has been exceeded--\n"COLOR_RESET);
                clearbuffer();
                asktocontinue();
                return;
            }

            accounts[i].balance = accounts[i].balance - amount;

            FILE *fp = fopen(filename, "a");
            if (fp != NULL)
            {
                fprintf(fp, "withdraw %.2f\n", amount);
                fclose(fp);
            }
            printf(COLOR_GREEN"\n---withdrawal is done successfully---\n"COLOR_RESET);
            printf(COLOR_YELLOW"the balance remaining in your account is %.2f\n"COLOR_RESET, accounts[i].balance);
            saveaccounts(accounts, count);

            asktocontinue();
            return;
        }
    }
    if (!found)
        printf(COLOR_YELLOW"account number is not found\n"COLOR_RESET);
    clearbuffer();
    asktocontinue();
    return;
}
void transfer(account accounts[], int *count)
{
    int num = *count;
    long long senderAcc, receiverAcc;
    int senderIndex = -1, receiveIndex = -1;
    float amount;
    char senderFile[50], receiverFile[50];
    printf("\nenter sender account number\n");
    if (scanf("%lld", &senderAcc) != 1)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    clearbuffer();
    printf("\nenter receiver account number\n");
    if (scanf("%lld", &receiverAcc) != 1)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        clearbuffer();
        asktocontinue();
        return;
    }
    clearbuffer();
    if (senderAcc == receiverAcc)
    {
        printf(COLOR_RED"invalid input\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    for (int i = 0; i < num; i++)
    {
        if (accounts[i].accountnumber == senderAcc)
            senderIndex = i;
        if (accounts[i].accountnumber == receiverAcc)
            receiveIndex = i;
    }
    if (receiveIndex == -1 || senderIndex == -1)
    {
        printf(COLOR_YELLOW"\none or both accounts cannot be found"COLOR_RESET);
        asktocontinue();
        return;
    }
    if (strcmp(accounts[senderIndex].status, "active") != 0 || strcmp(accounts[receiveIndex].status, "active") != 0)
    {
        printf(COLOR_YELLOW"\nwarning!! one or both accounts' status is inactive\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    printf("\nenter amount you want to be transferred");
    if (scanf("%f", &amount) != 1 || amount <= 0)
    {
        printf(COLOR_RED"\ninvalid input,transaction cannot be done\n"COLOR_RESET);
        while (getchar() != '\n')
            ;
        asktocontinue();
        return;
    }
    while (getchar() != '\n')
        ;
    if (amount > TRANSACTION_LIMIT)
    {
        printf(COLOR_YELLOW"\nwarning!! max transfer per transaction is %.2f\n"COLOR_RESET, TRANSACTION_LIMIT);
        asktocontinue();
        return;
    }
    if (amount > accounts[senderIndex].balance)
    {
        printf(COLOR_YELLOW"\nwarning!! no sufficient balance,transaction cannot be done\n"COLOR_RESET);
        asktocontinue();
        return;
    }
    accounts[senderIndex].balance = accounts[senderIndex].balance - amount;
    accounts[receiveIndex].balance = accounts[receiveIndex].balance + amount;
    sprintf(senderFile, "%lld.txt", senderAcc);
    FILE *fp = fopen(senderFile, "a");
    if (fp != NULL)
    {
        fprintf(fp, "\nsent %.2f\n", amount);
        fclose(fp);
    }
    sprintf(receiverFile, "%lld.txt", receiverAcc);
    fp = fopen(receiverFile, "a");
    if (fp != NULL)
    {
        fprintf(fp, "\n received %.2f", amount);
        fclose(fp);
    }

    printf(COLOR_GREEN"\n---transfer completed successfully---\n"COLOR_RESET);
    printf("sender new balance: %.2f\n", accounts[senderIndex].balance);
    printf("receiver new balance: %.2f\n", accounts[receiveIndex].balance);
    saveaccounts(accounts, count);
    asktocontinue();
    return;
}

#endif
