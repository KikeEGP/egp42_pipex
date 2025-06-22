/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:39:23 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/22 19:31:15 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

static void	pipe_and_execute_cmds(t_pipex_data pipex_data)
{
	int	pipe_fd[2];
	pid_t	pid_cmd_1;
	pid_t	pid_cmd_2;

	if (pipe(pipe_fd) == -1)
		error_happened(-1, "pipe");
	pid_cmd_1 = fork();
	pid_cmd_2 = fork();
}

int	main(int argc, char **argv, char **enviroment_list)
{
	t_pipex_data	pipex_data;

	if (argc == 5)
		error_happened(0, NULL);
	storage_data(&pipex_data, argv, enviroment_list);
	pipe_and_execute_cmds(pipex_data);
	return (0);
}
