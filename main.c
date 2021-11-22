#include "prompt.h"
#include "headers.h"

char *buffer_in;
void delete_p(long p)
{
    int a;
    for (int i = 1; i <= job_count; i++)
    {
        if (list_of_jobs[i].process_id == p)
        {
            a = i;
            break;
        }
    }
    for (int i = a + 1; i <= job_count; i++)
    {
        list_of_jobs[i - 1] = list_of_jobs[i];
    }
    job_count--;
}

void z_func()
{
    int pid = getpid();
    if (fore_grd.process_id != -1)
    {
        kill(fore_grd.process_id, SIGTSTP);
        job_count++;
        // printf("job count --%d\n", job_count);

        list_of_jobs[job_count].job_id = job_count;
        strcpy(list_of_jobs[job_count].name, fore_grd.name);
        list_of_jobs[job_count].process_id = fore_grd.process_id;
        list_of_jobs[job_count].st = 1;
        fore_grd.process_id = -1;
    }
    else
    {
        // printf("no process found in fg\n");
        prompt();
        fflush(stdout);
    }

    return;
}
void c_func()
{
    if (fore_grd.process_id != -1)
    {
        kill(fore_grd.process_id, SIGINT);
    }
    return;
}
void finished_process()
{
    int status_;
    long t_p = waitpid(-1, &status_, WNOHANG);

    for (int i = 1; i <= job_count; i++)
    {
        int w = 0;
        int e = WEXITSTATUS(status_);
        if (list_of_jobs[i].process_id == t_p)
        {
            list_of_jobs[i].st = 0;
            w = 1;
            if (status_ == 0)
                printf("%s with pid %d exited normally\n", list_of_jobs[i].name, list_of_jobs[i].process_id);
            else
                printf("%s with pid %d failed to exit normally\n", list_of_jobs[i].name, list_of_jobs[i].process_id);
            // delete_p(t_p);
        }
    }

    // if (WIFEXITED(status_))
    // {
    //     for (int i = 1; i <= job_count; i++)
    //     {
    //         if (list_of_jobs[i].process_id == t_p)
    //         {
    //             printf("%s with pid %d exited normally\n", list_of_jobs[i].name, list_of_jobs[i].process_id);
    //             //exit status given by wexitstatus(status)
    //             delete_p(t_p);
    //         }
    //     }
    // }
    // else if (!WIFEXITED(status_))
    // {

    //     for (int i = 1; i <= job_count; i++)
    //     {
    //         if (list_of_jobs[i].process_id == t_p)
    //         {
    //             printf("%s with pid %d failed to exit normally\n", list_of_jobs[i].name, list_of_jobs[i].process_id);
    //             //exit status given by wexitstatus(status)
    //             delete_p(t_p);
    //         }
    //     }
    // }

    return;
}
void find_command(char command[])
{
    int flag_r = 0;
    int flagb = 0;
    int flagp = 0;
    char command_dup[100];
    strcpy(command_dup, command);

    char **in_str = (char **)malloc(sizeof(char *) * 100);

    for (int i = 0; i < 10; i++)
    {
        in_str[i] = (char *)malloc(sizeof(char) * 100);
    }

    int c = 0;
    char *token = strtok(command, " \n");

    while (token != NULL)
    {
        in_str[c++] = token;
        token = strtok(NULL, " \n");
    }
    for (int i = 0; i < c; i++)
    {
        if (strcmp(in_str[i], ">") == 0 || strcmp(in_str[i], "<") == 0 || strcmp(in_str[i], ">>") == 0)
        {
            flag_r = 1;
        }
        if (strcmp(in_str[i], "|") == 0)
        {
            flagp = 1;
        }
    }
    if (strcmp(in_str[0], "replay") == 0)
    {
        replay_func(command_dup,in_str, c);
        return;
    }
    if (flagp == 1)
    {
        pipefunc(command_dup, in_str, c);
        return;
    }

    if (flag_r != 0 && flagp == 0)
    {
        // printf("io_red out");
        io_redirect(in_str, c);
        return;
    }

    if (strcmp(in_str[0], "cd") == 0)
    {
        change_direc(in_str, c);
    }
    else if (strcmp(in_str[0], "fg") == 0)
    {
        fg(in_str, c);
    }
    
    else if (strcmp(in_str[0], "bg") == 0)
    {
        bg(in_str, c);
    }
    else if (strcmp(in_str[0], "sig") == 0)
    {
        sig(in_str, c);
    }
    else if (strcmp(in_str[0], "jobs") == 0)
    {
        jobs_command(in_str, c);
    }
    else if (strcmp(in_str[0], "ls") == 0)
    {
        _ls(in_str, c);
    }
    else if (strcmp(in_str[0], "echo") == 0)
    {
        echo(in_str, c);
    }
    else if (strcmp(in_str[0], "pwd") == 0)
    {
        _pwd(in_str, c);
    }
    else if (strcmp(in_str[0], "repeat") == 0)
    {
        repeat(in_str, c);
    }
    else if (strcmp(in_str[0], "pinfo") == 0)
    {
        pinfo(in_str, c);
    }
    else
    {
        if (c > 1)
        {
            for (int i = 0; i < c; i++)
            {
                if (strcmp(in_str[i], "&") == 0)
                {
                    flagb = 1;
                }
            }
            if (flagb == 1)
            {
                background(in_str, c);
            }
            else if (flag_r == 0)
            {

                fore(in_str, c);
            }
        }
        else if (flag_r == 0)
        {
            // printf("came to fore");
            fore(in_str, c);
        }
    }

    return;
}
int main()
{
    int s_pid = getpid();
    job_count = 0;
    signal(SIGCHLD, finished_process);
    signal(SIGTSTP, z_func);
    signal(SIGINT, c_func);

    int size = 1000;
    buffer_in = (char *)malloc(size);
    getcwd(temp_home, sizeof(temp_home));
    strcpy(prev_wd, temp_home);
    long unsigned int len = 1000;

    char *commands[1000];

    while (1)
    {
        fore_grd.process_id = -1;

        prompt();
        int waste = getline(&buffer_in, &len, stdin); //takes input here
        if (waste <= 0)
        { //for handling ctrl+D
            exit(0);
        }
        char *temp_buf = buffer_in;

        int com_count = 0;

        commands[com_count] = strtok(temp_buf, ";\n");

        while (commands[com_count] != NULL)
        {
            com_count++;
            commands[com_count] = strtok(NULL, ";\n");
        }

        for (int j = 0; j < com_count; j++)
        {
            find_command(commands[j]);
        }
    }
    return 0;
}
