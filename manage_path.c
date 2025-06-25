/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:51:47 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/25 18:35:59 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*join_cmd_and_path(char *cmd, char *route_tested)
{
	char	*aux;
	char	*result;

	aux = ft_strjoin(route_tested, "/");
	if (!aux)
		return (NULL);
	result = ft_strjoin(aux, cmd);
	if (!result)
	{
		free(aux);
		return (NULL);
	}
	free(aux);
	return (result);
}

static char	*check_access_cmd(char *cmd, char **path_splitted)
{
	char	*route;
	char	*testing_route;
	int		access_returned;

	route = NULL;
	access_returned = -1;
	while (access_returned == -1 && *path_splitted != NULL)
	{
		testing_route = join_cmd_and_path(cmd, *path_splitted);
		// dprintf(2, "%s\n", testing_route);
		//write(2, "manage_path1\n", 13);
		if (testing_route == NULL)
			return (NULL);
		access_returned = access(testing_route, X_OK);
		if (access_returned == 0)
		{
			route = testing_route;
			break ;
		}
		(*path_splitted)++;
	}
	return (route);
}

char	*find_path(char *cmd, char **envp)
{
	char	*route;
	char	**path_splitted;

	route = NULL;
	path_splitted = NULL;
	
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '/' || ft_strchr(cmd, 47))
		return (cmd);
	// while (*envp != NULL && !ft_strnstr(*envp, "PATH=", 5))
	// {
	// 	//write(2, "manage_path2\n", 13);
	// 	(*envp)++;
	// }

	int i;

	i = 0;
	char *res;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			res = ft_strdup(envp[i]);
			// dprintf(2, "%s\n", envp[i]);
		}
		i++;
	}

	//dprintf(2, "ENVP ==> %s\n", *envp);
	if (res != NULL)
	{
		path_splitted = ft_split(res + 5, ':');
		route = check_access_cmd(cmd, path_splitted);
	}
	return (route);
}
