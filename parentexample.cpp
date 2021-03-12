#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 4096

int main(){
    int n, fd1[2],fd2[2];
    pid_t pid;
    char line[MAXLINE];
    printf("start\n");
    if(pipe(fd1)<0 || pipe(fd2)<0){
        fprintf(stderr,"pipe failed");
	return 1;
    }
    pid = fork();
    printf("pid:%d\n",pid);
    if(pid<0){
        fprintf(stderr,"fork failed");
        return 2;
    }
    else if(pid>0){ //parent
	printf("parent\n");
        close(fd1[0]);
        write(fd1[1],"hello world",11); //system
	close(fd1[1]);

	wait(NULL);

	close(fd2[1]);
	read(fd2[0],line,MAXLINE);
	printf("from pipe:%s\n",line);
	close(fd2[0]);
    }
    else{
        close(fd1[1]);
	read(fd1[0],line,MAXLINE);
        
	printf("Child:%s\n",line);
	close(fd1[0]);
	close(fd2[0]);

	write(fd2[1],"world hello",11);
	close(fd2[1]);
    }
    return 0;
}
