/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:49:05 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/13 17:45:19 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	enviroment_extract(char **env, t_data *data)
{
	int		i;
	int		size;

	i = 0;
	while (env[i])
		i++;
	data->env = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!data->env)
		ft_error(RED"Problem allocating memory.\n"DEFAULT, 0);
	i = -1;
	while (env[++i])
	{
		size = ft_strlen(env[i]);
		data->env[i] = ft_calloc(size + 1, sizeof(char));
		ft_strlcpy(data->env[i], env[i], size + 1);
	}
}

static void	init_data(t_data *data, char **env, int argc, char **argv)
{
	if (write(1, NULL, 0) == -1 || read(0, NULL, 0) == -1)
	{
		ft_perror("Error: No write/read permissions on main fd.\n");
		exit(EXIT_FAILURE);
	}
	ft_printf("%s", &(HEADER));
	data->n_commands = 0;
	enviroment_extract(env, data);
	data->lastcmd_value = 0;
	signal(SIGINT, sigint_handler);
	data->tube.fd_in = dup(0);
	data->tube.fd_t_in = dup(0);
	data->tube.fd_t_out = dup(1);
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;

	// atexit(ft_leaks);
	init_data(&data, env, argc, argv);
	while (1)
	{
		input = readlineplus(&data);
		if (input)
		{
			parse_line(input, &data);
			if (data.n_commands != 0)
				child_generator(&data);
			clean_commands(&data);
		}
		// ft_leaks();
	}
	clean_and_exit_success(&data);
}
