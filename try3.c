#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10
void read_com(char* cmd);
void parseCmd(char* cmd, char** params);
int cd(char ** params);
int executeCmd(char** params);
int rm(char ** params);
int ln(char ** params, char *nfile);



int main()

{

    char cmd[MAX_COMMAND_LENGTH + 1];
	char* params[MAX_NUMBER_OF_PARAMS + 1];
	
	while (1)
	{
	   pid_t pid = fork();
	   if (pid < 0)
	  {
	     char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
      }
      else if (pid == 0) {
      sprintf(cmd, "$");
   write(1,cmd,1);
   //puts(str);
   int nread = read(0,cmd,80);
   if (nread == 0)
   goto end;
   write (1,cmd,nread);
   if(cmd[nread-1] == '\n') {
           cmd[nread-1] = '\0';
        }
        parseCmd(cmd, params);
        
    if(strcmp(params[0], "exit") == 0)
   // printf ("%s",params[0]);
    goto end;	
      if(strcmp(params[0],"cd") == 0){
         cd(params);
         //params[0]=0;
//params[1]=0;
       }
       if(strcmp(params[0],"rm") == 0){
         rm(params);
         //params[0]=0;
//params[1]=0;
       }
           if(strcmp(params[0],"ln") == 0){
           char nfile[100];
           strcpy(nfile,params[2]);
         ln(params,nfile);
         //params[0]=0;
//params[1]=0;
       }
       system("ls");
    }
      else {
        // Wait for child process to finish
        //int childStatus;
        wait(NULL);
        return 1;
    }
    }
    end : 
    return 0;
    }
    
void parseCmd(char* cmd, char** params)
{       
int i = 0 ;   
 for(i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&cmd, " ");
        if(params[i] == NULL) break;
    }
}

int cd(char ** params){
//char arr[30];
//sprintf(arr,"w");
//write(1,arr,1);
//printf("welcome");
char path[1000];
strcpy(path,params[1]);
params[1]=0;
//static char *prompt = "OS";
   //static char *a = ">";
   char cwd[256]; 
   getcwd(cwd,sizeof(cwd));
    strcat(cwd,"/"); 
   strcat(cwd,path);
   chdir(cwd); 
//printf("%s-%s%s",prompt,path,a);
write(1,cwd,sizeof (cwd));
//memset(params,0,sizeof (params));
//write(1,params[1],sizeof params);
   return 0;
  }


int rm(char ** params){
   char file[100];
   strcpy(file,params[1]);
   write(1,file,sizeof file);
   unlink(file);
   return 0;
  }

int ln(char ** params, char *nfile){
   char file[100];
   char nn[100];
   strcpy(file,params[1]);
   strcpy(nn,params[2]);
   //write(1,file,sizeof file);
   link(file,nn);
   return 0;
  }
