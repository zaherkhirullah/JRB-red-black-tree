/*********************************
**********************************
 Zaher Khirullah
*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

#define MAX_COMMAND_LINE 256
#define TOKEN_LIMIT 128
static pid_t GBSH_PID;
static pid_t GBSH_PGID;
static int GBSH_IS_INTERACTIVE;
static struct termios GBSH_TMODES;

struct sigaction act_child;
struct sigaction act_int;

int NoPropmt;
static char* currentDirectory;

pid_t pid;

int commandExecute(char * command[],char* inputed[]);
void Cocuk(int p);
void signal_int(int p);
void IOProcess(char * command[], char* inputFile, char* outputFile, int control);
void execProgram(char **command, int background);
int changeDirectory(char * command[]);
