/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:35 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/03 13:47:39 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *env, t_data *data, int start, int size)
{
	int		i;
	char	*aux;

	i = 0;
	while (data->env[i])
	{
		aux = ft_strchr(data->env[i], '=') + 1;
		if (size == aux - data->env[i] - 1)
			if (ft_strncmp(&env[start], data->env[i], size - 2) == 0)
				return (ft_strdup(aux));
		i++;
	}
	return (ft_strdup(""));
}

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
