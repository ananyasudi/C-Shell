#include "headers.h"

void fore(char **token, int count)
{
    int status;

    pid_t fork_ret = fork();

    strcpy(fore_grd.name, token[0]);
    fore_grd.process_id = fork_ret;

    // printf("%d\n",fore_grd.process_id);

    char *modified_list[100];
    for (int i = 0; i < 100; i++)
    {
        modified_list[i] = (char *)malloc(100 * sizeof(char));
    }
    int i = 0;
    for (i = 0; i < count; i++)
    {
        strcpy(modified_list[i], token[i]);
    }
    // strcpy(modified_list[i],NULL);
    modified_list[i] = NULL;

    if (fork_ret < 0)
        perror("Error: Fork Failed\n");
    else if (fork_ret == 0)
    {
        int f = execvp(modified_list[0], modified_list);
        if (f < 0)
        {
            perror("Error: exec failed\n");
        }
        exit(0);
    }
    else if (fork_ret > 0) //parent process
    {
        waitpid(fork_ret, &status, WUNTRACED);
    }
    return;
}