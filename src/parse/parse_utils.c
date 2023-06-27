/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:35 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:07:28 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	forward_quotes(char *input, int *i)
{
	char	aux;

	aux = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != aux)
		(*i)++;
	(*i)++;
}

char	**chain_delete_one(char **array, int index)
{
	int		size;
	char	**new_array;
	int		i;
	int		j;

	size = 0;
	size = ft_split_size(array);
	if (index < 0 || index >= size)
		return (array);
	new_array = (char **)ft_calloc((size), sizeof(char *));
	if (!new_array)
		return (array);
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i != index)
		{
			new_array[j] = array[i];
			j++;
		}
	}
	ft_free_and_null((void **)&array[index]);
	ft_free_and_null((void **)&array);
	return (new_array);
}

static char	*conditions_heredoc(t_data *data, char *str, char *str_new, int *i)
{
	int	j;

	if (ft_isspace(str[*i]) || !str[*i] || str[*i] == '\'' || str[*i] == '\"')
	{
		str_new = ft_freeandjoin(str_new, ft_strdup("$\0"));
		(*i)++;
	}
	else if (str[*i] == '?')
	{
		str_new = ft_freeandjoin(str_new, ft_itoa(data->lastcmd_value));
		(*i)++;
	}
	else if (str[*i])
	{
		j = *i;
		while (str[*i] && str[*i] != '$' && str[*i] != '\'' \
		&& str[*i] != '\"' && !ft_isspace(str[*i]))
			(*i)++;
		str_new = ft_freeandjoin(str_new, ft_getenv(str, data, j, *i - j));
	}
	return (str_new);
}

char	*dollar_heredoc(t_data *data, char *str)
{
	int		i;
	char	*str_new;

	i = -1;
	str_new = ft_calloc(1, 1);
	while (str[++i])
	{
		while (str[i] == '$')
		{
			i++;
			str_new = conditions_heredoc(data, str, str_new, &i);
		}
		str_new = ft_freeandjoin(str_new, ft_substr(str, i, 1));
	}
	ft_free_and_null((void **)&str);
	return (str_new);
}

char	*ft_getenv(char *env, t_data *data, int start, int size)
{
	int		i;
	char	*aux;

	i = 0;
	while (data->env[i])
	{
		aux = ft_strchr(data->env[i], '=') + 1;
		if (size == aux - data->env[i] - 1)
			if (ft_strncmp(&env[start], data->env[i], size) == 0)
				return (ft_strdup(aux));
		i++;
	}
	return (ft_strdup(""));
}
