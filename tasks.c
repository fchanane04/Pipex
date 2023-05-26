/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 03:50:29 by fchanane          #+#    #+#             */
/*   Updated: 2022/04/24 22:01:34 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	**create_paths(char **env)
{
	int		i;
	char	**paths;
	char	**no_name;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			break ;
		i++;
	}
	no_name = ft_split(env[i], '=');
	paths = ft_split(no_name[1], ':');
	free(no_name[0]);
	free(no_name[1]);
	free(no_name);
	return (paths);
}

char	*find_path(char **PATHS, char *cmd)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	if (!access(cmd, X_OK))
	{
		free_paths(PATHS);
		return (cmd);
	}
	while (PATHS[i])
	{
		path = ft_strjoin_mod(PATHS[i], cmd);
		if (!access(path, X_OK))
		{
			free_paths(PATHS);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(PATHS);
	return (NULL);
}

void	writing_process(t_data *data, char **cmd, char *cmd_name, char **env)
{
	char	*str;

	cmd = ft_split(cmd_name, ' ');
	str = cmd[1];
	cmd[1] = ft_strtrim_mod(cmd[1], "\'");
	free(str);
	close(data->fd[0]);
	dup2(data->fd1, 0);
	dup2(data->fd[1], 1);
	data->path = find_path(create_paths(env), cmd[0]);
	if (!data->path)
	{
		write(2, "zsh :command not found: ", 25);
		ft_putstr_fd(cmd[0], 2);
		write(2, "\n", 2);
		exit(1);
	}
	close(data->fd1);
	close(data->fd[1]);
	if (execve(data->path, cmd, env) <= -1)
	{
		perror("execve");
		exit(1);
	}
}

void	reading_process(t_data *data, char **cmd, char **argv, char **env)
{
	char	*str;

	cmd = ft_split(argv[3], ' ');
	data->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	str = cmd[1];
	cmd[1] = ft_strtrim_mod(cmd[1], "\'");
	free(str);
	close(data->fd[1]);
	dup2(data->fd[0], 0);
	dup2(data->fd2, 1);
	data->path = find_path(create_paths(env), cmd[0]);
	if (!data->path)
	{
		write(2, "zsh :command not found: ", 25);
		ft_putstr_fd(cmd[0], 2);
		write(2, "\n", 2);
		exit(1);
	}
	close(data->fd2);
	close(data->fd[0]);
	if (execve(data->path, cmd, env) <= -1)
	{
		perror("execve");
		exit(1);
	}
}

void	finish_exec(t_data *data)
{
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->child1, 0, 0);
	waitpid(data->child2, 0, 0);
	free(data);
}
