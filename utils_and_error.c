/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_and_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:37:22 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/27 20:56:11 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_happened(char *place, t_pipex_data pipex_data)
{
	ft_putstr_fd("Error. ", 2);
	ft_putendl_error(place);
	free_cmd(pipex_data.cmd_1);
	free_cmd(pipex_data.cmd_2);
	exit(EXIT_FAILURE);
}

void	close_a_fd_and_error(int fd, char *place, t_pipex_data ppx_d)
{
	close(fd);
	error_happened(place, ppx_d);
}

void	close_fds_and_error(int fd1, int fd2, char *place, t_pipex_data ppx_d)
{
	close(fd1);
	close(fd2);
	error_happened(place, ppx_d);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	storage_data(t_pipex_data *ppx_d, char **argv, char **enviroment_list)
{
	ppx_d->cmd_1 = ft_split(argv[2], 32);
	ppx_d->cmd_2 = ft_split(argv[3], 32);
	ppx_d->infile = argv[1];
	ppx_d->outfile = argv[4];
	ppx_d->envp = enviroment_list;
}
