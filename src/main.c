/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:28:44 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/16 12:52:31 by javiersa         ###   ########.fr       */
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

int	count_commands(char *input)
{
	int		commands;
	int		i;
	int		j;
	char	aux;
	char	*dquote;

	commands = 1;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] != '|' && input[i] != '\'' && input[i] != '\"'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			aux = input[i];
			while (1)
			{
				while (input[i] && input[i] != aux)
					i++;
				if (!input[i])
				{
					j = -1;
					while (++j < commands)
						printf("pipe ");
					dquote = ft_strjoin("\n", readline("dquote> ")); //proteger
					input = ft_freeandjoin(input, dquote); //proteger
				}
				else
					break ;
			}
		}
		else if (input[i] == '|')
		{
			commands++;
			i++;
		}
	}
	return (commands);
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

	while (1)
	{
		text_minishell = ft_get_text_minishell();
		input = readline(text_minishell);
		free(text_minishell);
			int i = 0;
			i = count_commands(input);
		add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		printf("Entrada: %s, comandos: %d\n", input, i);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	ft_printf("%s", &(HEADER));
	(void)argc;
	(void)argv;
	(void)env;
	ft_getline();
}
