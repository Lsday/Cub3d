#ifndef CUBE_H
# define CUBE_H

# include <math.h>

#define texWidth 64
	#define texHeight 64
	#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


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






# ifdef __linux__
#  define KEY_UP 122
#  define KEY_DOWN 115
#  define KEY_LEFT 113
#  define KEY_RIGHT 100
#  define KEY_ECHAP 65307

# elif __APPLE__
#  define KEY_UP 13
#  define KEY_DOWN 1
#  define KEY_LEFT 0
#  define KEY_RIGHT 2
#  define KEY_ECHAP 53
#  define KEY_ROTATE_RIGHT 14
#  define KEY_ROTATE_LEFT 12

# endif

# define SPRITE_SIZE 64
# define DESTROYNOTIFY 17

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

#endif