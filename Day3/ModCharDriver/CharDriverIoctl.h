#ifndef CHARDRIVERIOCTL_H_
#define CHARDRIVERIOCTL_H_

#include <linux/ioctl.h>

#define MAGIC_NUM 0xF1
#define IOCTL_SET_BUF_SIZE _IOW(MAGIC_NUM, 0, int)
#define IOCTL_SET_MSG _IOW(MAGIC_NUM, 1, char *)
#define IOCTL_GET_MSG _IOR(MAGIC_NUM, 2, char *)

#endif
