#include"headers.h"

void _pwd(char** list_of_args,int count){
    if(count>1){
        perror("many args given");
        return;
    }
    char pwd_[1000];
    getcwd(pwd_,sizeof(pwd_));
    printf("%s\n",pwd_);
    return;

}