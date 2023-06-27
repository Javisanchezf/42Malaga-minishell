/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:58:58 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:27:12 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**chain_add_one(char **array, char *new)
{
	int		size;
	char	**new_array;
	int		i;

	size = 0;
	size = ft_split_size(array);
	if (!new)
		return (array);
	new_array = (char **)ft_calloc((size + 2), sizeof(char *));
	if (!new_array)
		return (array);
	i = -1;
	while (++i < size)
		new_array[i] = array[i];
	new_array[i] = new;
	ft_free_and_null((void **)&array);
	return (new_array);
}

void	ft_usleep(void)
{
	int	i;

	i = -1;
	while (i < 42424242)
		i++;
}

void	ft_perror(const char *str)
{
	ft_putstr_fd(RED"minishell: ", 2);
	perror(str);
	ft_putstr_fd(DEFAULT, 2);
}

int	delete_file(char *filename)
{
	if (unlink(filename) == 0)
		return (0);
	else
		return (-1);
}

void	free_tubes(t_data *data, int *tubes)
{
	int		cont;
	int		aux;
	int		aux2;

	close_tubes(data, tubes);
	cont = -1;
	while (++cont < data->n_commands)
	{
		waitpid(-1, &aux, 0);
		aux2 = check_errno(aux);
		data->lastcmd_value = aux2;
	}
	free(tubes);
}
