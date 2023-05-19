#include "minishell.h"

// static char	*special_chars(char *input, int *i)
// {
// 	char	aux;
// 	char	*dquote;

// 	aux = input[*i];
// 	(*i)++;
// 	while (1)
// 	{
// 		while (input[*i] && input[*i] != aux)
// 			(*i)++;
// 		if (!input[*i])
// 		{
// 			dquote = ft_strjoin(input, "\n"); // proteger
// 			free(input);
// 			input = dquote;
// 			dquote = readline("\033[36;1m> \033[0m"); //proteger
// 			input = ft_freeandjoin(input, dquote); //proteger
// 		}
// 		else
// 			break ;
// 	}
// 	(*i)++;
// 	return (input);
// }

static void	add_history_plus(char *input)
{
	add_history(input);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static char	*get_line_fd1(void)
{
	char	*text_minishell;
	char	path[1024];
	char	*aux;

	if (getcwd(path, sizeof(path)) == NULL)
		exit(EXIT_FAILURE); // Poner ft_error y liberar lo que haga falta
	aux = ft_strrchr(path, '/') + 1;
	aux = ft_strjoin("\033[36;1m", aux); // Proteger
	text_minishell = ft_strjoin(aux, " -> \033[0m"); // Proteger
	ft_free_and_null((void **)&aux);
	aux = readline(text_minishell);
	ft_free_and_null((void **)&text_minishell);
	return (aux);
}

static int	check_pipe(char *input, int *i, int type)
{
	if (type == 1)
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		if (type == 1 || input[*i] == '|')
		{
			add_history_plus(input);
			ft_putstr_fd("\033[31;1mminishell: syntax error \
near unexpected toke '|'.\n\033[0m", 2);
		}
		ft_free_and_null((void **)&input);
		return (1);
	}
	return (0);
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

char	*readlineplus(void)
{
	char	*input;
	int		i;

	i = 0;
	input = get_line_fd1();
	if (!input || check_pipe(input, &i, 0) == 1)
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
			if (check_pipe(input, &i, 1) == 1)
				return (NULL);
	}
	if (input && *input)
		add_history_plus(input);
	return (input);
}
