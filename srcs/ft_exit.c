/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:11 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:13 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_exit(t_shell *shell)
{
	free(shell->pwd);
	free(shell->env_cpy);
	free(shell->line);
	free(shell->splitline);
	free(shell->path);
	if (kill(0, SIGINT) == -1)
		ft_putendl("minishell: unknow error!");
}
