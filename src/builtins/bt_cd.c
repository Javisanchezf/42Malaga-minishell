/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:36:42 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 13:56:47 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_cd_setnewpdw(t_data *data, char *type)
{
	char	*aux;
	char	aux2[2048];
	int		i;

	if (getcwd(aux2, 2048) == NULL)
		return (ft_perror("getcwd"));
	aux = ft_strjoin(type, "=");
	i = ft_getenv_int(type, data, 0, ft_strlen(type));
	if (i != -1)
	{
		ft_free_and_null((void **)&data->env[i]);
		data->env[i] = ft_strjoin(aux, aux2);
		ft_free_and_null((void **)&aux);
		return ;
	}
	data->env = chain_add_one(data->env, ft_strjoin(aux, aux2));
	ft_free_and_null((void **)&aux);
}

void	bt_cd(t_data *data, t_command *cmd)
{
	char	*aux;

	if (cmd->opt[1] && cmd->opt[2])
		return (errno = 1, ft_putstr_fd(RED"minishell: exit: \
too many arguments\n"DEFAULT, 2));
	bt_cd_setnewpdw(data, "OLDPWD");
	if (!cmd->opt[1])
	{
		aux = ft_getenv("HOME", data, 0, 4);
		if (chdir(aux) != 0)
			return (free(aux), ft_perror("cd"));
		free(aux);
	}
	else
		if (chdir(cmd->opt[1]) != 0)
			return (ft_perror("cd"));
	bt_cd_setnewpdw(data, "PWD");
}
