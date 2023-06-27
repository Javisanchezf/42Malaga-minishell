/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:36:09 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 12:39:18 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_pwd(t_data *data, t_command *cmd)
{
	char	aux[2048];
	char	*aux2;
	int		fd;

	fd = 1;
	if (cmd->output_type == 1)
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->output_type == 2)
		fd = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (data->lastcmd_value = 1, ft_perror("open"));
	if (getcwd(aux, 2048) == NULL)
		return (ft_perror("pwd"));
	else
	{
		aux2 = ft_strjoin(aux, "\n");
		ft_putstr_fd(aux2, fd);
		free(aux2);
	}
}
