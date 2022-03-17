#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include "program.h"


char *builtin_str[]={
	"cd",
	"help",
	"quit"
};

int (*builtin_func[])(char**) = {
	&saush_cd,
	&saush_help,
	&saush_quit
};

int saush_num_builtins()
{
	return sizeof(builtin_str)/sizeof(char *);
}

int saush_cd(char **args)
{
	if (args[1]==NULL)
	{
		fprintf(stderr,"saush: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1])!=0)
		{
			perror("saush");
		}
	}
	return 1;
}

int saush_help(char **args)
{
	int i;
	printf("Isletım Sistemleri Odevi\n");
	for (i=0;i<saush_num_builtins();i++)
	{
		printf("  %s\n",builtin_str[i]);
	}
	printf("Use the man command for information on other programs.\n");
	return 1;
}

int saush_quit(char **args)
{
	int status;
	while (!waitpid(-1,&status,WNOHANG)){}
	exit(0);
}

#define AUXMAX 256
int commandHandler(char * args[])
{
	int i=0;
	int j=0;
	int fileDescriptor;
	int standartOut;
	int aux;
	char *args_aux[AUXMAX];
	int k;
	int background = 0;
	int status;
	
	while(args[j] != NULL)
	{
		if ((strcmp(args[j],">") == 0) || (strcmp(args[j],"<") == 0) || (strcmp(args[j],"&") == 0))
		{
			break;
		}
		args_aux[j] = args[j];
		j++;
	}
	args_aux[j]=NULL;

	int m;
	if (args[0] == NULL)
	{
		return 1;
	}
	for (m = 0 ; m < saush_num_builtins() ; m++)
	{
		if (strcmp(args[0],builtin_str[m])==0)
		{
			(*builtin_func[m])(args);
			return 1;
		}
	}
	while (args[i] != NULL && background == 0)
	{
		if (strcmp(args[i],"&") == 0)
		{
			background = 1;
		}
		else if (strcmp(args[i],"<") == 0)
		{
			if (args[i+1] == NULL )
			{
				printf ("Yeterli Arguman Yok\n");
			}
			inputRD(args_aux,args[i+1]);
			return 1;
		}
		else if (strcmp(args[i],">") == 0)
		{
			if (args[i+1] == NULL )
			{
				printf ("Yeterli Arguman Yok\n");
			}
			outputRD(args_aux,args[i+1]);
			return 1;
		}
		i++;
	}
	args_aux[i]==NULL;
	saush_launch(args_aux,background);

	return 1;
}

void inputRD(char *args[],char* inputFile)
{
	pid_t pid;
	if (!(access (inputFile,F_OK) != -1))
	{	
		printf("saush: %s adinda bir dosya bulunamadi\n",inputFile);
		return;
	}
	int err=-1;
	int fileDescriptor;
	if((pid=fork()) == -1)
	{
		printf("Child olusturulamadi\n");
		return;
	}
	if (pid==0)
	{
		fileDescriptor=open(inputFile, O_RDONLY, 0600);
		dup2(fileDescriptor,STDIN_FILENO);
		close(fileDescriptor);

		if (execvp(args[0],args)==err)	
		{
			printf("err");
			kill(getpid(),SIGTERM);
		} 
	}
	waitpid(pid,NULL,0);
}

void outputRD(char *args[],char* outputFile)
{
	pid_t pid;
	int err=-1;
	int fileDescriptor;
	if((pid=fork()) == -1)
	{
		printf("Child olusturulamadi\n");
		return;
	}
	if (pid==0)
	{
		fileDescriptor=open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		dup2(fileDescriptor,STDOUT_FILENO);
		close(fileDescriptor);

		if (execvp(args[0],args)==err)	
		{
			printf("err");
			kill(getpid(),SIGTERM);
		} 
	}
	waitpid(pid,NULL,0);
}


int saush_launchbg(char **args)
{
	pid_t pid;
	int status;

	struct sigaction act;
	act.sa_handler = sig_chld;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD,&act,NULL)<0)
	{
		fprintf(stderr,"sigaction failed\n");
		return 1;
	}

	pid=fork();
	if (pid == 0)
	{
		if (execvp(args[0],args) == -1)
		{
			printf("Command not found");
			kill(getpid(),SIGTERM);
		}
		//exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("saush");
	}
	else
	{
		printf("Proses PID:%d Degeriyle Olusturuldu\n",pid);
	}
	return 1; 
}

int saush_launch(char **args,int background)
{
	if (background==0)
	{
		pid_t pid;
		int status;
		pid=fork();
		if (pid == 0)
		{
			if (execvp(args[0],args) == -1)
			{
				printf("Command not found");
				kill(getpid(),SIGTERM);
			}
		}
		else if (pid < 0)
		{
			perror("saush");
		}
		else
		{
			waitpid(pid,NULL,0);
		}
	}
	else
	{
		saush_launchbg(args);
	}
	return 1; 
}

void sig_chld(int signo) 
{
    int status, child_val,chid;
	chid = waitpid(-1, &status, WNOHANG);
	if (chid > 0)//Arkaplanda çalışmayan processler için bu değer -1 olacağından bu kontrol yapılmıştır.
	{
		if (WIFEXITED(status))	//Çocuk Normal Bir Şekilde mi Sonlandı ?
	    {
	        child_val = WEXITSTATUS(status); // Çocuğun durumu alındı.
	        printf("[%d] retval : %d \n",chid, child_val); //Çocuğun pid'i ve durumu ekrana yazdırılır.
	    }
	}
}

void welcomeScreen(){
        printf("\n\t============================================\n");
        printf("\t                   C Shell  \n");
        printf("\t--------------------------------------------\n");
        printf("\t                                  \n");
        printf("\t============================================\n");
        printf("\n\n");
}

void PromptBas()
{
	char hostn[1204] = "";
	gethostname(hostn, sizeof(hostn));
	printf(YEL "%s@%s:"RESET RED "%s > " RESET, getenv("LOGNAME"), hostn, getcwd(currentDirectory, 1024));
}

int main (int argc, char **argv, char **envp)
{
	welcomeScreen();
	char line[MAXLINE];
	char *tokens[LIMIT];
	int numTokens;
	int status=1;
	environ=envp;
	
	while(status)
	{
		PromptBas();
		memset(line, '\0',MAXLINE);
		fgets(line,MAXLINE,stdin);
		if((tokens[0] = strtok(line," \n\t")) == NULL) continue;
		numTokens = 1;
		while((tokens[numTokens] = strtok(NULL, " \n\t")) != NULL) numTokens++;
		commandHandler(tokens);
	}
}
