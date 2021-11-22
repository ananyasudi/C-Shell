#include "headers.h"
void fg(char **list_of_args, int count)
{
    signal(SIGTSTP, z_func);

    if (count < 2 || count > 2)
    {
        printf("invalid number of arguments\n");
        return;
    }
    else
    {
        int job_id = atoi(list_of_args[1]);
        int i;
        for (i = 1; i <= job_count; i++)
        {
            if (list_of_jobs[i].st == 1)
            {
                if (list_of_jobs[i].job_id == job_id)
                {
                    int status;
                    kill(list_of_jobs[i].process_id, SIGCONT);
                    fore_grd.process_id = list_of_jobs[i].process_id;
                    strcpy(fore_grd.name, list_of_jobs[i].name);
                    fore_grd.st = 1;
                    list_of_jobs[i].st=0;
                    waitpid(list_of_jobs[i].process_id, &status, WUNTRACED);
                    fore_grd.st=-1;
                    return;
                }
            }
        }
        printf("No such process found\n");
        return;
    }
}
