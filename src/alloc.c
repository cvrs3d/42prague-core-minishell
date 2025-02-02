/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:27:16 by yustinov          #+#    #+#             */
/*   Updated: 2025/01/30 16:37:53 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_calloc
	Prevents an overflow allocation
	Passes flow to the memset to clear
	allocated memory and set it to 0
	returns *void
*/
void *ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (size != 0 && nmemb > ULONG_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
