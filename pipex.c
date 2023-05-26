/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:25:54 by fchanane          #+#    #+#             */
/*   Updated: 2022/04/24 22:00:25 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	main(int argc, char *argv[], char **env)
{
	t_data	*data;
	char	**cmd;

	cmd = NULL;
	arg_error(argc);
	if (cmd_error(argv[2]) == -1 || cmd_error(argv[3]) == -1)
		exit(1);
	data = malloc (sizeof(t_data));
	data->child2 = -2;
	data->fd1 = open(argv[1], O_RDONLY);
	fd_error(data->fd1);
	pipe(data->fd);
	data->child1 = fork();
	fork_error(data->child1);
	if (data->child1 == 0)
		writing_process(data, cmd, argv[2], env);
	if (data->child1 > 0)
	{
		data->child2 = fork();
		if (data->child2 == 0)
			reading_process(data, cmd, argv, env);
	}
	finish_exec(data);
	return (0);
}
