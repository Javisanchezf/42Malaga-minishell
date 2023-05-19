#include "minishell.h"

void	clean_commands(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_commands)
	{
		ft_split_free(data->cmd[i].opt);
		ft_free_and_null((void **)&data->cmd[i].path);
		ft_free_and_null((void **)&data->cmd[i].input);
		ft_free_and_null((void **)&data->cmd[i].output);
	}
	data->n_commands = 0;
	ft_free_and_null((void **)&data->cmd);
}

void	clean_and_exit_success(t_data *data)
{
	// int	i;

	clean_commands(data);
	// i = -1;
	// while (++i < NULL)
	// {
	// 	ft_free_and_null((void **)&data->env[i].value);
	// 	ft_free_and_null((void **)&data->env[i].variable);
	// }
	rl_clear_history();
	exit(EXIT_SUCCESS);
}