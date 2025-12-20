#include "loadacc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadaccounts(void){
    account accounts[30];
    char x[300];
    int count=0;

    FILE *fp=fopen("accounts.txt","r");
if(fp==NULL){
    printf("error opening file");
    return;
}
 while(fgets(x,sizeof(x),fp)!=NULL){
    x[strcspn(x,"\n")]='\0'; // da by3ed l7ad ma yla2y \n melakher by3ed char.s el line
    char *token=strtok(x,",");// byfsel el lines b kol comma
    if(token==NULL) continue;
    accounts[count].accountnumber= atoll(token); //el atoi bethawel mn string le long long
    token=strtok(NULL,",");
    strcpy(accounts[count].name,token);

    token=strtok(NULL,",");
    strcpy(accounts[count].address,token);
     token=strtok(NULL,",");
    accounts[count].balance =(float)atof(token); //el atof bethawel mn string le float
    token=strtok(NULL,",");
    accounts[count].mobile = atoll(token);
     token=strtok(NULL,",");
     sscanf(token, "%d-%d", &accounts[count].dateopened.month, &accounts[count].dateopened.year);
      token=strtok(NULL,",");
      strcpy(accounts[count].status,token);

      count++;
}
fclose(fp);}