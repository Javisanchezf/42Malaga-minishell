#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	sub_dup2(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);
}


char  *ft_getcmd(t_data *data, char *cmd)
{
    int     i;
    char    *aux;
    char    *c;

    i = 0;
    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    while (data->rute[i])
    {
        aux = ft_strjoin(data->rute[i], "/");
        c = ft_strjoin(aux, cmd);
        free(aux);
        if (access(c, X_OK) == 0)
            return (c);
        free(c);
        i++;
    }
    return (ft_strdup(""));
}





