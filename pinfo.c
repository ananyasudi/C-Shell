#include "headers.h"
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
void pinfo(char **list_of_args, int count)
{
    char *p; //waste
    int num;
    char comm[100];
    char state;
    long pid;
    long long conv;

    // printf("%ld", pid);
    char *file_name = (char *)malloc(1000 * sizeof(char));
    if (count == 1)
    {
        pid = getpid();
    }
    else if (count == 2)
    {
        sscanf(list_of_args[1], "%ld", &pid);
        printf("%ld", pid);
    }
    else if (count > 2)
    {
        printf("too many args given");
        return;
    }
    // pid = strtol(list_of_args[1], &p, 10);
    sprintf(file_name, "/proc/%ld/stat", pid);
    // printf("%s", file_name);
    FILE *f = fopen(file_name, "r");
    char *total = (char *)malloc(sizeof(char) * 10000);
    char *temp = (char *)malloc(sizeof(char) * 10000);

    unsigned long int len = 10000;
    int x = getline(&total, &len, f);
    if (x < 0)
    {
        perror("unable to read /proc file");
    }
    strcpy(temp, total);
    // printf("%s\n", total);
    printf("Process Id--%ld\n", pid);
    int number = 0;
    char *t;
    char st[10] = "";
    t = strtok(temp, " ");
    int pgrp, tgpid; //4, 7

    while (t != NULL)
    {
        number++;
        t = strtok(NULL, " ");
        if (number == 2)
        {
            // sscanf(st, "%s", t);

            printf("Process Status--%s\n", t);
        }
        if (number == 22)
        {
            conv = strtol(t, &p, 10);
            printf("Memory--%lld\n", conv);
        }
        // if (number == 4)
        // {
        //     pgrp = strtol(t, &p, 10);
        // }
        // if (number == 7)
        // {
        //     tgpid = strtol(t, &p, 10);
        // }
    }
    // if (pgrp == tgpid)
    // {
    //     strcat(t, "+");
    // }
    // printf("Process Status--%s\n", t);
    // printf("Memory--%lld\n", conv);

    sprintf(file_name, "/proc/%ld/exe", pid);
    FILE *f2 = fopen(file_name, "r");

    char total2[100] = "";

    int x2 = readlink(file_name, total2, sizeof(total2));
    total2[x2] = '\0';

    // getline(&total2, &len, f);
    // printf("%s\n", total2);----------------------------------------------filecontents of executable in total2

    // sprintf(file, "/proc/%d/exe", pid); // For executable path
    //

    // printf("%s",total);
    // t = strtok(total, " ");
    // number = 0;
    // while (number < 2)
    // {
    //     number++;
    //     t = strtok(NULL, " ");
    // }
    // printf("%s\n", t);
    //t contains name of executable file
    char cwd[200] = "";
    char direc[100] = "";
    getcwd(cwd, sizeof(cwd));
    if (strcmp(total2, temp_home) == 0)
    {

        strcpy(direc, "~");
    }
    else
    {

        int i = 0;
        if (strlen(total2) > strlen(temp_home))
        {
            int c_d = 1;
            for (i = 0; i < strlen(total2); i++)
            {
                if (total2[i] == temp_home[i])
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            if (i == strlen(temp_home))
            { //the direc we are in is in the temp_home
                direc[0] = '~';
                for (int j = i; j < strlen(total2); j++)
                {
                    direc[c_d++] = total2[j];
                }
                direc[c_d] = '\0';
            }
            else
            {
                strcpy(direc, total2);
            }
        }
        else
        {
            strcpy(direc, total2);
        }

        // printf("%s\n", direc);
    }
    // strcat(direc, "/");
    // strcat(direc, t);
    printf("executable path--%s\n", direc);

    // fscanf(f,"%d%s%c",&waste,comm,&state);
    // printf("%d\n%s\n%c\n",waste,comm,state);
}

