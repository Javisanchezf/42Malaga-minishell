#include "../inc/minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}