#include <stdio.h>
#include <time.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  struct	Conf	conf;
  char	*path	=	NULL;
  getConfigures(path,	&conf);
	myStart(&conf);
	printf("exit\n");
  return	0;
}

int
myStart(struct Conf * conf)
{
  time_t now;
  struct tm *timeNow;
  time(&now);
  timeNow = localtime(&now);
  if(timeNow->tm_wday	>=	conf->dayBegin	&&	timeNow->tm_wday	<=	conf->dayEnd)
  {
	if(timeNow->tm_hour	>=	conf->hourBegin		&&	timeNow->tm_hour	<=	conf->hourEnd)
	{
		char	**com	=	conf->command;
		char	*hope	=	*com;
		int	i	=	0;
		while(hope	!=	NULL)
		{
			//system(hope);
			pid_t	pid	=	fork();
			if(pid	==	0)
			{
				printf("commond	is %s\n",	hope);
				execlp(hope,	"",	(char	*)0);
				break;
			}
			else if(pid > 0)
			{
				sleep(2);
				i++;
				hope	=	*(com	+	i);
			}else
			{
				//exit(1);
			}
		}
	}
  }
  return 0;
}

int
test(char **hope)
{
	char *temp;
	int	i	=	0;
	do
	{
		temp	=	*(hope	+	i);
		printf("temp is %s\n",		temp);
		i++;
	}while(temp	!=	NULL);
	return	0;
}

int
getLocalConfigure(struct Conf * conf)
{
	int	size	=	sizeof(local)/sizeof(char *);
	int i;
	char	**temp	=	malloc(size	*	sizeof(char*));
	for(i	=	0;	i	<	size;	i++)
	{
		char	*com	=	*(local+i);	
		int	length	=	strlen(com)	+	1;
		char	*hope	=	malloc(length);
		strcpy(hope,	com);
		printf("com is %s, hope is %s\n", com,	hope);
		*(temp	+	i)	=	hope;
	}
	*(temp	+	i)	=	NULL;
	//test(conf->command);
	conf->command	=	temp;
	conf->dayBegin	=	1;
	conf->dayEnd	=	6;
	conf->hourBegin	=	9;
	conf->hourEnd	=	18;
	return	0;
}

int
getPathConfigure(char * path,struct Conf * conf)
{
	return	0;
}

int
getConfigures(char * path,struct Conf * conf)
{
	if(path		==	NULL)
	{
		getLocalConfigure(conf);
	}
	else
	{
		getPathConfigure(path,	conf);
	}
	return	0;
}