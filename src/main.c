#include "minishell.h"

void	enviroment_extract(char **env, t_data *data)
{
	int		i;
	char	*aux;

	i = 0;
	while (env[i])
		i++;
	data->n_envs = i;
	data->env = ft_calloc(i + 1, sizeof(t_env));
	if (!data->env)
		ft_error("Problem allocating memory.0", 0);
	i = -1;
	while (env[++i])
	{
		aux = ft_strchr(env[i], '=');
		data->env[i].value = ft_substr(env[i], 0, aux - env[i]);
		data->env[i].variable = ft_substr(env[i], aux - \
		env[i] + 1, ft_strlen(ft_strchr(env[i], '=')) - 1);
		if (!data->env[i].variable)
			data->env[i].variable = ft_calloc(1, 1);
	}
}

void	init_data(t_data *data, char **env, int argc, char **argv)
{
	data->n_commands = 0;
	enviroment_extract(env, data);
	data->lastcmd_value = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigint_handler);
	(void)argc;
	(void)argv;
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;

	atexit(ft_leaks);
	ft_printf("%s", &(HEADER));
	init_data(&data, env, argc, argv);
	while (1)
	{
		input = readlineplus(&data);
		if (input)
			parse_line(input, &data);
		ft_leaks();
		clean_commands(&data);
	}
	clean_and_exit_success(&data);
}
