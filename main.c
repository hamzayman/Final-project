#include <stdio.h>
#include <stdlib.h>

void login()


void startmenu(void)
{
    int x;
    int result;

    while (1)
    {
        printf("\n1: LOGIN\n0: QUIT\n");

        result = scanf("%d", &x);

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
            printf("Login selected.\n");
            break;
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
