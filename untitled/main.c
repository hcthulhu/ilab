#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    uid_t uid = getuid();
    uid_t gid = getgid();
    printf("Hello, World!\n");
    return 0;
}