/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Set errno to the given value.
 *
 * @param err_no Value for errno
 * @return void
 */
void	set_errno(int err_no)
{
	if (err_no >= 0)
		errno = err_no;
}

/**
 * Get a pointer to the static error buffer.
 * This buffer is initialized once and reused.
 */
static t_errorbuffer	*get_error_buffer(void)
{
	static t_errorbuffer	err_buf = {
		.buffer = {0},
		.index = 0
	};

	return (&err_buf);
}

/**
 * Append a string to the error buffer.
 * If the buffer is full, flush it first.
 */
void	append_to_error_buffer(const char *str)
{
	t_errorbuffer	*err_buf;
	int				len;

	err_buf = get_error_buffer();
	len = strlen(str);
	if (err_buf->index + len >= ERROR_BUFFER_SIZE)
	{
		flush_error_buffer();
	}
	memcpy(err_buf->buffer + err_buf->index, str, len);
	err_buf->index += len;
}

/**
 * Flush the error buffer to stderr.
 */
void	flush_error_buffer(void)
{
	t_errorbuffer	*err_buf;

	err_buf = get_error_buffer();
	if (err_buf->index > 0)
	{
		write(STDERR_FILENO, err_buf->buffer, err_buf->index);
		err_buf->index = 0;
	}
}
