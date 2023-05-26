#include "minishell.h"

void	enviroment_extract(char **env, t_data *data)
{
	int		i;
	int		size;

	i = 0;
	while (env[i])
		i++;
	data->env = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!data->env)
		ft_error("Problem allocating memory.", 0);
	i = -1;
	while (env[++i])
	{
		size = ft_strlen(env[i]);
		data->env[i] = ft_calloc(size + 1, sizeof(char));
		ft_strlcpy(data->env[i], env[i], size + 1);
	}
}

void	init_data(t_data *data, char **env, int argc, char **argv)
{
	if (write(1, NULL, 0) == -1 || read(0, NULL, 0) == -1)
	{
		perror("Error: No write/read permissions on main fd.");
		exit(EXIT_FAILURE);
	}
	ft_printf("%s", &(HEADER));
	data->n_commands = 0;
	enviroment_extract(env, data);
	data->lastcmd_value = 0;
	signal(SIGINT, sigint_handler);
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
