#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){

  int pipe1[2];
  int pipe2[2];
  pipe(pipe1);
  pipe(pipe2);

  int pid = fork();
  if(pid > 0){
    close(pipe1[0]);
    close(pipe2[1]);
    if(write(pipe1[1], "ping", 4) == -1){
      printf("write error");
    }
    close(pipe1[1]);
    char buffer[10];
    if(read(pipe2[0], buffer, 5) == -1){
      printf("read error");
    }
    close(pipe2[0]);
    printf("pid %d: received %s \n", getpid(),buffer);
  }
  else{
    close(pipe1[1]);
    close(pipe2[0]);
    char buffer[10];
    if(read(pipe1[0], buffer, 5) == -1){
       printf("read error");
    }
    printf("pid %d: received %s \n", getpid(),buffer);
    if(write(pipe2[1], "pong", 4) == -1){
    }
    close(pipe2[1]);
  }
  exit(0);
}

