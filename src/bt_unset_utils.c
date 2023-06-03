/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:22:11 by antdelga          #+#    #+#             */
/*   Updated: 2023/06/03 13:52:34 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_largest_string(char *a, char *b)
{
	if (ft_strlen(a) >= ft_strlen(b))
		return (ft_strlen(a));
	else
		return (ft_strlen(b));
}

void	modify_values(int *index, int *loc, int *offset, int *cont)
{
	(*index) = -1;
	(*loc) = 0;
	(*offset) = 0;
	(*cont) = 0;
}

void	restart_loop(int *cont, int *loc, char **aux)
{
	(*cont) = 0;
	(*loc) = 0;
	ft_split_free(aux);
}

void	bt_unset_init(t_data *data, t_command *cmd)
{
	int		index;
	int		cont;
	char	**new_env;

	if (!cmd->opt[1])
		return ;
	index = 0;
	cont = 0;
	while (cmd->opt[++index])
		bt_unset(data, cmd, index, &cont);
	new_env = ft_calloc(sizeof(char *), ft_split_size(data->env) - cont + 1);
	bt_unset_aux(data, cmd, new_env);
}
