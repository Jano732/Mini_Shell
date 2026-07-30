#define _GNU_SOURCE

#include <cstdio>
#include <stdbool.h>
#include <unistd.h>
#include <cstring>
#include <stdarg.h>
#include <errno.h>

void directory_navigation(char*);

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
      
    printf(command);      
      
	}

    return 0;
}

/*
void directory_navigation(const char* dir)
{

    if(strcmp(dir, "..") || strcmp(dir, "../"))
    {
        int res = chdir("..");
        printf("%i", res);
    }
}
*/

  
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
