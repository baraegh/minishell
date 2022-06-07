/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:08:16 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/07 11:44:41 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// 
// int		exitcode = 0;

typedef struct s_exec_p
{
	int		*fd;
	pid_t	pid;
	int		cmdnbr;
	int		*fd_f;
	int		p[2];
	int		fd_in;
	int		fd_heredoc;

}	t_exec_p;


// typedef struct s_file
// {
// 	char *file;
// 	int     fd;
// 	int	type;
// 	struct s_file *next;
// } t_file;

typedef struct s_vr
{
	char	**env;
    char	**export;
    int		envlen;
	int		explen;
}	t_vr;

// typedef struct s_cmd
// {
// 	char **cmd;
// 	t_file *file;
// 	int		pipenum;
// 	struct s_cmd *next;
// }	t_cmd;


void	pwd(int fd);
char	**get_path_splited(char **env);
void	cd(t_cmd *list);
void	exec_pipe(t_cmd *list, t_vr *vr);
t_vr	*fill_env(char **envp);
char 	**fill_export(char **envp, t_vr	*vr);
void	export(t_cmd *list, t_vr *vr, int fd);
char	*export_ut(char *envp);
t_vr	*unset(char **cmd, t_vr *vr);
void	env(char **cmd,t_vr *vr,int fd);
int		heredoc(char *file_name);
void	echo(t_cmd *list, int fd);
int		exec_builtin(t_cmd *list,t_vr *vr, int fd);
char	*ft_getpath(char **envp);
int		in_builtin(t_cmd *list);
void	 ft_exit(t_cmd *list);
char	*unset_word(char *target);
void	ft_error(char *msg, int exit_code);
int		ft_lstlen(t_cmd *lst);
void    duplicate_fd(t_cmd *list, t_exec_p * exec);
void	ft_freetwo(char **target);
char	*unset_word(char *target);
int		iterate_export(t_vr *vr, char *target);
void	check_exp_env(char *cmd, t_vr *vr);

#endif