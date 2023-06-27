/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:27:36 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:15:35 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_getenv_int(char *env, t_data *data, int start, int size)
{
	int		i;
	char	*aux;

	i = -1;
	while (data->env[++i])
	{
		aux = ft_strchr(data->env[i], '=') + 1;
		if (size == aux - data->env[i] - 1)
			if (ft_strncmp(&env[start], data->env[i], size) == 0)
				return (i);
	}
	return (-1);
}

char	*ft_getcmd_builtin(t_data *data, char *cmd)
{
	if (ft_strncmp_null(cmd, "cd\0", 3) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/cd"));
	if (ft_strncmp_null(cmd, "pwd\0", 4) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/pwd"));
	if (ft_strncmp_null(cmd, "env\0", 4) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/env"));
	if (ft_strncmp_null(cmd, "echo\0", 5) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/echo"));
	if (ft_strncmp_null(cmd, "exit\0", 5) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/exit"));
	if (ft_strncmp_null(cmd, "export\0", 7) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/export"));
	if (ft_strncmp_null(cmd, "unset\0", 6) == 0)
		return (ft_strjoin(data->builtins_dir, "/src/builtins/unset"));
	return (NULL);
}

char	*ft_getcmd(t_data *data, char *cmd)
{
	int		i;
	char	*aux;
	char	*c;

	i = 0;
	aux = ft_getcmd_builtin(data, cmd);
	if (aux)
		return (aux);
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
