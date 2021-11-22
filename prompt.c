#include "prompt.h"
#include "headers.h"
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>


void prompt()
{

    char direc[100] = "";
    char dis_name[500] = "";
    char cwd[400] = "";

    //extracting system name
    // struct utsname unameData;
    // uname(&unameData);
    // // char *sys_name = unameData.sysname;
    char sys_name[100]="";
    gethostname(sys_name,sizeof(sys_name));

    char *username;
    username = (char *)malloc(sizeof(char) * 300);
    username = getlogin(); //returns username
    // printf("%s",username);

    getcwd(cwd, sizeof(cwd));
    if (strcmp(cwd, temp_home) == 0)
    {

        strcpy(direc, "~");
    }
    else
    {

        int i = 0;
        if (strlen(cwd) > strlen(temp_home))
        {
            int c_d = 1;
            for (i = 0; i < strlen(cwd); i++)
            {
                if (cwd[i] == temp_home[i])
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            if(i==strlen(temp_home)){ //the direc we are in is in the temp_home 
            direc[0] = '~';
            for (int j = i; j < strlen(cwd); j++)
            {
                direc[c_d++] = cwd[j];
            }
            direc[c_d] = '\0';
            }
            else{
                strcpy(direc,cwd);
            }
        }
        else
        {
            strcpy(direc,cwd);

        }

    }

    
    dis_name[0] = '<';
    strcat(dis_name, username);
    strcat(dis_name, "@");
    strcat(dis_name, sys_name);
    strcat(dis_name, direc);
    strcat(dis_name, ">");

    printf("%s", dis_name);
}
