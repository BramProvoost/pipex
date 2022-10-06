/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 11:44:58 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/06 12:35:51 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_env_paths(char **envp)
{
	char	*paths;

	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		exit(127);
	paths = ft_strjoin(*envp + ft_strlen("PATH="), "/");
	if (!paths)
		exit(1);
	return (paths);
}

char	*get_cmd_path(char *cmd_without_flags, char **envp)
{
	char	*paths;
	char	**path;
	char	*tmp;
	char	*path_and_cmd;

	paths = get_env_paths(envp);
	path = ft_split(paths, ':');
	if (!path)
		exit(1);
	if (access(cmd_without_flags, X_OK) == 0)
		return (cmd_without_flags);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		path_and_cmd = ft_strjoin(tmp, cmd_without_flags);
		if (!tmp || !path_and_cmd)
			exit(1);
		free(tmp);
		if (access(path_and_cmd, X_OK) == 0)
			return (path_and_cmd);
		free(path_and_cmd);
		path++;
	}
	return (NULL);
}
