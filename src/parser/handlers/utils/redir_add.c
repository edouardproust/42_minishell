/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:41:32 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:43:14 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Adds a new element to a NULL-terminated redirection array in t_cmd,
 * resizing it dynamically.
 *
 * @param cmd_array Pointer to the array to modify.
 * @param new_element Element to add.
 * @param element_size Size of each element in the array.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on allocation failure.
 */
static int add_to_cmd_redir_array(void ***cmd_array, void *new_element,
	size_t element_size)
{
    size_t count = ft_matrix_size((char **)*cmd_array);
    size_t old_size = (count + 1) * element_size;
    size_t new_size = (count + 2) * element_size;

    void **new_array = (void **)ft_realloc(*cmd_array, old_size, new_size);
    if (!new_array)
        return (EXIT_FAILURE);
    new_array[count] = new_element;
    new_array[count + 1] = NULL;
    *cmd_array = new_array;
    return (EXIT_SUCCESS);
}

/**
 * Add a new t_infile to the infiles array of t_cmd.
 *
 * @param cmd Pointer to t_cmd struct
 * @param new_infile Pointer to the new t_infile to add
 * @return EXIT_SUCCESS if success, EXIT_FAILURE if malloc failure
 */
int add_infile_to_cmd(t_cmd *cmd, t_infile *new_infile)
{
    return add_to_cmd_redir_array(
		(void ***)&cmd->infiles, new_infile, sizeof(t_infile *)
    );
}

/**
 * Add a new t_outfile to the outfiles array of t_cmd.
 *
 * @param cmd Pointer to t_cmd struct
 * @param new_infile Pointer to the new t_infile to add
 * @return EXIT_SUCCESS if success, EXIT_FAILURE if malloc failure
 */
int add_outfile_to_cmd(t_cmd *cmd, t_outfile *new_outfile)
{
    return add_to_cmd_redir_array(
		(void ***)&cmd->outfiles, new_outfile, sizeof(t_outfile *)
	);
}
