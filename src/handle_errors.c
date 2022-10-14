/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:32:47 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 14:01:31 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	msg_error_code(char *err, int code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
	return (code);
}

int	msg_error(char *err)
{
	return (msg_error_code(err, errno));
}

int	msg_custom_error_code(char *err, char *cmd, int code)
{
	ft_putstr_fd(err, 2);
	ft_putendl_fd(cmd, 2);
	return (code);
}
