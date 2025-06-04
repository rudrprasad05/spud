#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <dirent.h>
#include "ascii/ascii.h"

int get_current_dir(char *path, size_t size);
void get_host_name(char *hostname, size_t size);
void handle_exit(int *is_running);
void handle_sigint(int sig);
void ls();

volatile sig_atomic_t flag;

int main(void) {
    char hostname[_POSIX_HOST_NAME_MAX];
    char username[_SC_LOGIN_NAME_MAX];
    char buffer[1024] = "";
    
    char current_path[PATH_MAX];
    char *current_dir;

    int is_shell_running = 1;
    
    signal(SIGINT, handle_sigint);

    printf("%s", title);
    
    while(is_shell_running){
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
            printf("%s", buffer);
            ls();
        } 
        else if (strcmp(buffer, "xxx") == 0){
            printf("%s:%s $", hostname, current_path);
        }
        else if (strcmp(buffer, "exit") == 0){
            handle_exit(&is_shell_running);
            return 0;
        }
        else{
            printf("Command not recognized\n");
        }
    }

    

    return 0;
}

void handle_exit(int *is_runnning){
    *is_runnning = 0;
    printf("Exiting shell\n");
}

void handle_sigint(int sig) {
    // Custom message or logic
    printf("\nCaught SIGINT %d (Ctrl+C). Ignoring...\n", sig);
    // Optionally reset prompt or reprint shell prompt
}

int get_current_dir(char *path, size_t size){
    if (getcwd(path, size) != NULL) {
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
        printf("%s\t", entry->d_name);
    }

    printf("\n");

    closedir(dp);
}