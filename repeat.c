#include "headers.h"
void repeat(char **list_of_args, int count)
{
    int flagb2 = 0; //assuming no backgroundpro
    char *modified_list[100];
    for (int i = 0; i < 100; i++)
    {
        modified_list[i] = (char *)malloc(100 * sizeof(char));
    }
    if (count < 3)
    {
        perror("less arguments given");
    }
    else
    {
        int c = 0;
        for (int i = 2; i < count; i++)
        {
            strcpy(modified_list[c++], list_of_args[i]);
        }
        for (int i = 0; i < c; i++)//for checking bg process
        {
            if (strcmp(modified_list[i], "&") == 0)
            {
                flagb2 = 1;
            }
        }
        int r_num = list_of_args[1][0] - 48;
        for (int j = 0; j < r_num; j++)
        {
            if (strcmp(list_of_args[2], "cd") == 0)
            {
                change_direc(modified_list, count - 2);
            }
            else if (strcmp(list_of_args[2], "echo") == 0)
            {
                echo(modified_list, count - 2);
            }
            else if (strcmp(list_of_args[2], "ls") == 0)
            {
                _ls(modified_list, count - 2);
            }
            else
            {
                if(flagb2==0){
                fore(modified_list, count - 2);
                }
                else if (flagb2!=0){
                    background(modified_list,count-2);
                }
            }
        }
    }
    return;
}