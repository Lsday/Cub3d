/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:24:03 by oronda            #+#    #+#             */
/*   Updated: 2022/02/17 16:52:38 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetNextLine/get_next_line.h"
#include "fcntl.h"
#include "cube.h"

int is_valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'N'&& c !='S' && c != 'E' && c != 'W' && c != '\n' )
		return 0;
	return 1;
}

int parse_map(char *str, t_cube *data)
{
	int fd;
	fd = open(str,O_RDONLY);
	if (fd <= 0)
		return 0;
	char *line;
	int nb_of_lines = 0;

	while((line = get_next_line(fd)))
	{
		nb_of_lines++;
		int i = -1;
		int j = ft_strlen(line);
		while(++i < j)
		{
			if(!is_valid_char(line[i]))
				return 0;
		}
	}
	data->map.map = malloc(sizeof(char *) * nb_of_lines);
	close(fd);
	fd = open(str,O_RDONLY);
	int i = -1;
	while((line = get_next_line(fd)))
	{	
		i++;
		int l = ft_strlen(line);
		data->map.map[i] = malloc(sizeof(char) * l);
		int k = 0;
		while(k < l)
		{
			data->map.map[i][k] = line[k];
			printf("%c",data->map.map[i][k]);
			k++;
		}
	}
	return 1;

	
	
	
	
}