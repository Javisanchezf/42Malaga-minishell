/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:48:21 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:07:17 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*dollar_normalize(char *input, char *line, int *i, t_data *data)
{
	char	*aux;
	int		j;

	(*i)++;
	if (ft_isspace(input[*i]) || !input[*i] || \
	input[*i] == '\'' || input[*i] == '\"')
	{
		aux = ft_strjoin(line, "$");
		return (free(line), aux);
	}
	else if (input[*i] == '?')
	{
		(*i)++;
		return (ft_freeandjoin(line, ft_itoa(data->lastcmd_value)));
	}
	else
	{
		j = *i;
		while (input[*i] && input[*i] != '$' && !ft_isspace(input[*i]) \
		&& input[*i] != '\'' && input[*i] != '\"')
			(*i)++;
		aux = ft_getenv(input, data, j, *i - j);
		return (ft_freeandjoin(line, aux));
	}
	return (line);
}

static char	*quotes_normalize(char *input, char *line, int *i, t_data *data)
{
	int		j;

	j = *i;
	if (input[*i] == '\'')
	{
		forward_quotes(input, i);
		line = ft_freeandjoin(line, ft_substr(input, j + 1, *i - j - 2));
	}
	else if (input[*i] == '\"')
	{
		(*i)++;
		while (input[*i] != '\"' && input[*i])
		{
			while (input[*i] == '$')
				line = dollar_normalize(input, line, i, data);
			if (input[*i] && input[*i] != '\"')
			{
				(*i)++;
				line = ft_freeandjoin(line, ft_substr(input, *i - 1, 1));
			}
		}
		(*i)++;
	}
	return (line);
}

char	**normalize_line(char **split, t_data *data, int i)
{
	int		j;
	char	*line;
	int		k;

	k = -1;
	while (split[++k])
	{
		i = 0;
		line = ft_calloc(1, sizeof(char));
		while (split[k][i])
		{
			j = i;
			while (split[k][i] && split[k][i] != '$' && \
			split[k][i] != '\'' && split[k][i] != '\"')
				i++;
			line = ft_freeandjoin(line, ft_substr(split[k], j, i - j));
			if (split[k][i] == '$')
				line = dollar_normalize(split[k], line, &i, data);
			else if (split[k][i] == '\'' || split[k][i] == '\"')
				line = quotes_normalize(split[k], line, &i, data);
		}
		ft_free_and_null((void **)&split[k]);
		split[k] = line;
	}
	return (split);
}

void	parse_line(char *input, t_data *data)
{
	char	**commands;
	char	*aux;
	int		i;

	commands = split_by_pipes(input, 0, 0);
	data->n_commands = ft_split_size(commands);
	data->cmd = ft_calloc(data->n_commands + 1, sizeof(t_command));
	aux = ft_getenv("PATH", data, 0, 4);
	data->rute = ft_split(aux, ':');
	ft_free_and_null((void **)&aux);
	i = 0;
	while (commands[i])
	{
		data->cmd[i].opt = \
		normalize_line(split_by_args(commands[i], 0, 0, 0), data, 0);
		if (parse_redirections(data, i) == 1)
			break ;
		data->cmd[i].path = ft_getcmd(data, data->cmd[i].opt[0]);
		i++;
	}
	ft_free_and_null((void **)&commands);
	ft_free_and_null((void **)&input);
}
