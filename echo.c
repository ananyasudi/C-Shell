#include"headers.h"
//this is not so perfect.. getting space before shell name
void echo(char** list_of_args,int count){
    // printf("echofun");
    if(list_of_args[count-1][strlen(list_of_args[count-1])]=='\n')
    list_of_args[count-1][strlen(list_of_args[count-1])]='\0';
    for(int i=1;i<count;i++){
        printf("%s ",list_of_args[i]);
    }
    printf("\n");
}