/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:38:44 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 13:49:39 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_exit(t_data *data, t_command *cmd)
{
	int	i;
	int	n_exit;

	i = -1;
	n_exit = 0;
	if (cmd->opt[1] && cmd->opt[2])
		return (errno = 1, ft_putstr_fd(RED"minishell: exit: \
too many arguments\n"DEFAULT, 2));
	else if (cmd->opt[1])
	{
		while (cmd->opt[1][++i])
			if (!ft_isdigit(cmd->opt[1][i]))
				return (errno = 255, ft_putstr_fd(RED"minishell: exit: numeric\
 argument required\n"DEFAULT, 2));
		n_exit = ft_atoi(cmd->opt[1]);
	}
	clean_commands(data);
	ft_split_free(data->env);
	rl_clear_history();
	exit (n_exit);
}
