#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED

#include "account.h"
#include "loadacc.h"

int isDuplicateAccount(account accounts[], int *count, long long accNo);
void addAccount(account accounts[], int *count);
void deleteAccount(account accounts[], int *count);
void multidelete(account accounts[], int *count);
void deposit(account accounts[],int *count);
int checkstring(char s[]);
int checkint(char s[]);
int valid_email(const char *email);
int dailylimit(long long accNum,float newAmount);
void withDraw(account accounts[],int* count);
void transfer(account accounts[],int *count);



#endif
