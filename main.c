#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct 
{
    int month;
    int year; 
}date;

typedef struct{
    long long accountnumber;
    char name[100];
     char address[100];
     float balance;
    long long mobile;
     date dateopened;
    char status[100];
   
}account;
void loadaccounts(account accounts[]){
    char x[300];
    int count=0;

    FILE *fp=fopen("account.txt","r");
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
    accounts[count].balance =atof(token); //el atof bethawel mn string le float
    token=strtok(NULL,",");
    accounts[count].mobile = atoll(token);
     token=strtok(NULL,",");
     sscanf(token, "%d-%d", &accounts[count].dateopened.month, &accounts[count].dateopened.year);
      token=strtok(NULL,",");
      strcpy(accounts[count].status,token);
      count++;
      

    }
fclose(fp);}
