/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:57:24 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/22 20:52:48 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_close_and_dup_fd(int fd, int id)
{
	if (fd < 0)
	{
		ft_perror("Error when opening file");
		exit(1);
	}
	if (dup2(fd, id) < 0)
	{
		ft_perror("Error when redirecting");
		exit(1);
	}
	close(fd);
}

void	close_tubes(t_data *data, int *tubes)
{
	int	cont;

	cont = -1;
	while (++cont < 2 * (data->n_commands - 1))
		close(tubes[cont]);
}
