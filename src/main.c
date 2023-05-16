/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:28:44 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/16 19:30:07 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*count_commands(char *input, int *commands, int i)
{
	char	aux;
	char	*dquote;

	*commands = 1;
	while (input[i])
	{
		while (input[i] && (input[i] != '|' && input[i] != '\'' && input[i] != '\"'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			aux = input[i];
			i++;
			while (1)
			{
				while (input[i] && input[i] != aux)
					i++;
				if (!input[i])
				{
					dquote = ft_strjoin("\n", input); // proteger
					free(input);
					input = dquote;
					dquote = readline("\033[36;1m> \033[0m"); //proteger
					input = ft_freeandjoin(input, dquote); //proteger
				}
				else
					break ;
			}
			i++;
		}
		else if (input[i] == '|')
		{
			(*commands)++;
			i++;
		}
	}
	return (input);
}

char	*ft_get_text_minishell(void)
{
	char	*text_minishell;
	char	path[1024];
	char	*aux;

	if (getcwd(path, sizeof(path)) == NULL)
		exit(EXIT_FAILURE); //Poner ft_error y liberar lo que haga falta
	aux = ft_strrchr(path, '/') + 1;
	aux = ft_strjoin("\033[36;1m", aux); //Proteger
	text_minishell = ft_strjoin(aux, " -> \033[0m"); //Proteger
	free(aux);
	return (text_minishell);
}


void ft_getline()
{
	char	*input;
	char	*text_minishell;
	int		n_commands;

	while (1)
	{
		text_minishell = ft_get_text_minishell();
		input = readline(text_minishell);
		free(text_minishell);
			input = count_commands(input, &n_commands, 0);
		add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		printf("Entrada: %s, comandos: %d\n", input, n_commands);
		free(input);
	}
}

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
