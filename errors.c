/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 03:34:00 by fchanane          #+#    #+#             */
/*   Updated: 2022/04/24 00:00:22 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	arg_error(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd(ERROR_ARGS, 1);
		exit(1);
	}
	return (0);
}

int	fd_error(int fd)
{
	if (fd == -1)
	{
		perror("file1");
		exit(1);
	}
	return (0);
}

int	fork_error(int pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	return (0);
}

int	cmd_error(char *cmd)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (cmd[i] && cmd[i] != '\'')
		i++;
	while (cmd[i] && cmd[i++] == '\'')
		start ++;
	while (cmd[i] && cmd[i] != '\'')
		i++;
	while (cmd[i] && cmd[i++] == '\'')
		end ++;
	if (cmd[i] != '\0' || start != end)
		return (-1);
	return (0);
}
