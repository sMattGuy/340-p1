/**
 * Author: Matthew Flammia
 * CUNYID: 23661371
 * CSCI 340 Operating Systems
 * Professor Svadlenka
 * to compile use command: gcc -o time time.cpp
 * Test case results and code discussion located in submitted PDF
**/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>

#define MAXLINE 4096

int main(int argc, char** argv){
    //setting up variables for PID and pipe
    int n, fd1[2],fd2[2];
    pid_t pid;
    char line[MAXLINE];
    
    //setting up variables for time stamping
    struct timeval start,end;
    
    //checking pipe
    if(pipe(fd1)<0||pipe(fd2)<0){
        fprintf(stderr,"pipe failed\n");
	return 1;
    }

    //creating child process
    pid = fork();
    //checking fork for error
    if(pid<0){
	fprintf(stderr,"fork failed\n");
	return 2;
    }
    //parent case
    else if(pid>0){
	//waits for child to finish
	wait(NULL);
	//read from child
	gettimeofday(&end, NULL);
	printf("Parent end time:%d usec\n",end.tv_usec);
	
	//reads start time from pipe
	close(fd2[1]);
	read(fd2[0],&start,MAXLINE);
	printf("Parent start time from pipe:%d usec\n",start.tv_usec);

	//calculates elapsed time based on start time and end time
	double time_taken;
	//converts to milliseconds
	time_taken = (end.tv_sec - start.tv_sec)*1e6;
	//converts to microseconds, and will be final output
	time_taken = (time_taken + (end.tv_usec - start.tv_usec))*1e-6;

	printf("Elapsed time:%f seconds\n",time_taken);
    }
    //child case
    else{
	//creates second child within first to run execlp (explained in pdf)
	pid_t pid2;
	pid2 = fork();
	if(pid2<0){
	    //fork failure error check
	    fprintf(stderr,"fork failed\n");
	    return 2;
	}
	else if(pid2>0){
   	    //parent function, gets time of day
	    gettimeofday(&start,NULL);
	    printf("Child start time:%d usec\n",start.tv_usec);
	    printf("Command Name:%s\n",argv[1]);

	    //waits for child to complete
	    wait(NULL);
	    
	    //writes start time to pipe after child finishes
	    write(fd2[1],&start,sizeof(start));
	    close(fd2[1]);
	}
	else{
	    //runs command and then terminates child
	    execlp(argv[1],argv[1],NULL);
	}
    }
    return 0;
}
