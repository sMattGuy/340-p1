#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#define MAXLINE 4096


void func(){
    for(int i=0;i<1000000;i++){}
}

int main(int argc, char** argv){
    struct timeval start,end;
    gettimeofday(&start,NULL);
    func();
    gettimeofday(&end,NULL);

    double time_taken;

    time_taken = (end.tv_sec - start.tv_sec)*1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec))*1e-6;

    printf("time taken:%f secs\n",time_taken);
    return 0;
}
