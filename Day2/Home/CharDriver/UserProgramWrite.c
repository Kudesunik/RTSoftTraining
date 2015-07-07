#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {

    int fileDescriptor, counter = 0;
    
    char buffer[] = "Test message";
    
    fileDescriptor = open("/dev/TestDevice", O_WRONLY);
    
    printf("%d\n", fileDescriptor);
    
    counter = write(fileDescriptor, buffer, strlen(buffer));
    
    printf("%d\n", counter);
    
    return EXIT_SUCCESS;
}
