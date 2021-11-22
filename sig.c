#include"headers.h"
void killjob(int jobid){
    int a;

    for(int i=1;i<=job_count;i++){
        if(list_of_jobs[i].job_id==jobid){
            a=i;
            break;
        }
    }
    for (int i = a+1; i <= job_count; i++)
    {
        list_of_jobs[i-1]=list_of_jobs[i];
    }
    job_count--;
    

}
void sig(char** list_of_args,int count){
    if(count<3){
        printf("less arguments given\n");
    }
    else{
        for(int i=1;i<=job_count;i++){
            if(list_of_jobs[i].job_id==atoi(list_of_args[1])){
                pid_t pid=list_of_jobs[i].process_id;
                list_of_jobs[i].st=0; //0 means no longer existing
                // if(atoi(list_of_args[2])==9){
                //     killjob(atoi(list_of_args[1]));
                // }
                kill(pid,atoi(list_of_args[2]));
                return;
            }
        }
        printf("no such job exists\n");
    }
    return;

}
