/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 11:46:23 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/09/29 20:44:38 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handle_2e_cmd(int iofd[2], int pipe_end[2], char *cmd2, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	dup2(pipe_end[READ_FD], STDIN_FILENO);
	close(pipe_end[WRITE_FD]);
	dup2(iofd[WRITE_FD], STDOUT_FILENO);
	splitted_cmd = ft_split(cmd2, ' ');
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	if (path_and_cmd == NULL)
		exit(msg_error_code(splitted_cmd[0], 127));
	execve(path_and_cmd, splitted_cmd, envp);
	if (cmd2[0] == '\0')
		exit(msg_error_code(cmd2, 126));
	if (ft_isspace(cmd2[0]))
		exit(msg_error_code(cmd2, 127));
}

void	handle_1e_cmd(int iofd[2], int pipe_end[2], char *cmd1, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	if (iofd[READ_FD] < 0)
		exit(1);
	dup2(pipe_end[WRITE_FD], STDOUT_FILENO);
	close(pipe_end[READ_FD]);
	dup2(iofd[READ_FD], STDIN_FILENO);
	splitted_cmd = ft_split(cmd1, ' ');
	path_and_cmd = get_cmd_path(splitted_cmd[0], envp);
	if (path_and_cmd == NULL)
		msg_error_code(splitted_cmd[0], 127);
	execve(path_and_cmd, splitted_cmd, envp);
	if (cmd1[0] == '\0' || ft_isspace(cmd1[0]))
		exit(msg_error_code(cmd1, 0));
}
