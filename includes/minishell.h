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
	pid_t			pid;
	struct stat		st;
	char			**env_cpy;
	char			*line;
	char			*trimline;
	char			**splitline;
	char			**tab;
	char			*pwd;
	char			*home;
	char			**path;
	char			*pathdir;
	char			*exec;
}					t_shell;

typedef void		(*t_ptr)(t_shell *);

void				ft_catch(int sig);
void				ft_catch_in_fork(int sig);
void				ft_parse_env(t_shell *shell, char *env[], int i, int n);
void				ft_create_env(t_shell *shell);
char				**ft_trimline(t_shell *shell);
char				*ft_parseline(t_shell *shell);
void				ft_init(t_shell *shell, int argc, char **argv);
char				*ft_parsetild(t_shell *shell, char *line, int i, int j);
char				**ft_tab_init(void);
t_ptr				*ft_ptr_init(void);
void				ft_path(t_shell *shell, char **env);
void				ft_parse_path(t_shell *shell, char *s);
void				ft_swaggy_prompt(void);
void				ft_loop(t_shell	*shell);
int					ft_isexec(t_shell *shell, char *s);
int					ft_access(t_shell *shell, char *s, int i, char *tmp);
void				ft_error(t_shell shell);
void				ft_exec(t_shell *shell);
int					ft_builtins(t_shell *shell);
void				ft_builtins_list(t_shell *shell);
void				ft_env(t_shell *shell);
void				ft_printenv(t_shell *shell);
void				ft_setenv(t_shell *shell);
char				**ft_update_setenv(t_shell *shell);
void				ft_free_setenv(t_shell *shell, char **update_env);
void				ft_free_setenv_plus(t_shell *shell, char **update_env);
void				ft_modif_setenv(t_shell *shell);
char				**ft_maj_setenv(t_shell *shell, char *tmp, int i, char **update_env);
char				**ft_new_setenv(t_shell *shell, int i, char **update_env);
void				ft_unsetenv(t_shell *shell);
int					ft_verif_unset(t_shell *shell, char *arg);
void				ft_modif_unsetenv(t_shell *shell);
int					ft_is_unset(t_shell *shell);
void				ft_delete(t_shell *shell);
void				ft_cd(t_shell *shell);
void				ft_true_cd(t_shell *shell);
void				ft_verif_cd(t_shell *shell, int i, int pwd, int oldpwd);
char				*ft_verif_cd_pathdir(t_shell *shell, char *tmp);
void				ft_add_pwd(t_shell *shell, int pwd, int oldpwd);
void				ft_cd_home(t_shell *shell);
void				ft_new_oldpwd(t_shell *shell, int i, char *tmp);
void				ft_cd_home_error(t_shell *shell, char *path);
void				ft_cd_error(char *path);
void				ft_exec_cd(t_shell *shell);
void				ft_parse_cd(t_shell *shell, char *path);
void				ft_cd_moins(t_shell *shell);
char				*ft_init_pwd(t_shell *shell);
char				*ft_pwd_loop(t_shell *shell);
char				*ft_oldpwd_loop(char *path);
void				ft_maj_pwd(t_shell *shell);
void				ft_maj_oldpwd(t_shell *shell);
void				ft_echo(t_shell *shell);
void				ft_echo_var(char **env, char *str);
void				ft_print_var(char **env, char *str);
void				ft_echo_brut(char *str);
void				ft_echo_loop(t_shell *shell, int i);
int					ft_tablen(char **tab);
char				*ft_cut_arg(char *arg);
char				*ft_cut_val(char *arg);
char				*ft_add_env(t_shell *shell);
char				*ft_get_the_line(void);
void				ft_free_tab(char **tab);
void				ft_print_arg(char *s);
void				ft_exit(t_shell *shell);

#endif
