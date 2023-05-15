#include "../inc/minishell.h"

void	child(t_command *cmd)
{
	if (!cmd->cmd)
	{
		free_matrix(cmd->opt);
		free(cmd->cmd);
		err_msg_exit(CMD_ERROR);
	}
	check_awk(cmd);
	execve(cmd->cmd, cmd->opt, cmd->envp);
}

void	create_tube(t_pipe *link, int cont)
{
	int	piping[2];

	dup2(link->fd_in, 0);
	close(link->fd_in);
	if (cont != link->cmd_count - 1)
	{
		if (pipe(piping) == -1)
			err_msg(PIPE_ERROR);
		link->fd_in = piping[0];
		link->fd_out = piping[1];
	}
	else
		link->fd_out = dup(link->fd_t_out);
	dup2(link->fd_out, 1);
	close(link->fd_out);
}

void	child_generator(t_pipe *link, t_command *cmd)
{
	int		cont;
	pid_t	pid[3];
	int		to_wait;
	int		inp_fd;

	inp_fd = dup(0);
	cont = -1;
	while (++cont < link->cmd_count)
	{
		create_tube(link, cont);
		pid[cont] = fork();
		if (!pid[cont])
			child(&cmd[cont]);
		waitpid(pid[cont], &to_wait, 0);
		free_matrix(cmd[cont].opt);
	}
	free(cmd);
	dup2(inp_fd, 0);
}
