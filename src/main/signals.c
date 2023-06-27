/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:47:30 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/27 14:20:02 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	(void) sig;
	g_data.lastcmd_value = 1;
	if (g_data.ctrl_c_flag == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("   ", 1);
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		printf("\033[K\n");
}

void	ctrl_d(char *input, t_data *data)
{
	char	path[2048];
	char	*aux;
	char	*text_minishell;

	if (!input)
	{
		if (getcwd(path, sizeof(path) - 1) == NULL)
			ft_strlcpy(path, "/minishell", 10);
		aux = ft_strrchr(path, '/') + 1;
		if (!aux[0])
		{
			aux[0] = '~';
			aux[1] = 0;
		}
		if (data->lastcmd_value == 0)
			aux = ft_strjoin("\033[32;1m➜ \033[36;1m", aux);
		else
			aux = ft_strjoin("\033[31;1m➜ \033[36;1m", aux);
		text_minishell = ft_strjoin(aux, " \033[0m");
		ft_free_and_null((void **)&aux);
		printf("\033[F\033[K"BLUE"%s"DEFAULT"exit\n", text_minishell);
		ft_free_and_null((void **)&text_minishell);
		clean_and_exit_success(data);
	}
}
