/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 22:06:25 by oronda            #+#    #+#             */
/*   Updated: 2021/08/06 14:33:48 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	destlen;
	unsigned int	i;
	unsigned int	result;

	i = 0;
	destlen = strlen(dst);
	result = strlen(src);
	if (size <= destlen)
		result += size;
	else
		result += destlen;
	while (src[i] && (destlen + 1 < size))
	{
		dst[destlen] = src[i];
		destlen++;
		i++;
	}
	dst[destlen] = '\0';
	return (result);
}
