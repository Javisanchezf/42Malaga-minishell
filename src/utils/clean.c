/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:49:18 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:21:39 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_commands(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_commands)
	{
		ft_split_free(data->cmd[i].opt);
		ft_free_and_null((void **)&data->cmd[i].path);
		ft_free_and_null((void **)&data->cmd[i].input);
		ft_free_and_null((void **)&data->cmd[i].output);
	}
	if (data->n_commands != 0)
	{
		ft_free_and_null((void **)&data->cmd);
		ft_split_free(data->rute);
	}
	data->n_commands = 0;
}

void	clean_and_exit_success(t_data *data)
{
	clean_commands(data);
	ft_split_free(data->env);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

void	clean_and_exit_fail(t_data *data)
{
	clean_commands(data);
	ft_split_free(data->env);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
