#include"headers.h"
int is_ioredirect(char** list,int count){
    for(int i=0;i<count;i++){
        if(strcmp(list[i],">>")==0||strcmp(list[i],"<")==0||strcmp(list[i],">")==0){
            return 1;
        }
    }
    return 0;
}
void pipefunc(char* command,char** list_of_args,int count){

    char* c[100];
    int k=0; //number of commands after separated by |
    char* token=strtok(command,"|");
    while(token!=NULL){
        c[k++]=token;
        token=strtok(NULL,"|");
    }
    int p[2];
    int in_o=dup(0);
    int out_o=dup(1);
    for(int i=0;i<k;i++){

        int k1=0;
        char* c1[100];
        token=strtok(c[i]," \t\n");
        while(token!=NULL){
            c1[k1++]=token;
            token=strtok(NULL," \t\n");
        }

        if(i==0){
            pipe(p);
            if(dup2(p[1],1)<0){
                printf("error in dup2\n");
                return;
            }
            close(p[1]);

        }
        else if(i==k-1){
            dup2(p[0],0);
            dup2(out_o,1);

        }
        else{
            dup2(p[0],0);
            pipe(p);
            if(dup2(p[1],1)<0){
                printf("error in dup2\n");
                return;
            }
            close(p[1]);

        }
        int f_r=fork();
        int stat;
        if(f_r<0){
            printf("failed to fork\n");
        }
        else if(f_r==0){
            // io_redirect(c,k1);
            if(is_ioredirect(c1,k1)==1){
                io_redirect(c1,k1);
            }
            else if(strcmp(c1[0],"pinfo")==0){
                pinfo(c1,k1);
            }
            else if(strcmp(c1[0],"jobs")==0){
                jobs_command(c1,k1);
            }
            else{
            execvp(c1[0],c1);
            }
            exit(0);
        }
        else{
            waitpid(f_r,&stat,WUNTRACED);
            dup2(in_o,0);
            dup2(out_o,1);
        }

    }

    return;
}