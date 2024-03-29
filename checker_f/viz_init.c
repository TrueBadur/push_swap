/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <ehugh-be@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:30:53 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/06/07 14:26:58 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

#ifdef VIZUALIZER

void	gradient_img (t_img * img, t_ucol4 start, t_ucol4 end, int n_el)
{
	int x;
	int y;
	t_ucol4 col_loc_st;
	t_ucol4 col_loc_en;

	y = img->res.y;
	col_loc_st = col_lerp(start, end, img->pos, n_el);
	col_loc_en = col_lerp(start, end, img->pos + 1, n_el);
	while (y--)
	{
		x = img->res.x;
		while(x--)
			((int*)img->data)[y * img->res.x + x] = col_lerp(col_loc_st,
					col_loc_en, y, img->res.y).i_col;
	}
}

void	fill_img(t_img *img, int col)
{
	int i;

	i = img->res.x * (img->res.y);
	while (i--)
		((int*)img->data)[i] = col;
}

int calc_w(int pos, int w_width, t_mngr *mngr)
{
	return ((((w_width - ((w_width / 100) * 4)) / 2) /
	mngr->stk[0]->lst_s) * (pos + 1));
}

int calc_h(int num_els)
{
	static int left = (W_HEIGHT - (Y_PAD * 2));
	int ret;

	ret = (int)(left / num_els);
	left -= ret;
	return (ret);
}

t_img *gen_img(int tmp, t_vector *vec, t_mngr *mngr, int i)
{
	t_img *img;
	static int height;
	int pos;

	height = calc_h(mngr->stk[0]->lst_s - i);
	if (!(img = malloc(sizeof(t_img))))
		pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
	if ((pos = ft_vecbinsearch_int(vec, tmp)) == -1)
		pushswap_exit(mngr, INTERNAL_ERROR);
	img->pos = pos;
	img->res = (t_uint2){calc_w(img->pos, W_WIDTH, mngr), height};
	if (!(img->img_ptr = mlx_new_image(mngr->mlx->mlx, img->res.x, img->res.y)))
		pushswap_exit(mngr, MLX_FAIL);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line,
			&img->endian);
	gradient_img(img, (t_ucol4)0x00345678, (t_ucol4)0x009e7777, mngr->stk[0]->lst_s);
	return (img);
}

int		active(t_eops cmd, int i, int mode, int len)
{
	t_int3 a;
	t_int3 b;
	a.x = !(mode & 1) && (i == 0 && cmd != SWP_B && cmd != ROT_B && cmd
			!= RROT_B && cmd != PSH_B && cmd != INIT);
	a.y = !(mode & 1) && i == 1 && (cmd == SWP_A || cmd == SWP_S);
	a.z = !(mode & 1) && (i == len - 1) && (cmd == RROT_A || cmd == RROT_R ||
	cmd == ROT_A || cmd == ROT_R);
	b.x = (mode & 1) && (i == 0 && cmd != SWP_A && cmd != ROT_A && cmd
									 != RROT_A && cmd != PSH_A && cmd != INIT);
	b.y = (mode & 1) && i == 1 && (cmd == SWP_B || cmd == SWP_S);
	b.z = (mode & 1) && (i == len - 1) && (cmd == RROT_B || cmd == RROT_R ||
											 cmd == ROT_B || cmd == ROT_R);
	return (a.x || a.y || a.z || b.x || b.y || b.z);
}

void	put_active(t_mngr *mngr, int pad_x, int pad_y, t_list *lst)
{
	t_img *tmp;
	t_img *img;

	img = ((t_simg*)lst->data)->img;
	if (!(tmp = malloc(sizeof(t_img))))
		pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
	tmp->img_ptr = mlx_new_image(mngr->mlx->mlx, img->res.x, img->res.y);
	tmp->data = mlx_get_data_addr(tmp->img_ptr, &tmp->bpp, &tmp->size_line,
								  &tmp->endian);
	tmp->res = img->res;
	fill_img(tmp, 0x00ff0000);
	mlx_put_image_to_window(mngr->mlx->mlx, mngr->mlx->win_ptr,
							tmp->img_ptr, pad_x, pad_y);
	mlx_destroy_image(mngr->mlx->mlx, tmp->img_ptr);
	free(tmp);
}

