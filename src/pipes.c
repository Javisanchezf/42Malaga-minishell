/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:47:21 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/20 19:12:03 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_redir_and_tubes(t_data *data, int cont, int *tubes)
{
	int	fd;

	if (data->cmd[cont].input_type == 1)
	{
		fd = open(data->cmd[cont].input, O_RDONLY, 0644);
		check_close_and_dup_fd(fd, STDIN_FILENO);
	}
	if (cont > 0)
		dup2(tubes[(cont - 1) * 2], STDIN_FILENO);
	if (cont < data->n_commands - 1)
		dup2(tubes[cont * 2 + 1], STDOUT_FILENO);
	if (data->cmd[cont].output_type == 1)
	{
		fd = open(data->cmd[cont].output, O_TRUNC | O_CREAT | O_RDWR, 0644);
		check_close_and_dup_fd(fd, STDOUT_FILENO);
	}
	if (data->cmd[cont].output_type == 2)
	{
		fd = open(data->cmd[cont].output, O_CREAT | O_RDWR | O_APPEND, 0644);
		check_close_and_dup_fd(fd, STDOUT_FILENO);
	}
	cont = -1;
	while (++cont < 2 * (data->n_commands - 1))
		close(tubes[cont]);
}

int	child(t_command *comando, t_data *data, int cont, int *tubes)
{
	if (!comando->path[0])
	{
		ft_putstr_fd(RED"minishell: ", 2);
		if (comando->opt[0])
			ft_putstr_fd(comando->opt[0], 2);
		ft_putstr_fd(": command not found\n"DEFAULT, 2);
		exit(127);
	}
	child_redir_and_tubes(data, cont, tubes);
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

void	child_generator(t_data *data)
{
	int		cont;
	pid_t	pid;
	int		*tubes;

	tubes = create_tube(data);
	cont = -1;
	//cree .tmp (data->tmp_dir)
	while (++cont < data->n_commands)
	{
		if (select_builtin(data, &data->cmd[cont], cont, tubes) == 0)
		{
			pid = fork();
			if (pid == 0)
				child(&data->cmd[cont], data, cont, tubes);
		}
	}
	//borrar .tmp
	free_tubes(data, tubes);
}

void	free_tubes(t_data *data, int *tubes)
{
	int		cont;
	char	*tmp;
	int		aux;

	close_tubes(data, tubes);
	cont = -1;
	while (++cont < data->n_commands)
	{
		waitpid(-1, &aux, 0);
		if (WIFEXITED(aux))
		{
			data->lastcmd_value = WEXITSTATUS(aux);
			if (ft_atoi(data->cmd[cont].input) == cont)
			{
				tmp = ft_strjoin("/Users/antdelga/Desktop/Minishell/",ft_itoa(cont));
				delete_file(tmp);
				free(tmp);
			}
		}
		if (ft_atoi(data->cmd[cont].input) == cont)
		{
			tmp = ft_strjoin("/Users/antdelga/Desktop/Minishell/",ft_itoa(cont));
			delete_file(tmp); // CAMBIAR AL MAC DE 42
			free(tmp);
		}
	}
	free(tubes);
}
