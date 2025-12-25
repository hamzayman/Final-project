#ifndef LOADACC_H_INCLUDED
#define LOADACC_H_INCLUDED

#include "account.h"
#include "add.h"

void startmenu(void);
void menu(account accounts[], int *count, int *accFound);
void asktocontinue(void);


account *loadaccounts(int *count);
void saveaccounts(account accounts[], int *count);


void printAccounts(account accounts[], int *count);
void querySearch(account accounts[], int *count, int *accFound);
void advancedSearch(account accounts[], int *count, int *accFound);
void modifyAccount(account accounts[], int *count);
void changeStatus(account accounts[], int *count);

#endif
