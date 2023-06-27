/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:37 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/27 14:16:21 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	select_builtin(t_data *data, t_command *cmd)
{
	if (ft_strncmp_null(cmd->opt[0], "cd\0", 3) == 0)
		return (bt_cd(data, cmd), 1);
	if (ft_strncmp_null(cmd->opt[0], "pwd\0", 4) == 0)
		return (bt_pwd(data, cmd), 1);
	if (ft_strncmp_null(cmd->opt[0], "env\0", 4) == 0)
		return (bt_env(data, cmd), 1);
	if (ft_strncmp_null(cmd->opt[0], "echo\0", 5) == 0)
		return (bt_echo(data, cmd), 1);
	if (ft_strncmp_null(cmd->opt[0], "exit\0", 5) == 0)
		return (bt_exit(data, cmd), 1);
	if (ft_strncmp_null(cmd->opt[0], "export\0", 7) == 0)
		return (bt_export(data, cmd), 1);
	if (ft_strncmp_null(cmd->opt[0], "unset\0", 6) == 0)
		return (bt_unset(data, cmd), 1);
	return (0);
}
