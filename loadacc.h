#ifndef LOADACC_H
#define LOADACC_H

typedef struct
{
    int month;
    int year;
} date;

typedef struct
{
    long long accountnumber;
    char name[100];
    char address[100];
    double balance;
    long long mobile;
    date dateopened;
    char status[100];
} account;

account *loadaccounts(int *count);
void sortByName(account accounts[], int count);
void sortByBalance(account accounts[], int count);
void sortByDate(account accounts[], int count);
void sortByStatus(account accounts[], int count);
void printAccounts(account accounts[], int count);
const char *getMonthName(int month);
void querySearch(account accounts[], int count, int *accFound);
void advancedSearch(account accounts[], int count, int *accFound);
void modifyAccount(account accounts[], int count);
void changeStatus(account accounts[], int count);
void asktocontinue();
void menu(account accounts[], int count,int *accFound);
void saveaccounts(account accounts[], int count);


#endif
