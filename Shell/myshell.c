#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define COMMAND_MEMORY 25
#define BUFFER_SIZE 1024

char command[1024];
char var_name[256];
char *token;
char *outfile;
int i, fd, amper, redirect_std, redirect_err, retid, append, status;
char *argv[32];
char prompt[256] = "hello:";
char *last_command [COMMAND_MEMORY];
int command_index =  0;
int counter;
int position = 1;

char buffer[BUFFER_SIZE];
pid_t pid;
int pipe_fd[2];
int fd_in = STDIN_FILENO;

void ctrl_C_handler(int ctrl_c_signal){
    switch (ctrl_c_signal){
    case SIGINT:
        printf("\nYou typed Control-C!\n");
        printf("%s ", prompt);
        fflush(stdout);
        break;
    }
    
}

int main() {
    signal(SIGINT, ctrl_C_handler);
    while (1) {
        printf("%s", prompt);
        printf(" ");
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0';
        if(command[0] == '\033'){
            printf("\033[1A");//line up
			printf("\x1b[2K");//delete line
            // printf("index - %d , counter - %d\n", command_index, counter_command);
			switch(command[2]) { // the real value
                case 'A':
                    // code for arrow up
                    // printf("UP\n");
                    if (counter < COMMAND_MEMORY && counter < command_index){
                        printf("%s\n", last_command[(command_index - counter -1) % COMMAND_MEMORY]);
                        counter++;
                    }
                    break;
                case 'B':
                    // code for arrow down
                    if (counter > 0){
                        counter--;
                        printf("%s\n", last_command[(command_index - counter) % COMMAND_MEMORY]);
                    }
                    break;
		    }
            continue;
        }

        last_command[command_index % COMMAND_MEMORY] = malloc(strlen(command) * sizeof(char));
        strcpy(last_command[command_index % COMMAND_MEMORY], command);
        command_index++;
        counter= 0;
    
        /* parse command line */
        i = 0;
        token = strtok (command," ");
        while (token != NULL) {
            argv[i] = token;
            token = strtok (NULL, " ");
            i++;
        }
        argv[i] = NULL;
        /* Is command empty */
        if (argv[0] == NULL){
            continue;
        }

        /* Does command line end with & */ 
        if (! strcmp(argv[i - 1], "&")) {
            amper = 1;
            argv[i - 1] = NULL;
        } else { 
            amper = 0; 
        }

        if (i >= 2 && ! strcmp(argv[i - 2], ">")) {
            redirect_std = 1;
            argv[i - 2] = NULL;
            outfile = argv[i - 1];
        } else { 
            redirect_std = 0; 
        }

        if (i >= 2 && (redirect_std == 0) && (! strcmp(argv[i - 2], "2>"))) {
            redirect_err = 1;
            argv[i - 2] = NULL;
            outfile = argv[i - 1];
        } else { 
            redirect_err = 0; 
        }

        if (i >= 2 && (redirect_std == 0) && (redirect_err == 0) && (! strcmp(argv[i - 2], ">>"))) {
            append = 1;
            argv[i - 2] = NULL;
            outfile = argv[i - 1];
        } else { 
            append = 0; 
        }

        if (! strcmp(argv[0], "prompt") && ! strcmp(argv[i - 2], "=")){
            strncpy(prompt, argv[i - 1],sizeof(prompt));
            continue;
        }

        if (! strcmp(argv[i-1], "$?")){
            printf("%d\n", status);
            continue;
        }

        if (! strcmp(argv[0], "cd")){
            chdir(argv[i-1]);
            continue;
        }

        if (! strcmp(argv[0], "!!")){
            printf("%s\n", last_command[(command_index - 2) % COMMAND_MEMORY]);
            command_index--;
            continue;
        }

        if (! strcmp(argv[0], "quit")){
            exit(1);
        }

        if (argv[0][0] == '$' && !strcmp(argv[1],"=")){
            setenv(argv[0]+1, argv[i - 1], 1);
            continue;
        }

        if (argv[i-1][0] == '$' && ! strcmp(argv[0],"echo")){
            printf("%s\n", getenv(argv[i-1]+1));
            continue;
        }

        if (! strcmp(argv[0], "read")){
            fgets(var_name, 256, stdin);
            var_name[strlen(var_name) - 1] = '\0';
            setenv(argv[i-1], var_name, 1);
            continue;
        }

        if(i >= 2 && ! strcmp(argv[1], "|")){
            int result;
            char output[1024];
            // printf("%s\n", last_command[command_index - 1]);
            if ((result = system(last_command[command_index - 1])) != -1) {
                sprintf(output, "%d", result);
            } else {
                printf("Error executing command\n");
            }
            continue;
        }

        if(i >= 2 && ! strcmp(argv[0], "if")){
            char condition[1024];
            char line[256];
            int if_index = strlen(last_command[command_index-1]);
            int flag_fi = 0;
            int result;
            char output[1024];
            strncpy(condition, last_command[command_index-1],if_index);
            strcat(condition, "\n");
            while(1){
                fgets(line, 256, stdin);
                line[strlen(line) - 1] = '\0';
                strcat(condition, line);
                strcat(condition, "\n");
                if(! strcmp(line, "fi")){
                    last_command[command_index % COMMAND_MEMORY] = malloc(strlen(condition) * sizeof(char));
                    strcpy(last_command[command_index%COMMAND_MEMORY], condition);
                    command_index++;
                    counter = 0;
                    break;
                }
            }
            // printf("%s\n", command);
            if ((result = system(condition)) != -1) {
                sprintf(output, "%d", result);
            } else {
                printf("Error executing command\n");
            }
            continue;
        }

        /* for commands not part of the shell command language */ 

        if (fork() == 0) { 
            // printf("i'm in fork\n");
            signal (SIGINT,SIG_DFL);
            /* redirect_stdion of IO ? */
            if (redirect_std) {
                fd = creat(outfile, 0660); 
                close (STDOUT_FILENO) ; 
                dup(fd); 
                close(fd); 
                /* stdout is now redirect_stded */
            } 
            if (redirect_err) {
                fd = creat(outfile, 0660); 
                close (STDERR_FILENO) ; 
                dup2(fd, STDERR_FILENO); 
                close(fd); 
                /* stdout is now redirect_stderr */
            } 
            if (append) {
                freopen(outfile, "a+", stdout); 
            } 

            execvp(argv[0], argv);

            if (! append){
                freopen("/dev/tty", "w", stdout);
            }
        }
        /* parent continues here */
        if (amper == 0) {
            retid = wait(&status);
        } // fork
    } // while
}