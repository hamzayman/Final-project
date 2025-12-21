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

void loadaccounts(void);

#endif
