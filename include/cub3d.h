/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifontai <vifontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:28:34 by vifontai          #+#    #+#             */
/*   Updated: 2021/04/14 13:55:24 by vifontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "gnl/get_next_line.h"
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



#endif CUB3D_H
