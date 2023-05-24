#include "minishell.h"

static void	add_history_plus(char *input)
{
	if (input && *input)
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static char	*get_line_fd1(t_data *data)
{
	char	*text_minishell;
	char	path[1024];
	char	*aux;

	if (getcwd(path, sizeof(path)) == NULL)
		exit(EXIT_FAILURE); // Poner ft_error y liberar lo que haga falta
	aux = ft_strrchr(path, '/') + 1;
	if (data->lastcmd_value == 0)
		aux = ft_strjoin("\033[32;1m➜ \033[36;1m", aux); // Proteger
	else
		aux = ft_strjoin("\033[31;1m➜ \033[36;1m", aux); // Proteger
	text_minishell = ft_strjoin(aux, " \033[0m"); // Proteger
	ft_free_and_null((void **)&aux);
	aux = readline(text_minishell);
	ft_free_and_null((void **)&text_minishell);
	return (aux);
}

static char	*check_pipe(char *input, int *i, int type)
{
	char	*dquote;

	if (type == 1)
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		if (input[*i] == '|')
		{
			add_history_plus(input);
			ft_putstr_fd("\033[31;1mminishell: syntax error \
near unexpected toke '|'.\n\033[0m", 2);
		}
		else if (type == 1 && !input[*i])
		{
			dquote = ft_strjoin(input, " ");
			free(input);
			input = readline("\033[36;1m> \033[0m");
			return (ft_freeandjoin(dquote, input));
		}
		ft_free_and_null((void **)&input);
		return (NULL);
	}
	return (input);
}

static int	check_quotes(char *input, int *i)
{
	char	aux;

	aux = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != aux)
		(*i)++;
	if (!input[*i])
	{
		add_history_plus(input);
		ft_putstr_fd("\033[31;1mminishell: syntax \
error due to unclosed quotes.\n\033[0m", 2);
		ft_free_and_null((void **)&input);
		return (1);
	}
	(*i)++;
	return (0);
}

void	ctrl_d(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 2);
		exit (0);
	}
	// return (1);
}

char	*readlineplus(t_data *data)
{
	char	*input;
	int		i;

	i = 0;
	input = get_line_fd1(data);
	ctrl_d(input);
	if (!input || !check_pipe(input, &i, 0))
		return (NULL);
	while (input[i])
	{
		while (input[i] && (input[i] != '\'' && \
		input[i] != '\"' && input[i] != '|'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			if (check_quotes(input, &i) == 1)
				return (NULL);
		if (input[i] == '|')
		{
			input = check_pipe(input, &i, 1);
			if (!input)
				return (NULL);
		}
	}
	add_history_plus(input);
	return (input);
}
