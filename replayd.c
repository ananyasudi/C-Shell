#include "headers.h"
void finding(char **list, int k)
{
}
int is_pipe(char** list,int count){
     for (int i = 0; i < count; i++)
    {
        if (strcmp(list[i], "|") == 0)
        {
            return 1;
        }
    }
    return 0;
}
void replay_func(char* command,char **list_of_args, int count)
{
    int comm_p = -1;
    int per_p = -1;
    int inte_p = -1;
    int interval, period;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(list_of_args[i], "-interval") == 0 && (i + 1 < count))
        {
            inte_p = i;
            interval = atoi(list_of_args[i + 1]);
        }
        else if (strcmp(list_of_args[i], "-period") == 0 && (i + 1 < count))
        {
            per_p = i;
            period = atoi(list_of_args[i + 1]);
        }
        else if (strcmp(list_of_args[i], "-command") == 0 && (i + 1 < count))
        {
            comm_p = i + 1;
        }
    }
    if (comm_p == -1 || per_p == -1 || inte_p == -1)
    {
        printf("arguments not given completely\n");
    }
    else
    {
        char *list[count];
        int till;
        if (inte_p < per_p)
        {
            till = inte_p - 1;
        }
        else
        {
            till = per_p - 1;
        }
        int k = 0;

        for (int i = comm_p; i <= till; i++)
        {
            list[k++] = list_of_args[i];
        }
        list[k]=NULL;
        for(int i=0;i<period/interval;i++){
            int fork_r=fork();
            if(fork_r>0){
                int status;
                waitpid(fork_r, &status, WUNTRACED);
                sleep(interval);
            }
            else if(fork_r==0){
                int fp=0;
                int fd=0;
                if(is_pipe(list,k)==1){
                    fp=1;
                    pipefunc(command,list,k);
                }
                if((is_ioredirect(list,k)==1)&&fp==0){
                    io_redirect(list,k);
                }
                else{
                if(execvp(list[0],list)<0){
                    printf("execvp failed\n");
                }
                }
                exit(0);
            }
            
        }

        return;
    }
    return;
}