#include "minishell.h"

int		n_commands(char **commands)
{
	int	i;

	i = 0;
	if (commands && *commands && **commands)
		while (commands[i])
			i++;
	return (i);
}

void	parse_line(char *input)
{
	char	**commands;
	char	**borrar;

	commands = split_by_pipes(input, 0, 0);
	ft_printf_split(commands);
	printf("Nº commands: %d\n", n_commands(commands));
	borrar = split_by_args(commands[0], 0, 0, 0);
	ft_printf_split(borrar);
	ft_split_free(borrar);
	free(commands);
	if (ft_strncmp(input, "exit", 5) == 0)
	{
		free(input);
		rl_clear_history();
		exit(EXIT_SUCCESS) ;
	}
}
