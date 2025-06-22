/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:39:23 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/22 14:06:15 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	pid_t	fork_pid;

	if (argc == 5)
	{
		fork_pid = fork();
		if (fork_pid == -1)
			return(1);
		if (fork_pid == 0)
			ft_printf("We are in child of %s\n", argv[0]);
		/* <file1 command1 | command2 >file2
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
			return (0);//correct execution, end
	}
	return (1);//wrong execution
}
