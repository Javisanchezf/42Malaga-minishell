/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:39:20 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:44:55 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_unset(t_data *data, t_command *cmd)
{
	int	i;
	int	aux;

	i = 0;
	while (cmd->opt[++i])
	{
		aux = ft_getenv_int(cmd->opt[i], data, 0, ft_strlen(cmd->opt[i]));
		if (aux != -1)
			data->env = chain_delete_one(data->env, aux);
	}
}
