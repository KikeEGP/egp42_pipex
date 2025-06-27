/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:40:19 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/27 20:51:31 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/complete_libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex_data
{
	char	**cmd_1;
	char	**cmd_2;
	char	*infile;
	char	*outfile;
	char	**envp;
}	t_pipex_data;
/*	*	*	*   utils_and_error.c	*	*	*	*/
void	storage_data(t_pipex_data *ppx_d, char **argv, char **enviroment_list);
void	free_cmd(char **cmd);
void	error_happened(char *place, t_pipex_data pipex_data);
void	close_a_fd_and_error(int fd, char *place, t_pipex_data ppx_d);
void	close_fds_and_error(int fd1, int fd2, char *place, t_pipex_data ppx_d);
/*	*	*	*	*	*	*	*	*	*/
/*									*/
/*	*	*	* 	childs.c	*	*	*	*/
void	execute_cmd_1(t_pipex_data pipex_data, int *pipe_fd);
void	execute_cmd_2(t_pipex_data pipex_data, int *pipe_fd);
/*	*	*	*	*	*	*	*	*	*/
/*									*/
/*	*	*	*     manage_path.c	*	*	*	*/
char	*find_path(char *cmd, char **envp);

#endif
