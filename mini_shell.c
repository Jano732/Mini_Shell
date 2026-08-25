#define _GNU_SOURCE

#include <cstdio>
#include <stdbool.h>
#include <unistd.h>
#include <cstring>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

void directory_navigation(char*);
void list_files();
void list_files(char*);
char** castingStreamInput(char*);
char* trim(char*);
void freeArray(char**);

int main(){

   char* current_dir;
   char precommand[64]; 
   char command[64];

while(true){
      
    memset(precommand, '\0', sizeof(precommand));
    memset(command, '\0', sizeof(command));
    current_dir = nullptr;

    current_dir = get_current_dir_name();
    strcat(precommand, current_dir);
    strcat(precommand, "$ ");

    printf(precommand);
    fgets(command, 64, stdin);

    int result = strncmp(command, "cd\0", 3); 
 
    if(strncmp(command, "cd ", 3) == 0) directory_navigation(command);
    else list_files(command);      
    //if(strncmp(command, "ls", 2) == 0) list_files(current_dir);      
   
    //if(strncmp(command, "ls", 2) == 0) list_files(command);      
	}

    return 0;
}



void directory_navigation(char* directory)
{
    if(directory != nullptr)
    {

        char *space_ptr = strchr(directory, ' ');
        space_ptr++;
        int newline_index = strcspn(space_ptr, "\n");
        space_ptr[newline_index] = '\0';       
        const char* upcoming_directory = space_ptr;
        if(chdir(upcoming_directory)) 
            printf("chdir() error: %s | %s\n",upcoming_directory, strerror(errno));
    }

}

void list_files(char* command)
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
