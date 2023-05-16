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
// 	enviroment = ft_calloc(i + 1, sizeof(t_env));
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

// char	*parse_aux(char *input, char delimiter, int *i)
// {
// 	int	start;

// 	start = *i;
// 	while (input[*i] && input[*i] != delimiter)
// 		*i++;
// 	if (input[*i] == delimiter)
// 		return (ft_substr(input, start, *i - start + 1));

// }

// char	**parse(char *input)
// {
// 	char	**input_parse;
// 	int		i;
// 	int		n_args;

// 	i = 0;
// 	n_args = 0;
// 	while (input[i])
// 	{
// 		while (ft_isspace(input[i]))
// 			i++;
// 		if (input[i] == '\'' || input[i] == '\"')
// 			input_parse[n_args] = parse_aux(input, input[i], &i);
// 	}
// }

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	ft_printf("%s", &(HEADER));
	atexit(ft_leaks);
	(void)argc;
	(void)argv;
	(void)env;
	ft_getline();
}
