/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:24:03 by oronda            #+#    #+#             */
/*   Updated: 2022/02/20 21:45:17 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cube.h"



int is_valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c !='S' && c != 'E' && c != 'W' && c != ' ' )
		return 0;
	return 1;
}

void remove_newline(char *line)
{
  if (line[ft_strlen(line) - 1] == '\n')
    line[ft_strlen(line) - 1] = '\0';
}



int    parse_cub_file_map(int fd, char *file, t_cube *data, int nb_of_line_before)
{
	char 	*line;
    int      max_line_lenght;
    char    **map;
	int 	nb_of_lines; 


 // ---------VERIFY THE MAP --------- (First pass)
 	nb_of_lines = 0;
	line = get_next_line(fd);
	if(!line)
		return 0;
	max_line_lenght = 0;
	while(line)
	{
		remove_newline(line);
		int i;
		int line_lenght;

		i = 0;
		if (line[i] == 0) // line is empty
			return 0;
		nb_of_lines++;
		
		line_lenght = ft_strlen(line);

		if (max_line_lenght < line_lenght)
			max_line_lenght = line_lenght;
		
		while(i < line_lenght)
			if(!is_valid_char(line[i++]))
				return 0;
		free(line);
		line = get_next_line(fd);
		
		
	}
	if (nb_of_lines < 3) // has to be minimum 3 lines for a valid map
		return 0;

	close(fd);
	fd  = open(file, O_RDONLY);

	
	
 // ---------PARSE THE MAP --------- (second pass)
 	int k;
	k = 0;
	while(k++ < nb_of_line_before) // go to the begining of the map
		free(get_next_line(fd));
	int x;
	int y;
	x = 0;
	y = 0;
	map = (char **)malloc(sizeof(char *) * nb_of_lines);
	while(x < nb_of_lines)
	{
		map[x] = (char *)malloc(sizeof(char) * (max_line_lenght));
		memset(map[x],0,max_line_lenght);
		x++;
	}
		
	line = get_next_line(fd);
	
	while(line)
	{	
		remove_newline(line);
		x = 0;
		while(x < strlen(line))
		{
			if (line[x] == ' ')
				map[y][x] = 0;
			else
				map[y][x] = line[x] - '0';
			x++;
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}

	
	for (int j = 0; j < nb_of_lines; j++)
	{
		for (int i = 0; i < max_line_lenght; i++)
		{
			printf("%d", map[j][i]);
		}
		printf("\n");
	}
	return 1;
}

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return 1;
	return 0;
}

// int get_floor_color(char *str)
// {
// 	char *temp = str;
// 	while(is_space(*temp))
// 		temp++;
// 	int R = ft_atoi(temp);
// }