void viz_stack(t_stk *stk, t_mngr *mngr, unsigned mode, t_eops cmd)
{
	int pad_x;
	int pad_y;
	int i;
	t_list *lst;

	lst = stk->lst;
	pad_y = Y_PAD;
	i = 0;
	while (lst)
	{
		pad_x = (mode & 1) ? X_PAD * 3 + COL_WIDTH : X_PAD;
		if (mode & (1 << 1))
			pad_x += (COL_WIDTH - ((t_simg*)lst->data)->img->res.x);
		if (mngr->mlx->active && active(cmd, i++, mode, stk->lst_s))
			put_active(mngr, pad_x, pad_y, lst);
		else
			mlx_put_image_to_window(mngr->mlx->mlx, mngr->mlx->win_ptr,
				((t_simg*)lst->data)->img->img_ptr, pad_x, pad_y);
		pad_y += ((t_simg*)lst->data)->img->res.y;
		lst = lst->next;
	}
}

void	viz_stacks(t_mngr *mngr, t_eops cmd)
{
	viz_stack(mngr->stk[0], mngr, 1 << 1, cmd);
	viz_stack(mngr->stk[1], mngr, 1, cmd);
}

void	populate_stack_imgs(t_mngr *mngr)
{
	t_vector *vec;
	t_list		*lst;
	int			tmp;
	int			i;

	vec = ft_vecinit(sizeof(int) * mngr->stk[0]->lst_s);
	ft_avltovec(mngr->s_arr, vec);
	lst = mngr->stk[0]->lst;
	i = 0;
	while (lst)
	{
		tmp = (int)lst->data;
		if(!(lst->data = malloc(sizeof(t_simg))))
			pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
		lst->content_size = sizeof(t_simg);
		((t_simg*)lst->data)->val = tmp;
		((t_simg*)lst->data)->img = gen_img(tmp, vec, mngr, i++);
		lst = lst->next;
	}
	ft_vecdel((void**)&vec);
	viz_stacks(mngr, INIT);
}

int		window_close(void *param)
{
	pushswap_exit((t_mngr*)param, INTERUPTED);
	return (0);
}

void	viz_step(t_mngr *mngr)
{
	int loop;

	mlx_clear_window((mngr)->mlx->mlx, (mngr)->mlx->win_ptr);
	loop = parse_command(mngr);
	viz_stacks(mngr, loop);
	(mngr)->mlx->sleep = clock() + (mngr)->mlx->interval;
	if (!loop)
	{
		sleep(2);
		end_programm(mngr);
	}
}

int		hook_keydwn(int key, void *param)
{
	if (key == SPEED_INCREASE)
		((t_mngr*)param)->mlx->interval += SPEED_STEP;
	if (key == SPEED_DECREASE)
		((t_mngr*)param)->mlx->interval -= ((t_mngr*)param)->mlx->interval >=
				SPEED_STEP ? SPEED_STEP : 0;
	if (key == PAUSE)
		((t_mngr *) param)->mlx->pause = !((t_mngr *) param)->mlx->pause;
	if (key == STEP_FORWARD)
		viz_step((t_mngr*)param);
	if (key == QUIT)
		end_programm((t_mngr*)param);
	if (key == ACTIVE)
		((t_mngr*)param)->mlx->active = !((t_mngr*)param)->mlx->active;
	return (0);
}

int viz_loop(void *param)
{
	t_mngr *mngr;

	mngr = (t_mngr*)param;
	if ((mngr)->mlx->sleep > clock())
		return (0);
	if (!(mngr)->mlx->pause)
		viz_step(mngr);
	return (0);
}

void start_viz(t_mngr *mngr)
{
	if (!(mngr->mlx = malloc(sizeof(t_mlx))))
		pushswap_exit(mngr, MEMORY_ALLOC_FAIL);
	ft_bzero(mngr->mlx, sizeof(t_mlx));
	mngr->mlx->mlx = mlx_init();
	mngr->mlx->interval = SPEED;
	mngr->mlx->pause = 0;
	mngr->mlx->active = 0;
	mngr->mlx->win_ptr = mlx_new_window(mngr->mlx->mlx, W_WIDTH, W_HEIGHT,
			"Push Swap Viz");
	populate_stack_imgs(mngr);
	mlx_hook(mngr->mlx->win_ptr, 2, 5, hook_keydwn, (void*)mngr);
	mlx_hook(mngr->mlx->win_ptr, 17, (1L << 3), window_close, (void*)mngr);
	mlx_loop_hook(mngr->mlx->mlx, viz_loop, (void*)mngr);
	mngr->mlx->sleep = clock() + mngr->mlx->interval;
	mlx_loop(mngr->mlx->mlx);
}

#endif