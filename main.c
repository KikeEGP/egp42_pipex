/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:39:23 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/22 15:00:40 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	pid_t	fork_pid;
	int	pipefd[2];
	char	str[100];

	ft_bzero(str, 100);
	if (argc == 5)
	{
		if (pipe(pipefd) == -1)
			return (1);
		fork_pid = fork();
		if (fork_pid == -1)
			return(1);
		if (fork_pid == 0)
		{
			close(pipefd[0]);
			ft_printf("CHILD: %s, pid is %d\n", argv[0], fork_pid);
			ft_printf("\tpipefd open is %d\n", pipefd[0]);
			ft_printf("\tstr is %s\n", str);
			write(pipefd[1], "Hello\n", 6);
			close(pipefd[1]);
		}
		/* infile command1 | command2 outfile <-shell
		 * infile command1 command2 outfile <-my program
		 * 
		 * These are the expected arguments for pipex
		 *
		 *
		 * */
	/*	*	* PARSE	*	*	*/
		//1) file1 exists? path to command1? 
			//argv[2][0] is a "|"?	
			//What about command2 and file2?
		//2)
	/*	*	Next step	*	*/
		if (fork_pid > 0)
		{
			close(pipefd[1]);
			wait(NULL);
			ft_printf("PARENT: %s, pid is %d\n", argv[0], fork_pid);
			ft_printf("\tpipefd open is %d\n", pipefd[1]);
			read(pipefd[0], str, 6);
			ft_printf("\tstr is %s", str);
			close(pipefd[0]);
			return (0);//correct execution, end
		}
	}
	return (1);//wrong execution
}
