#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    int userArgument =1;
    if(argc <= 1){
        printf("you do not give any argument!\n");
        exit(1);
    }
    if(argc != 2 || atoi(argv[userArgument]) == 0){
        printf("invalid argument!\n");
        exit(1);
    }
    sleep(atoi(argv[userArgument]));
    exit(0);
}
