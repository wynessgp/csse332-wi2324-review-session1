#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No argument provided to christmassy, did you do it right?\n");
        return 100;
    } else if (argc > 2) {
        printf("too many args provided to christmassy!\n");
        return 200;
    }
    // just right
    printf("Process %s says merry chrysler!\n", argv[1]);
    return 0;
}