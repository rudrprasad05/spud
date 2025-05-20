#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <dirent.h>

int get_current_dir(char *dir, size_t size);
void get_host_name(char *hostname, size_t size);
void ls();

int main(void) {
    char hostname[_POSIX_HOST_NAME_MAX];
    char username[_SC_LOGIN_NAME_MAX];

    char current_path[PATH_MAX];
    char *current_dir;

    char buffer[1024] = "";

    get_host_name(hostname, sizeof(hostname));
    get_current_dir(current_path, sizeof(current_path));
    getlogin_r(username, sizeof(username));

    char* token = strtok(current_path, "/");

    while (token != NULL) {
        current_dir = token;
        token = strtok(NULL, "/");
    }

    printf("%s:%s %s$ ", hostname, current_dir, username);
    scanf("%s", buffer);

    if (strcmp(buffer, "ls") == 0) {
        ls();
    } 
    else if (strcmp(buffer, "xxx") == 0){
        printf("%s:%s $", hostname, current_path);
    }
    else{
        printf("Command not recognized\n");
    }
    

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

void ls(){
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
    }

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}