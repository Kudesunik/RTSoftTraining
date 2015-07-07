#include "CharDriverIoctl.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void ioctl_get_msg(int msg) {
    int fileDescriptor = open("/dev/TestDevice", 0);
    int result = ioctl(fileDescriptor, IOCTL_GET_MSG, msg);
    printf("Result code = %d\n", result);
}

int main(int argc, char** argv) {
    
    ioctl_get_msg(10);

    return EXIT_SUCCESS;
}

