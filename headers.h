#include <stdio.h>    
#include<unistd.h>
#include <sys/utsname.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<pwd.h>
#include<sys/stat.h>
#include<grp.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<fcntl.h>

typedef struct jobs
{
    char name[20];
    int process_id;
    int job_id;
    int st;
}jobs;
jobs fore_grd;
jobs list_of_jobs[10000];
int s_pid;


void change_direc(char** list_of_args,int count);
void _ls(char** list_of_args,int count);
void echo(char** list_of_args,int count);
void _pwd(char** list_of_args,int count);
void repeat(char** list_of_args,int count);
void fore(char** list_of_args,int count);
void background(char** list_of_args,int count);
void pinfo(char**,int);
void io_redirect(char**,int);
void find_command(char command[]);
void jobs_command(char**,int);
void sig(char**,int);
void pipefunc(char*,char**,int);
int is_ioredirect(char** list,int count);
void fg(char**,int);
void bg(char**,int);
void replay_func(char*,char**,int);
void find_command(char*);
void z_func();
int is_ioredirect(char** list,int count);
int is_pipe(char**,int);


char temp_home[100];
char prev_wd[100];
int job_count;
