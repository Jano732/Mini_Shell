#define _GNU_SOURCE

#include <cstdio>
#include <stdbool.h>
#include <unistd.h>
#include <cstring>
#include <stdarg.h>


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
		//printf("Twoja komenda: %s\n", command);
      int result = strncmp(command, "cd\0", 3); 
 
      if(strncmp(command, "cd ", 3) == 0) printf("cd command\n");
      
      
      
	}

	return 0;
}


void directory_navigation(const char* cd, ...)
{

   va_list args;
   va_start(args, cd);

   for(int i = 0; i < 3; i++)
   {  
      printf("result: %s", va_arg(args, const char*));
   }   






}
