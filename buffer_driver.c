#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

#define MAGOR 
static const char device_name[] = "buffer-device";

static int __init buffer_init(void)
{
    //register_chdev();
    return 0;
}

static void __exit buffer_exit(void)
{
    return;
}


ssize_t buffer_driver_read(struct file *f, char __user buf,
                           size_t sz, loff_t *off)
{
    return 0;
}

ssize_t buffer_driver_write(struct file *f, char __user buf,
                           size_t sz, loff_t *off)
{
    return 0;
}

int buffer_driver_open(struct inode *i, struct file *f)
{
    return 0;
}

int buffer_driver_close(struct inode *i, struct file *f)
{
    return 0;
}

static struct file_operations buffer_driver_fops =
    {
        .owner = THIS_MODULE,
        // .read = buffer_driver_read,
        // .write = buffer_driver_write,
        .open = buffer_driver_open,
        .release = buffer_driver_close,
};

module_init(buffer_init);
module_exit(buffer_exit);
MODULE_LICENSE("GPL");