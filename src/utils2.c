/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:58:58 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/20 19:54:05 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
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

	close_tubes(data, tubes);
	cont = -1;
	while (++cont < data->n_commands)
	{
		waitpid(-1, &aux, 0);
		if (WIFEXITED(aux))
			data->lastcmd_value = WEXITSTATUS(aux);
	}
	free(tubes);
}
