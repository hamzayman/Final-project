#include "add.h"
#include "loadacc.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TRANSACTION_LIMIT 10000.0
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
        printf("Error loading accounts\n");
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

    printf("\n--- ADD NEW ACCOUNT ---\n");
    printf("Enter Account Number: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkint(temp))
    {
        printf("Invalid input \n");
        asktocontinue();
        return;
    }
     if (strlen(temp) == sizeof(temp) - 1)
    {
        printf("Invalid input \n");
        while (getchar() != '\n');
        asktocontinue();
        return;
    }
    accNo = atoll(temp);

    if (isDuplicateAccount(accounts, count, accNo))
    {
        printf("Error: Account number already exists!\n");

        asktocontinue();
        return;
    }

    printf("Enter Account Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (!checkstring(name))
    {
        printf("invalid input");\
        asktocontinue();
        return;
    }
    if (strlen(name) == sizeof(name) - 1)
    {
        printf("invalid input");\
        while (getchar() != '\n');
        asktocontinue();
        return;
    }

    printf("Enter Initial Balance: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkint(temp))
    {
        printf("invalid input");
        asktocontinue();
        return;
    }

        if (strlen(temp) == sizeof(temp) - 1)
    {
        printf("invalid input");
        while (getchar() != '\n');
        asktocontinue();
        return;
    }
    balance = atof(temp);

    printf("Enter Phone Number: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkint(temp))
    {
        printf("invalid input");
        asktocontinue();
        return;
    }
    if (strlen(temp) == sizeof(temp) - 1)
    {
        printf("invalid input");
        while (getchar() != '\n');
        asktocontinue();
        return;
    }
    mobile = atoll(temp);
    printf("Enter Address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';
    if (!valid_email(address))
    {
        printf("invalid input");
        asktocontinue();
        return;
    }
    if (strlen(address) == sizeof(address) - 1)
    {
        printf("invalid input");
        while (getchar() != '\n');
        asktocontinue();
        return;
    }
    // Add new account to array
    if (*count >= 100)
    {
        printf("Error: Maximum account limit reached!\n");
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

    printf("\nAccount added successfully on %d-%d\n", month, year);

    // Save to file
    saveaccounts(accounts, count);
    // Ask to continue
    asktocontinue();
}
void deleteAccount(account accounts[], int *count)
{
    if (accounts == NULL)
    {
        printf("Error: No accounts loaded\n");
        return;
    }

    if (*count == 0)
    {
        printf("No accounts found in the system.\n");
        return;
    }

    long long accToDelete;
    int found = 0;

    printf("\n--- DELETE ACCOUNT ---\n");
    printf("Enter account number to delete: ");
    scanf("%lld", &accToDelete);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == accToDelete)
        {
            found = 1;

            if (accounts[i].balance > 0.0)
            {
                printf("Deletion rejected, balance must be zero.\n");
                printf("Current balance: %.2f\n", accounts[i].balance);
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
                printf("Account deleted successfully.\n");
                break;
            }
        }
    }

    if (!found)
    {
        printf("Error: Account number not found.\n");
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
        printf("Invalid input\n");
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
            printf("Invalid year input\n");
            asktocontinue();
            return;
        }

        if (year < 1900 || year > st.wYear)
        {
            printf("Year out of valid range\n");
            asktocontinue();
            return;
        }

        printf("Enter month (1-12): ");
        if (scanf("%d", &month) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid month input\n");
            asktocontinue();
            return;
        }
        while (getchar() != '\n')
            ;

        if (month < 1 || month > 12)
        {
            printf("Invalid month (must be 1-12)\n");
            asktocontinue();
            return;
        }

        for (int i = 0; i < *count;)
        {
            if (accounts[i].dateopened.year == year &&
                accounts[i].dateopened.month == month)
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
        printf("Invalid choice\n");
        asktocontinue();
        return;
    }

    printf("\n%d account(s) deleted successfully.\n", deleted);

    if (deleted > 0)
        saveaccounts(accounts, count);

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
            printf("\n----modifying account %lld----\n", accnum);
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
            printf("\naccount is updated successfully\n");
            break; // aashan el loop awel ma tela2y el acc number ely el user medakhloh tewa2af mato3odsh tedawar fi el ba2y
        }
    }
    if (!found)
        printf("couldn't find account %lld to be modified\n", accnum);
    saveaccounts(accounts, count);
    asktocontinue();
}
void changeStatus(account accounts[], int *count)
{
    long long accNum;
    int found = 0;
    printf("\nenter account number to change status\n");
    scanf("%lld", &accNum);
    getchar();
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
                newStatus[strcspn(newStatus, "\n")] = '\0';
                if ((strcmp(newStatus, "active") == 0 || strcmp(newStatus, "inactive") == 0))
                {
                    break;
                }
                else
                {
                    printf("invalid input , try again.\n");
                }
            }
            if (strcmp(newStatus, accounts[i].status) == 0)
                printf("attention! the account already have the status of %s .no changes made\n", accounts[i].status);
            else
            {
                strcpy(accounts[i].status, newStatus);
                saveaccounts(accounts, count);
                printf("account status updated successfully to %s\n", accounts[i].status);
            }
            break;
        }
    }

    if (!found)
        printf("account number %lld is not found\n", accNum);

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
    scanf("%lld", &accNum);
    for (int i = 0; i < num; i++)
    {
        if (accounts[i].accountnumber == accNum)
        {
            found = 1;
            if (strcmp(accounts[i].status, "active") != 0)
            {
                printf("\nwarning!! the account status is inactive,transaction cannot be done");
                return;
            }
            printf("\nenter the amount you want to deposit");
            scanf("%f", &amount);
            if (amount > TRANSACTION_LIMIT)
            {
                printf("\nmax deposit per transaction is %.2f ,transaction cannot be done\n", TRANSACTION_LIMIT);
                return;
            }
            if (amount <= 0)
            {
                printf("invalid amount");
                return;
            }
            accounts[i].balance = accounts[i].balance + amount;
            sprintf(filename, "%lld.txt", accounts[i].accountnumber);
            FILE *fp = fopen(filename, "a");
            if (fp != NULL)
            {
                fprintf(fp, "\ndeposit %.2f\n", amount);
                fclose(fp);
            }
            else
            {
                printf("\nerror in opening transaction file\n");
                return;
            }
            printf("\n---deposit completed successfully---\n");
            printf("current balance is: %.2f", accounts[i].balance);
            return;
        }
    }
    if (!found)
    {
        printf("\naccount number cannot be found");
        asktocontinue();
    }
}
int valid_email(const char *email)
{
    if (!email)
        return 0;

    // Just check for @ and . in reasonable positions
    char *at = strchr(email, '@');
    if (!at || at == email)
        return 0; // No @ or @ at start

    char *dot = strchr(at + 1, '.');
    if (!dot || dot[1] == '\0')
        return 0; // No . or . at end

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
