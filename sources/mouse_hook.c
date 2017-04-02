/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 01:50:53 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/02 02:53:08 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void		find_fractal(int x, int y, t_all *a)
{
	a->act = (x == 0 && y == 0 ? &a->mdlb : a->act);
	a->act = (x == 0 && y == 1 ? &a->pdlb : a->act);
	a->act = (x == 1 && y == 0 ? &a->nwtn : a->act);
	a->act = (x == 1 && y == 1 ? &a->rsce : a->act);
	a->act = (x == 2 && y == 0 ? &a->jul : a->act);
	a->act = (x == 2 && y == 1 ? &a->pjul : a->act);
	a->act = (x == 3 && y == 0 ? &a->trtl : a->act);
	a->act = (x == 3 && y == 1 ? &a->jlnw : a->act);
	a->frac = (x == 0 && y == 0 ? (void *)mandelbrot : (void *)a->frac);
	a->frac = (x == 0 && y == 1 ? (void *)powdelbrot : (void *)a->frac);
	a->frac = (x == 1 && y == 0 ? (void *)newton : (void *)a->frac);
	a->frac = (x == 1 && y == 1 ? (void *)rosace : (void *)a->frac);
	a->frac = (x == 2 && y == 0 ? (void *)julia : (void *)a->frac);
	a->frac = (x == 2 && y == 1 ? (void *)pow_julia : (void *)a->frac);
	a->frac = (x == 3 && y == 0 ? (void *)turtle : (void *)a->frac);
	a->frac = (x == 3 && y == 1 ? (void *)jul_new : (void *)a->frac);
}

static void		zoom_in(int x, int y, long double i, t_all *a)
{
	long double	dx;
	long double	dy;

	dx = x;
	dy = y;
	dx *= (a->act->zoom + i) / (a->act->zoom);
	dy *= (a->act->zoom + i) / (a->act->zoom);
	a->act->x1 += ((dx - IMGF_MX) / (a->act->zoom)) / 2;
	a->act->x2 += ((dx - IMGF_MX) / (a->act->zoom)) / 2;
	a->act->y1 += ((dy - IMGF_MY) / (a->act->zoom)) / 2;
	a->act->y2 += ((dy - IMGF_MY) / (a->act->zoom)) / 2;
	a->act->zoom = a->act->zoom + i;
}

static void		zoom_out(int x, int y, long double i, t_all *a)
{
	double	dx;
	double	dy;

	dx = x;
	dy = y;
	dx *= (a->act->zoom + i) / (a->act->zoom);
	dy *= (a->act->zoom + i) / (a->act->zoom);
	a->act->x1 += (((double)dx - (double)IMGF_MX) / (a->act->zoom));
	a->act->x2 += (((double)dx - (double)IMGF_MX) / (a->act->zoom));
	a->act->y1 += (((double)dy - (double)IMGF_MY) / (a->act->zoom));
	a->act->y2 += (((double)dy - (double)IMGF_MY) / (a->act->zoom));
	a->act->zoom -= i;
}

int				mouse_clic(int button, int x, int y, t_all *a)
{
	if (x > 0 && x < IMGF_X && y > 0 && y < IMGF_Y
		&& (button == 1 || button == 4))
		zoom_in(x, y, a->act->zoom_i *= 1.10f, a);
	else if (x > 0 && x < IMGF_X && y > 0 && y < IMGF_Y
		&& (button == 2 || button == 5))
		zoom_out(x, y, a->act->zoom_i *= (1 / 1.10f), a);
	else if (x > 0 && x < IMGF_X && y > IMGF_Y && y < WIN_Y)
		find_fractal(x / M_IMGF_X, (y - IMGF_Y) / M_IMGF_Y, a);
	else
		return (0);
	redraw(a);
	return (1);
}

int				mouse_pos(int x, int y, t_all *a)
{
	if (x > 0 && y > 0 && x < IMGF_X && y < IMGF_Y && a->done == 1
	&& a->block == 0)
	{
		if (a->act->id == ID_JUL || a->act->id == ID_PJUL
		|| a->act->id == ID_TRTL || a->act->id == ID_ISLD)
		{
			a->act->ci = (double)((double)y - IMGF_Y / 2) / 380;
			a->act->c = (double)((double)x - IMGF_X / 2) / 760;
		}
		else if (a->act->id == ID_PDLB)
			a->act->pow = (double)((double)(x + y - 50) / 10 + 20) / 10;
		else
			return (0);
		redraw(a);
	}
	return (0);
}
