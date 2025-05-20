#include <stdio.h>
#include <unistd.h>
#include <limits.h>
void get_host_name(char *hostname, size_t size);

int main(void) {
    char hostname[_POSIX_HOST_NAME_MAX];
    char current_dir[PATH_MAX];
    char buffer[1024] = "";

    get_host_name(hostname, sizeof(hostname));
    get_current_dir(current_dir, sizeof(current_dir));

    printf("%s$:%s ", hostname, current_dir);
    scanf("%s", buffer);

    printf("%s", buffer);

    return 0;
}

int get_current_dir(char *dir, size_t size){
    if (getcwd(dir, size) != NULL) {
        return 0;
    } else {
        perror("getcwd() error");
        return 1;
    }
}

void get_host_name(char *hostname, size_t size){
    int status = gethostname(hostname, size);

    if (status != 0) {
        perror("gethostname");
    } else {
        hostname[size - 1] = '\0';  // Ensure null termination
    }
}