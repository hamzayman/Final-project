#include <windows.h>
#include <stdio.h>
#include <string.h>
int isDuplicateAccount(long long accNo){
FILE *fp;
long long fileAccNo;
char line [200];
fp= fopen("accounts.txt","r");
if (fp==NULL) 
return 0; 
while (fgets(line,sizeof(line),fp)){
   if(sscanf(line,"%lld", &fileAccNo)==1){
    if (fileAccNo==accNo){
        fclose(fp);
        return 1;
    }
}
}
fclose(fp);
return 0;
}
void addAccount(){
    FILE *fp;
    long long accNo;
    char name[50];
    float balance;
    char date [11];
    char status[]="active";
    char email [100];
    int phone;
    SYSTEMTIME st;
    GetLocalTime(&st);
    sprintf(date,"%02d-%02d-%04d",st.wDay,st.wMonth,st.wYear);
    printf("Enter Account Number:");
    scanf("%lld",&accNo);
     while (getchar()!='\n');
    if (isDuplicateAccount(accNo)){
        printf("Error Account number already exists!\n");
        return;
    }
    printf("Enter Account Name:");
     gets(name);
     printf("Enter Initial Balance:");
     scanf("%f",&balance);
      while (getchar()!='\n');
     printf("Enter phone number:");
     scanf("%d",&phone);
      while (getchar()!='\n');
     printf("Enter the email:");
     gets(email);
     fp=fopen("accounts.txt","a");
     if (fp==NULL){
        printf("Error opening file!\n");
        return;
     }
     fprintf(fp,"%lld,%s,%s,%.2f,%d,%s,%s\n",accNo,name,email,balance,phone,date,status);
     fclose(fp);
     printf("Account is added successfully on %s\n",date);

}
typedef struct {
    int accountNumber;
    char name[50];
    float balance;
    char status[20];
    char date[20];
    char email[100];
    int phone;
} BankAccount;

void deleteAccount() {
    BankAccount accounts[100];
    int count = 0;
    FILE *fp;
    int accToDelete;
    int found = 0;
    char line[300];
    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token;
        token = strtok(line, ",");
        if (token == NULL) continue;
        accounts[count].accountNumber = atoi(token);
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(accounts[count].name, token, sizeof(accounts[count].name));
        accounts[count].name[sizeof(accounts[count].name)-1] = '\0';
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(accounts[count].email, token, sizeof(accounts[count].email));
        accounts[count].email[sizeof(accounts[count].email)-1] = '\0';
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        accounts[count].balance = atof(token);
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        accounts[count].phone = atoi(token);
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(accounts[count].date, token, sizeof(accounts[count].date));
        accounts[count].date[sizeof(accounts[count].date)-1] = '\0';
        token = strtok(NULL, "\n");  
        if (token == NULL) continue;
        strncpy(accounts[count].status, token, sizeof(accounts[count].status));
        accounts[count].status[sizeof(accounts[count].status)-1] = '\0';
        count++;
        if (count >= 100) break;
    }
    fclose(fp);
    printf("Enter account number to delete: ");
    scanf("%d", &accToDelete);
    fp = fopen("accounts.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accToDelete) {
            found = 1;
            if (accounts[i].balance > 0) {
                printf("Deletion rejected, balance must be zero.\n");
            } else {
                printf("Account deleted successfully.\n");
                continue;  
            }
        }
        fprintf(fp,"%d,%s,%s,%.2f,%d,%s,%s\n",
                accounts[i].accountNumber,
                accounts[i].name,
                accounts[i].email,
                accounts[i].balance,
                accounts[i].phone,
                accounts[i].date,
                accounts[i].status);
    }

    if (!found) {
        printf("Error: account number not found.\n");
    }

    fclose(fp);
}
int main(){
    addAccount();
    return 0;
}



