/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:57:24 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/25 18:51:18 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_close_and_dup_fd(int fd, int id)
{
	if (fd < 0)
	{
		ft_perror("Error when opening file");
		exit(1);
	}
	if (dup2(fd, id) < 0)
	{
		ft_perror("Error when redirecting");
		exit(1);
	}
	close(fd);
}

void	close_tubes(t_data *data, int *tubes)
{
	int	cont;

	cont = -1;
	while (++cont < 2 * (data->n_commands - 1))
		close(tubes[cont]);
}

void	sub_dup2(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);
}

void	set_lastcmd(t_data *data, char	**opt)
{
	int	i;
	int	select;

	select = -1;
	while (opt[++select])
		;
	select--;
	i = ft_getenv_int("_", data, 0, 1);
	if (i != -1)
	{
		ft_free_and_null((void **)&data->env[i]);
		data->env[i] = ft_strjoin("_=", opt[select]);
		return ;
	}
	data->env = chain_add_one(data->env, ft_strjoin("_=", opt[select]));
}

void	check_errno(int	*num, int cont)
{
	*num = WEXITSTATUS(cont);
	if (WIFSIGNALED(cont))
		*num = WIFSIGNALED(cont);
	if (*num == 22)
		*num = 0;
}

/* void	set_lastcmd(t_data *data, char	*new_dir)
{
	int		i;

	if (!new_dir || !new_dir[0])
		new_dir = data->builtins_dir;
	i = ft_getenv_int("_", data, 0, 1);
	if (i != -1)
	{
		ft_free_and_null((void **)&data->env[i]);
		data->env[i] = ft_strjoin("_=", new_dir);
		return ;
	}
	data->env = chain_add_one(data->env, ft_strjoin("_=", new_dir));
} */
