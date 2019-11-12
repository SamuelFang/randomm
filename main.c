#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int random_number(){
    int file = open("/dev/random", O_RDONLY);
    int num;
    read(file, &num, sizeof(int));
    if (file == -1){
        printf("errno: %s\n", strerror(errno));
    }
    close(file);
    return num;
}

int main(){
    int nums[10];
    int i;
    for (i = 0; i < 10; i++){
        nums[i] = random_number();
    }
    printf("Generating random numbers:\n");
    for (i = 0; i < 10; i++){
        printf("        random %d: %d\n", i, nums[i]);
    }
    printf("\n");
    
    printf("Writing numbers to file...\n");
    printf("\n");
    int file = open("nums.txt", O_WRONLY | O_CREAT);
    if (file == -1){
        printf("errno: %s\n", strerror(errno));
    }
    int written = write(file, nums, sizeof(nums));
    if (written == -1){
        printf("errno: %s\n", strerror(errno));
    }
    close(file);
    
    printf("Reading numbers from file...\n");
    printf("\n");
    int checknums[10];
    file = open("nums.txt", O_RDONLY);
    if (file == -1){
        printf("error: %s\n", strerror(errno));
    }
    int reading = read(file, checknums, written);
    if (reading == -1){
        printf("error: %s\n", strerror(errno));
    }

    printf("Verification that written values were the same:\n");
    for (i = 0; i < 10; i++){
        printf("        random %d: %d\n", i, checknums[i]);
    }
    close(file);
    return 1;
}