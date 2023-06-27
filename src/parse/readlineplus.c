/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlineplus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:10 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:07:31 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_history_plus(char *input)
{
	if (input && *input)
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static char	*get_line_fd1(t_data *data)
{
	char	*text_minishell;
	char	path[2048];
	char	*aux;

	if (getcwd(path, sizeof(path) - 1) == NULL)
		ft_strlcpy(path, "/minishell", 10);
	aux = ft_strrchr(path, '/') + 1;
	if (!aux[0])
	{
		aux[0] = '~';
		aux[1] = 0;
	}
	if (data->lastcmd_value == 0)
		aux = ft_strjoin(GREEN"➜ "CYAN, aux);
	else
		aux = ft_strjoin(RED"➜ "CYAN, aux);
	text_minishell = ft_strjoin(aux, " "DEFAULT);
	ft_free_and_null((void **)&aux);
	aux = readline(text_minishell);
	ft_free_and_null((void **)&text_minishell);
	ctrl_d(aux, data);
	return (aux);
}

static char	*check_pipe(char *input, int *i, int type, t_data *data)
{
	char	*dquote;

	if (type == 1)
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		if (input[*i] == '|')
		{
			add_history_plus(input);
			ft_putstr_fd(RED"minishell: syntax error \
near unexpected toke '|'\n"DEFAULT, 2);
		}
		else if (type == 1 && !input[*i])
		{
			dquote = ft_strjoin(input, " ");
			free(input);
			input = readline(CYAN"pipe > "DEFAULT);
			ctrl_d(input, data);
			return (ft_freeandjoin(dquote, input));
		}
		return (ft_free_and_null((void **)&input), NULL);
	}
	return (input);
}

static int	check_quotes(char *input, int *i)
{
	char	aux;

	aux = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != aux)
		(*i)++;
	if (!input[*i])
	{
		add_history_plus(input);
		ft_putstr_fd(RED"minishell: syntax \
error due to unclosed quotes\n"DEFAULT, 2);
		ft_free_and_null((void **)&input);
		return (1);
	}
	(*i)++;
	return (0);
}

char	*readlineplus(t_data *data)
{
	char	*input;
	int		i;

	i = 0;
	input = get_line_fd1(data);
	if (!input || !check_pipe(input, &i, 0, data))
		return (NULL);
	while (input[i])
	{
		while (input[i] && (input[i] != '\'' && \
		input[i] != '\"' && input[i] != '|'))
			i++;
		if (input[i] == '|')
		{
			input = check_pipe(input, &i, 1, data);
			if (!input)
				return (NULL);
		}
		else if (input[i] == '\'' || input[i] == '\"')
			if (check_quotes(input, &i) == 1)
				return (NULL);
	}
	add_history_plus(input);
	return (input);
}
