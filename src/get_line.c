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

// static char	*special_chars(char *input, int *i)
// {
// 	char	aux[2];
// 	char	*dquote;

// 	aux[0] = input[*i];
// 	aux[1] = 0;
// 	(*i)++;
// 	while (1)
// 	{
// 		while (input[*i] && input[*i] != aux[0])
// 			(*i)++;
// 		if (!input[*i])
// 		{
// 			dquote = input;
// 			input = ft_strjoin(input, (char *)aux); // proteger
// 			free(dquote);
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
	rl_redisplay();
}

static char	*special_chars(char *input, int *i)
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
		input[0] = 0;
		(*i) = -1;
	}
	(*i)++;
	return (input);
}

static char	*ft_get_text_minishell(void)
{
	char	*text_minishell;
	char	path[1024];
	char	*aux;

	if (getcwd(path, sizeof(path)) == NULL)
		exit(EXIT_FAILURE); // Poner ft_error y liberar lo que haga falta
	aux = ft_strrchr(path, '/') + 1;
	aux = ft_strjoin("\033[36;1m", aux); // Proteger
	text_minishell = ft_strjoin(aux, " -> \033[0m"); // Proteger
	free(aux);
	return (text_minishell);
}

static char	*readlineplus(int *commands, char *text_minishell, int i)
{
	char	*input;

	input = readline(text_minishell);
	free(text_minishell);
	*commands = 1;
	while (input[i])
	{
		while (input[i] && (input[i] != '|' && \
		input[i] != '\'' && input[i] != '\"'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			input = special_chars(input, &i);
		if (input[i] == '|')
		{
			(*commands)++;
			i++;
		}
	}
	if (input && *input)
		add_history_plus(input);
	else
		*commands = 1;
	return (input);
}

void	ft_getline(void)
{
	char	*input;
	int		n_commands;

	while (1)
	{
		input = readlineplus(&n_commands, ft_get_text_minishell(), 0);
		parse(input, n_commands);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
	rl_clear_history();
}
