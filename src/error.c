#include "../inc/minishell.h"

void	argc_error(void)
{
	printf("Structure= ./minishell\n");
	exit(1);
}

void	err_msg(char *str)
{
	perror (str);
}

void	err_msg_exit(char *str)
{
	perror (str);
	exit(1);
}
