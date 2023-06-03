/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:37 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/03 13:50:09 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_cd_setnewpdw(t_data *data)
{
	int		i;
	char	aux2[2048];

	i = 0;
	while (ft_strncmp(data->env[i], "PWD=", 4) != 0)
		i++;
	if (data->env[i])
	{
		if (data->env[i + 1])
		{
			ft_free_and_null((void **)&data->env[i + 1]);
			data->env[i + 1] = ft_strdup(data->env[i]);
		}
		ft_free_and_null((void **)&data->env[i]);
		if (getcwd(aux2, 2048) == NULL)
			return (perror("PWD"));
		data->env[i] = ft_strjoin("PWD=", aux2);
	}
}

void	bt_cd(t_data *data, t_command *cmd)
{
	char	*aux;

	if (!cmd->opt[1])
	{
		aux = ft_getenv("ZDOTDIR", data, 0, 7);
		if (chdir(aux) != 0)
			return (free(aux), perror("cd"));
		free(aux);
	}
	else
		if (chdir(cmd->opt[1]) != 0)
			return (perror("cd"));
	bt_cd_setnewpdw(data);
}

void	bt_pwd(void)
{
	char	aux[2048];

	if (getcwd(aux, 2048) == NULL)
		return (perror("pwd"));
	else
		printf("%s\n", aux);
}

void	bt_echo_n(t_command *cmd)
{
	if (cmd->opt[2])
		printf("%s", cmd->opt[2]);
}

int	select_builtin(t_data *data, t_command *comando)
{	
	if (ft_strncmp(comando->opt[0], "cd", 2) == 0)
		return (bt_cd(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp(comando->opt[0], "pwd", 3) == 0)
		return (bt_pwd(), data->lastcmd_value = 0, 1);
	if (ft_strncmp(comando->opt[0], "env", 3) == 0)
		return (bt_env(data), data->lastcmd_value = 0, 1);
	if (ft_strncmp(comando->opt[0], "echo", 4) == 0 && \
	ft_strncmp(comando->opt[1], "-n", 2) == 0)
		return (bt_echo_n(comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp(comando->opt[0], "exit", 4) == 0)
		return (clean_and_exit_success(data), data->lastcmd_value = 0, 1);
	if (ft_strncmp(comando->opt[0], "export", 6) == 0)
		return (bt_export_aux(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp(comando->opt[0], "unset", 5) == 0)
		return (bt_unset_init(data, comando), data->lastcmd_value = 0, 1);
	return (0);
}
