/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:58:58 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/07 19:05:04 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_perror(const char *str)
{
	ft_putstr_fd(RED"minishell: ", 2);
	perror(str);
	ft_putstr_fd(DEFAULT, 2);
}
