/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:19 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/26 13:52:03 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_env(t_data *data, t_command *cmd)
{
	int	i;
	int	fd;

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

void	bt_export_aux(t_data *data, t_command *cmd)
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
