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
	int		i;

	ft_verif_cd(shell, 0, 0, 0);
	if (ft_tablen(shell->splitline) > 2)
		ft_putendl("cd: Too many arguments.");
	else if (!shell->splitline[1] || ft_strcmp(shell->splitline[1], "--") == 0)
		ft_cd_home(shell);
	else if (ft_strcmp(shell->splitline[1], "-") == 0)
		ft_cd_moins(shell);
	else
		ft_exec_cd(shell);
	free(shell->pathdir);
}

void		ft_cd_moins(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "OLDPWD") == 0)
		{
			free(tmp);
		 	tmp = ft_cut_val(shell->env_cpy[i]);
		 	break ;
		}
		free(tmp);
		i++;
	}
	if (chdir(tmp) == -1)
		ft_cd_error(shell, shell->splitline[1]);
	else
		ft_new_oldpwd(shell, shell->splitline[1], 0);
	free(tmp);
}

void		ft_exec_cd(t_shell *shell)
{
	if (chdir(shell->pathdir) == -1)
		ft_cd_error(shell, shell->splitline[1]);
	else
		ft_new_oldpwd(shell, shell->splitline[1], 0);
}

void		ft_cd_home(t_shell *shell)
{
	if (chdir(shell->home) == -1)
		ft_cd_home_error(shell, shell->home);
	else
		ft_new_oldpwd(shell, shell->home, 0);
	return ;
}

void		ft_new_oldpwd(t_shell *shell, char *path, int i)
{
	char	**update_env;
	char	*tmp;
	char	*pwd;

	update_env = (char **)malloc(sizeof(char *) * ft_tablen(shell->env_cpy) + 1);
	pwd = ft_init_pwd(shell);
	while(shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "PWD") == 0)
			update_env[i] = ft_pwd_loop(shell);
		else if (ft_strcmp(tmp, "OLDPWD") == 0)
			update_env[i] = ft_oldpwd_loop(shell, pwd);
		else
		{
			update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcpy(update_env[i], shell->env_cpy[i]);
		}
		free(tmp);
		i++;
	}
	free(pwd);
	update_env[i] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

char		*ft_pwd_loop(t_shell *shell)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strnew(ft_strlen(shell->pwd) + 5);
	tmp2 = getcwd(NULL, 0);
	ft_strcat(tmp, "PWD=");
	ft_strcat(tmp, tmp2);
	pwd = ft_strnew(ft_strlen(tmp));
	ft_strcpy(pwd, tmp);
	free(tmp2);
	free(tmp);
	return (pwd);
}

char		*ft_oldpwd_loop(t_shell *shell, char *pwd)
{
	char	*oldpwd;

	oldpwd = ft_strnew(ft_strlen(pwd) + 8);
	ft_strcat(oldpwd, "OLDPWD=");
	ft_strcat(oldpwd, pwd);
	return (oldpwd);
}

char		*ft_init_pwd(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*pwd;

	i = 0;
	while(shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "PWD") == 0)
		{
			pwd = ft_cut_val(shell->env_cpy[i]);
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	return (pwd);
}

void		ft_cd_home_error(t_shell *shell, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "HOME") == 0)
		{
			free(tmp);
			ft_cd_error(shell, path);
			return ;
		}
		free(tmp);
		i++;
	}
	ft_putendl("cd: No home directory.");
}

void		ft_cd_error(t_shell *shell, char *path)
{
	struct	stat st;

	if (lstat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode) == 1)
			ft_putstr("cd: not a directory: ");
		else if (S_ISDIR(st.st_mode) == 1)
			ft_putstr("cd: permission denied: ");
	}
	else
		ft_putstr("cd: no such file of directory: ");
	ft_putendl(path);
}

void		ft_verif_cd(t_shell *shell, int i, int pwd, int oldpwd)
{
	char	*tmp;

	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "PWD") == 0)
			pwd = 1;
		else if (ft_strcmp(tmp, "OLDPWD") == 0)
			oldpwd = 1;
		free(tmp);
		i++;
	}
	if (!shell->pwd)
		shell->pwd = getcwd(NULL, 0);
	ft_add_pwd(shell, pwd, oldpwd);

	if (shell->splitline[1])
		shell->pathdir = ft_verif_cd_pathdir(shell, tmp);
	else 
	{
		shell->pathdir = ft_strnew(ft_strlen(shell->home));
		ft_strcpy(shell->pathdir, shell->home);
	}
	ft_strcpy(shell->pathdir, shell->splitline[1]);
}

char		*ft_verif_cd_pathdir(t_shell *shell, char *tmp)
{
	char	*pathdir;

	tmp = getcwd(NULL, 0);
	pathdir = ft_strnew(ft_strlen(tmp) + ft_strlen(shell->splitline[1]));
	ft_strcat(pathdir, tmp);
	ft_strcat(pathdir, shell->splitline[1]);
	free(tmp);
	return (pathdir);
}

void		ft_add_pwd(t_shell *shell, int pwd, int oldpwd)
{	
	if (pwd == 0)
		ft_maj_pwd(shell);
	if (oldpwd == 0)
		ft_maj_oldpwd(shell);
}

void		ft_maj_pwd(t_shell *shell)
{
	char	**update_env;
	int		i;

	i = 0;
	update_env = (char **)malloc(sizeof(char *)
				* ft_tablen(shell->env_cpy) + 20);
	while (shell->env_cpy[i])
	{
		update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
		update_env[i] = ft_strcat(update_env[i], shell->env_cpy[i]);
		i++;
	}
	update_env[i] = ft_strnew(3 + ft_strlen(shell->pwd) + 2);
	ft_strcat(update_env[i], "PWD");
	ft_strcat(update_env[i], "=");
	ft_strcat(update_env[i], shell->pwd);
	update_env[i + 1] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

void		ft_maj_oldpwd(t_shell *shell)
{
	char	**update_env;
	int		i;

	i = 0;
	update_env = (char **)malloc(sizeof(char *)
				* ft_tablen(shell->env_cpy) + 20);
	while (shell->env_cpy[i])
	{
		update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
		ft_strcat(update_env[i], shell->env_cpy[i]);
		i++;
	}
	update_env[i] = ft_strnew(ft_strlen("OLDPWD") +
						ft_strlen(shell->pwd) + 2);
	ft_strcat(update_env[i], "OLDPWD");
	ft_strcat(update_env[i], "=");
	ft_strcat(update_env[i], shell->pwd);
	update_env[i + 1] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}
