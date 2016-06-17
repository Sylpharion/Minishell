/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:47 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:49 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_cd(t_shell *shell)
{
// 	ft_verif_cd(shell);
// }

// void		ft_verif_cd(t_shell *shell)
// {
// 	int		i;
// 	int		pwd;
// 	int		oldpwd;

// 	i = 0;
// 	pwd = 0;
// 	oldpwd = 0;
// 	while (shell->env_cpy[i])
// 	{
// 		if (ft_strcmp(ft_cut_arg(shell->env_cpy[i]), "PWD") == 0)
// 		{
// 			pwd = 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	if (pwd == 0)
// 		ft_add_pwd(shell, shell->pwd);
// 	i = 0;
// 	while (shell->env_cpy[i])
// 	{
// 		if (ft_strcmp(ft_cut_arg(shell->env_cpy[i]), "OLDPWD") == 0)
// 		{
// 			oldpwd = 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	if (oldpwd == 0)
// 		ft_add_pwd(shell, shell->pwd);
}
