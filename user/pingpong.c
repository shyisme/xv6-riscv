#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int fds[2];

    if (argc != 1)
    {
        fprintf(2, "usage: pingpong \n");
        exit(1);
    }


    if(pipe(fds) < 0){
      printf("pipe() failed\n");
      exit(1);
    }
    int Ret = fork();

    if(Ret==0)
    {
        int childpid=getpid();
        fprintf(fds[1], "%d",childpid);
        printf("%d:  received ping\n", getpid());
        close(fds[1]);
 
        exit(0);
    }
    if(Ret>0)
    {
        wait(0);
        char buf='a';
        read(fds[0], &buf, sizeof(buf));
        printf("%d: father received pong\n", getpid());
        close(fds[0]);
        exit(0);
    }
    exit(1);
}