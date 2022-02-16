/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:39:00 by oronda            #+#    #+#             */
/*   Updated: 2022/02/11 21:50:52 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../mlx_linux/mlx.h"
#include "mlx.h"
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


int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

void    mlx_put_pixel_img(t_img_data *img, int x, int y, int color)
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
		if(worldMap[(int)(data->player.x + data->player.dirX)][(int)(data->player.y)] == 0)
		{
			data->player.x += data->player.dirX;
			hasmove = 1;
		}
    		
		if(worldMap[(int)(data->player.x)][(int)(data->player.y + data->player.dirY)] == 0)
		{
			data->player.y += data->player.dirY;
			hasmove = 1;
		}	
	}

    //move backwards if no wall behind you
    if(keycode == KEY_DOWN) 
    {
      if(worldMap[(int)(data->player.x - data->player.dirX)][(int)(data->player.y)] == 0)
	  {
		  data->player.x -= data->player.dirX;
		  hasmove = 1;
	  }
    		
		if(worldMap[(int)(data->player.x)][(int)(data->player.y - data->player.dirY)] == 0)
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
	{}
		//end_game(data);
	//ft_putnbr(data->player.x);
	//update_player(data);	
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

void render(t_cube *data)
{
  
	draw_rectangle(data,&((t_vector){0,0}),SCREEN_WIDTH,SCREEN_HEIGHT/2,COLOR_GREY);
	draw_rectangle(data,&((t_vector){0,SCREEN_HEIGHT/2}),SCREEN_WIDTH,SCREEN_HEIGHT/2,COLOR_DARK_GREY);
	t_ray ray;

	int h = SCREEN_HEIGHT;
	int w = SCREEN_WIDTH;
    for(int x = 0; x < w; x++)
    {
		//calculate ray position and direction
		double cameraX = cameraX =  2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = data->player.dirX +  data->player.planeX * cameraX;
		double rayDirY = data->player.dirY + data->player.planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(data->player.x);
		int mapY = (int)(data->player.y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

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

		double deltaDistX =(rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;

      	//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
		}
		//calculate_steps(t_ray *ray, t_cube *data)

		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}

		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - data.player.x + (1 - stepX) / 2) / raydata.player.dirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else 
			perpWallDist = (sideDistY - deltaDistY);
		
		// perpWallDist = (sideDistY - deltaDistY);


		//Calculate height of line to draw on screen
		int h = SCREEN_HEIGHT;
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
			drawEnd = h - 1;
		
		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = data->player.y + perpWallDist * rayDirY;
		else           wallX = data->player.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;

		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

		for(int y = drawStart; y< drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = data->textures.texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			mlx_put_pixel_img(&data->img, x, y, color);

		}
		
	}
	mlx_put_image_to_window(data->mlx_ptr, data->wnd_ptr, data->img.img, 0, 0);
}

int main(void)
{	
	t_cube data;
	
	init(&data);
	generate_textures(&data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	return 0;
}
