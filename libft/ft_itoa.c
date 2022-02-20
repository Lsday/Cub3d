/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:22:19 by oronda            #+#    #+#             */
/*   Updated: 2021/08/08 22:09:31 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_count(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static char	*zero(char *result)
{
	result = malloc(2);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

static char	*positive(char *result, int digits, unsigned int unb)
{
	result = malloc(sizeof(char) * digits + 1);
	if (!result)
		return (NULL);
	result[digits] = '\0';
	while (digits)
	{
		result[digits - 1] = (unb % 10) + '0';
		unb /= 10;
		digits--;
	}
	return (result);
}

static char	*negative(char *result, int digits, unsigned int unb)
{
	result = malloc(sizeof(char) * digits + 2);
	if (!result)
		return (NULL);
	result[digits + 1] = '\0';
	result[0] = '-';
	while (digits)
	{
		result[digits] = (unb % 10) + '0';
		unb /= 10;
		digits--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int				signe;
	unsigned int	unb;
	char			*result;
	int				digits;

	result = NULL;
	signe = 1;
	if (n < 0)
	{
		signe = -1;
		unb = (unsigned int)(n *= -1);
	}
	else
		unb = (unsigned int)n;
	digits = digits_count(unb);
	if (unb == 0)
		result = zero(result);
	else if (signe > 0)
		result = positive(result, digits, unb);
	else if (signe < 0)
		result = negative(result, digits, unb);
	return (result);
}
