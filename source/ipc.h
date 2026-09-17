#ifndef _IPC_H_
#define _IPC_H_

#include <stddef.h>

typedef enum {
    IPC_OK = 0,
    IPC_EBUSY = -2,
    IPC_EINVAL = -4,
    IPC_ENOENT = -6,
    IPC_EQUEUEFULL = -8,
    IPC_ENOMEM = -22,
} ios_ret_t;

typedef enum {
    IPC_OPEN_NONE = 0,
    IPC_OPEN_READ = 1,
    IPC_OPEN_WRITE = 2,
    IPC_OPEN_RW = IPC_OPEN_READ + IPC_OPEN_WRITE
} ios_mode_t;

typedef void *usr_t;
typedef int ios_fd_t;
typedef void (*ios_open_cb_t)(ios_fd_t result, usr_t usrdata);
typedef void (*ios_cb_t)(ios_ret_t result, usr_t usrdata);

typedef struct _ioctlv {
	void *data;
	unsigned int len;
} ioctlv;

ios_fd_t IOS_Open(const char *filepath, ios_mode_t mode);
ios_ret_t IOS_OpenAsync(
    const char *filepath, ios_mode_t mode, ios_open_cb_t cb, usr_t usrdata);
    
ios_ret_t IOS_Close(ios_fd_t fd);
ios_ret_t IOS_CloseAsync(ios_fd_t fd, ios_cb_t cb, usr_t usrdata);

ios_ret_t IOS_Read(ios_fd_t fd, void *buffer, size_t length);
ios_ret_t IOS_ReadAsync(
    ios_fd_t fd, void *buffer, size_t length, ios_cb_t cb, usr_t usrdata);
ios_ret_t IOS_Write(ios_fd_t fd, const void *buffer, size_t length);
ios_ret_t IOS_WriteAsync(
    ios_fd_t fd, const void *buffer, size_t length, ios_cb_t cb, usr_t usrdata);
ios_ret_t IOS_Seek(ios_fd_t fd, int offset, int base);
ios_ret_t IOS_SeekAsync(
    ios_fd_t fd, int offset, int base, ios_cb_t cb, usr_t usrdata);

ios_ret_t IOS_Ioctl(
    ios_fd_t fd, int ioctl, const void *input, size_t input_length,
    void *output, size_t output_length);
ios_ret_t IOS_IoctlAsync(
    ios_fd_t fd, int ioctl, const void *input, size_t input_length,
    void *output, size_t output_length, ios_cb_t cb, usr_t usrdata);

ios_ret_t IOS_Ioctlv(
    ios_fd_t fd, int ioctl, int input_count, int output_count, ioctlv *argv);
ios_ret_t IOS_IoctlvAsync(
    ios_fd_t fd, int ioctl, int input_count, int output_count, ioctlv *argv,
    ios_cb_t cb, usr_t usrdata);

#endif//_IPC_H_