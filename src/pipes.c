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
	execve(comando->path, comando->opt, data->env);
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(comando->opt[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n"DEFAULT, 2);
	exit(errno);
}

void	create_tube(t_data *data, int cont)
{
	int	piping[2];

	dup2(data->tube.fd_in, 0);
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
	pid_t	pid;
	int		inp_fd;
	int		aux;

	inp_fd = dup(0);
	cont = -1;
	while (++cont < data->n_commands)
	{
		create_tube(data, cont);
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
	dup2(inp_fd, 0);
}
