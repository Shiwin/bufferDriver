#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int test_it(const char *test_value)
{
    char buf[1024];
    int fd = open("/dev/buffer-device", O_RDWR);
    write(fd, test_value, strlen(test_value));
    close(fd);
    fd = open("/dev/buffer-device", O_RDWR);
    read(fd, buf, sizeof(buf));
    close(fd);

    int result = strcmp(test_value, buf);
    if (result == 0)
    {
        printf("%s <=> %s\n", test_value, buf);
    }
    else
    {
        printf("%s <> %s\n Lengths: %lu %lu\n", test_value, buf,
               strlen(test_value), strlen(buf));
    }
    return result;
}

main()
{
    int test_result = 0;
    //test_result |= test_it("One");
    //test_result |= test_it("Two");
    //test_result |= test_it("Three");
    //test_result |= test_it("");

    char long_string[1000];
    memset(long_string, 'r', 999);
    test_result |= test_it(long_string);

    if (test_result == 0)
    {
        printf("Test passed\n");
    }
    else
    {
        printf("Something wrong\n");
    }
}