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
	if (!shell->splitline[1])
	{
		ft_putendl("unsetenv: Too few arguments.");
		return ;
	}
	if (ft_is_unset(shell) == 0)
		return ;
	ft_delete(shell);
}

void		ft_delete(t_shell *shell)
{
	char	**update_env;
	int		i;
	int		j;

	i = ft_tablen(shell->env_cpy);
	j = 0;
	update_env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (i < ft_tablen(shell->env_cpy))
	{
		if (ft_verif_unset(shell, shell->env_cpy[i]) == 1)
		{
			update_env[j] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcpy(update_env[j], shell->env_cpy[i]);
			j++;
		}
		i++;
	}
	update_env[j] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

int			ft_is_unset(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env_cpy[i])
	{
		if (ft_verif_unset(shell, shell->env_cpy[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			ft_verif_unset(t_shell *shell, char *arg)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_cut_arg(arg);
	while (shell->splitline[i])
	{
		if (ft_strcmp(shell->splitline[i], tmp) == 0)
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	free(tmp);
	return (1);
}

char		*ft_cut_arg(char *arg)
{
	int		i;
	char	*res;
	
	i = 0;
	while (arg[i] != '=')
		i++;
	res = ft_strnew(i + 1);
	i = 0;
	while (arg[i] != '=')
	{
		res[i] = arg[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
