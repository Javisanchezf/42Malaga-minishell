/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:19 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/21 20:53:01 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_env(t_data *data)
{
	int	i;
	int	loc;

	loc = ft_getenv_int("_", data, 0, 1);
	if (loc != -1)
	{
		free(data->env[loc]);
		data->env[loc] = ft_strjoin("_=", "/usr/bin/env");
	}
	i = -1;
	while (data->env[++i])
		printf("%s\n", data->env[i]);
}

void	bt_export_aux(t_data *data, t_command *cmd)
{
	int	index;

	if (data->n_commands != 1)
		return ;
	index = 0;
	while (cmd->opt[++index])
	{
		if (cmd->opt[index][0] == '=')
			continue ;
		if (ft_strchr(cmd->opt[index], '='))
			bt_export(data, cmd, index);
	}
}

void	bt_export(t_data *data, t_command *cmd, int loc)
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

void	bt_unset_aux(t_data *data, t_command *cmd, char **new_env)
{
	int		index;
	int		loc;
	int		cont;
	char	**aux;
	int		offset;

	modify_values(&index, &loc, &offset, &cont);
	while (data->env[++index])
	{
		aux = ft_split(data->env[index], '=');
		while (cmd->opt[++loc])
		{
			if (ft_strncmp(aux[0], cmd->opt[loc], \
			choose_largest_string(cmd->opt[loc], aux[0])) == 0)
				cont = 1;
		}
		if (cont == 0)
			new_env[index - offset] = ft_strdup(data->env[index]);
		else
			offset++;
		restart_loop(&cont, &loc, aux);
	}
	ft_split_free(data->env);
	data->env = new_env;
}

void	bt_unset(t_data *data, t_command *cmd, int loc, int *cont)
{
	int		i;
	char	**aux;

	if (data->n_commands != 1)
		return ;
	i = -1;
	while (data->env[++i])
	{
		aux = ft_split(data->env[i], '=');
		if (ft_strncmp(aux[0], cmd->opt[loc], \
		choose_largest_string(cmd->opt[loc], aux[0])) == 0)
			(*cont)++;
		ft_split_free(aux);
	}
}
