#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

static const int MAJOR = 44;
static const char DEVICE_NAME[] = "buffer-device";

#define CONTAINING_VALUE_LEN 1024
static char containing_value[CONTAINING_VALUE_LEN];
static ssize_t containing_value_len = 0;

ssize_t buffer_driver_read(struct file *f, char __user *buf, size_t sz, loff_t *off);

ssize_t buffer_driver_write(struct file *f, const char __user *buf, size_t sz, loff_t *off);

static struct file_operations buffer_driver_fops =
    {
        .owner = THIS_MODULE,
        .read = buffer_driver_read,
        .write = buffer_driver_write,
};

static int __init buffer_init(void)
{
    if (register_chrdev(MAJOR, DEVICE_NAME,
                        &buffer_driver_fops))
    {
        printk("buffer_driver: unable to get major\n");
        return -EIO;
    }
    return 0;
}

static void __exit buffer_exit(void)
{
    unregister_chrdev(MAJOR, DEVICE_NAME);
    return;
}

ssize_t buffer_driver_read(struct file *f, char __user *buf, size_t sz, loff_t *off)
{
    return 0;
}

ssize_t buffer_driver_write(struct file *f, const char __user *buf, size_t sz, loff_t *off)
{
    return 0;
}

module_init(buffer_init);
module_exit(buffer_exit);
MODULE_LICENSE("GPL");