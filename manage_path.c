/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:51:47 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/06/27 19:14:23 by enrgil-p         ###   ########.fr       */
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
	int		i;

	route = NULL;
	access_returned = -1;
	i = 0;
	while (access_returned == -1 && path_splitted[i] != NULL)
	{
		testing_route = join_cmd_and_path(cmd, path_splitted[i]);
		if (testing_route == NULL)
			return (NULL);
		access_returned = access(testing_route, X_OK);
		if (access_returned == 0)
			route = testing_route;
		i++;
		if (!route)
			free(testing_route);//tryin
	}
	return (route);
}

char	*find_path(char *cmd, char **envp)
{
	char	*route;
	char	*path_found;
	char	**path_splitted;
	int	i;

	route = NULL;
	path_found = NULL;
	path_splitted = NULL;
	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '/' || ft_strchr(cmd, 47))
		return (ft_strdup(cmd));
	while (!path_found && envp[i] != NULL)
		path_found = ft_strnstr(envp[i++], "PATH=", 5);
	if (path_found != NULL)
	{
		path_splitted = ft_split(path_found + 5, ':');
		route = check_access_cmd(cmd, path_splitted);
		if (!route)
			free_cmd(path_splitted);
	}
	return (route);
}
