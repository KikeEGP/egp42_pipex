/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:07:36 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/24 20:10:23 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd_2(t_pipex_data pipex_data, int *pipe_fd)
{
	char	*path_to_execute;
	int		fd_outfile;

	if (close(pipe_fd[1]) == -1)
		error_happened(-1, "close pipe_fd[0] in cmd_1");
	fd_outfile = open(pipex_data.outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		error_happened(-1, "No such file or directory");
	if (dup2(fd_outfile, 1) == -1 || dup2(pipe_fd[0], 0) == -1)
		error_happened(-1, "dup2() in cmd_1");
	if (close(fd_outfile) == -1)
		error_happened(-1, "close fd_infile in cmd_1");
	if (close(pipe_fd[0]) == -1)
		error_happened(-1, "close pipe_fd[1] in cmd_1");
	path_to_execute = find_path(pipex_data.cmd_2[0], pipex_data.envp);
	if (path_to_execute)
	{
		execve(path_to_execute, pipex_data.cmd_1, pipex_data.envp);
		free(path_to_execute);
	}
	ft_putstr_fd(pipex_data.cmd_2[0], 2);
	ft_putendl_error(": command not found");
	exit(127);
}

void	execute_cmd_1(t_pipex_data pipex_data, int *pipe_fd)
{
	char	*path_to_execute;
	int		fd_infile;

	if (close(pipe_fd[0]) == -1)
		error_happened(-1, "close pipe_fd[0] in cmd_1");
	fd_infile = open(pipex_data.infile, O_RDONLY);
	if (fd_infile == -1)
		error_happened(-1, "No such file or directory");
	if (dup2(fd_infile, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		error_happened(-1, "dup2() in cmd_1");
	if (close(fd_infile) == -1)
		error_happened(-1, "close fd_infile in cmd_1");
	if (close(pipe_fd[1]) == -1)
		error_happened(-1, "close pipe_fd[1] in cmd_1");
	path_to_execute = find_path(pipex_data.cmd_1[0], pipex_data.envp);
	if (path_to_execute)
	{
		execve(path_to_execute, pipex_data.cmd_1, pipex_data.envp);
		free(path_to_execute);
	}
	ft_putstr_fd(pipex_data.cmd_1[0], 2);
	ft_putendl_error(": command not found");
	exit(127);
}
