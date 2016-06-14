/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:54:25 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:54:51 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_init(t_shell *shell, char **argv)
{
	shell->pid = 0;
	shell->line = NULL;
	shell->path = NULL;
	shell->splitline = NULL;
	shell->exec = NULL;
	shell->env_cpy = NULL;
	shell->pwd = NULL;
}

t_ptr		*ft_ptr_init(void)
{
	t_ptr	*ptr;

	ptr = malloc(sizeof(&ptr) * 7);
	ptr[0] = ft_env;
	ptr[1] = ft_setenv;
	ptr[2] = ft_unsetenv;
	ptr[3] = ft_cd;
	ptr[4] = ft_exit;
	ptr[5] = ft_printenv;
	ptr[6] = NULL;
	return (ptr);
}

char		**ft_tab_init(void)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 7);
	tab[0] = ft_strdup("env");
	tab[1] = ft_strdup("setenv");
	tab[2] = ft_strdup("unsetenv");
	tab[3] = ft_strdup("cd");
	tab[4] = ft_strdup("exit");
	tab[5] = ft_strdup("printenv");
	tab[6] = NULL;
	return (tab);
}