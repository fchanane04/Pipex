/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 11:06:11 by fchanane          #+#    #+#             */
/*   Updated: 2022/04/24 21:50:47 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>
# include<errno.h>
# include<sys/wait.h>
# include<stdio.h>

# define ERROR_ARGS "Arguments must be 4: file1 cmd1 cmd2 file2\n"

typedef struct t_data
{
	int		child1;
	int		child2;
	int		fd1;
	int		fd2;
	char	*path;
	int		fd[2];
}	t_data;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_mod(char const *s1, char const *s2);
char	*ft_strtrim_mod(char *s1, char *set);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);

char	**create_paths(char **env);
char	*find_path(char **PATHS, char *cmd);
void	finish_exec(t_data *data);

int		arg_error(int argc);
int		fd_error(int fd);
int		fork_error(int pid);
int		cmd_error(char *cmd);
void	free_paths(char **paths);

void	writing_process(t_data *data, char **cmd, char *cmd_name, char **env);
void	reading_process(t_data *data, char **cmd, char **argv, char **env);
#endif
