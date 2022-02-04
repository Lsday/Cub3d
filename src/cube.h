#ifndef CUBE_H
# define CUBE_H

# include <math.h>


typedef struct s_player
{
	double x;
	double y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;

}	t_player;

typedef struct s_map
{
	
} t_map;

typedef struct s_cube
{
	void	*mlx_ptr;
	void	*wnd_ptr;
	//char map;
	int map_size_x;
	int map_size_y;

	t_player player;

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
# endif

# define SPRITE_SIZE 64
# define DESTROYNOTIFY 17

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

#endif