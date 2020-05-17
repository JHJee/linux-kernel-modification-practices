#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
int file_write(int fd, char* data, int size){
	loff_t pos = 0;
	struct file *file;
	mm_segment_t oldfs = get_fs();
	int ret;

	set_fs(KERNEL_DS);

	if(fd >= 0){
		file = fget(fd);
		if(file){
			ret = vfs_write(file, data, size, &pos);
			fput(file);
		}
	}
	set_fs(oldfs);
	return ret;
}
int sys_swrite(int fd, char* buf, int len){
    unsigned char p;
    int i, j, wbytes = 0;
    for (j = 0; j < len; j++) {
        p = 0x80;
        for (i = 0; i < 8; i++) {
            buf[j] = buf[j] ^ p;
            p = p >> 1;
        }
    }   
    wbytes = file_write(fd, buf, len);
    printk("wbytes: %d", wbytes);
    printk("sys_swrite()\n");
    return wbytes;
}
SYSCALL_DEFINE3(swrite, int, fd, char*, buf, int, len)
{
	return sys_swrite(fd, buf, len);
}
