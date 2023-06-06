/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:21 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/06 21:03:48 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_strncmp(comando->opt[0], "cat", 3) && \
	!comando->opt[1] && comando->input_type == 2)
		exit(0);
	execve(comando->path, comando->opt, data->env);
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(comando->opt[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n"DEFAULT, 2);
	exit(errno);
}

void	create_tube(t_data *data, t_command *cmd, int cont)
{
	int	piping[2];

	if (cmd->input_type == 0)
		dup2(data->tube.fd_in, 0);
	if (cont != data->n_commands - 1)
	{
		if (pipe(piping) == -1)
			perror(PIPE_ERROR);
		if (cmd->input_type == 0)
			data->tube.fd_in = piping[0];
		if (cmd->output_type == 0)
			data->tube.fd_out = piping[1];
	}
	else if (cmd->output_type == 0)
		data->tube.fd_out = dup(data->tube.fd_t_out);
	if (cmd->output_type == 0)
	{
		dup2(data->tube.fd_out, 1);
		close(data->tube.fd_out);
	}
}

int	redir_check(t_data *data, t_command *cmd, int i)
{
	if (cmd->input_type == 1)
	{
		data->tube.fd_in = open(data->cmd[i].input, O_RDONLY, 0644);
		if (data->tube.fd_in == -1)
			return (perror("Error reading file\n"), 0);
		dup2(data->tube.fd_in, 0);
		if (i != data->n_commands - 1)
			data->tube.fd_in = data->tube.piping[0];
	}
	if (cmd->output_type == 0)
		return (1);
	if (cmd->output_type == 1)
		data->tube.fd_out = open(data->cmd[i].output, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else if (cmd->output_type == 2)
		data->tube.fd_out = open(data->cmd[i].output, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->tube.fd_out == -1)
		return (0);
	if (i != data->n_commands - 1)
		data->tube.fd_out = data->tube.piping[1];
	dup2(data->tube.fd_out, 1);
	close(data->tube.fd_out);
	return (1);
}


void	child_generator(t_data *data)
{
	int		cont;
	pid_t	pid;
	int		fds[2];
	int		aux;

	fds[0] = dup(0);
	fds[1] = dup(1);
	cont = -1;
	while (++cont < data->n_commands)
	{	
		create_tube(data, data->cmd, cont);
		if (data->cmd[cont].input_type != 0 || data->cmd[cont].output_type != 0)
			if (!redir_check(data, &data->cmd[cont], cont))
				break ;
		if (data->n_commands == 1)
			if (select_builtin(data, &data->cmd[cont]) == 1)
				continue ;
		pid = fork();
		if (pid == 0)
			child(&data->cmd[cont], data);
		waitpid(-1, &aux, 0);
		if (WIFEXITED(aux))
			data->lastcmd_value = WEXITSTATUS(aux);
	}
	reset_fd(fds);
}
