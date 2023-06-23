/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:21 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/23 14:31:03 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_redir_and_tubes(t_data *data, int cont, int *tubes)
{
	int	fd;

	if (data->cmd[cont].input_type == 2)
	{
		fd = open(data->tmp_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(fd, data->cmd[cont].input, ft_strlen(data->cmd[cont].input));
		close(fd);
		fd = open(data->tmp_dir, O_RDONLY, 0644);
		check_close_and_dup_fd(fd, STDIN_FILENO);
	}
	else if (data->cmd[cont].input_type == 1)
	{
		fd = open(data->cmd[cont].input, O_RDONLY, 0644);
		check_close_and_dup_fd(fd, STDIN_FILENO);
	}
	else if (cont > 0)
		dup2(tubes[(cont - 1) * 2], STDIN_FILENO);
	if (data->cmd[cont].output_type == 1)
	{
		fd = open(data->cmd[cont].output, O_TRUNC | O_CREAT | O_RDWR, 0644);
		check_close_and_dup_fd(fd, STDOUT_FILENO);
	}
	else if (data->cmd[cont].output_type == 2)
	{
		fd = open(data->cmd[cont].output, O_CREAT | O_RDWR | O_APPEND, 0644);
		check_close_and_dup_fd(fd, STDOUT_FILENO);
	}
	else if (cont < data->n_commands - 1)
		dup2(tubes[cont * 2 + 1], STDOUT_FILENO);
	cont = -1;
	while (++cont < 2 * (data->n_commands - 1))
		close(tubes[cont]);
}

int	child(t_command *comando, t_data *data)
{
	if (!comando->path[0])
	{
		ft_putstr_fd(RED"minishell: ", 2);
		if (comando->opt[0])
			ft_putstr_fd(comando->opt[0], 2);
		ft_putstr_fd(": command not found\n"DEFAULT, 2);
		exit(127);
	}
	execve(comando->path, comando->opt, data->env);
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(comando->opt[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n"DEFAULT, 2);
	exit(errno);
}

int	*create_tube(t_data *data)
{
	int	*piping;
	int	i;

	piping = ft_calloc(sizeof(int), 2 * (data->n_commands - 1));
	i = 0;
	while (i < (data->n_commands - 1))
	{
		if (pipe(piping + i * 2) < 0)
			ft_perror(PIPE_ERROR);
		i++;
	}
	return (piping);
}

void	set_lastcmd(t_data *data, char	*new_dir)
{
	int		i;

	if (!new_dir || !new_dir[0])
		new_dir = data->builtins_dir;
	i = ft_getenv_int("_", data, 0, 1);
	if (i != -1)
	{
		ft_free_and_null((void **)&data->env[i]);
		data->env[i] = ft_strjoin("_=", new_dir);
		return;
	}
	data->env = chain_add_one(data->env, ft_strjoin("_=", new_dir));
}

void	child_generator(t_data *data)
{
	int		cont;
	int		*tubes;

	if (data->n_commands == 1)
		if (select_builtin(data, &data->cmd[0]) == 1)
			return set_lastcmd(data, data->cmd[0].path);
	tubes = create_tube(data);
	cont = -1;
	while (++cont < data->n_commands)
	{
		if (fork() == 0)
		{
			child_redir_and_tubes(data, cont, tubes);
			if (select_builtin(data, &data->cmd[cont]) == 0)
				child(&data->cmd[cont], data);
			exit (errno);
		}
		set_lastcmd(data, data->cmd[cont].path);
	}
	wait(&cont);
	data->lastcmd_value = WEXITSTATUS(cont);
	if (WIFSIGNALED(cont))
		data->lastcmd_value = WIFSIGNALED(cont);
	free_tubes(data, tubes);
	delete_file(data->tmp_dir);
}
