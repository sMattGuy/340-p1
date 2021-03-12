#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv){
    printf("Number of args:%i\n",argc);
    printf("arguments:\n");
    for(int i=0;i<argc;++i)
	    printf("%s\n",argv[i]);
    return 0;
}
