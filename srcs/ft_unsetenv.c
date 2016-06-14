/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:31 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:33 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_unsetenv(t_shell *shell)
{
	char	**update_env;
	int		i;
	int		j;

	if (!shell->splitline[1])
	{
		ft_putendl("unsetenv: Too few arguments.");
		return ;
	}
	i = ft_tablen(shell->env_cpy);
	update_env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	j = 0;
	while (shell->env_cpy[i])
	{
		if (ft_verif_unset(shell, shell->env_cpy[i]) == 1)
		{
			update_env[j] = ft_strdup(shell->env_cpy[i]);
			j++;
		}
		i++;
	}
	update_env[j] = NULL;
	free(shell->env_cpy);
	shell->env_cpy = update_env;
}

int			ft_verif_unset(t_shell *shell, char *arg)
{
	int		i;
	int		j;

	i = 1;
	while (shell->splitline[i])
	{
		if (ft_strcmp(shell->splitline[i], ft_cut_arg(arg)) == 0)
			return (0);
		i++;
	}
	return (1);
}

char		*ft_cut_arg(char *arg)
{
	int		i;
	char	*res;
	
	i = 0;
	res = ft_strnew(ft_strlen(arg));
	while (arg[i] != '=')
	{
		res[i] = arg[i];
		i++;
	}
	return (ft_strdup(res));
}