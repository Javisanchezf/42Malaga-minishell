#include "minishell.h"

// char *is_in_git_repo(char *cwd)
// {
// 	char *git_dir;

// 	git_dir = ft_strjoin(cwd, "/.git"); //Proteger
// 	if (access(git_dir, F_OK) != -1)
// 	{
// 		ft_free_and_null((void **)&git_dir);
// 		return ("\033[34;1m (git) \033[36;1m> \033[0m");
// 	}
// 	ft_free_and_null((void **)&git_dir);
// 	return ("> \033[0m");
// }

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

void	init_data(t_data *data, char **env)
{
	data->n_commands = 0;
	(void)env;
	enviroment_extract(env, data);
	data->lastcmd_value = 0;
	char *borrar = ft_getenv("aPATH", data, 1, 4);
	ft_printf("Puntero: %p, String: %s\n", borrar, borrar);
	ft_printf("Puntero: %p, String: %s\n", data->env[2].variable, data->env[2].variable);
	free(borrar);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void sigint_handler(int sig) {
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  ", 1);
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;


	atexit(ft_leaks);
	ft_printf("%s", &(HEADER));
	(void)argc;
	(void)argv;
	init_data(&data, env);
	
	// Establecer el controlador de señales
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigint_handler);

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
