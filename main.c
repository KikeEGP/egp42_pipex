/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:39:23 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/27 20:44:29 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Child will inherit *pipe_fd. In childs, close end which is not used.
 * But parent also will have to close both pipe_fdat the end*/
static int	pipe_and_execute_cmds(t_pipex_data pipex_data, int *pipe_fd)
{
	pid_t	pid_cmd_1;
	pid_t	pid_cmd_2;
	int		wstatus;

	pid_cmd_1 = fork();
	if (pid_cmd_1 == -1)
		close_fds_and_error(pipe_fd[0], pipe_fd[1], "fork", pipex_data);
	if (pid_cmd_1 == 0)
		execute_cmd_1(pipex_data, pipe_fd);
	pid_cmd_2 = fork();
	if (pid_cmd_2 == -1)
		close_fds_and_error(pipe_fd[0], pipe_fd[1], "fork", pipex_data);
	if (pid_cmd_2 == 0)
		execute_cmd_2(pipex_data, pipe_fd);
	if (close(pipe_fd[0]) == -1)
		close_a_fd_and_error(pipe_fd[1], "close pipe_fd", pipex_data);
	if (close(pipe_fd[1]) == -1)
		error_happened("close pipe_fd", pipex_data);
	if (waitpid(pid_cmd_1, &wstatus, 0) == -1)
		error_happened("waitpid cmd_1", pipex_data);
	if (waitpid(pid_cmd_2, &wstatus, 0) == -1)
		error_happened("waitpid cmd_2", pipex_data);
	return (WEXITSTATUS(wstatus));
}

/*If everything is okay, main will return 2nd child end's status*/
int	main(int argc, char **argv, char **enviroment_list)
{
	t_pipex_data	pipex_data;
	int				status;
	int				pipe_fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("Error. ", 2);
		ft_putendl_error("Expected: './pipex file1 cmd1 cmd2 file2'");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		ft_putendl_error("Error in pipe()");
		exit(EXIT_FAILURE);
	}
	storage_data(&pipex_data, argv, enviroment_list);
	status = pipe_and_execute_cmds(pipex_data, pipe_fd);
	free_cmd(pipex_data.cmd_1);
	free_cmd(pipex_data.cmd_2);
	return (status);
}
