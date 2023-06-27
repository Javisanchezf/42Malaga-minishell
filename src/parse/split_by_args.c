/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:46:24 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:07:35 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_separator_char(char c)
{
	return (c == '<' || c == '>' || ft_isspace(c) || c == 0);
}

static void	forward_operators(char *input, int *i)
{
	while (input[*i] && (input[*i] == '<' || input[*i] == '>'))
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '\"')
		forward_quotes(input, i);
	else
		while (!is_separator_char(input[*i]))
			(*i)++;
}

static int	ft_size_split_by_args(char *input, int i, int n)
{
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			forward_quotes(input, &i);
			n++;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			forward_operators(input, &i);
			n++;
		}
		else if (!is_separator_char(input[i]))
		{
			n++;
			while (!is_separator_char(input[i]))
				i++;
		}
	}
	return (n);
}

static char	**ft_splitfree(char **split, int n)
{
	while (n-- > 0)
		ft_free_and_null((void **)&split[n]);
	ft_free_and_null((void **)&split);
	return (0);
}

char	**split_by_args(char *input, int i, int j, int size_split)
{
	char	**split;
	int		n;

	n = -1;
	size_split = ft_size_split_by_args(input, 0, 0);
	split = (char **)ft_calloc((size_split + 1), sizeof(char *));
	if (!split || !input)
		return (0);
	while (input[i] && ++n < size_split)
	{
		while (ft_isspace(input[i]))
			i++;
		j = i;
		if (input[i] == '\'' || input[i] == '\"')
			forward_quotes(input, &i);
		else if (input[i] == '<' || input[i] == '>')
			forward_operators(input, &i);
		if (!is_separator_char(input[i]))
			while (!is_separator_char(input[i]))
				i++;
		split[n] = ft_substr(input, j, i - j);
		if (!split[n])
			return (ft_splitfree(split, n));
	}
	return (split);
}
