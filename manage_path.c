/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:51:47 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/24 20:12:43 by enrgil-p         ###   ########.fr       */
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
		if (testing_route == NULL)
			return (NULL);
		access_returned = access(testing_route, X_OK);
		if (access_returned == 0)
			route = testing_route;
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
	if (cmd[0] == '/' || ft_strchr(cmd, 47))
		return (cmd);
	while (*envp != NULL && !ft_strnstr(*envp, "PATH=", 5))
		(*envp)++;
	if (*envp != NULL)
	{
		path_splitted = ft_split(*envp, ':');
		route = check_access_cmd(cmd, path_splitted);
	}
	return (route);
}
