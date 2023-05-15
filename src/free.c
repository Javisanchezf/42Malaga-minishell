#include "../inc/minishell.h"

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_pipes(int *tube)
{
	printf("ENTRO!\n");
	close(tube[0]);
	close(tube[1]);
}
