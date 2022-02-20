/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:39:00 by oronda            #+#    #+#             */
/*   Updated: 2022/02/20 21:48:03 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
//#include "mlx.h"
#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>



#define COLOR_GREEN 0x00FF00
#define COLOR_GREEN_STYLE 0x69EC80
#define COLOR_RED 0xFF0000
#define COLOR_BLUE 0x0000FF
#define COLOR_WHITE 0xFFFFFF

#define COLOR_GREY 0xAAAAAA
#define COLOR_DARK_GREY 0x555555


#define mapWidth 24
#define mapHeight 24

void render(t_cube *data);

// int data->map.map[mapWidth][mapHeight]=
// {
//   {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
//   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
//   {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//   {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//   {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
//   {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
//   {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
//   {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//   {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
//   {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//   {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
//   {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
//   {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//   {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
//   {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//   {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//   {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
//   {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//   {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//   {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
// };

int	str_chr_end(char *str, char *strtofind)
{
	int		strlen;
	int		tofind_len;

	if (!str || !strtofind)
		return (0);
	tofind_len = ft_strlen(strtofind);
	strlen = ft_strlen(str);
	if (!tofind_len)
		return (1);
	if (strlen < tofind_len)
		return (0);
	str += strlen - tofind_len;
	while (*str || *strtofind)
	{
		if (*str++ != *strtofind++)
			return (0);
	}
	return (1);
}

int print_error(char* str)
{
	printf("%s", str);
	return (1);
}

int	validate_args(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("enter a unique map as argument\n"));
	if (!str_chr_end(argv[1], ".cub"))
		return (print_error("map format is not .cub\n"));
	return (1);
}

int	exit_hook(void *g_data)
{
	// t_cube	*data;
	// data = (t_cube *)g_data;
	exit(0);
	return (0);
}

void mlx_put_pixel_img(t_img_data *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *((unsigned int *)dst) = color;
}

int handle_input(int keycode, void *g_data)
{
	t_cube	*data;
	data = (t_cube *)g_data;
	double rotSpeed = 3.14 / 8;
	int hasmove = 0;
	//ft_putnbr(keycode);

	//move forward if no wall in front of you
    if (keycode == KEY_UP)
	{
		if(data->map.map[(int)(data->player.x + data->player.dirX)][(int)(data->player.y)] == 0)
		{
			data->player.x += data->player.dirX;
			hasmove = 1;
		}
    		
		if(data->map.map[(int)(data->player.x)][(int)(data->player.y + data->player.dirY)] == 0)
		{
			data->player.y += data->player.dirY;
			hasmove = 1;
		}	
	}

    //move backwards if no wall behind you
    if(keycode == KEY_DOWN) 
    {
      if(data->map.map[(int)(data->player.x - data->player.dirX)][(int)(data->player.y)] == 0)
	  {
		  data->player.x -= data->player.dirX;
		  hasmove = 1;
	  }
    		
		if(data->map.map[(int)(data->player.x)][(int)(data->player.y - data->player.dirY)] == 0)
		{
			data->player.y -= data->player.dirY;
			hasmove = 1;
		}			
    }

    //rotate to the right
    if(keycode == KEY_ROTATE_RIGHT)
    {
		
      //both camera direction and camera plane must be rotated
      double oldDirX = data->player.dirX;
      data->player.dirX = data->player.dirX * cos(-rotSpeed) - data->player.dirY * sin(-rotSpeed);
      data->player.dirY = oldDirX * sin(-rotSpeed) + data->player.dirY * cos(-rotSpeed);
      double oldPlaneX = data->player.planeX;
      data->player.planeX = data->player.planeX * cos(-rotSpeed) - data->player.planeY * sin(-rotSpeed);
      data->player.planeY = oldPlaneX * sin(-rotSpeed) + data->player.planeY * cos(-rotSpeed);
	  hasmove = 1;
    }
    //rotate to the left
    if(keycode == KEY_ROTATE_LEFT)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX =  data->player.dirX;
      data->player.dirX = data->player.dirX * cos(rotSpeed) -  data->player.dirY * sin(rotSpeed);
       data->player.dirY = oldDirX * sin(rotSpeed) +  data->player.dirY * cos(rotSpeed);
      double oldPlaneX =  data->player.planeX;
       data->player.planeX =  data->player.planeX * cos(rotSpeed) -  data->player.planeY * sin(rotSpeed);
       data->player.planeY = oldPlaneX * sin(rotSpeed) +  data->player.planeY * cos(rotSpeed);
	   hasmove = 1;
    }
	
	 
	if (keycode == KEY_LEFT) // STRAFE LEFT
	{
		data->player.x -= data->player.planeX;
		data->player.y -= data->player.planeY;
		hasmove = 1;
	}
	
	if (keycode == KEY_RIGHT) //STRAFE RIGHT
	{
		data->player.x += data->player.planeX;
		data->player.y += data->player.planeY;
		hasmove = 1;
	}
		
	if (keycode == KEY_ECHAP)
	{
		exit(0);
	}
	
	printf("X : %lf , Y :%lf \n", data->player.x, data->player.y);
	

	if(hasmove)
	{
		//mlx_clear_window(data->mlx_ptr, data->wnd_ptr);	
		render(data);
		
	}
	
	return 0;
}

void initPlayer(t_cube *data)
{
	data->player.x = 10;
	data->player.y = 22;  //x and y start position
	data->player.dirX = -1;
	data->player.dirY = 0; //initial direction vector
	data->player.planeX = 0;
	data->player.planeY = 0.66; //the 2d raycaster version of camera plane
}

void init_mlx(t_cube *data)
{
	data->mlx_ptr = mlx_init();
	data->wnd_ptr = mlx_new_window(data->mlx_ptr,SCREEN_WIDTH,SCREEN_HEIGHT,"BelloCubo");
	mlx_hook(data->wnd_ptr, DESTROYNOTIFY,1L << 17, exit_hook, &data);
	mlx_key_hook(data->wnd_ptr, &handle_input, data);
}

void init(t_cube *data)
{
	init_mlx(data);
	initPlayer(data);
	t_img_data img_t;
	img_t.img = mlx_new_image(data->mlx_ptr,SCREEN_WIDTH,SCREEN_HEIGHT);
	img_t.addr = mlx_get_data_addr(img_t.img, &img_t.bpp, &img_t.line_length, &img_t.endian);
	data->img = img_t;
	
}

void draw_rectangle(t_cube *data, t_vector *origin, int xlenght, int ylenght, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y < ylenght)
	{
		x = 0;
		while ( x < xlenght)
		{
			mlx_put_pixel_img(&data->img, origin->x + x, origin->y + y, color);
			x++;
		}
		y++;
	}
}

void generate_textures(t_cube *data)
{
	for(int x = 0; x < texWidth; x++)
	{
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			data->textures.texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			data->textures.texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			data->textures.texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			data->textures.texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			data->textures.texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			data->textures.texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			data->textures.texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			data->textures.texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
}

void calculate_steps(t_ray *ray, t_cube *data)
{
	if(ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->player.x - data->map.mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (data->map.mapX + 1.0 - data->player.x) * ray->deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->player.y - data->map.mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (data->map.mapY + 1.0 - data->player.y) * ray->deltaDistY;
	}
}

void DDA(t_cube *data, t_ray *ray)
{
	ray->hit = 0;
	while(ray->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			data->map.mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			data->map.mapY += ray->stepY;
			ray->side = 1;
		}
		//Check if ray has hit a wall
		if(data->map.map[data->map.mapX][data->map.mapY] > 0) 
			ray->hit = 1;
	}
}

void calculate_wall_height(t_cube *data, t_ray *ray)
{
	
	data->lineHeight = (int)(SCREEN_HEIGHT / ray->perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	data->drawStart = -data->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if(data->drawStart < 0)
		data->drawStart = 0;

	data->drawEnd = data->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if(data->drawEnd >= SCREEN_HEIGHT)
		data->drawEnd = SCREEN_HEIGHT - 1;
}

void calculate_ray_pos_and_dir(t_cube *data, t_ray *ray, int *x)
{
		data->cameraX = 2 * *x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
		ray->rayDirX = data->player.dirX +  data->player.planeX * data->cameraX;
		ray->rayDirY = data->player.dirY + data->player.planeY * data->cameraX;
		//which box of the map we're in
		data->map.mapX = (int)(data->player.x);
		data->map.mapY = (int)(data->player.y);
}

void calculate_ray_x_impact(t_cube *data, t_ray *ray)
{
	
		if (ray->side == 0) 
			ray->wallX = data->player.y + ray->perpWallDist * ray->rayDirY;
		else           
			ray->wallX = data->player.x + ray->perpWallDist * ray->rayDirX;
		ray->wallX -= floor((ray->wallX));
}

void calculate_tex_x_coordinate(t_cube *data, t_ray *ray)
{
		//x coordinate on the texture
		data->texX = (int)(ray->wallX * (double)(texWidth));
		if(ray->side == 0 && ray->rayDirX > 0)
			data->texX = texWidth - data->texX - 1;
		if(ray->side == 1 && ray->rayDirY < 0)
			data->texX = texWidth - data->texX - 1;
}

void draw_texture(t_cube *data, t_ray *ray, int *x)
{
	double step = 1.0 * texHeight / data->lineHeight;
	double texPos = (data->drawStart - SCREEN_HEIGHT / 2 + data->lineHeight / 2) * step;

	int y;
	y = data->drawStart;
	//for(int y = data->drawStart; y< data->drawEnd; y++)
	while(y < data->drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;
		int color = data->textures.texture[data->texNum][texHeight * texY + data->texX];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(ray->side == 1) color = (color >> 1) & 8355711;
		mlx_put_pixel_img(&data->img, *x, y, color);
		y++;
	}
}

void render(t_cube *data)
{
  
	draw_rectangle(data,&((t_vector){0,0}),SCREEN_WIDTH,SCREEN_HEIGHT/2,COLOR_GREY);
	draw_rectangle(data,&((t_vector){0,SCREEN_HEIGHT/2}),SCREEN_WIDTH,SCREEN_HEIGHT/2,COLOR_DARK_GREY);
	t_ray ray;
	
    // for(int x = 0; x < SCREEN_WIDTH; x++)
	int x;
	x = -1;
	while(++x < SCREEN_WIDTH)
    {
		//calculate ray position and direction
		// data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
		// ray.rayDirX = data->player.dirX +  data->player.planeX * data->cameraX;
		// ray.rayDirY = data->player.dirY + data->player.planeY * data->cameraX;
		// //which box of the map we're in
		// data->map.mapX = (int)(data->player.x);
		// data->map.mapY = (int)(data->player.y);
		calculate_ray_pos_and_dir(data,&ray,&x);

		//length of ray from current position to next x or y-side
		// double sideDistX;
		// double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (raydata.player.dirX * raydata.player.dirX))
		//deltaDistY = sqrt(1 + (raydata.player.dirX * raydata.player.dirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / raydata.player.dirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (raydata.player.dirX, rayDirY). Its length,
		//unlike (data.player.dirX, data.player.dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.

		//double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		//double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		 ray.deltaDistX =(ray.rayDirX == 0) ? 1e30 : fabs(1 / ray.rayDirX);
		 ray.deltaDistY = (ray.rayDirY == 0) ? 1e30 : fabs(1 / ray.rayDirY);

		//double perpWallDist;

      	//what direction to step in x or y-direction (either +1 or -1)
		// int stepX;
		// int stepY;

		// int hit = 0; //was there a wall hit?
		// int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		// if(ray.rayDirX < 0)
		// {
		// 	ray.stepX = -1;
		// 	ray.sideDistX = (data->player.x - data->map.mapX) * ray.deltaDistX;
		// }
		// else
		// {
		// 	ray.stepX = 1;
		// 	ray.sideDistX = (data->map.mapX + 1.0 - data->player.x) * ray.deltaDistX;
		// }
		// if(ray.rayDirY < 0)
		// {
		// 	ray.stepY = -1;
		// 	ray.sideDistY = (data->player.y - data->map.mapY) * ray.deltaDistY;
		// }
		// else
		// {
		// 	ray.stepY = 1;
		// 	ray.sideDistY = (data->map.mapY + 1.0 - data->player.y) * ray.deltaDistY;
		// }
		calculate_steps(&ray, data);

		//perform DDA
		// ray.hit = 0;
		// while(ray.hit == 0)
		// {
		// 	//jump to next map square, either in x-direction, or in y-direction
		// 	if(ray.sideDistX < ray.sideDistY)
		// 	{
		// 		ray.sideDistX += ray.deltaDistX;
		// 		data->map.mapX += ray.stepX;
		// 		ray.side = 0;
		// 	}
		// 	else
		// 	{
		// 		ray.sideDistY += ray.deltaDistY;
		// 		data->map.mapY += ray.stepY;
		// 		ray.side = 1;
		// 	}
		// 	//Check if ray has hit a wall
		// 	if(data->map.map[data->map.mapX][data->map.mapY] > 0) ray.hit = 1;
		// }
		DDA(data,&ray);

		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - data.player.x + (1 - stepX) / 2) / raydata.player.dirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(ray.side == 0)
			ray.perpWallDist = (ray.sideDistX - ray.deltaDistX);
		else 
			ray.perpWallDist = (ray.sideDistY - ray.deltaDistY);
		
		// perpWallDist = (sideDistY - deltaDistY);


		// //Calculate height of line to draw on screen
		// int lineHeight = (int)(SCREEN_HEIGHT / ray.perpWallDist);

		// //calculate lowest and highest pixel to fill in current stripe
		// int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		// if(drawStart < 0)
		// 	drawStart = 0;

		// int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		// if(drawEnd >= SCREEN_HEIGHT)
		// 	drawEnd = SCREEN_HEIGHT - 1;
		calculate_wall_height(data,&ray);
		
		//texturing calculations
		data->texNum = data->map.map[data->map.mapX][data->map.mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		// double wallX; //where exactly the wall was hit
		// if (ray.side == 0) 
		// 	wallX = data->player.y + ray.perpWallDist * ray.rayDirY;
		// else           
		// 	wallX = data->player.x + ray.perpWallDist * ray.rayDirX;
		// wallX -= floor((wallX));
		calculate_ray_x_impact(data, &ray);

		// //x coordinate on the texture
		// data->texX = (int)(ray.wallX * (double)(texWidth));
		// if(ray.side == 0 && ray.rayDirX > 0)
		// 	data->texX = texWidth - data->texX - 1;
		// if(ray.side == 1 && ray.rayDirY < 0)
		// 	data->texX = texWidth - data->texX - 1;
		calculate_tex_x_coordinate(data ,&ray);

		
		// // How much to increase the texture coordinate per screen pixel
		// double step = 1.0 * texHeight / data->lineHeight;

		// // Starting texture coordinate
		// double texPos = (data->drawStart - SCREEN_HEIGHT / 2 + data->lineHeight / 2) * step;

		// for(int y = data->drawStart; y< data->drawEnd; y++)
		// {
		// 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		// 	int texY = (int)texPos & (texHeight - 1);
		// 	texPos += step;
		// 	int color = data->textures.texture[data->texNum][texHeight * texY + texX];
		// 	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// 	if(ray.side == 1) color = (color >> 1) & 8355711;
		// 	mlx_put_pixel_img(&data->img, x, y, color);
		// }

		draw_texture(data,&ray, &x);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->wnd_ptr, data->img.img, 0, 0);
}

int main(int argc, char **argv)
{	
	t_cube data;
	validate_args(argc, argv);
	int fd = open(argv[1], O_RDONLY);
	if(!parse_cub_file_map(fd,argv[1], &data,0))
		return (print_error("error\n"));
	

	// init(&data);
	// generate_textures(&data);
	// render(&data);
	//mlx_loop(data.mlx_ptr);
	return 0;
}
