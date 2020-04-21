#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Arguments {
    unsigned int nsecs;
    unsigned int nplaces;
    unsigned int nthreads;
    char fifoname[256];
}Args;

void init_args(Args *args){
    args->nsecs=-1;
    args->nplaces=-1;
    args->nthreads=-1;
    args->fifoname[0]=0;
}

int get_args(Args *args, int argc, char *argv[]){
    if(argc>8){
        printf("Usage: %s <-t nsecs> fifoname", argv[0]);
        return -1;
    }

    for (int i=0; i<argc; i++){
        if (!strcmp(argv[i], "-t")){
            if (args->nsecs!=-1) return -1;
            if (atoi(argv[i+1])){
                args->nsecs = atoi(argv[i+1]);
                i++;
            }
            else{
                return -1; //The next argument is not a number
            } 
        }
        else if (!strcmp(argv[i], "-l")){
            if (args->nplaces!=-1) return -1;
            if (atoi(argv[i+1])){
                args->nplaces = atoi(argv[i+1]);
                i++;
            }
            else{
                return -1; //The next argument is not a number
            } 
        }
        else if (!strcmp(argv[i], "-n")){
            if (args->nthreads!=-1) return -1;
            if (atoi(argv[i+1])){
                args->nthreads = atoi(argv[i+1]);
                i++;
            }
            else{
                return -1; //The next argument is not a number
            } 
        }
        else if (argv[i][1] != '-'){
            strncpy(args->fifoname, argv[i], sizeof(args->fifoname));
        }
    }
    return 0;
}

void print_args(Args args){
    printf("nsecs: %d\n", args.nsecs);
    printf("nplaces: %d\n", args.nplaces);
    printf("nthreads: %d\n", args.nthreads);
    printf("fifoname: %s\n", args.fifoname);
}

int main(int argc, char *argv[], char *envp[]){
    Args args;
    init_args(&args);
    if(get_args(&args, argc, argv)==-1){
        perror("Error getting args!");
        exit(1);
    }
    print_args(args);
    return 0;
}