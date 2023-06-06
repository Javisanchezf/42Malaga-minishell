/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:27:36 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/06 17:58:51 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	ft_strncmp_null(const char *s1, const char *s2, size_t n)
{
	if (ft_strlen(s1) < (int)n || ft_strlen(s2) < (int)n)
		return (1);
	else
		return (ft_strncmp(s1, s2, n));
}

void	sub_dup2(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);
}

char	*ft_getcmd(t_data *data, char *cmd)
{
	int		i;
	char	*aux;
	char	*c;

	i = 0;
	if (!cmd)
		return (ft_strdup(""));
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (data->rute[i])
	{
		aux = ft_strjoin(data->rute[i], "/");
		c = ft_strjoin(aux, cmd);
		free(aux);
		if (access(c, X_OK) == 0)
			return (c);
		free(c);
		i++;
	}
	return (ft_strdup(""));
}

void	reset_fd(int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
}

void	print_fds(t_data *data, t_command *cmd)
{
	printf("FD OUT: %d\n", data->tube.fd_out);
	printf("TUBE OUT: %d\n", data->tube.piping[1]);
	printf("FD IN: %d\n", data->tube.fd_in);
	printf("TUBE IN: %d\n", data->tube.piping[0]);
	printf("OUTPUT TYPE: %d\n", cmd->output_type);
	printf("INPUT TYPE: %d\n\n", cmd->input_type);
}
