#include "headers.h"

char opt = 0;

void printing_func(struct stat sfile, char *filename)
{
    char date[100];
    struct passwd *p;
    struct group *g;
    p = getpwuid(sfile.st_uid);
    strftime(date, sizeof(date), "%b %2d %H:%M ", localtime(&(sfile.st_ctime)));
    long long int size = sfile.st_size;
    if (S_ISDIR(sfile.st_mode))
        printf("d");
    else
        printf("-");

    if ((sfile.st_mode & S_IRUSR) ? printf("r") : printf("-"))
        ;
    if ((sfile.st_mode & S_IWUSR) ? printf("w") : printf("-"))
        ;
    if ((sfile.st_mode & S_IXUSR) ? printf("x") : printf("-"))
        ;
    if ((sfile.st_mode & S_IRGRP) ? printf("r") : printf("-"))
        ;
    if ((sfile.st_mode & S_IWGRP) ? printf("w") : printf("-"))
        ;
    if ((sfile.st_mode & S_IXGRP) ? printf("x") : printf("-"))
        ;
    if ((sfile.st_mode & S_IROTH) ? printf("r") : printf("-"))
        ;
    if ((sfile.st_mode & S_IWOTH) ? printf("w") : printf("-"))
        ;
    if ((sfile.st_mode & S_IXOTH) ? printf("x") : printf("-"))
        ;

    printf(" ");
    printf("%5ld", sfile.st_nlink);
    printf("%12s ", p->pw_name);
    printf("%12s ", getgrgid(sfile.st_gid)->gr_name);
    printf("%7ld", sfile.st_size);
    printf("%20s %20s\n", date, filename);
    return;
}
void print_totblocks(char *dir_name)
{
    // printf("coming to printblocks");
    long int total = 0;
    struct dirent **list_of_files;
    long int n;
    // printf("%s\n",dir_name);
    n = scandir(dir_name, &list_of_files, 0, alphasort);
    int i = 0;
    while (i < n)
    {
        char path[1000] = "";
        char filename[100];
        strcpy(filename, list_of_files[i]->d_name);
        struct stat sfile;
        strcpy(path, dir_name);
        strcat(path,"/");
        strcat(path, list_of_files[i++]->d_name);

        if (stat(path, &sfile) == 0)
        {
        // printf("%ld\n",total);

            total += sfile.st_blocks;
        }
    }
    printf("total %ld\n", total/2);
    return;
}
void ls_al(char *dir_name, int flag_dir)
{
    // printf("coming to lsal");

    int tot = 0;
    char d_n[1000];
    char temp[1000];
    DIR *dip;
    long long int n;
    struct dirent **list_of_files;
    if (flag_dir == 0)
    {
        // printf("scans pres dir\n");
        n = scandir(".", &list_of_files, 0, alphasort);
        strcpy(d_n, "");
        getcwd(d_n, sizeof(d_n));
        print_totblocks(d_n);
        // printf("%s\n", d_n);
    }
    else
    {
        n = scandir(dir_name, &list_of_files, 0, alphasort);
        strcpy(d_n, dir_name);
        print_totblocks(d_n);

    }
    if (n < 0)
    {
        printf("no such direc exists\n");
    }
    else
    {
        if (d_n[strlen(d_n) - 1] != '/')
        {
            strcat(d_n, "/");
        }
        int i = 0;
        while (i < n)
        {
            char path[1000] = "";
            char filename[100];
            strcpy(filename, list_of_files[i]->d_name);
            struct stat sfile;
            strcpy(path, d_n);
            strcat(path, list_of_files[i++]->d_name);

            if (stat(path, &sfile) == 0)
            {
                printing_func(sfile, filename);
            }
            else
            {
                printf("file doesnt exist\n");
                return;
            }
            // printf("\n");
        }
    }
    return;
}
void ls_l(char *dir_name, int flag_dir)
{
    char d_n[1000];
    char temp[1000];
    DIR *dip;
    long long int n;
    struct dirent **list_of_files;
    if (flag_dir == 0)
    {
        n = scandir(".", &list_of_files, 0, alphasort);
        strcpy(d_n, "");
        getcwd(d_n, sizeof(d_n));
    }
    else
    {
        n = scandir(dir_name, &list_of_files, 0, alphasort);
        strcpy(d_n, dir_name);
    }
    if (n < 0)
    {
        printf("no such direc exists\n");
    }
    else
    {
        if (d_n[strlen(d_n) - 1] != '/')
        {
            strcat(d_n, "/");
        }
        int i = 0;
        while (i < n)
        {
            if (strcmp(list_of_files[i]->d_name, ".") == 0 || strcmp(list_of_files[i]->d_name, "..") == 0)
            {
                i++;
                continue;
            }
            else
            {
                char path[1000] = "";
                char filename[100];
                strcpy(filename, list_of_files[i]->d_name);
                struct stat sfile;
                strcpy(path, d_n);
                strcat(path, list_of_files[i++]->d_name);

                if (stat(path, &sfile) == 0)
                {
                    printing_func(sfile, filename);
                }
                else
                {
                    printf("file doesnt exist\n");
                    return;
                }
                // printf("\n");
            }
        }
    }

    return;
}
void ls_a(char *dir_name, int flag_dir)
{
    DIR *dip;
    long long int n;
    struct dirent **list_of_files;

    if (flag_dir == 0)
    {
        n = scandir(".", &list_of_files, 0, alphasort);
    }
    else
    {
        n = scandir(dir_name, &list_of_files, 0, alphasort);
    }
    if (n < 0)
        perror("dirscan");
    else
    {
        int i = 0;
        while (i < n)
        {
            // if (strcmp(list_of_files[i]->d_name, ".") == 0 || (strcmp(list_of_files[i]->d_name, "..") == 0))
            // {
            //     i++;
            //     continue;
            // }
            // else
            // {
            printf("%s\n", list_of_files[i]->d_name);
            i++;
            // }
        }
    }
}
void func_decide(char *dir_name, int flagl, int flaga, int flag_dir)
{
    if (flagl > 0 && flaga > 0)
    {
        ls_al(dir_name, flag_dir);
        // ls_al();
        // printf("implements al func")
    }
    else if (flaga > 0 && flagl == 0)
    {
        ls_a(dir_name, flag_dir);
        // printf("implemts a only");
    }
    else if (flaga == 0 && flagl > 0)
    {
        ls_l(dir_name, flag_dir);
        // printf("only l");
    }
    return;
}
void ls_woa(char *dir_name, int flag_dir)
{
    DIR *dip;
    long long int n;
    struct dirent **list_of_files;
    if (flag_dir == 0)
    {
        n = scandir(".", &list_of_files, 0, alphasort);
    }
    else
    {
        n = scandir(dir_name, &list_of_files, 0, alphasort);
    }
    if (n < 0)
        perror("dirscan");
    else
    {
        int i = 0;
        while (i < n)
        {
            if ((list_of_files[i]->d_name)[0]=='.')
            {
                i++;
                continue;
            }
            else
            {
                printf("%s\n", list_of_files[i]->d_name);
                i++;
            }
        }
    }
}

