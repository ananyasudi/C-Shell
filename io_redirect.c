#include "headers.h"
void io_redirect(char **list_of_args, int count)
{

    char *dup_a[100];

    int ipr = 0, opr = 0, app = 0; // count of symbols
    int ip_p = -1, op_p = -1, ap_p = -1;
    char *ip_f;
    char *op_f;
    char *ap_f;
    int fd[2];
    int in_o, op_o; //stdin and stdout
    int stat;

    int till=0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(list_of_args[i], ">>") == 0)
        {
            ap_p = i;
            app++;
        }
        else if (strcmp(list_of_args[i], ">") == 0)
        {
            op_p = i;
            opr++;
        }
        else if (strcmp(list_of_args[i], "<") == 0)
        {
            ip_p = i;
            ipr++;
        }
    }
    int temp_i = 0;
    
    if (ip_p != 0 && ip_p != count - 1)
        ip_f = list_of_args[ip_p + 1];
    if (op_p != 0 && op_p != count - 1)
        op_f = list_of_args[op_p + 1];
    if (ap_p != 0 && ap_p != count - 1)
        ap_f = list_of_args[ap_p + 1];
    if(ip_p==count-1||op_p==count-1||ap_p==count-1){
        printf("invalid command\n");
        return;
    }

    if (ipr!=0)
    {
        in_o = dup(0);
        fd[0] = open(ip_f, O_RDONLY);
        if(fd[0]<0){
            printf("file doesn't exist\n");
        }
        till=ip_p;
        dup2(fd[0], 0);

    }
    if(opr||app){

        op_o=dup(1);
        if(opr){
        fd[1]=open(op_f,O_WRONLY | O_CREAT | O_TRUNC,0644);
        if(ipr==0)
        till=op_p;
        }
        if(app){
        fd[1]=open(ap_f,O_WRONLY | O_CREAT | O_APPEND,0644);
        if(ipr==0)
        till=ap_p;
        }
        dup2(fd[1],1);


    }
    for (int i = 0; i < till; i++)
    {
            dup_a[temp_i++] = list_of_args[i];
    }
    dup_a[temp_i] = NULL;

    int pid = fork();
    if (pid == 0)
    {
        // close(fd[1]);
        
        if (fd[0] < 0)
        {
            printf("dup failed");
            exit(0);
        }
        if(dup_a[0]=="pinfo"){
            pinfo(dup_a, temp_i);

        }
        else if (execvp(dup_a[0], dup_a) < 0)
        {
            printf("execvp failed");
        }
        
        exit(0);
    }
    else
    {
        waitpid(pid,&stat,WUNTRACED);
        // close(fd[1]);
        // close(fd[0]);
        dup2(in_o, 0);
        dup2(op_o,1);
        
        
        return;
    }

    return;
}