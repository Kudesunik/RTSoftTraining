#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {

    int fileDescriptor, counter = 1;
    
    char buffer[100];
    
    fileDescriptor = open("/dev/TestDevice", O_RDONLY);
    
    printf("%d\n", fileDescriptor);
    
    while (counter > 0) {
        counter = read(fileDescriptor, buffer, 10);
        if (counter < 0) {
            break;
        }
        buffer[counter] = 0;
        printf("Read %2d chars: %s\n", counter, buffer);
    }
    
    return EXIT_SUCCESS;
}
