#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/module.h>

static const int MAJOR = 44;
static const char DEVICE_NAME[] = "buffer-device";

#define CONTAINING_VALUE_LEN 1024
#define CONTAINING_VALUE_USED_LEN ((CONTAINING_VALUE_LEN - 1)) // the last byte will be always '\0'
static char containing_value[CONTAINING_VALUE_LEN] = {'\0'};

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
    int read_bytes = (CONTAINING_VALUE_USED_LEN < sz) ? CONTAINING_VALUE_USED_LEN : sz;

    return copy_to_user(buf, containing_value, read_bytes);
}

ssize_t buffer_driver_write(struct file *f, const char __user *buf, size_t sz, loff_t *off)
{
    int write_bytes = (CONTAINING_VALUE_USED_LEN < sz) ? CONTAINING_VALUE_USED_LEN : sz;

    return copy_from_user(containing_value, buf, write_bytes);
}

module_init(buffer_init);
module_exit(buffer_exit);
MODULE_LICENSE("GPL");