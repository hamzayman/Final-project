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
void loadaccounts(account accounts[],int *count){
    char x[300];
    *count=0;

    FILE *fp=fopen("accounts.txt","r");
if(fp==NULL){
    printf("error opening file");
    return;
}
 while(fgets(x,sizeof(x),fp)!=NULL){
    x[strcspn(x,"\n")]='\0'; // da by3ed l7ad ma yla2y \n melakher by3ed char.s el line
    char *token=strtok(x,",");// byfsel el lines b kol comma
    if(token==NULL) continue;
    accounts[*count].accountnumber= atoll(token); //el atoi bethawel mn string le long long
    token=strtok(NULL,",");
    strcpy(accounts[*count].name,token);

    token=strtok(NULL,",");
    strcpy(accounts[*count].address,token);
     token=strtok(NULL,",");
    accounts[*count].balance =atof(token); //el atof bethawel mn string le float
    token=strtok(NULL,",");
    accounts[*count].mobile = atoll(token);
     token=strtok(NULL,",");
     sscanf(token, "%d-%d", &accounts[*count].dateopened.month, &accounts[*count].dateopened.year);
      token=strtok(NULL,"\n");
      if (token[0] == ' ')
       token++;
      strcpy(accounts[*count].status,token);
      (*count)++;
}
fclose(fp);}
void sortByName(account accounts[],int count){
    account temp;
    for(int i=0;i<count-1;i++){
            for(int j=i+1;j<count;j++)
        if(strcmp(accounts[i].name,accounts[j].name)>0){
            temp=accounts[i];
            accounts[i]=accounts[j];
            accounts[j]=temp;

        }


    }





}
void sortByBalance(account accounts[],int count){
    account temp;
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++)
        if(accounts[i].balance>accounts[j].balance){
            temp=accounts[i];
            accounts[i]=accounts[j];
            accounts[j]=temp;

        }
    }






}
void sortByDate(account accounts[],int count){
    account temp;
  for(int i=0;i<count-1;i++){
    for(int j=i+1;j<count;j++)
    if(accounts[i].dateopened.year>accounts[j].dateopened.year ||(accounts[i].dateopened.year==accounts[j].dateopened.year && accounts[i].dateopened.month>accounts[j].dateopened.month) ){
        temp=accounts[i];
        accounts[i]=accounts[j];
        accounts[j]=temp;
    }
  }


}
void sortByStatus(account accounts[],int count){
    account temp;
  for(int i=0;i<count-1;i++){
    for(int j=i+1;j<count;j++)
        if(strcmp(accounts[i].status,accounts[j].status)>0){
            temp=accounts[i];
            accounts[i]=accounts[j];
            accounts[j]=temp;
        }

  }

}
void printAccounts(account accounts[],int count){
    int choice;
    printf("\n you need accounts to be sorted by:\n");
    printf("1-name\n");
    printf("2-balance\n");
    printf("3-date opened\n");
    printf("4-status\n");
    printf("please input your choice\n");
    scanf("%d",&choice);

    switch(choice){
      case 1:
          sortByName(accounts,count);
          break;
      case 2:
          sortByBalance(accounts,count);
          break;
      case 3:
          sortByDate(accounts,count);
          break;
      case 4:
          sortByStatus(accounts,count);
          break;
      default:
          printf("invalid choice\n");
          return;

    }
printf("\n accounts list\n");
   for(int i=0;i<count;i++){
    printf("account number: %lld\n",accounts[i].accountnumber);
    printf("name: %s\n",accounts[i].name);
    printf("address: %s\n",accounts[i].address);
    printf("balance: %f\n",accounts[i].balance);
    printf("mobile: %lld\n",accounts[i].mobile);
    printf("date opened: %d-%d\n",accounts[i].dateopened.month,accounts[i].dateopened.year);
    printf("status: %s\n",accounts[i].status);
    }
    }
    const char* getMonthName(int month) {
    switch(month) {
        case 1:  return "January";
        case 2:  return "February";
        case 3:  return "March";
        case 4:  return "April";
        case 5:  return "May";
        case 6:  return "June";
        case 7:  return "July";
        case 8:  return "August";
        case 9:  return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
        default: return "Invalid month";
    }
}
void querySearch(account accounts[],int count,int *accFound){
  long long searchnumber;
  int found=0;
  * accFound=0;
  printf("input account number to search");
  scanf("%lld",&searchnumber);
       for(int i=0;i<count;i++){
        if(accounts[i].accountnumber==searchnumber){
            printf("\naccount number: %lld\n",accounts[i].accountnumber);
            printf("name: %s\n",accounts[i].name);
            printf("address: %s\n",accounts[i].address);
            printf("balance: %f\n",accounts[i].balance);
            printf("mobile: %lld\n",accounts[i].mobile);
            printf("date opened: %s %d\n",getMonthName(accounts[i].dateopened.month),accounts[i].dateopened.year);
            printf("status: %s\n",accounts[i].status);
            found=1;
            (*accFound)++;
            break;

        }

       }
       if(!found)
        printf("\n account not found\n");

}
void advancedSearch(account accounts[],int count,int *accFound){
  char keyword[100];
  int found=0;
  *accFound=0;
  printf("input keyword: ");
  getchar();
  fgets(keyword,sizeof(keyword),stdin);
  keyword[strcspn(keyword,"\n")]='\0';
    for(int i=0;i<count;i++){
        if(strstr(accounts[i].name,keyword)!=NULL){
            printf("\naccount number: %lld\n",accounts[i].accountnumber);
            printf("name: %s\n",accounts[i].name);
            printf("address: %s\n",accounts[i].address);
            printf("balance: %f\n",accounts[i].balance);
            printf("mobile: %lld\n",accounts[i].mobile);
            printf("date opened: %s %d\n",getMonthName(accounts[i].dateopened.month),accounts[i].dateopened.year);
            printf("status: %s\n",accounts[i].status);
            found=1;
            (*accFound)++;


        }
    }

if(!found)
    printf("\nthe keyword is not found in any account\n");

}
void modifyAccount(account accounts[],int count){
 long long accnum;
 int found=0;
 printf("input account number to modify");
 scanf("%lld",&accnum);
    for(int i=0;i<count;i++){
        if(accounts[i].accountnumber==accnum){
            found=1;
            printf("\n----modifying account %lld----\n",accnum);
            getchar(); //aashan takhod el enter ely dostaha baad ma katabt el acc number

            printf("current name: %s\n",accounts[i].name);
            printf("enter new name(or press enter to keep current name):\n");
            char newname[100];
            fgets(newname,sizeof(newname),stdin);
            newname[strcspn(newname,"\n")]='\0';
            if(strlen(newname)>0)   //aashan law el user karar y-keep current name haydos enter fa ma3mlsh copy lel enter fi el name
                strcpy(accounts[i].name,newname);

            printf("current e-mail: %s\n",accounts[i].address);
            printf("enter new e-mail(or press enter to keep current e-mail):\n");
            char newEmail[100];
            fgets(newEmail,sizeof(newEmail),stdin);
            newEmail[strcspn(newEmail,"\n")]='\0';
            if(strlen(newEmail)>0)
                strcpy(accounts[i].address,newEmail);

                printf("current mobile number: %lld\n",accounts[i].mobile);
                printf("enter new mobile number(or press enter to keep current mobile number):\n");
                char newMobile[30];
                fgets(newMobile,sizeof(newMobile),stdin);
                newMobile[strcspn(newMobile,"\n")]='\0';
                if(strlen(newMobile)>0)
                    accounts[i].mobile=atoll(newMobile);
                    printf("\naccount is updated successfully\n");
                    break; //aashan el loop awel ma tela2y el acc number ely el user medakhloh tewa2af mato3odsh tedawar fi el ba2y
        }
    }
      if(!found)
        printf("couldn't find account %lld to be modified",accnum);


}
void changeStatus(account accounts[],int count){
   long long accNum;
   int found=0;
   printf("\nenter account number to change status\n");
   scanf("%lld",&accNum);
   getchar();
   for(int i=0;i<count;i++){
    if(accounts[i].accountnumber==accNum){
        found=1;
        printf("\ncurrent status of your account %lld is %s\n",accNum,accounts[i].status);
        printf("enter new status(active or inactive):\n");
        char newStatus[20];
        while(1){
        fgets(newStatus,sizeof(newStatus),stdin);
        newStatus[strcspn(newStatus,"\n")]='\0';
        if((strcmp(newStatus,"active")==0 || strcmp(newStatus,"inactive")==0)){
            break;}
            else{
                printf("invalid input , try again.\n");
            }
        }
        if(strcmp(newStatus,accounts[i].status)==0)
            printf("attention! the account already have the status of %s .no changes made\n",accounts[i].status);
        else {
            strcpy(accounts[i].status,newStatus);
            printf("account status updated successfully to %s\n",accounts[i].status);
        }
        break;
    }


   }

  if(!found)
    printf("account number %lld is not found",accNum);

}
int main() {
    account accounts[30];
    int count = 0;
    int accFound=0;

    loadaccounts(accounts, &count);
    changeStatus(accounts,count);



    return 0;
}
