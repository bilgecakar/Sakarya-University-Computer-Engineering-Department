/*
G171210003 Ali Kerem Öcal
G161210033 Bilge Çakar
G171210066 Berke Furkan Kaya
G171210069 Ahmet Kutay Karacair
*/

#define TRUE 1
#define FALSE !TRUE
#define LIMIT 256
#define MAXLINE 1024


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

static char* drct;
extern char** evr;

int cd(char** args);
int help(char** args);
int quit(char** args);
void chld(int);
int launch(char **args, int bg);
void intrd(char *args[],char* inFile);
void outrd(char *args[],char* outFile);

