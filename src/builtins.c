/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:37 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/25 19:31:07 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	bt_cd_setnewpdw(data, "OLDPWD");
	if (!cmd->opt[1])
	{
		aux = ft_getenv("ZDOTDIR", data, 0, 7);
		if (chdir(aux) != 0)
			return (free(aux), ft_perror("cd"));
		free(aux);
	}
	else
		if (chdir(cmd->opt[1]) != 0)
			return (ft_perror("cd"));
	bt_cd_setnewpdw(data, "PWD");
}

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

int	select_builtin(t_data *data, t_command *comando)
{
	if (ft_strncmp_null(comando->opt[0], "cd\0", 3) == 0)
		return (bt_cd(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "pwd\0", 4) == 0)
		return (bt_pwd(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "env\0", 4) == 0)
		return (bt_env(data), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "echo\0", 5) == 0)
		return (bt_echo(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "exit\0", 5) == 0)
		return (clean_and_exit_success(data), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "export\0", 7) == 0)
		return (bt_export_aux(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "unset\0", 6) == 0)
		return (bt_unset_init(data, comando), data->lastcmd_value = 0, 1);
	return (0);
}
