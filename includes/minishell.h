/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 15:24:43 by smassand          #+#    #+#             */
/*   Updated: 2016/05/11 15:24:49 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/resource.h>

typedef struct		s_shell
{
	char			**env_cpy;
	char			**splitline;
}					t_shell;

void		ft_swaggy_prompt(void);
int			ft_isexec(char **line);
void		ft_parse_env(t_shell *shell, char *env[]);
void		ft_exec();

#endif