#include "headers.h"
void bg(char **list_of_args, int count)
{

    int flag=0;
    if (count < 2 || count > 2)
    {
        printf("enter correct number of arguments\n");
        return;
    }
    else
    {

        int job_id = atoi(list_of_args[1]);
        int pid = getpid();

        for (int i = 1; i <= job_count; i++)
        {
            if (job_id == list_of_jobs[i].job_id && list_of_jobs[i].st==1)
            {
                flag=1;
                kill(pid, SIGCONT);
                return;
            }
        }
        if(flag==0){
            printf("no such job exists\n");
            return;
        }

    }
    return;
}