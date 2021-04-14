#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIDTH 1200
#define HEIGHT 800
#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00


// destroy_image c'est avant le put_image_to_window

//rajouter des un autour
int map[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



typedef struct  s_mlx_img {
    void        *image;
	  void		    *ptr;
    char        *addr;
    int         bpp;
    int         line_length;
    int         endian;
	  int    	 	  width;
    int     	  height;
}               t_mlx_img;


typedef struct	s_mlx {
	void 		*ptr;
	void		*win;
	t_mlx_img		img;
}				t_mlx;

typedef struct s_var {

    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    double  perpWallDist;
    double rayDirX;
    double rayDirY;
    int     key_forward;
    int     key_left;
    int     key_backward;
    int     key_right;
    int     color;
    int     side;
    int     lineheight;
    int     text_num;
    float   rayDirX0;
    float   rayDirY0;
    float   rayDirX1;
    float   rayDirY1;
    int     p;
    float   posZ;
    float   rowDistance;
    float floorStepX;
    float floorStepY;
    float floorX;
    float floorY;
    //double movespeed;
}               t_var;

typedef struct s_text {
  char *relative_path;
  void  *img;
  int   img_width;
  int   img_height;
  char *img_addr;
  int   bpp;
  int   length;
  int   endian;
}               t_text;

typedef struct s_sprite 
{
  double x;
  double y;
  int texture;
}               t_sprite;  

typedef struct 	s_cub3d {
	t_mlx		mlx;	
  t_var       var;	
  t_sprite    spr;
  t_text      text[5]; //nombre de texture que tu as 
}				        t_cub3d;

t_sprite sprite[2] =
{
  {5, 5, 8},
  {5, 4, 8}
};

double ZBuffer[WIDTH];


void		init_window(t_cub3d *cube)
{
  cube->mlx.ptr = mlx_init();
	cube->mlx.win = mlx_new_window(cube->mlx.ptr, WIDTH, HEIGHT, "argh");
	cube->mlx.img.image = mlx_new_image(cube->mlx.ptr, WIDTH, HEIGHT);
	cube->mlx.img.addr = mlx_get_data_addr(cube->mlx.img.image, &(cube->mlx.img.bpp), &(cube->mlx.img.line_length), &(cube->mlx.img.endian));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*src_cast;
	char		*dest_cast;

	i = 0;
	dest_cast = (char *)dest;
	src_cast = (const char *)src;
	while (i < n)
	{
		dest_cast[i] = src_cast[i];
		i++;
	}
	return (dest_cast);
}

int		ft_close(t_cub3d *cube)
{
	mlx_clear_window(cube->mlx.ptr, cube->mlx.win);
  exit(0);
	return (0);
}

void    init_var(t_cub3d *cube)
{
    cube->var.posX = 22;cube->var.posY = 12;  //x and y start position
    cube->var.dirX = -1; cube->var.dirY = 0; //initial direction vector la ou il regarde quand spawn
    cube->var.planeX = 0; cube->var.planeY = 0.66; // angle de vue the 2d raycaster version of camera plane
	//mlx_clear_window(cube->mlx.ptr, cube->mlx.win);
}

void	pixel_put(t_cub3d *cube, int x, int y, int color)
{
	char	r;
	char	g;
	char	b;
	int		len;

	len = 4 * ((WIDTH) * y + x); //axe x et y et vu que c'est un char la ligne deux commence a 680+680=1360 pui s + x pour etre sur ton axe x et 4 parce que 1 cqhqr c 4 bytes
	r = (int)((color & 16711680) >> 16);
	g = (int)((color & 65280) >> 8);
	b = (int)(color & 255);
	cube->mlx.img.addr[len] = b;
	cube->mlx.img.addr[len + 1] = g;
	cube->mlx.img.addr[len + 2] = r;
  
}

void    sky(t_cub3d *cube, int column, int y)
{
    int i;

    i = 0;
    while (i < y)
    {
        pixel_put(cube, column, i, 0x00FFFF);
        i++;
    }
}

void	put_wall_texture(t_cub3d *cube, int column, int y, int end)
{
	int		len;
	int		y_text;
	double	x_text;
	int		img_size;

	img_size = 200;
	if (cube->var.side == 0)
		x_text = cube->var.posY + cube->var.perpWallDist * cube->var.rayDirY;
	else
		x_text = cube->var.posX + cube->var.perpWallDist * cube->var.rayDirX;
  
  x_text = x_text * (double)(img_size);

	if (cube->var.side == 0 && cube->var.dirX > 0)
		x_text = fabs(img_size - x_text - 1);
	if (cube->var.side == 1 && cube->var.dirY < 0)
		x_text = fabs(img_size - x_text - 1);

	while (y < end)
	{
		len = 4 * ((WIDTH) * y + column);
		y_text = abs((((y * 256 - HEIGHT * 128 + cube->var.lineheight * 128) * img_size) 
    / cube->var.lineheight) / 256); // 128 et 256 to avoid float
    ft_memcpy(&cube->mlx.img.addr[len], &cube->text[cube->var.text_num].img_addr[y_text % img_size * cube->text[cube->var.text_num].length + 
    (int)x_text % img_size * (cube->text[cube->var.text_num].bpp / 8)], sizeof(int));
    y++;
	}
}

void    wall(t_cub3d *cube, int column, int y, int end)
{
    int i;

    i = y;
    while (i < end)
    {
        pixel_put(cube, column, i, cube->var.color);
        i++;
    }
}   

void    my_floor(t_cub3d *cube, int column, int y)
{
    int i;

    i = y;
    while (i < HEIGHT)
    {
        pixel_put(cube, column, i, 0x919191);
        i++;
    }
}

void    drawy(int column, int y, int end, t_cub3d *cube)
{
    sky(cube, column, y);
    my_floor(cube, column, end);
    put_wall_texture(cube, column, y, end);
}

int     move(t_cub3d *cub) // .h
{
	// 12 q
	// 13 w
	// 14 e 
	// 1 s
  double moveSpeed = 0.05;
  double rotSpeed = 0.05;
  if (cub->var.key_left == 1) //a gauche a
      {
        double oldDirX = cub->var.dirX;
        cub->var.dirX = cub->var.dirX * cos(rotSpeed) - cub->var.dirY * sin(rotSpeed);
        cub->var.dirY = oldDirX * sin(rotSpeed) + cub->var.dirY * cos(rotSpeed);
        double oldPlaneX = cub->var.planeX;
        cub->var.planeX = cub->var.planeX * cos(rotSpeed) - cub->var.planeY * sin(rotSpeed);
        cub->var.planeY = oldPlaneX * sin(rotSpeed) + cub->var.planeY * cos(rotSpeed);
      }
    if (cub->var.key_forward == 1) // tout droit z
      {
        if(map[(int)(cub->var.posX + cub->var.dirX * moveSpeed)][(int)cub->var.posY] == 0) 
          cub->var.posX += cub->var.dirX * moveSpeed;
        if(map[(int)cub->var.posX][(int)(cub->var.posY + cub->var.dirY * moveSpeed)] == 0) 
          cub->var.posY += cub->var.dirY * moveSpeed;
      }
    if (cub->var.key_right == 1) // a droite e
    {
      double oldDirX = cub->var.dirX;
      cub->var.dirX = cub->var.dirX * cos(-rotSpeed) - cub->var.dirY * sin(-rotSpeed);
      cub->var.dirY = oldDirX * sin(-rotSpeed) + cub->var.dirY * cos(-rotSpeed);
      double oldPlaneX = cub->var.planeX;
      cub->var.planeX = cub->var.planeX * cos(-rotSpeed) - cub->var.planeY * sin(-rotSpeed);
      cub->var.planeY = oldPlaneX * sin(-rotSpeed) + cub->var.planeY * cos(-rotSpeed);
    }
    if (cub->var.key_backward == 1) // reculer s
    {
      if(map[(int)(cub->var.posX - cub->var.dirX * moveSpeed)][(int)(cub->var.posY)] == 0) 
        cub->var.posX -= cub->var.dirX * moveSpeed;
      if(map[(int)(cub->var.posX)][(int)(cub->var.posY - cub->var.dirY * moveSpeed)] == 0) 
        cub->var.posY -= cub->var.dirY * moveSpeed;
    }  
    return (0);
}

int    raycasting(t_cub3d *cube)
{    
    
    int j=0;
    while (j < HEIGHT)
    {
      cube->var.rayDirX0 = cube->var.dirX - cube->var.planeX;
      cube->var.rayDirY0 = cube->var.dirY - cube->var.planeY;
      cube->var.rayDirX1 = cube->var.dirX + cube->var.planeX;
      cube->var.rayDirY1 = cube->var.dirY + cube->var.planeY;

      cube->var.p = j - HEIGHT / 2;
      
      cube->var.posZ = 0.5 * HEIGHT;

      cube->var.rowDistance = cube->var.posZ/cube->var.p;

      cube->var.floorStepX = cube->var.rowDistance * (cube->var.rayDirX1 - cube->var.rayDirX0)/WIDTH;
      cube->var.floorStepY = cube->var.rowDistance * (cube->var.rayDirY1 - cube->var.rayDirY0)/WIDTH;
      
      cube->var.floorX = cube->var.posX + cube->var.rowDistance * cube->var.rayDirX0;
      cube->var.floorY = cube->var.posY + cube->var.rowDistance * cube->var.rayDirY0;
      j++;
    }
    int i = 0;
    move(cube);
    while (i < WIDTH)
    {
        //calculate ray position and direction
      double cameraX = 2 * i / (double)WIDTH - 1; //x-coordinate in camera space
      cube->var.rayDirX = cube->var.dirX + cube->var.planeX * cameraX;
      cube->var.rayDirY = cube->var.dirY + cube->var.planeY * cameraX;
      int mapX = (int)cube->var.posX;
      int mapY = (int)cube->var.posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY; 
      double deltaDistX = fabs(1 / cube->var.rayDirX);
      double deltaDistY = fabs(1 / cube->var.rayDirY);

      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      //int side; //was a NS or a EW wall hit?
      
      if(cube->var.rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (cube->var.posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - cube->var.posX) * deltaDistX;
      }
      if(cube->var.rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (cube->var.posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - cube->var.posY) * deltaDistY;
      }
      while (hit == 0)
      {
           if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          cube->var.side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          cube->var.side = 1;
        }
        //Check if ray has hit a wall dans la map si c'est un
        if(map[mapX][mapY] > 0) 
            hit = 1;
      }
      if(cube->var.side == 0) 
        cube->var.perpWallDist = (mapX - cube->var.posX + (1 - stepX) / 2) / cube->var.rayDirX;
      else          
        cube->var.perpWallDist = (mapY - cube->var.posY + (1 - stepY) / 2) / cube->var.rayDirY;
      cube->var.lineheight = (int)(HEIGHT / cube->var.perpWallDist);
    
      int drawStart = -(cube->var.lineheight) / 2 + HEIGHT / 2;
      if(drawStart < 0)
        drawStart = 0;
      int drawEnd = cube->var.lineheight / 2 + HEIGHT / 2;
      if(drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
      cube->var.text_num = 0;
      cube->var.color = RED;
      if ((stepX == 1) && ((stepY == -1) || stepY == 1))
	    {
        cube->var.text_num = 1;
			  cube->var.color = BLUE;
	    }
      if (cube->var.side == 1)
	    {
        cube->var.text_num = 2;
       cube->var.color = YELLOW;
        if ((stepY == 1) && ((stepX == -1) || stepX == 1))
		    {
          cube->var.text_num = 3;
				  cube->var.color = GREEN;
		    }
      }
      
    drawy(i, drawStart, drawEnd, cube);
       
      ZBuffer[i] = cube->var.perpWallDist;
       i++;                      
    }
    double spriteX = sprite[0].x - cube->var.posX;
    double spriteY = sprite[0].y - cube->var.posY;
      
    double invDet = 1.0 / (cube->var.planeX * cube->var.dirY - cube->var.dirX * cube->var.planeY); //required for correct matrix multiplication

    double transformX = invDet * (cube->var.dirY * spriteX - cube->var.dirX * spriteY);
    double transformY = invDet * (-(cube->var.planeY) * spriteX + cube->var.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

    int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

          //calculate height of the sprite on screen
      int spriteHeight = abs((int)(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
      if(drawStartY < 0) 
        drawStartY = 0;
      int drawEndY = spriteHeight / 2 + HEIGHT / 2;
      if(drawEndY >= HEIGHT) 
        drawEndY = HEIGHT - 1;
      int spriteWidth = abs((int)(HEIGHT / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) 
        drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= WIDTH) 
        drawEndX = WIDTH - 1;
      double y_text;
      int stripe = drawStartX;
      
      int len;
    //  int img_size = 1564;
       int img_size = 64;
      double x_text;
      while (stripe < drawEndX)
      {
        x_text = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * img_size / spriteWidth) / 256;
        
       if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < ZBuffer[stripe])
       {
          int y = drawStartY;
          while (y < drawEndY)
          {
            int d = y * 256 - HEIGHT * 128 + spriteHeight * 128;
            len = 4 * WIDTH * y + stripe * 4;
            y_text = (d * img_size / spriteHeight)/256;
           if (cube->text[4].img_addr[(int)y_text % img_size * cube->text[4].length + 
            (int)x_text % img_size * (cube->text[4].bpp / 8)] != 0)
              ft_memcpy(&cube->mlx.img.addr[len], &cube->text[4].img_addr[(int)y_text % img_size * cube->text[4].length + 
            (int)x_text % img_size * (cube->text[4].bpp / 8)], sizeof(int));
            y++;
          }
       }
      stripe++;
      }
    mlx_put_image_to_window(cube->mlx.ptr, cube->mlx.win, cube->mlx.img.image, 0, 0);

    return (0);
}



int   key_press(int key, t_cub3d *cube)
{
  if (key == 13)
    cube->var.key_forward = 1;
  if (key == 14)
    cube->var.key_right = 1;
  if (key == 1)
    cube->var.key_backward = 1;
  if (key == 12)
    cube->var.key_left = 1;
  return (0);
}

int   key_release(int key, t_cub3d *cube)
{
  if (key == 53)
    return(ft_close(cube));
  if (key == 13)
    cube->var.key_forward = 0;
  if (key == 14)
    cube->var.key_right = 0;
  if (key == 1)
    cube->var.key_backward = 0;
  if (key == 12)
    cube->var.key_left = 0;
  return (0);
}

void ft_start(t_cub3d *cube)
{
  mlx_loop_hook(cube->mlx.ptr,raycasting, cube);
}

int   load_texture(t_cub3d *cube)
{
  int width;int height;

  // cube->text[0].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/1.xpm", &width, &height);
  // cube->text[0].img_addr = mlx_get_data_addr(cube->text[0].img, &(cube->text[0].bpp), &(cube->text[0].length), &(cube->text[0].endian));
  // cube->text[1].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/2.xpm", &width, &height);
  // cube->text[1].img_addr = mlx_get_data_addr(cube->text[1].img, &(cube->text[1].bpp), &(cube->text[1].length), &(cube->text[1].endian));
  // cube->text[2].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/3.xpm", &width, &height);
  // cube->text[2].img_addr = mlx_get_data_addr(cube->text[2].img, &(cube->text[2].bpp), &(cube->text[2].length), &(cube->text[2].endian));
  // cube->text[3].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/4.xpm", &width, &height);
  // cube->text[3].img_addr = mlx_get_data_addr(cube->text[3].img, &(cube->text[3].bpp), &(cube->text[3].length), &(cube->text[3].endian));
  // cube->text[4].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/5.xpm", &width, &height);
  // cube->text[4].img_addr = mlx_get_data_addr(cube->text[4].img, &(cube->text[4].bpp), &(cube->text[4].length), &(cube->text[4].endian));
  cube->text[0].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/blue_bricks.xpm", &width, &height);
  cube->text[0].img_addr = mlx_get_data_addr(cube->text[0].img, &(cube->text[0].bpp), &(cube->text[0].length), &(cube->text[0].endian));
  cube->text[1].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/red_bricks.xpm", &width, &height);
  cube->text[1].img_addr = mlx_get_data_addr(cube->text[1].img, &(cube->text[1].bpp), &(cube->text[1].length), &(cube->text[1].endian));
  cube->text[2].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/green_bricks.xpm", &width, &height);
  cube->text[2].img_addr = mlx_get_data_addr(cube->text[2].img, &(cube->text[2].bpp), &(cube->text[2].length), &(cube->text[2].endian));
  cube->text[3].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/yellow_bricks.xpm", &width, &height);
  cube->text[3].img_addr = mlx_get_data_addr(cube->text[3].img, &(cube->text[3].bpp), &(cube->text[3].length), &(cube->text[3].endian));
  cube->text[4].img = mlx_xpm_file_to_image(cube->mlx.ptr, "./images/barrel.xpm", &width, &height);
  cube->text[4].img_addr = mlx_get_data_addr(cube->text[4].img, &(cube->text[4].bpp), &(cube->text[4].length), &(cube->text[4].endian));
  // printf("%d,%d", width,height);
  return (0);
}


int		main(void)
{
	t_cub3d cube;
  int width; int height;

	init_window(&cube);
  init_var(&cube);
  load_texture(&cube);
  ft_start(&cube);
  // void *img;
  // img= mlx_xpm_file_to_image(cube.mlx.ptr, "./cat.xpm", &width, &height);

  
  mlx_hook(cube.mlx.win, 2, 0, key_press, &cube);
  mlx_hook(cube.mlx.win, 3, 0, key_release, &cube);

  //mlx_hook(cube.mlx.win, key_release, &cub);
  // mlx_hook(&cube, raycasting, &cub);
  
	mlx_loop(cube.mlx.ptr);
	return (0);
}

// int   main(void)
// {
//   void    *mlx;
//     void    *img;
// 	void	*img2;
// 	void	*win;
//     char    *relative_path = "./cat.xpm";
//     int     img_width;
//     int     img_height;
// 	char 	*addr;
// 	int bpp;
// 	int length;
// 	int endian;

//   mlx = mlx_init();
// 	win = mlx_new_window(mlx, 800,800, "XPM");
// 	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
// 	addr = mlx_get_data_addr(mlx, &bpp, &length, &endian);
// 	mlx_put_image_to_window(mlx, win, img, 0,0);
// 	mlx_loop(mlx);
// 	return (0);
// }



//  mlx = mlx_init();
// 	win = mlx_new_window(mlx, 800,800, "XPM");
// 	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
// 	addr = mlx_get_data_addr(mlx, &bpp, &length, &endian);
// 	mlx_put_image_to_window(mlx, win, img, 0,0);
// 	img2 = mlx_xpm_file_to_image(mlx, relative_path2, &img_width, &img_height);
// 	addr = mlx_get_data_addr(mlx, &bpp, &length, &endian);
// 	mlx_put_image_to_window(mlx, win, img, img_width, img_height);
// 	mlx_put_image_to_window(mlx, win, img2, 700, 500);
