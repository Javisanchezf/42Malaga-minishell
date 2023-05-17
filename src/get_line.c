
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

static char	*special_chars(char *input, int *i)
{
	char	aux;

	aux = input[*i];
	(*i)++;
	while (1)
	{
		while (input[*i] && input[*i] != aux)
			(*i)++;
		if (!input[*i])
		{
			add_history(input);
			rl_replace_line("", 0);
			rl_redisplay();
			ft_putstr_fd("\033[31;1mminishell: syntax \
error due to unclosed quotes.\n\033[0m", 2);
			input[0] = 0;
			(*i) = -1;
		}
		break ;
	}
	(*i)++;
	return (input);
}

char	**extract_commands(char *input, int n_commands, int i)
{
	char	**input_parse;
	int		n_args;

	input_parse = (char **)ft_calloc((n_commands + 1), sizeof(char *)); //Proteger
	input_parse[0] = &input[0];
	n_args = 1;
	while (n_args < n_commands)
	{
		while (input[i] && (input[i] != '|' && input[i] != '\'' && input[i] != '\"'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			input = special_chars(input, &i);
		if (input[i] == '|')
		{
			input[i] = 0;
			i++;
			input_parse[n_args] = &input[i];
			n_args++;
		}
	}
	n_args = -1;
	if (n_commands != 1)
	{
		while (++n_args < n_commands)
		{
			i = 0;
			while (ft_isspace(input_parse[n_args][i]))
				i++;
			if (input_parse[n_args][i] == 0)
			{
				ft_putstr_fd("\033[31;1mminishell: syntax error near unexpected toke '|'.\n\033[0m", 2);
				free(input_parse);
				input_parse = (char **)ft_calloc(2, sizeof(char *)); //proteger
				input[0] = 0;
				input_parse[0] = input;
				break ;
			}
		}
	}
	return (input_parse);
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
	{
		add_history(input);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		*commands = 1;
	return (input);
}

void	print_commands(char **argumentos)
{
	int		i;

	i = 0;
	while (argumentos[i] != NULL)
	{
		printf("Comando %d: %s\n", i, argumentos[i]);
		i++;
	}
}

void	ft_getline(void)
{
	char	*input;
	int		n_commands;
		char	**borrar;

	while (1)
	{
		input = readlineplus(&n_commands, ft_get_text_minishell(), 0);
			borrar = extract_commands(input, n_commands, 0);
			print_commands(borrar);
			free(borrar);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
	rl_clear_history();
}
