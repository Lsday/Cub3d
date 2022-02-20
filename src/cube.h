#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include "../libft/libft.h"
# include "../GetNextLine/get_next_line.h" 
#include "fcntl.h"
# define texWidth 64
# define texHeight 64
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600


typedef struct s_player
{
	double x;
	double y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;

}	t_player;

typedef struct s_ray
{
	double rayDirX;
	double rayDirY;
	int stepX;
	int stepY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;  //length of ray from current position to next x or y-side
	double sideDistY;
	int hit;
	int side;
	double perpWallDist;
	double wallX;
}	t_ray;

typedef struct s_map
{
	char **map;
	int mapX;
	int mapY;
} t_map;

typedef struct s_camera
{
	
} t_camera;

typedef struct s_img_data
{
    void    *img;
    char    *addr;
    int        bpp;
    int        line_length;
    int        endian;
}    t_img_data;

typedef struct s_texture
{
	int floor_color;
	int ceiling_color;
	
	int texture[8][texWidth * texHeight];
} t_texture;

typedef struct s_cube
{
	void	*mlx_ptr;
	void	*wnd_ptr;
	
	t_img_data img;
	t_texture textures;
	t_player player;
	t_map map;
	double cameraX;
	int drawStart;
	int drawEnd;
	int lineHeight;
	int texNum;
	int texX;
	

} t_cube;


int parse_cub_file_map(int fd, char *file, t_cube *data, int nb_of_line_before);


# ifdef __linux__
#  define KEY_UP 119
#  define KEY_DOWN 115
#  define KEY_LEFT 97
#  define KEY_RIGHT 100
#  define KEY_ECHAP 65307
#  define KEY_ROTATE_RIGHT 65363
#  define KEY_ROTATE_LEFT 65361

# elif __APPLE__
#  define KEY_UP 13
#  define KEY_DOWN 1
#  define KEY_LEFT 0
#  define KEY_RIGHT 2
#  define KEY_ECHAP 53
#  define KEY_ROTATE_RIGHT 124
#  define KEY_ROTATE_LEFT 123
#  define KEY_ECHAP 53


# endif

# define SPRITE_SIZE 64
# define DESTROYNOTIFY 17

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

#endif