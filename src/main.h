/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 09:32:52 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/05 12:05:39 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define READ_FD 0
# define WRITE_FD 1

# include "../lib/libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

int		msg_error(char *err);
int		msg_error_code(char *err, int code);
int		msg_custom_error_code(char *err, int code);
char	*get_env_paths(char **envp);
char	*get_cmd_path(char *cmd_without_flags, char **envp);
void	handle_2e_cmd(int iofile[2], int pipe_end[2], char *cmd2, char **envp);
void	handle_1e_cmd(int iofile[2], int pipe_end[2], char *cmd1, char **envp);

#endif
