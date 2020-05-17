#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
int read(int fd, char* data, int size, loff_t* pos){
	struct file* file;
	//loff_t pos = 0;
	int ret;
	mm_segment_t oldfs = get_fs();
	
	set_fs(KERNEL_DS);
	if(fd >= 0){
		file = fget(fd);
		if(file){
			ret = vfs_read(file, data, size, pos);
		}
	}
	set_fs(oldfs);
	return ret;
}
int sys_sread(int fd, char* buf, int len){
    unsigned char p;
    int i, j, rbytes = 0;
    loff_t pos = 0;

    for (j = 0; j < len; j++){
	pos = j;
        if(read(fd, &buf[j], 1, &pos) == 1){ 
            rbytes++;
        } else {
            printk("rbytes: %d", rbytes);
            printk("sys_sread()\n");
            return rbytes;
        }
        p = 0x80;
        for(i = 0; i < 8; i++){
            buf[j] = buf[j] ^ p;
            p = p >> 1;
        }
    }
    printk("rbytes: %d", rbytes);
    printk("sys_sread()\n");
    return rbytes;
}
SYSCALL_DEFINE3(sread, int, fd, char*, buf, int, len)
{
	return sys_sread(fd, buf, len);
}
