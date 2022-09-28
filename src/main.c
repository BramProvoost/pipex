/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 09:31:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/09/28 09:43:52 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_env_paths(char **envp)
{
	char	*paths;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = ft_strjoin(*envp + ft_strlen("PATH="), "/");
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
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		path_and_cmd = ft_strjoin(tmp, cmd_without_flags);
		free(tmp);
		if (access(path_and_cmd, 0) == 0)
			return (path_and_cmd);
		free(path_and_cmd);
		path++;
	}
	return (NULL);
}

void	child_process(int iofile[2], int pipe_end[2], char *cmd1, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	splitted_cmd = ft_split(cmd1, ' ');
	printf("cmd1: %s\n", cmd1);
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	close(iofile[0]);
	dup2(iofile[1], 0);
	close(iofile[1]);
	execve(path_and_cmd, splitted_cmd, envp);
}

void	parent_process(int iofile[2], int pipe_end[2], char *cmd2, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;
	int		status;

	splitted_cmd = ft_split(cmd2, ' ');
	waitpid(-1, &status, 0);
	printf("cmd2: %s\n", cmd2);
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	close(pipe_end[0]);
	dup2(0, pipe_end[1]);
	close(iofile[0]);
	execve(path_and_cmd, splitted_cmd, envp);
}

void	handle_second_command(int iofile[2], int pipe_end[2], char *cmd2, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	close(iofile[1]);
	dup2(iofile[0], STDOUT_FILENO);
	close(iofile[0]);
	splitted_cmd = ft_split(cmd2, ' ');
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	execve(path_and_cmd, splitted_cmd, envp);
}

void	handle_first_command(int iofile[2], int pipe_end[2], char *cmd1, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	close(iofile[0]);
	dup2(iofile[1], STDIN_FILENO);
	close(iofile[1]);
	splitted_cmd = ft_split(cmd1, ' ');
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	execve(path_and_cmd, splitted_cmd, envp);
}

void	pipex(int iofile[2], char *argv[], char **envp)
{
	int		pipe_end[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipe_end);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("Fork1: "));
	if (pid1 == 0)
		handle_first_command(iofile, pipe_end, argv[1], envp);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (perror("Fork2: "));
		if (pid2 == 0)
			handle_second_command(iofile, pipe_end, argv[3], envp);
		close(iofile[1]);
		close(iofile[0]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0); 
	}
	// if (pid == 0)
	// 	child_process(iofile, pipe_end, argv[2], envp);
	// else
	// 	parent_process(iofile, pipe_end, argv[3], envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int	iofile[2];

	if (argc != 5)
		return (-1);
	iofile[0] = open(argv[1], O_RDONLY);
	iofile[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (iofile[0] < 0 || iofile < 0)
		return (-1);
	pipex(iofile, argv, envp);
	return (0);
}

/*
infile -> cmd1 ->    |     -> cmd2 -> outfile
       ^       ^     ^     ^       ^         
      dup2    dup2  pipe  dup2    dup2       
       1       2           1       2         

intput types:
	- file
	- cmd
*/

// https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901
