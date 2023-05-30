#include "minishell.h"

int	child(t_command *comando, t_data *data)
{
	execve(comando->path, comando->opt, data->env);
	perror(CMD_ERROR);
	exit(errno);
}

void	create_tube(t_data *data, int cont)
{
	int	piping[2];

	dup2(data->tube.fd_in, 0);
	// close(data->tube.fd_in);
	if (cont != data->n_commands - 1)
	{
		if (pipe(piping) == -1)
			perror(PIPE_ERROR);
		data->tube.fd_in = piping[0];
		data->tube.fd_out = piping[1];
	}
	else
		data->tube.fd_out = dup(data->tube.fd_t_out);
	dup2(data->tube.fd_out, 1);
	close(data->tube.fd_out);
}

void	child_generator(t_data *data)
{
	int		cont;
	pid_t	*pid;
	int		inp_fd;
	int 	aux;

	inp_fd = dup(0);
	cont = -1;
	pid = ft_calloc(sizeof(pid_t), data->n_commands);
	while (++cont < data->n_commands)
	{
		create_tube(data, cont);
		pid[cont] = fork();
		if (pid[cont] == 0)
			child(&data->cmd[cont], data);
		waitpid(pid[cont], &aux, 0);
		if (WIFEXITED(aux))
			data->lastcmd_value = WEXITSTATUS(aux);
	}
	free(pid);
	dup2(inp_fd, 0);
}
