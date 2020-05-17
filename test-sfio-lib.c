#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFSIZE 100
int swrite(int fd, char* buf, int len);
int sread(int fd, char* buf, int len);
void to_binary(char* buf)
{
    unsigned char p;
    int i, j;

    for (j = 0; j < strlen(buf); j++) {
        p = 0x80;
        for (i = 0; i < 8; i++) {
            if (buf[j] & p) {
                printf("1");
            } else {
                printf("0");
            }
            p = p >> 1;
        }
        printf(" ");
    }   
    printf("\n");
}

int main(){
    char* temp1;
    char* temp2;
    char* temp3;
    char* temp4;
    int fd; 

    temp1 = (char*)calloc(100, sizeof(char));
    temp2 = (char*)calloc(100, sizeof(char));
    temp3 = (char*)calloc(100, sizeof(char));
    temp4 = (char*)calloc(100, sizeof(char));
    
    // swrite() test
    printf("Input data : ");
    scanf("%s", temp1);
    printf("Input binary data : ");
    to_binary(temp1);

    if (0 < (fd = open("./test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644))) {
        swrite(fd, temp1, strlen(temp1));
        close(fd);
    } else {
        printf("Open Error\n");
        exit(-1);
    }   

    if (0 < (fd = open("./test.txt", O_RDONLY, 0644))) {
        read(fd, temp2, BUFSIZE);
        close(fd);
    } else {
        printf("Open Error.\n");
        exit(-1);
    }
    printf("sys_read() data : %s\n", temp2);
    printf("sys_read() binary data : ");
    to_binary(temp2);

    // sread() test
    if (0 < (fd = open("./test.txt", O_RDONLY, 0644))) {
        read(fd, temp3, BUFSIZE);
        close(fd);
    } else {
        printf("Open Error.\n");
        exit(-1);
    }   

    printf("sys_read() data : %s\n", temp3);
    printf("sys_read() binary data : ");
    to_binary(temp3);

    if (0 < (fd = open("./test.txt", O_RDONLY, 0644))) {
        sread(fd, temp4, BUFSIZE);
        close(fd);
    } else {
        printf("Open Error.\n");
        exit(-1);
    }   
    printf("sys_read() data : %s\n", temp4);
    printf("sys_read() binary data : ");
    to_binary(temp4);


	return 1;
}
