/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:06:15 by oronda            #+#    #+#             */
/*   Updated: 2021/08/14 20:41:34 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	int		len;
	char	*ptr;

	ptr = NULL;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == (unsigned char)c)
			ptr = &s[i];
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (ptr = &s[i]);
	if (!ptr)
		return (NULL);
	return (ptr);
}
