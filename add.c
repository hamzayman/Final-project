#include "add.h"
#include "loadacc.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

int isDuplicateAccount(account accounts[], int *count, long long accNo)
{
    for (int i = 0; i < *count; i++)
    {
        if (accounts[i].accountnumber == accNo)
        {
            return 1;  // Duplicate found
        }
    }
    return 0;  // No duplicate
}
void addAccount(account accounts[],int *count)
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
    
    SYSTEMTIME st;
    GetLocalTime(&st);
    month = st.wMonth;
    year = st.wYear;
    
    printf("\n--- ADD NEW ACCOUNT ---\n");
    printf("Enter Account Number: ");
    scanf("%lld", &accNo);
    while (getchar() != '\n');
    
    if (isDuplicateAccount(accounts, count, accNo))
    {
        printf("Error: Account number already exists!\n");
        asktocontinue();
        return;
    }
    
    printf("Enter Account Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Enter Initial Balance: ");
    scanf("%f",&balance);
    while (getchar() != '\n');
    
    printf("Enter Phone Number: ");
    scanf("%lld", &mobile);
    while (getchar() != '\n');
    
    printf("Enter Address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';
    
    // Add new account to array
    if (*count >= 100) {
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
    *count++;
    
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
    while (getchar() != '\n');
    
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
                (*count)--;  // Decrease the *count
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
    saveaccounts(accounts,count);
    asktocontinue();
}
void multidelete(account accounts[],int *count,int *accfound){

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
        saveaccounts(accounts,count);
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
                saveaccounts(accounts,count);
                printf("account status updated successfully to %s\n", accounts[i].status);
            }
            break;
        }
    }

    if (!found)
        printf("account number %lld is not found\n", accNum);
    
    asktocontinue();
}