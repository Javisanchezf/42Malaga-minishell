/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:37 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/21 21:27:38 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	bt_cd_setnewpdw(t_data *data)
// {
// 	int		i;
// 	char	aux2[2048];
// 	char	**aux;

// 	i = 0;
// 	while (ft_strncmp(data->env[i], "PWD=", 4) != 0)
// 		i++;
// 	if (data->env[i])
// 	{
// 		if (data->env[i + 1])
// 		{
// 			aux = ft_split(data->env[i], '=');
// 			if (aux[1])
// 			{
// 				ft_free_and_null((void **)&data->env[i + 1]);
// 				data->env[i + 1] = ft_strjoin("OLDPWD=", aux[1]);
// 				ft_split_free(aux);
// 			}
// 		}
// 		ft_free_and_null((void **)&data->env[i]);
// 		if (getcwd(aux2, 2048) == NULL)
// 			return (ft_perror("PWD"));
// 		data->env[i] = ft_strjoin("PWD=", aux2);
// 	}
// }

char	**chain_add_one(char **array, char *new)
{
	int		size;
	char	**new_array;
	int		i;

	size = 0;
	size = ft_split_size(array);
	if (!new)
		return (array);
	new_array = (char **)ft_calloc((size + 1), sizeof(char *));
	if (!new_array)
		return (array);
	i = -1;
	while (++i < size)
		new_array[i] = array[i];
	new_array[i] = new;
	ft_free_and_null((void **)&array);
	return (new_array);
}

void	bt_cd(t_data *data, t_command *cmd)
{
	char	*aux;
	// char	aux2[1024];
	int		i;

	printf("asf");
	i = ft_getenv_int("OLDPWD", data, 0, 6);
	// if (i != -1)
	// 	data->env = chain_delete_one(data->env, i);
	// getcwd(aux2, 1023);
	// data->env = chain_add_one(data->env, ft_strjoin("OLDPWD=", aux2));
	printf("a");
	if (data->n_commands != 1)
		return ;
	if (!cmd->opt[1])
	{
		aux = ft_getenv("ZDOTDIR", data, 0, 7);
		if (chdir(aux) != 0)
			return (free(aux), perror("cd"));
		free(aux);
	}
	else
		if (chdir(cmd->opt[1]) != 0)
			return (ft_perror("cd"));
	// i = ft_getenv_int("PWD", data, 0, 6);
	// if (i != -1)
	// 	data->env = chain_delete_one(data->env, i);
	// getcwd(aux2, 1023);
	// data->env = chain_add_one(data->env, ft_strjoin("PWD=", aux2));
	// bt_cd_setnewpdw(data);
}

void	bt_pwd(t_data *data, t_command *cmd)
{
	char	aux[2048];
	char	*aux2;
	int		fd;

	fd = 0;
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

void	bt_echo_n(t_data *data, t_command *cmd)
{
	int	i;
	int	fd;

	fd = 0;
	if (cmd->output_type == 1)
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->output_type == 2)
		fd = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (data->lastcmd_value = 1, ft_perror("open"));
	i = 1;
	while (cmd->opt[++i])
	{
		ft_putstr_fd(cmd->opt[i], fd);
		if (cmd->opt[i + 1])
			ft_putstr_fd(" ", fd);
	}
	if (fd != 0)
		close(fd);
	data->lastcmd_value = 0;
}

int	select_builtin(t_data *data, t_command *comando, int cont, int *tubes)
{	
	(void) cont;
	(void) tubes;
	if (ft_strncmp_null(comando->opt[0], "cd", 2) == 0)
		return (bt_cd(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "pwd", 3) == 0)
		return (bt_pwd(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "env", 3) == 0)
		return (bt_env(data), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "echo", 4) == 0 && \
	ft_strncmp_null(comando->opt[1], "-n", 2) == 0)
		return (bt_echo_n(data, comando), 1);
	if (ft_strncmp_null(comando->opt[0], "exit", 4) == 0)
		return (clean_and_exit_success(data), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "export", 6) == 0)
		return (bt_export_aux(data, comando), data->lastcmd_value = 0, 1);
	if (ft_strncmp_null(comando->opt[0], "unset", 5) == 0)
		return (bt_unset_init(data, comando), data->lastcmd_value = 0, 1);
	return (0);
}
