#include "headers.h"
// command[strlen(command)-1]='\0';


void change_direc(char **list_of_args, int count)
{
    char curr[300];
    strcpy(curr,"");
    getcwd(curr,sizeof(curr));

    if (count > 2)
    {
        printf("many arguments given");
        return;
    }
    if (count == 2)
    {
        if (list_of_args[1][strlen(list_of_args[1]) - 1] == '\n')
        {
            list_of_args[1][strlen(list_of_args[1]) - 1] = '\0';
        }

        int check = 0;
        if (strcmp(list_of_args[1], "~") == 0)
        {
            strcpy(prev_wd,curr);
            chdir(temp_home);
            // strcpy(prev_wd,temp_home);
            return;
        }
        else if (list_of_args[1][0] == '~' && strlen(list_of_args[1]) > 0) //for ~/dup_direc -> ./dup_direc
        {
            list_of_args[1][0] = '.';
            strcpy(prev_wd,curr);
            check = chdir(list_of_args[1]);
            if (check < 0)
            {
                printf("there doesn't exist any such direc\n");
                return;
            }
            // strcpy(prev_wd,list_of_args[1]);
            // printf("%s",prev_wd);
            return;
        }
        else
        {
            if (strcmp(list_of_args[1],"-")==0)
            {
                chdir(prev_wd);
                printf("%s\n",prev_wd);
                strcpy(prev_wd,curr);

            }
            else
            {
                strcpy(prev_wd,curr);
                check = chdir(list_of_args[1]); //for cd <dirname>
                if (check < 0)
                {
                    printf("%d couldn't open directory", check);
                    return;
                }
                // strcpy(prev_wd,list_of_args[1]);
            }
        }
        // else succesfully went to direc
    }
    else
    {
        //go to home direc
        strcpy(prev_wd,curr);
        chdir(temp_home);
    }
    return;
}