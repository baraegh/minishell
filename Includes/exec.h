/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:08:16 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/14 23:54:18 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec_p
{
	int		*fd;
	pid_t	pid;
	int		cmdnbr;
	int		*p;
	int		fd_in;
	int		fd_heredoc;

}	t_exec_p;

typedef struct s_vr
{
	char	**env;
	int		envlen;
	int		flag;

}	t_vr;

typedef struct s_v
{
	int			pipe_num;
	t_cmd		*tmp;
	void		*exec;
	int			i;
	int			j;
	int			status;
	int			len;
	char		*rd;
	int			len_h;
	int			fd[2];

}	t_v;

void	pwd(int fd);
char	**get_path_splited(char **env);
char	*ft_checkaccess(char *cmd, char **env);
void	cd(t_cmd *list, t_vr *vr);
void	*exec_pipe(t_cmd *list, t_vr *vr);
t_vr	*fill_env(char **envp);
void	export(t_cmd *list, t_vr *vr, int fd);
char	*export_ut(char *envp);
t_vr	*unset(char **cmd, t_vr *vr);
void	env(char **cmd, t_vr *vr, int fd);
int		heredoc(char *file_name);
void	echo(t_cmd *list, int fd);
t_vr	*exec_builtin(t_cmd *list, t_vr *vr, int fd);
char	*ft_getpath(char **envp);
int		in_builtin(t_cmd *list);
void	ft_exit(t_cmd *list);
char	*unset_word(char *target);
void	ft_error(char *msg, int exit_code);
int		ft_lstlen(t_cmd *lst);
void	duplicate_fd(t_cmd *list, t_exec_p *exec);
void	ft_freetwo(char **target);
char	*unset_word(char *target);
int		iterate_export(t_vr *vr, char *target);
void	check_exp_env(char *cmd, t_vr *vr);
char	**add_to_export(char **env, char *elmnt);
int		check_cmd(char *cmd);
int		*openfile(t_cmd *list);
void	ft_execve(t_cmd *list, t_vr *vr, char *cmderr);
void	closepipe_andwait(t_exec_p *exec, t_v *v);
void	print_n_echo(char **cmd, int fd, int i);

#endif