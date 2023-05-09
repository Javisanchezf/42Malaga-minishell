/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:36:25 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/09 21:21:52 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*enviroment_extract(char **env, int i)
{
	t_env	*enviroment;
	char	*aux;

	while (env[i])
		i++;
	enviroment = ft_calloc(i + 1, sizeof(t_env));
	i = -1;
	while (env[++i])
	{
		aux = ft_strchr(env[i], '=');
		if (aux == NULL)
			printf("WTF\n"); //Gestionar el error
		enviroment[i].value = ft_substr(env[i], 0, aux - env[i]);
		enviroment[i].variable = getenv(enviroment[i].value); //proteger si es null
	}
	return (enviroment);
}
