/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:27:36 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/08 20:02:54 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp_null(const char *s1, const char *s2, size_t n)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
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
