#ifndef CHARDRIVERIOCTL_H_
#define CHARDRIVERIOCTL_H_

#include <linux/ioctl.h>

#define MAGIC_NUM 0xF1
#define IOCTL_GET_MSG _IOR(MAGIC_NUM, 0, int)

#endif
