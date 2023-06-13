/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:57:24 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/08 20:00:11 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_close_and_dup_fd(int fd, int id)
{
	if (fd < 0)
	{
		perror("Error when opening file");
		exit(1);
	}
	if (dup2(fd, id) < 0)
	{
		perror("Error when redirecting");
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
