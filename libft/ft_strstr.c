/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:10:37 by oronda            #+#    #+#             */
/*   Updated: 2021/08/04 22:46:10 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strstr(char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!(*needle))
		return (haystack);
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{	
			while (needle[j])
			{
				if (haystack[i + j] == needle[j])
					j++;
				else
					break ;
				if (needle[j] == '\0')
					return (haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
