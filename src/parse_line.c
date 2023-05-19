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

void	parse_line(char *input, t_data *data)
{
	char	**commands;
	int		i;

	commands = split_by_pipes(input, 0, 0);
	i = 0;
	data->n_commands = n_commands(commands);
	data->cmd = ft_calloc(data->n_commands + 1 ,sizeof(t_command)); //Proteger
	while (commands[i])
	{
		data->cmd[i].opt = split_by_args(commands[i], 0, 0, 0);
		data->cmd[i].path = ft_strdup("");
		data->cmd[i].input = ft_strdup("");
		data->cmd[i].output = ft_strdup("");
		printf("\n\tCommand Nº%d:\n---------------------------\n", i);
		ft_printf_split(data->cmd[i].opt);
		i++;
	}

	// i++;
	// (void)data;

	// ft_printf_split(commands);
	// printf("Nº commands: %d\n", n_commands(commands));
	// char **borrar = split_by_args(commands[0], 0, 0, 0);
	// ft_printf_split(borrar);
	// ft_split_free(borrar);
	ft_free_and_null((void **)&commands);
	if (ft_strncmp(input, "exit", 5) == 0)
	{
		ft_free_and_null((void **)&input);
		clean_and_exit_success(data);
	}
	ft_free_and_null((void **)&input);
}
