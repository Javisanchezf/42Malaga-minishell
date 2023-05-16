#include "minishell.h"

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

static char	*special_chars(char *input, int *i)
{
	char	aux;
	char	*dquote;

	aux = input[*i];
	(*i)++;
	while (1)
	{
		while (input[*i] && input[*i] != aux)
			(*i)++;
		if (!input[*i])
		{
			dquote = ft_strjoin(input, "\n"); // proteger
			free(input);
			input = dquote;
			dquote = readline("\033[36;1m> \033[0m"); //proteger
			input = ft_freeandjoin(input, dquote); //proteger
		}
		else
			break ;
	}
	(*i)++;
	return (input);
}

static char	*readlineplus(int *commands, int i)
{
	char	*text_minishell;
	char	*input;

	text_minishell = ft_get_text_minishell();
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
		else if (input[i] == '|')
		{
			(*commands)++;
			i++;
		}
	}
	add_history(input);
	return (input);
}

void	ft_getline(void)
{
	char	*input;
	int		n_commands;

	while (1)
	{
		input = readlineplus(&n_commands, 0);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		printf("Entrada: %s, comandos: %d\n", input, n_commands);
		free(input);
	}
}
