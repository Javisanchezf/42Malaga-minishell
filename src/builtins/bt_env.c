/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:39:03 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 13:54:44 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_env(t_data *data, t_command *cmd)
{
	int	i;
	int	fd;

	if (cmd->opt[1])
		return (errno = 1, ft_putstr_fd(RED"minishell: env: \
too many arguments\n"DEFAULT, 2));
	fd = STDOUT_FILENO;
	if (cmd->output_type == 1)
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->output_type == 2)
		fd = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (data->lastcmd_value = 1, ft_perror("open"));
	i = -1;
	while (data->env[++i])
	{
		ft_putstr_fd(data->env[i], fd);
		ft_putstr_fd("\n", fd);
	}
	if (fd != STDOUT_FILENO)
		close(fd);
}
