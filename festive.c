#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    if (argc < 2) { // just warns you if you have too few args
        printf("Proper usage is ./festive <integer input>");
        return 100;
    } else if (argc > 2) { // too many args warning
        printf("Proper usage is ./festive <integer input>");
        return 200;
    }
    int num_attempts = atoi(argv[1]); // change the local var name if you see fit
    
    /* TODO: Add your code here! */


    
}