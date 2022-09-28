/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 11:46:23 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/09/28 11:46:39 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handle_second_command(int iofile[2], int pipe_end[2], char *cmd2, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	dup2(pipe_end[READ_FD], STDIN_FILENO);
	close(pipe_end[WRITE_FD]);
	dup2(iofile[WRITE_FD], STDOUT_FILENO);
	splitted_cmd = ft_split(cmd2, ' ');
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	execve(path_and_cmd, splitted_cmd, envp);
}

void	handle_first_command(int iofile[2], int pipe_end[2], char *cmd1, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	dup2(pipe_end[WRITE_FD], STDOUT_FILENO);
	close(pipe_end[READ_FD]);
	dup2(iofile[READ_FD], STDIN_FILENO);
	splitted_cmd = ft_split(cmd1, ' ');
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	execve(path_and_cmd, splitted_cmd, envp);
}
