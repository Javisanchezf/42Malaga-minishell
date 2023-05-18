#include "minishell.h"

static int	ft_size_split_by_pipes(char *input)
{
	int	commands;
	int	i;

	i = 0;
	commands = 1;
	while (input[i])
	{
		while (input[i] && (input[i] != '|' && \
		input[i] != '\'' && input[i] != '\"'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			forward_quotes(input, &i);
		if (input[i] == '|')
		{
			commands++;
			i++;
		}
	}
	return (commands);
}

static char	**check_void_pipes(int size_split, char**input_parse, char *input)
{
	int	i;
	int	n_args;

	n_args = -1;
	if (size_split != 1)
	{
		while (++n_args < size_split)
		{
			i = 0;
			while (ft_isspace(input_parse[n_args][i]))
				i++;
			if (input_parse[n_args][i] == 0)
			{
				ft_putstr_fd("\033[31;1mminishell: syntax error \
near unexpected toke '|'.\n\033[0m", 2);
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

char	**split_by_pipes(char *input, int size_split, int i)
{
	char	**input_parse;
	int		n_args;

	size_split = ft_size_split_by_pipes(input);
	input_parse = (char **)ft_calloc((size_split + 1), sizeof(char *)); //Proteger
	input_parse[0] = &input[0];
	n_args = 1;
	while (n_args < size_split)
	{
		while (input[i] && input[i] != '|' && input[i] != '\'' && input[i] != '\"')
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			forward_quotes(input, &i);
		if (input[i] == '|')
		{
			input[i] = 0;
			i++;
			input_parse[n_args] = &input[i];
			n_args++;
		}
	}
	input_parse = check_void_pipes(size_split, input_parse, input);
	return (input_parse);
}
