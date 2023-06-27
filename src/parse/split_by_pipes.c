/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:27:24 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:07:38 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_size_split_by_pipes(char *input)
{
	int	commands;
	int	i;

	i = 0;
	commands = 1;
	while (input[i])
	{
		while (input[i] && (input[i] != '|' && \
		input[i] != '\'' && input[i] != '\"'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			forward_quotes(input, &i);
		if (input[i] == '|')
		{
			commands++;
			i++;
		}
	}
	return (commands);
}

char	**split_by_pipes(char *input, int size_split, int i)
{
	char	**split;
	int		n;

	size_split = ft_size_split_by_pipes(input);
	split = (char **)ft_calloc((size_split + 1), sizeof(char *));
	if (!split || !input)
		return (NULL);
	split[0] = &input[0];
	n = 1;
	while (n < size_split)
	{
		while (input[i] && input[i] != '|' && \
		input[i] != '\'' && input[i] != '\"')
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			forward_quotes(input, &i);
		if (input[i] == '|')
		{
			input[i] = 0;
			i++;
			split[n] = &input[i];
			n++;
		}
	}
	return (split);
}
