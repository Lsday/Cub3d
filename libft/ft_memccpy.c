/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:59:48 by oronda            #+#    #+#             */
/*   Updated: 2021/08/02 19:59:48 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	unsigned int	i;
	unsigned char	uc;

	i = -1;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	uc = (unsigned char)c;
	while (++i < n)
	{
		*dest_ptr = *src_ptr;
		if (uc == *src_ptr)
			return (dest_ptr + 1);
		dest_ptr++;
		src_ptr++;
	}
	return (NULL);
}
