#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED

#include "account.h"
#include "loadacc.h"

int isDuplicateAccount(account accounts[], int *count, long long accNo);
void addAccount(account accounts[], int *count);
void deleteAccount(account accounts[], int *count);
void multidelete(account accounts[], int *count);

#endif
