/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:57:11 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/15 07:41:09 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
static void			init_fractal(t_all *a, int zoom)
{
	a->mdlb = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -1.5f, 1.2f, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 1, 0, 0, 0, 1};
	a->mdlb.zoom_i = 10;
	a->pdlb = (t_fractal){ ID_PDLB, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f, 0, 0, 0, 1};
	a->pdlb.zoom_i = 10;
	a->jul = (t_fractal){ ID_JUL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 1000,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, -0.75, 0.067546, 0, 0, 0, 0, 1};
	a->jul.zoom_i = 10;
	a->pjul = (t_fractal){ ID_PJUL, -2.1, 0.0, -1.2, 1.2, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f, 0, 0, 0, 1};
	a->pjul.zoom_i = 10;
	a->nwtn = (t_fractal){ ID_NWTN, -2.1f, 1.0f, -1.8f, 1.0f, zoom, 220,
		(2.0f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f, 0, 1};
	a->nwtn.zoom_i = 10;
	a->rsce = (t_fractal){ ID_RSCE, -2.7, 1.0f, -2.1f, 1.0f, zoom * 0.8, 220,
		(2.1f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f, 0, 1};
	a->rsce.zoom_i = 10;
	a->trtl = (t_fractal){ ID_TRTL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, -0.071053, 0.632895, 0, 0, 0, 0, 1};
	a->trtl.zoom_i = 10;
	a->jlnw = (t_fractal){ ID_ISLD, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, -0.518421, -0.225, 0, 0, 0, 0, 1};
	a->jlnw.zoom_i = 10;
}

static int			**make_m_addr(t_mlx *mlx)
{
	int		**img;
	int		i;
	int		steps;

	i = 0;
	steps = M_IMGF_Y;
	img = (int **)malloc(sizeof(int *) * (M_IMGF_Y + 1));
	img[0] = (int *)mlx->addr;
	while (++i < steps)
		img[i] = (int *)&mlx->addr[i * M_IMGF_X * 4];
	img[i] = NULL;
	return (img);
}

t_mlx				make_mini_mlx(t_all *a)
{
	t_mlx		mlx;

	mlx.mlx = a->mlx->mlx;
	mlx.win = a->mlx->win;
	mlx.image = mlx_new_image(mlx.mlx, WIN_X, WIN_Y);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bpp, &mlx.line_size,
																&mlx.edian);
//	mlx.img = make_m_addr(&mlx);
	return (mlx);
}

static void			init_colors(t_all *a)
{
	a->colors[0][0] = 0x7F1637;
	a->colors[0][1] = 0x047878;
	a->colors[0][2] = 0xFFB733;
	a->colors[0][3] = 0xF57336;
	a->colors[0][4] = 0xC22121;
	a->colors[0][5] = 0xFFB733;

	a->colors[1][0] = 0x091D36;
	a->colors[1][1] = 0x3A4E7A;
	a->colors[1][2] = 0x5E83BA;
	a->colors[1][3] = 0xC2D2E9;
	a->colors[1][4] = 0xF1F1F0;
	a->colors[1][5] = 0x3A4E7A;

	a->colors[2][5] = 0xe56b6b;
	a->colors[2][4] = 0xdd5151;
	a->colors[2][3] = 0xba3404;
	a->colors[2][2] = 0xab1f1f;
	a->colors[2][1] = 0x940808;
	a->colors[2][0] = 0xba3404;

	a->colors[3][0] = 0xfdcf58;
	a->colors[3][1] = 0xf07f13;
	a->colors[3][2] = 0xf27d0c;
	a->colors[3][3] = 0x800909;
	a->colors[3][4] = 0xf07f13;
	a->colors[3][5] = 0xfdcf58;

	a->colors[4][5] = 0xf0e5c4;
	a->colors[4][4] = 0xead8a1;
	a->colors[4][3] = 0xe1c782;
	a->colors[4][2] = 0xd2b25b;
	a->colors[4][1] = 0xc3983a;
	a->colors[4][0] = 0xe1c782;
}

void				init(t_all *a)
{
	init_colors(a);
	a->block = 1;
	a->pal = 0;
	a->smooth = 0;
	a->thread_cnt = 16;
	a->thread = malloc_thread(a->thread_cnt);
	a->p_max = 6;
	a->mlx = make_mlx();
//	a->mini_mlx = make_mini_mlx(a);
	init_fractal(a, (WIN_X - LEFT_MENU) / 4.2);
	cl_init(a);
	mlx_hook(a->mlx->win, 2, (1L << 0), keyboard_hook, a);
	mlx_hook(a->mlx->win, 6, (1L << 6), mouse_pos, a);
	mlx_mouse_hook(a->mlx->win, mouse_clic, a);
	mlx_loop_hook(a->mlx->mlx, redraw, a);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
}
