/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:31 by oronda            #+#    #+#             */
/*   Updated: 2021/08/08 19:15:21 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	else
		return (0);
}

static char	*get_substr(char const *s, char sep)
{
	int		i;
	int		len;
	char	*result;

	len = 0;
	i = 0;
	while (!is_sep(s[i], sep) && s[i])
	{
		len ++;
		i++;
	}
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (!is_sep(s[i], sep) && s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

void	cut_str(char const *s, char sep, char **result)
{
	int		i;
	int		j;
	int		k;
	char	*substr;

	i = 0;
	j = 0;
	k = -1;
	while (s[i])
	{
		j = 0;
		while (!is_sep(s[i], sep) && s[i])
		{
			if (!j)
				substr = get_substr(&(s[i]), sep);
			i++;
			j++;
		}
		if (j)
			result[++k] = substr;
		while (is_sep(s[i], sep))
			i++;
	}
	result[++k] = 0;
}

static int	count_words(char const *s, char sep)
{
	int	i;
	int	j;
	int	wcount;

	wcount = 0;
	i = 0;
	while (s[i])
	{	
		j = 0;
		while (!is_sep(s[i], sep) && s[i])
		{	
			if (!j)
				wcount++;
			j++;
			i++;
		}
		while (is_sep(s[i], sep) && s[i])
			i++;
	}
	return (wcount);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	cut_str(s, c, result);
	return (result);
}
