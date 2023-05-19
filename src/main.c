#include "minishell.h"

// char *is_in_git_repo(char *cwd)
// {
// 	char *git_dir;

// 	git_dir = ft_strjoin(cwd, "/.git"); //Proteger
// 	if (access(git_dir, F_OK) != -1)
// 	{
// 		free(git_dir);
// 		return ("\033[34;1m (git) \033[36;1m> \033[0m");
// 	}
// 	free(git_dir);
// 	return ("> \033[0m");
// }

// t_env	*enviroment_extract(char **env, int i)
// {
// 	t_env	*enviroment;
// 	char	*aux;

// 	while (env[i])
// 		i++;
// 	enviroment = ft_calloc(i + 1, sizeof(t_env)); //proteger
// 	i = -1;
// 	while (env[++i])
// 	{
// 		aux = ft_strchr(env[i], '=');
// 		if (aux == NULL)
// 			printf("WTF\n"); //Gestionar el error
// 		enviroment[i].value = ft_substr(env[i], 0, aux - env[i]);
// 		enviroment[i].variable = getenv(enviroment[i].value); //proteger si es null
// 	}
// 	return (enviroment);
// }

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	// t_data	data;

	atexit(ft_leaks);
	ft_printf("%s", &(HEADER));
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = readlineplus();
		if (input)
		{
			parse_line(input);
			free(input);
		}
	}
	rl_clear_history();
}
