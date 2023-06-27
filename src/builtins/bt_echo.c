/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:35:32 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 12:40:27 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_echo(t_data *data, t_command *cmd)
{
	int	i;
	int	flag;
	int	fd;

	fd = STDOUT_FILENO;
	flag = 0;
	if (cmd->output_type == 1)
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->output_type == 2)
		fd = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (data->lastcmd_value = 1, ft_perror("open"));
	if (ft_strncmp_null(cmd->opt[1], "-n\0", 3) == 0)
		flag = 1;
	i = flag;
	while (cmd->opt[++i])
	{
		ft_putstr_fd(cmd->opt[i], fd);
		if (cmd->opt[i + 1])
			ft_putstr_fd(" ", fd);
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	if (fd != STDOUT_FILENO)
		close(fd);
}
