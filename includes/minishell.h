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

typedef 	struct s_shell t_shell;
typedef 	void (*t_ptr)(t_shell *);

typedef struct		s_shell
{
	pid_t			pid;
	struct stat		st;
	char			*pwd;
	char			*home;
	char			**env_cpy;
	char			*line;
	char			**splitline;
	char			**path;
	char			*exec;
	char			**tab;
	t_ptr			*ptr;

}					t_shell;

/*
	rappel :
*/

//typedef 	void (*t_ptr)(t_shell *);

void		ft_parse_env(t_shell *shell, char *env[]);
void		ft_create_env(t_shell *shell);
void		ft_init(t_shell *shell, char **argv);
//t_ptr		*ft_ptr_init(void);
//char		**ft_tab_init(void);
void		ft_path(t_shell *shell, char **env);
void		ft_parse_path(t_shell *shell, char *s);
void		ft_swaggy_prompt(void);

int			ft_isexec(t_shell *shell, char *s);
int			ft_access(t_shell *shell, char *s);
void		ft_error(t_shell shell);
void		ft_exec(t_shell *shell, char *cmd, char *env[]);

/*	builtins  */

int			ft_builtins(t_shell *shell);
void		ft_env(t_shell *shell);
void		ft_setenv(t_shell *shell);
char		**ft_ft_setenv(t_shell *shell, char **update_env);
void		ft_unsetenv(t_shell *shell);
int			ft_verif_unset(t_shell *shell, char *arg);
void		ft_cd(t_shell *shell);
int			ft_verif_cd(t_shell *shell);
void		ft_exit(t_shell *shell);
void		ft_printenv(t_shell *shell);

/* autres */

int			ft_tablen(char **tab);
char		*ft_cut_arg(char *arg);
char		*ft_add_env(t_shell *shell);
char		*ft_get_the_line(void);


#endif

