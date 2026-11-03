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

void history_add(char* command, size_t size)
{

    struct stat st;
    int last_number = 0;

    int fd = open("/home/vboxuser/coding/cwiczenia/miniShell/.bash_history_minishell", O_RDWR | O_CREAT |
    O_APPEND, S_IRWXU, S_IRWXG);

    if((fd != 0) && (fstat(fd, &st) == 0)){

        char* buffer = malloc(st.st_size);
        int readres = read(fd, buffer, st.st_size);

        for(int i = (st.st_size - 2); i > 0; i--){
            if(buffer[i] == '\n'){
                last_number = buffer[i+1] - '0';
                break;
                }
        }
        
        free(buffer);
        buffer = calloc(size, sizeof(char));
        
        last_number++;
        char casted_last_number[2];

//TODO trzeba obciac buffer o niepotrzebnie zaalokowane bajty, poniewaz
//sa one zapisywane do pliku i rozjezdza sie odczytywanie ostatniego
//numeru.

        snprintf(casted_last_number, sizeof(casted_last_number), "%d", last_number);
        strcat(buffer, casted_last_number);
        strcat(buffer, " ");
        strcat(buffer, command);
        
        char* tmp = realloc(buffer, sizeof

        printf("%s\n", buffer);

        if(lseek(fd, 0, SEEK_END) != -1){
         write(fd, buffer, size); 
        }

        close(fd);

    }
}


