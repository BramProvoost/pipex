/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 09:31:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/06 12:17:59 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	wait_on_childs(pid_t pid1, pid_t pid2)
{
	int	wstatus;

	waitpid(pid1, NULL, 0);
	waitpid(pid2, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit(WEXITSTATUS(wstatus));
}

void	pipex(int iofd[2], char *argv[], char **envp)
{
	int		pipe_end[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipe_end);
	pid1 = fork();
	if (pid1 < 0)
		return (exit(msg_error("fork 1")));
	if (pid1 == 0)
		handle_1e_cmd(iofd, pipe_end, argv[2], envp);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (exit(msg_error("fork 2")));
		if (pid2 == 0)
			handle_2e_cmd(iofd, pipe_end, argv[3], envp);
		close(pipe_end[READ_FD]);
		close(pipe_end[WRITE_FD]);
		wait_on_childs(pid1, pid2);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int	iofd[2];

	if (argc != 5)
		return (1);
	iofd[READ_FD] = open(argv[1], O_RDONLY);
	if (iofd[READ_FD] < 0)
		msg_error(argv[1]);
	iofd[WRITE_FD] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (iofd[WRITE_FD] < 0 || access(argv[4], W_OK) != 0)
		exit(msg_error_code(argv[4], 1));
	pipex(iofd, argv, envp);
	return (0);
}
