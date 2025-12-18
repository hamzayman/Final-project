#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int login(){

    int c;
    while ((c = getchar()) != '\n' && c != EOF); //by2ra char's l7ad \n aw eof (byclear el bufffer) 
FILE*fp;
char f_user[50],f_pass[50],in_user[50],in_pass[50];
printf("Enter username :\n");
scanf("%49s",in_user); //49 exactly cuz last character is \0
printf("Enter password :\n");
scanf("%49s",in_pass); //49 exactly cuz last character is \0

fp=fopen("users.txt","r"); // 3ayez a read el data
if (fp == NULL) 
{
    printf("error occured "); // law el file hasal error
    return 0;
}
while (fscanf(fp,"%49s %49s",f_user,f_pass)==2){        // ==2 yaany while it reads ONLY 2 words
    if (strcmp(in_user,f_user)==0&&strcmp(in_pass,f_pass)==0){ // input = data
        fclose(fp); 
        printf("login successfull\n");
        return 1; // login success
        
    }

}
fclose(fp);
return 0; // login failed
}

void startmenu(void)
{
    int x;
    int result;

    while (1)
    {
        printf("\n1: LOGIN\n0: QUIT\n");

        result = scanf("%d", &x); // law akhad rakam haykoon 1 law akhad ay haga tanya hayb2a 0

        if (result != 1)
        {
            printf("Invalid\nenter a number\n");

            while (getchar() != '\n');       //i used this to remove the wrong input from the scanf so i can get new input so it does not get into an infinite loop
            continue;
        }

        if (x == 0)
        {
            exit(0);
        }
        else if (x == 1)
        {
            int login_result=login(); // de feeha value el result 3shan mancallsh el func kaza mara
            
           if( login_result==0){         // bro forgot his password :p
            printf("UNAUTHORIZED USER SYSTEM WILL CLOSE\n");
            exit(0);
           }if( login_result==1){
            printf("USER CONFIRMED\n");
            exit(0);
           }
        }
        else
        {
            printf("Invalid\n");
        }
    }
}

int main(void)
{
    startmenu();
    return 0;
}