void _ls(char **list_of_args, int count)
{
    int dir_count = 0;
    int flagl = 0, flaga = 0, flagtil = 0;
    int flag_dir = 0; //assumng no dir name given
    // char *dir_name = (char *)malloc(sizeof(char) * 100);
    char *dir_name[100];
    for (int i = 0; i < 100; i++)
    {
        dir_name[i] = (char *)malloc(100 * sizeof(char));
    }

    if (list_of_args[count - 1][strlen(list_of_args[count - 1]) - 1] == '\n')
    {
        list_of_args[count - 1][strlen(list_of_args[count - 1]) - 1] = '\0';
    }

    for (int i = 1; i < count; i++)
    {
        // printf("%s",list_of_args[i]);
        if (list_of_args[i][0] != '-' && list_of_args[i][0] != '\0')
        {
            // printf("coming to dire");
            if(list_of_args[i][0]=='~'&&strlen(list_of_args[i])>0){
                list_of_args[i][0]='.';
                dir_name[dir_count++]=list_of_args[i];
                flag_dir=1;
            }
            else{
            dir_name[dir_count++] = list_of_args[i];
            flag_dir = 1;
            }
        }
        else if (strcmp(list_of_args[i], "-l") == 0){
            flagl++;
            // printf("llllllllll");

        }
        else if (strcmp(list_of_args[i], "-a") == 0){
            flaga++;
        //    printf("aaaaaaaaa");

        }
        else if (strcmp(list_of_args[i], "-al") == 0 || strcmp(list_of_args[i], "-la") == 0)
        {
            flaga++;
            flagl++;
            // printf("%d %d\n",flagl,flaga);

        }
    }
    if (dir_count == 0)
    {
        dir_count = 1;
    }
    for (int i = 0; i < dir_count; i++)
    {
        if (flagl > 0 && flaga > 0)
        {
            // printf("gong to al");
            ls_al(dir_name[i], flag_dir);
        }
        else if (flaga > 0 && flagl == 0)
        {
            ls_a(dir_name[i], flag_dir);
        }
        else if (flaga == 0 && flagl > 0)
        {
            ls_l(dir_name[i], flag_dir);
        }
        else
        {
            ls_woa(dir_name[i], flag_dir);
        }
    }
    // printf("%d %d %d",flagl,flaga,flag_dir);
    return;
}
