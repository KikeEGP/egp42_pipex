/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:39:23 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/25 18:03:32 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Child will inherit *pipe_fd. In childs, close end which is not used.
 * But parent also will have to close both pipe_fdat the end*/
static int	pipe_and_execute_cmds(t_pipex_data pipex_data)
{
	pid_t	pid_cmd_1;
	pid_t	pid_cmd_2;
	int		pipe_fd[2];
	int		wstatus;

	if (pipe(pipe_fd) == -1)
		error_happened(-1, "pipe");
	pid_cmd_1 = fork();
	if (pid_cmd_1 == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error_happened(-1, "fork for cmd_1");
	}
	if (pid_cmd_1 == 0)
		execute_cmd_1(pipex_data, pipe_fd);
	pid_cmd_2 = fork();
	if (pid_cmd_2 == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error_happened(-1, "fork for cmd_2");
	}
	if (pid_cmd_2 == 0)
		execute_cmd_2(pipex_data, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_cmd_1, &wstatus, 0);
	waitpid(pid_cmd_2, &wstatus, 0);/*ALWAYS RETURN THE STATUS
	OF SECOND WAITPID, EVEN IF WAITPID FAILS*//*Would work a if one of waitpid
					== -1, error_happened()?*/
	return (WEXITSTATUS(wstatus));
}

/*If everything is okay, main will return 2nd child end's status*/
int	main(int argc, char **argv, char **enviroment_list)
{
	t_pipex_data	pipex_data;
	int				status;

	if (argc != 5)
		error_happened(0, NULL);
	storage_data(&pipex_data, argv, enviroment_list);
	status = pipe_and_execute_cmds(pipex_data);
	free_cmd(pipex_data.cmd_1);
	free_cmd(pipex_data.cmd_2);
	return (status);
}
