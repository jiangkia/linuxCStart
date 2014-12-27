#ifndef STARTUP
#define STARTUP

#define SIZE	256
typedef struct Conf
{
	int	dayBegin;
	int	dayEnd;
	int	hourBegin;
	int	hourEnd;
	char	**command;
}Conf;

char *local[]={"/usr/bin/gitg","/usr/bin/emacs"};

int
getConfigures(char *path,	struct	Conf	*conf);

static	int
getLocalConfigure(struct	Conf	*conf);

static	int
getPathConfigure(char	*path,	struct	Conf	*conf);

static	int
startCommon(char	*commond);

static int
myStart(struct	Conf	*conf);

#endif