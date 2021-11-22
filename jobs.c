#include "headers.h"
void jobs_command(char **list_of_args, int count)
{
    char st[100] = "";
    char file[200];
    int flagr=0;
    int flags=0;
    char w1[10],w2[10];
    char s[10];
    if(count>1){
        for(int i=0;i<count;i++){
        if(strcmp(list_of_args[i],"-r")==0)
            flagr++;
        else if(strcmp(list_of_args[i],"-s")==0)
            flags++;
        }
    }

    //sorting in alphabetical order
    jobs temp_jobs[job_count+1];

    for(int i=0;i<=job_count;i++){
        temp_jobs[i]=list_of_jobs[i];
    }
    
    jobs temp;
    for(int i=1;i<=job_count;i++){
      for(int j=i+1;j<=job_count;j++){
         if(strcmp(temp_jobs[i].name,temp_jobs[j].name)>0){
            temp=temp_jobs[i];
            temp_jobs[i]=temp_jobs[j];
            temp_jobs[j]=temp;
         }
      }
    }


    for (int i = 1; i <= job_count; i++)
    {
        if(temp_jobs[i].st==1){
        sprintf(file, "/proc/%d/stat", temp_jobs[i].process_id);
        FILE *fd;
        fd = fopen(file, "r");
        if(fd<0){
            printf("file /proc/pid/stat doest exist");
            return;
        }

        fscanf(fd,"%s %s %s",w1,w2,w2);

        if (strcmp(w2,"T")==0)
            strcpy(s, "Stopped");
        else
            strcpy(s, "Running");
        if((flagr!=0 && strcmp(s,"Running")==0)||(flags!=0&&strcmp(s,"Stopped")==0)||(flagr==0&&flags==0)||(flagr!=0&&flags!=0))
        printf("[%d] %s %s [%d]\n", temp_jobs[i].job_id, s, temp_jobs[i].name, temp_jobs[i].process_id);
        }
    }
    return;
}