#include "headers.h"
pid_t pr_id;
void background(char **list_of_args, int count)
{
    char *modified_list[100];
    for (int i = 0; i < 100; i++)
    {
        modified_list[i] = (char *)malloc(100 * sizeof(char));
    }
    int i = 0;
    for (i = 0; i < count; i++)
    {
        strcpy(modified_list[i], list_of_args[i]);
    }
    // strcpy(modified_list[i],NULL);
    modified_list[i - 1] = NULL;
    modified_list[i] = NULL;

    int f_r = fork();
    setpgid(0, 0);
    if (f_r < 0)
    {
        perror("fork failed");
    }
    else if (f_r == 0)
    {
        execvp(modified_list[0], modified_list);
    }
    else
    {
        job_count += 1;
        printf("[%d] %d %s\n", job_count, f_r, modified_list[0]);
        list_of_jobs[job_count].job_id=job_count;
        list_of_jobs[job_count].st=1;
        list_of_jobs[job_count].process_id = f_r; //copying jobs
        strcpy(list_of_jobs[job_count].name, modified_list[0]);
    }
    return;
}
