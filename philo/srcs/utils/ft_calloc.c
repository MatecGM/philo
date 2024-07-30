/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:49:13 by mateo             #+#    #+#             */
/*   Updated: 2024/07/18 10:08:41 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc_mem;
	size_t	len;

	len = nmemb * size;
	if (!nmemb || !size)
		return (malloc(0));
	if (len / size != nmemb)
		return (NULL);
	alloc_mem = malloc(len);
	if (alloc_mem == NULL)
		return (NULL);
	while (len-- > 0)
		((char *)alloc_mem)[len] = 0;
	return (alloc_mem);
}
