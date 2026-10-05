#define _GNU_SOURCE

#include "build-ins.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

void directory_navigation(char*);
void list_files();
void non_build_in(char*);
char** castingStreamInput(char*);
char* trim(char*);
void freeArray(char**);

int main(){

   char* current_dir;
   char precommand[100]; 
   char command[64];
   char hostname[16];
   char user_hostname[32];
   memset(user_hostname, '\0', sizeof(user_hostname));

   //char* user = getenv("USERNAME");
   char* user =  getlogin();
   gethostname(hostname, sizeof(hostname));
   strcat(user_hostname, user);
   strcat(user_hostname, "@");
   strcat(user_hostname, hostname);
   strcat(user_hostname, ":");

while(true){

    memset(precommand, '\0', sizeof(precommand));
    memset(command, '\0', sizeof(command));
    current_dir = NULL;
    strcpy(precommand, user_hostname);

    //current_dir = get_current_dir_name();
	current_dir = getcwd(NULL, 0);
    strcat(precommand, current_dir);
    strcat(precommand, "$ ");

    printf("%s" ,precommand);
    fgets(command, 64, stdin);

    int result = strncmp(command, "cd\0", 3); 
 
    if(strncmp(command, "cd ", 3) == 0) directory_navigation(command);
    else if(strncmp(command, "exit", 4) == 0) exit(0); 
    else non_build_in(command);      
    //if(strncmp(command, "ls", 2) == 0) list_files(current_dir);      
   
    //if(strncmp(command, "ls", 2) == 0) list_files(command);
    history_add(command, sizeof(command));
    free(current_dir);
	}

    return 0;
}



void non_build_in(char* command)
{
    if(fork() == 0){
        char** input_stream_ptr = castingStreamInput(command);
        //execv("/bin/ls", input_stream_ptr);
        execvp(input_stream_ptr[0], input_stream_ptr);
        perror("Blad uruchamiania programu");
        freeArray(input_stream_ptr);
        exit(1);
    }
    wait(NULL);
}


char** castingStreamInput(char* command)
{
    int array_size = 1;
    int i = 1;
    char* token = strtok(command, " ");
    char** token_array = (char**) malloc(sizeof(char*));

    if(token != NULL){
        token_array[0] = (char*) malloc(strlen(token) + 1);
        strcpy(token_array[0], trim(token));
    }

    while(token != NULL){
        token = strtok(NULL, " ");
        array_size++;
        char** tmp = (char**) realloc(token_array, array_size * sizeof(char*));

        if(tmp != NULL){
            token_array = tmp;
            if(token != NULL){
               token = trim(token);
               token_array[i] = (char*) malloc(strlen(token) + 1);
               strcpy(token_array[i], token);
            }
            else token_array[i] = NULL;
            i++;
        }
    }
    return token_array;
}


char* trim(char* command){

    int index = -1;
    if(strchr(command, '\n') != NULL){   
        int index = strchr(command, '\n') - command;
        command[index] = '\0';
    }
    return command;
}


void freeArray(char** input)
{
    size_t num_of_elements = sizeof(input) / sizeof(char*);
    printf("Liczba elementow: %zs\n", num_of_elements);
}
