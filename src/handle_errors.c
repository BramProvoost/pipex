/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:32:47 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/06 11:25:21 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	msg_error(char *err)
{
	int	nr;

	nr = errno;
	write(2, "pipex: ", 7);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (nr);
}

int	msg_error_code(char *err, int code)
{
	write(2, "pipex: ", 7);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (code);
}

int	msg_custom_error_code(char *err, char *cmd, int code)
{
	write(2, err, ft_strlen(err));
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (code);
}
