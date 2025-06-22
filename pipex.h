/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:40:19 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/22 19:33:47 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/complete_libft.h"
# include <unistd.h>
# include <sys/wait.h>

typedef struct	s_pipex_data
{
	char	**cmd_1;
	char	**cmd_2;
	char	*infile;
	char	*outfile;
	char	**envp;
}	t_pipex_data;

void	storage_data(t_pipex_data *ppx_d, char **argv, char **enviroment_list);
void	error_happened(int failure, char *place);

#endif
