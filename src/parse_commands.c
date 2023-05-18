#include "minishell.h"

static char	**check_void_pipes(int n_commands, char**input_parse, char *input)
{
	int	i;
	int	n_args;

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

char	**extract_commands(char *input, int n_commands, int i)
{
	char	**input_parse;
	int		n_args;

	input_parse = (char **)ft_calloc((n_commands + 1), sizeof(char *)); //Proteger
	input_parse[0] = &input[0];
	n_args = 1;
	while (n_args < n_commands)
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
	input_parse = check_void_pipes(n_commands, input_parse, input);
	return (input_parse);
}

void	parse(char *input, int n_commands)
{
	char	**commands;
	char	**borrar;

	commands = extract_commands(input, n_commands, 0);
	ft_printf_split(commands);
	// ft_split_free(commands);
	borrar = ft_split_mod(commands[0], 0, 0, 0);
	free(commands);
	ft_printf_split(borrar);
	ft_split_free(borrar);
}
