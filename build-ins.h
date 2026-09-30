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
#include <fcntl.h>
#include <sys/stat.h>



void directory_navigation(char* directory)
{
    if(directory != NULL)
    {

        char *space_ptr = strchr(directory, ' ');
        space_ptr++;
        int newline_index = strcspn(space_ptr, "\n");
        space_ptr[newline_index] = '\0';       
        const char* upcoming_directory = space_ptr;
        if(strcmp(upcoming_directory, "~") == 0){
            chdir("/home/vboxuser/");
        }
        else if(chdir(upcoming_directory)) 
            printf("chdir() error: %s | %s\n",upcoming_directory, strerror(errno));
    }

}

void history_add(char* command)
{
       int fd = open("/home/vboxuser/coding/cwiczenia/miniShell/.bash_history_minishell", O_RDWR | O_CREAT | O_EXCL |
       O_APPEND, S_IRWXU, S_IRWXG);

       int last_number = 0;

       struct stat st;
       if(fstat(fd, &st) == -1) perror("fstat");

       if(fd != 0) perror("open");

       char* buffer = malloc(st.st_size);

       int readres = read(fd, buffer, st.st_size);

       for(int i = (st.st_size - 2); i > 0; i--)
       {
            if(buffer[i] == '\n'){
               last_number = buffer[i+1] - '0';
               break;
            }
       }

       printf("%i\n", last_number);

}


