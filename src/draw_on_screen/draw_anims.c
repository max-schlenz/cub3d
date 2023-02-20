/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_anims.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:56:41 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 13:56:59 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	show_anim_sprite(t_anim *anim, mlx_image_t *img, int x, int y)
{
	mlx_draw_texture(img, anim->frames[anim->idx], x, y);
}

void	next_sprite(t_anim *anim)
{
	anim->idx++;
	if (anim->idx >= anim->max)
		anim->idx = 0;
}

void	choose_frame(t_sprites *sprites, mlx_t *mlx)
{
	static double	time = DEFAULT_SPRITE_LIFE;

	time -= mlx->delta_time;
	if (time < 0)
		time = DEFAULT_SPRITE_LIFE;
	else
		return ;
	next_sprite(sprites->door_locked);
	next_sprite(sprites->door_opened);
	next_sprite(sprites->player);
}

void	draw_anim(t_tile tile, mlx_image_t *img, t_sprites *sprites)
{
	if (tile.color == A_PLAYER)
		show_anim_sprite(sprites->player, img, tile.x, tile.y);
	else if (tile.color == A_LDOOR)
		show_anim_sprite(sprites->door_locked, img, tile.x, tile.y);
	else if (tile.color == A_ODOOR)
		show_anim_sprite(sprites->door_opened, img, tile.x, tile.y);
}
