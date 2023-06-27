/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:57 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:07:23 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_data *data, int i)
{
	char	*prompt;
	char	*aux1;
	char	*aux2;

	aux1 = ft_strjoin(CYAN"heredoc \'", data->cmd[i].input);
	prompt = ft_strjoin(aux1, "\'> "DEFAULT);
	ft_free_and_null((void **)&aux1);
	aux1 = readline(prompt);
	ctrl_d(aux1, data);
	aux1 = dollar_heredoc(data, aux1);
	aux2 = ft_calloc(1, 1);
	while (ft_strncmp(aux1, data->cmd[i].input, \
	ft_strlen(data->cmd->input) + 1) != 0)
	{
		aux2 = ft_freeandjoin(aux2, aux1);
		aux2 = ft_freeandjoin(aux2, ft_strdup("\n\0"));
		aux1 = readline(prompt);
		ctrl_d(aux1, data);
		aux1 = dollar_heredoc(data, aux1);
	}
	ft_free_and_null((void **)&aux1);
	ft_free_and_null((void **)&data->cmd[i].input);
	ft_free_and_null((void **)&prompt);
	data->cmd[i].input = aux2;
}

void	input_parse(t_data *data, int i, int j, int cont)
{
	int		k;
	int		file;

	k = 0;
	while (data->cmd[i].opt[j][k] && (data->cmd[i].opt[j][k] == '<' \
	|| ft_isspace(data->cmd[i].opt[j][k])))
		k++;
	data->cmd[i].input_type = cont;
	ft_free_and_null((void **)&data->cmd[i].input);
	data->cmd[i].input = ft_substr(data->cmd[i].opt[j], k, \
	ft_strlen(data->cmd[i].opt[j]) - k);
	if (cont == 1 || cont == 3)
	{
		file = open(data->cmd[i].output, O_RDONLY, 0644);
		close(file);
		if (cont == 3)
		{
			data->cmd[i].input = ft_freeandjoin(\
data->cmd[i].input, ft_strdup("\n\0"));
			data->cmd[i].input_type = 3;
		}
	}
	else
		heredoc(data, i);
	data->cmd[i].opt = chain_delete_one(data->cmd[i].opt, j);
}

void	output_parse(t_data *data, int i, int j, int cont)
{
	int		k;
	int		file;

	k = 0;
	while (data->cmd[i].opt[j][k] && (data->cmd[i].opt[j][k] == '>' \
	|| ft_isspace(data->cmd[i].opt[j][k])))
		k++;
	data->cmd[i].output_type = cont;
	ft_free_and_null((void **)&data->cmd[i].output);
	data->cmd[i].output = ft_substr(data->cmd[i].opt[j], k, \
	ft_strlen(data->cmd[i].opt[j]) - k);
	if (cont == 1)
		file = open(data->cmd[i].output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		file = open(data->cmd[i].output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	close(file);
	data->cmd[i].opt = chain_delete_one(data->cmd[i].opt, j);
}

static int	parse_redirections_aux(t_data *data, int i, int j, char type)
{
	int	cont;

	cont = 0;
	while (data->cmd[i].opt[j][cont] && (data->cmd[i].opt[j][cont] == '<' || \
	data->cmd[i].opt[j][cont] == '>' || ft_isspace(data->cmd[i].opt[j][cont])))
		cont++;
	if (!data->cmd[i].opt[j][cont])
		return (ft_putstr_fd("\033[31;1mminishell: syntax error near\
 unexpected token\n\033[0m", 2), clean_commands(data), 1);
	cont = 0;
	while (data->cmd[i].opt[j][cont] == '<' || data->cmd[i].opt[j][cont] == '>')
	{
		if (data->cmd[i].opt[j][cont] != type)
			return (ft_putstr_fd("\033[31;1mminishell: syntax error near\
 unexpected token\n\033[0m", 2), clean_commands(data), 1);
		cont++;
	}
	if ((cont > 2 && type == '>') || (cont > 3 && type == '<'))
		return (ft_putstr_fd("\033[31;1mminishell: syntax error near\
 unexpected token\n\033[0m", 2), clean_commands(data), 1);
	if (type == '>')
		output_parse(data, i, j, cont);
	else if (type == '<')
		input_parse(data, i, j, cont);
	return (0);
}

int	parse_redirections(t_data *data, int i)
{
	int	j;

	data->cmd[i].input = ft_strdup("");
	data->cmd[i].output = ft_strdup("");
	data->cmd[i].input_type = 0;
	data->cmd[i].output_type = 0;
	j = 0;
	while (data->cmd[i].opt[j])
	{
		if (data->cmd[i].opt[j][0] == '<')
		{
			if (parse_redirections_aux(data, i, j, data->cmd[i].opt[j][0]) == 1)
				return (1);
		}
		else if (data->cmd[i].opt[j][0] == '>')
		{
			if (parse_redirections_aux(data, i, j, data->cmd[i].opt[j][0]) == 1)
				return (1);
		}
		else if (data->cmd[i].opt[j])
			j++;
	}
	return (0);
}
