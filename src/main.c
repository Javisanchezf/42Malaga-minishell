/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:28:44 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/09 21:05:30 by javiersa         ###   ########.fr       */
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

void	ft_getline(void)
{
	char	*input;
	char	*text_minishell;

	while (1)
	{
		text_minishell = ft_get_text_minishell();
		input = readline(text_minishell);
		free(text_minishell);
		add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		printf("Entrada: %s\n", input);
		free(input);
	}
}

void	cleaner(t_data	*data, int i)
{
	while (data->env[++i].value)
		ft_free_and_null((void **)&data->env[i].value);
	ft_free_and_null((void **)&data->env);
}

// Add atexit(ft_leaks); in main and # include <stdlib.h>

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	// (void)env;
	atexit(ft_leaks);
	ft_printf("%s", &(HEADER));
	data.env = enviroment_extract(env, 0);
	int i = -1;
	while (data.env[++i].value != 0)
		ft_printf("Variable: %s Value: %s\n", data.env[i].value, data.env[i].variable);
	ft_getline();
	cleaner(&data, -1);
   return 0;
}
