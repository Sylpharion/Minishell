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
	char			**env_cpy;
	char			*line;
	char			*trimline;
	char			**splitline;
	char			**tab;
	t_ptr			*ptr;
	char			*pwd;
	char			*home;
	char			**path;
	char			*exec;
}					t_shell;

/*
	rappel :

	init = 1 fois au debut du prog
	free (tab) != free d'un tableau

	while (tab[i])
		free(tab[i]);
	free(tab);

	important : free de supprime pas les donnee de tes variables
	free libere la memoire mais supprime pas le contenue

	exemple :
		malloc("coucou\n"); => on as allouer 7 octect ou tu as ecris coucou
		free(la variable de coucou); => liberation de la memoire mais pas le contenu 
*/

void		ft_parse_env(t_shell *shell, char *env[]);
void		ft_create_env(t_shell *shell);
void		ft_init(t_shell *shell, char **argv);
void		ft_path(t_shell *shell, char **env);
void		ft_parse_path(t_shell *shell, char *s);
void		ft_swaggy_prompt(void);

void		ft_loop(t_shell	*shell);
int			ft_isexec(t_shell *shell, char *s);
int			ft_access(t_shell *shell, char *s);
void		ft_error(t_shell shell);
void		ft_exec(t_shell *shell, char *cmd, char *env[]);

/*	builtins  */

int			ft_builtins(t_shell *shell);
void		ft_env(t_shell *shell);
void		ft_setenv(t_shell *shell);
char		**ft_update_setenv(t_shell *shell);
void		ft_free_setenv(t_shell *shell, char  **update_env);


void		ft_unsetenv(t_shell *shell);
int			ft_verif_unset(t_shell *shell, char *arg);
int			ft_is_unset(t_shell *shell);
void		ft_delete(t_shell *shell);


void		ft_cd(t_shell *shell);
void		ft_verif_cd(t_shell *shell);
void		ft_add_pwd(t_shell *shell, int pwd, int oldpwd);
void		ft_go_home(t_shell *shell);
void		ft_new_oldpwd(t_shell *shell, char *path);
void		ft_cd_home_error(t_shell *shell, char *path);
void		ft_cd_home_error_sup(t_shell *shell, char *path);


void		ft_exit(t_shell *shell);
void		ft_printenv(t_shell *shell);


void		ft_echo(t_shell *shell);
void		ft_echo_var(char **env, char *str);
void		ft_print_var(char **env, char *str);
void		ft_echo_quote(char *str);
void		ft_echo_brut(char *str);

/* autres */

int			ft_tablen(char **tab);
char		*ft_cut_arg(char *arg);
char		*ft_add_env(t_shell *shell);
char		*ft_get_the_line(void);
void		ft_free_tab(char **tab);
void		ft_print_arg(char *s);

#endif

