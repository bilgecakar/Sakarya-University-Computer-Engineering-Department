#define TRUE 1
#define FALSE !TRUE
#define LIMIT 256 // max number of tokens for a command
#define MAXLINE 1024 // max number of characters from user input



#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

static char* currentDirectory;
extern char** environ;

void sig_chld(int);
int saush_launch(char **args, int background);
void inputRD(char *args[],char* inputFile);
void outputRD(char *args[],char* inputFile);
int saush_cd(char **args);
int saush_help(char **args);
int saush_quit(char **args);

