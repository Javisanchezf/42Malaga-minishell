/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:39:09 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:10:41 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_export_aux(t_data *data, t_command *cmd, int loc)
{
	char	*aux;
	int		i;
	char	**new_env;

	if (!cmd->opt[loc])
		return ;
	aux = ft_substr(cmd->opt[loc], 0, \
	ft_strchr(cmd->opt[loc], '=') + 1 - cmd->opt[loc]);
	if (ft_strchr(aux, '='))
	{
		i = 0;
		while (data->env[i] && \
		ft_strncmp(data->env[i], aux, ft_strlen(aux)) != 0)
			i++;
		if (data->env[i])
			return (free(data->env[i]), \
			data->env[i] = ft_strdup(cmd->opt[loc]), free(aux));
		new_env = ft_calloc(sizeof(char *), ft_split_size(data->env) + 2);
		i = -1;
		while (++i < ft_split_size(data->env))
				new_env[i] = ft_strdup(data->env[i]);
		new_env[i] = ft_strdup(cmd->opt[loc]);
		return (ft_split_free(data->env), data->env = new_env, free(aux));
	}
	free(aux);
}

void	bt_export(t_data *data, t_command *cmd)
{
	int	index;

	index = 0;
	if (!cmd->opt[1])
		return (bt_env(data, cmd));
	while (cmd->opt[++index])
	{
		if (cmd->opt[index][0] == '=')
			continue ;
		if (ft_strchr(cmd->opt[index], '='))
			bt_export_aux(data, cmd, index);
	}
}
