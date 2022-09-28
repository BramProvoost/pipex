/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 09:31:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/09/28 11:48:17 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
		handle_first_command(iofile, pipe_end, argv[2], envp);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (perror("Fork2: "));
		if (pid2 == 0)
			handle_second_command(iofile, pipe_end, argv[3], envp);
		close(pipe_end[READ_FD]);
		close(pipe_end[WRITE_FD]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0); 
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int	iofile[2];

	if (argc != 5)
		return (-1);
	iofile[READ_FD] = open(argv[1], O_RDONLY);
	iofile[WRITE_FD] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (iofile[READ_FD] < 0 || iofile < 0)
		return (-1);
	pipex(iofile, argv, envp);
	return (0);
}
