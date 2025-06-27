/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:07:36 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/27 20:36:35 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	command_not_found(char **cmd_executed, char **other_cmd)
{
	free_cmd(other_cmd);
	if (cmd_executed[0] == 0)
		ft_putendl_error("Command '' not found");	
	else
	{
		ft_putstr_fd(cmd_executed[0], 2);
		ft_putendl_error(": command not found");
	}
	free_cmd(cmd_executed);
	exit(127);
}

void	execute_cmd_2(t_pipex_data pipex_data, int *pipe_fd)
{
	char	*path_to_execute;
	int		fd_outfile;

	if (close(pipe_fd[1]) == -1)
		close_a_fd_and_error(pipe_fd[0], "close pipe_fd[0]" pipex_data);
	fd_outfile = open(pipex_data.outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		close_a_fd_and_error(pipe_fd[0],
			"No such file or directory", pipex_data);
	if (dup2(fd_outfile, 1) == -1 || dup2(pipe_fd[0], 0) == -1)
		close_fds_and_error(fd_infile, pipe_fd[0], "dup2", pipex_data);
	if (close(fd_outfile) == -1)
		close_a_fd_and_error(pipe_fd[0], "close fd_outfile" pipex_data);
	if (close(pipe_fd[0]) == -1)
		error_happened("close pipe_fd[1] in cmd_1", pipex_data);
	path_to_execute = find_path(pipex_data.cmd_2[0], pipex_data.envp);
	if (path_to_execute)
	{
		execve(path_to_execute, pipex_data.cmd_2, pipex_data.envp);
		free(path_to_execute);
	}
	command_not_found(pipex_data.cmd_2, pipex_data.cmd_1);
}

void	execute_cmd_1(t_pipex_data pipex_data, int *pipe_fd)
{
	char	*path_to_execute;
	int		fd_infile;

	if (close(pipe_fd[0]) == -1)
		close_a_fd_and_error(pipe_fd[1], "close pipe_fd[1]" pipex_data);
	fd_infile = open(pipex_data.infile, O_RDONLY);
	if (fd_infile == -1)
		close_a_fd_and_error(pipe_fd[1],
			"No such file or directory", pipex_data);
	if (dup2(fd_infile, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		close_fds_and_error(fd_infile, pipe_fd[1], "dup2", pipex_data);
	if (close(fd_infile) == -1)
		close_a_fd_and_error(pipe_fd[1], "close fd_infile" pipex_data);
	if (close(pipe_fd[1]) == -1)
		error_happened("close pipe_fd[1] in cmd_1", pipex_data);
	path_to_execute = find_path(pipex_data.cmd_1[0], pipex_data.envp);
	if (path_to_execute)
	{
		execve(path_to_execute, pipex_data.cmd_1, pipex_data.envp);
		free(path_to_execute);
	}
	command_not_found(pipex_data.cmd_1, pipex_data.cmd_2);
}
