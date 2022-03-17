/*
G171210003 Ali Kerem Öcal
G161210033 Bilge Çakar
G171210066 Berke Furkan Kaya
G171210069 Ahmet Kutay Karacair
*/

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


char *str[]={
	"cd",
	"help",
	"quit"
};

int (*strFunction[])(char**) = {
	&cd,
	&help,
	&quit
};

int numStr()
{
	return sizeof(str)/sizeof(char *);
}

int cd(char **args)
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

int help(char **args)
{
	int i;
	for (i=0;i< numStr();i++)
	{
		printf("  %s\n",str[i]);
	}
	printf("Use the man command for information on other programs.\n");
	return 1;
}

int quit(char **args)
{
	int sts;
	while (!waitpid(-1,&sts,WNOHANG)){}
	exit(0);
}

#define AUXMAX 256
int cmd(char * args[])
{
	int i=0;
	int j=0;
	int fileDesc;
	int stdOut;
	int aux;
	char *args_aux[AUXMAX];
	int k;
	int bg = 0;
	int sts;
	
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
	for (m = 0 ; m < numStr() ; m++)
	{
		if (strcmp(args[0],str[m])==0)
		{
			(*strFunction[m])(args);
			return 1;
		}
	}
	while (args[i] != NULL && bg == 0)
	{
		if (strcmp(args[i],"&") == 0)
		{
			bg = 1;
		}
		else if (strcmp(args[i],"<") == 0)
		{
			if (args[i+1] == NULL )
			{
				printf ("Yeterli Arguman Yok\n");
			}
			intrd(args_aux,args[i+1]);
			return 1;
		}
		else if (strcmp(args[i],">") == 0)
		{
			if (args[i+1] == NULL )
			{
				printf ("Yeterli Arguman Yok\n");
			}
			outrd(args_aux,args[i+1]);
			return 1;
		}
		i++;
	}
	args_aux[i]==NULL;
	launch(args_aux,bg);

	return 1;
}

void intrd(char *args[],char* inFile)
{
	pid_t pid;
	if (!(access (inFile,F_OK) != -1))
	{	
		printf("saush: %s dosyasi bulunamadi\n", inFile);
		return;
	}
	int err=-1;
	int fileDesc;
	if((pid=fork()) == -1)
	{
		printf("Child olusturulamadi\n");
		return;
	}
	if (pid==0)
	{
		fileDesc =open(inFile, O_RDONLY, 0600);
		dup2(fileDesc,STDIN_FILENO);
		close(fileDesc);

		if (execvp(args[0],args)==err)	
		{
			printf("err");
			kill(getpid(),SIGTERM);
		} 
	}
	waitpid(pid,NULL,0);
}

void outrd(char *args[],char* outFile)
{
	pid_t pid;
	int err=-1;
	int fileDesc;
	if((pid=fork()) == -1)
	{
		printf("Child olusturulamadi\n");
		return;
	}
	if (pid==0)
	{
		fileDesc =open(outFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		dup2(fileDesc,STDOUT_FILENO);
		close(fileDesc);

		if (execvp(args[0],args)==err)	
		{
			printf("err");
			kill(getpid(),SIGTERM);
		} 
	}
	waitpid(pid,NULL,0);
}


int launchbg(char **args)
{
	pid_t pid;
	int sts;

	struct sigaction action;
	action.sa_handler = chld;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD,&action,NULL)<0)
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

int launch(char **args,int bg)
{
	if (bg==0)
	{
		pid_t pid;
		int sts;
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
		launchbg(args);
	}
	return 1; 
}

void chld(int signo) 
{
    int sts, cValue,chd;
	chd = waitpid(-1, &sts, WNOHANG);
	if (chd > 0)
	{
		if (WIFEXITED(sts))	
	    {
			cValue = WEXITSTATUS(sts); 
	        printf("[%d] retval : %d \n", chd, cValue);
	    }
	}
}

void Prompt()
{
	char hst[1204] = "";
	gethostname(hst, sizeof(hst));
	printf(YEL "%s@%s:"RESET RED "%s > " RESET, getenv("LOGNAME"), hst, getcwd(drct, 1024));
}

int main (int argc, char **argv, char **evp)
{
	
	char satir[MAXLINE];
	char *tk[LIMIT];
	int ntk;
	int sts=1;
	__environ =evp;
	
	while(sts)
	{
		Prompt();
		memset(satir, '\0',MAXLINE);
		fgets(satir,MAXLINE,stdin);
		if((tk[0] = strtok(satir," \n\t")) == NULL) continue;
		ntk = 1;
		while((tk[ntk] = strtok(NULL, " \n\t")) != NULL) ntk++;
		cmd(tk);
	}
}
