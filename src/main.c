#include <stdio.h>
#include "get_next_line.h"
#include "filler.h"

void	set_player_info(t_filler *filler)
{
	char	*line;

	get_next_line(0, &line);
	if (line[10] == '1')
	{
		filler->me = 'O';
		filler->opponent = 'X';
	}
	else
	{
		filler->me = 'X';
		filler->opponent = 'O';
	}
	ft_strdel(&line);
}

int		length_num(int a)
{
	int len;

	len = 1;
	while (a > 0)
	{
		a /= 10;
		len++;
	}
	return (len);
}

void	set_map(t_obj *map)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	map->height = ft_atoi((const char*)line + 7);
	map->width = ft_atoi((const char*)line + 7 + length_num(map->height));
	ft_strdel(&line);
	get_next_line(0, &line);
	ft_strdel(&line);
	i = 0;
	if (!(map->fig = (char **)malloc(sizeof(char *) * (map->height + 1))))
		exit(1);

	while (i < map->height)
	{
		if (!(map->fig[i] = (char*)malloc(sizeof(char) * (map->width + 1))))
			exit(1);
//		get_next_line(0, &line);
//		map->fig[i] = ft_strdup(*(&line + 4));
//		ft_strdel(&line);
		i++;
	}
	map->fig[i] = NULL;
	
	i = 0;
//	FILE *fp;

//	fp = fopen("test.txt", "a+");
	while (i < map->height)
	{
		get_next_line(0, &line);
//		fprintf(fp, "LINE %s\n",line);
//		map->fig[i] = ft_strdup(*(&line + 4));
		free(line);
	//	ft_strdel(&line);
		i++;
	}		
//	fclose(fp);
	ft_putnbr(8);
	ft_putchar(' ');
	ft_putnbr(2);
	ft_putchar('\n');
}

void	set_piece(t_obj *piece)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	piece->height = ft_atoi((const char*)line + 5);
	piece->width = ft_atoi((const char*)line + 5 + length_num(piece->height));
	ft_strdel(&line);
	i = 0;
	if (!(piece->fig = (char **)malloc(sizeof(char *) * (piece->height + 1))))
		exit(1);
	while (i <= (piece->height))
	{
		get_next_line(0, &line);
		piece->fig[i] = ft_strdup((const char *)(&line[0]));
		ft_strdel(&line);
	}
	piece->fig[i] = NULL;
}

int		mod(int a)
{
	return (a >= 0 ? a : -1 * a);
}

int		get_dist(t_filler *filler, int y, int x)
{
	int		min_dist;
	int		dist;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dist = 0;
	min_dist = 2147483647;
	while (i < filler->map->height)
	{
		j = 0;
		while (j < filler->map->width)
		{
			if (filler->map->fig[i][j] == filler->opponent || filler->map->fig[i][j] == (filler->opponent + 32))
			{
				dist = mod(y - i) + mod(x - j);
				if (dist < min_dist)
					min_dist = dist;
			}
			j++;
		}
		i++;
	}
	return (min_dist);
}

void	set_heat_map(t_filler *filler)
{
	int		i;
	int		j;

	filler->heat->height = filler->map->height;
	filler->heat->width = filler->map->width;
	if (!(filler->heat->fig = (int **)malloc(sizeof(int *) * (filler->heat->height + 1))))
		exit(1);
	i = 0;
	while (i < filler->heat->height)
	{
		j = 0;
		if (!(filler->heat->fig[i] = (int *)malloc(sizeof(int) * (filler->heat->width + 1))))
			exit(1);
		while (j <= filler->heat->width)
		{
			if (filler->map->fig[i][j] == filler->me || filler->map->fig[i][j] == (filler->me + 32))
				filler->heat->fig[i][j] = -1;
			else if (filler->map->fig[i][j] == filler->opponent || filler->map->fig[i][j] == (filler->opponent + 32))
				filler->heat->fig[i][j] = 0;
			else
				filler->heat->fig[i][j] = get_dist(filler, i, j);
			j++;
		}
		i++;
	}
	filler->heat->fig[i] = NULL;
}

void	print_heat_map(t_filler *filler, FILE *fd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < filler->heat->height)
	{
		j = 0;
		while (j < filler->heat->width)
		{
			fprintf(fd, "%2.2i ",filler->heat->fig[i][j]);
			j++;
		}
		fprintf(fd, "\n");
		i++;
	}
}

void	print_piece(t_obj *piece, FILE *fd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < piece->height)
	{
		j = 0;
		while (j < piece->width)
		{
			fprintf(fd, "%c ",piece->fig[i][j]);
			j++;
		}
		fprintf(fd, "\n");
		i++;
	}
	fprintf(fd, "\n");
}

void	print_grad_map(t_heat *grad, FILE *fd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < grad->height)
	{
		j = 0;
		while (j < grad->width)
		{
			fprintf(fd, "%2.2i ",grad->fig[i][j]);
			j++;
		}
		fprintf(fd, "\n");
		i++;
	}
}

void	set_filler(t_filler *filler)
{
	bzero(filler, sizeof(t_filler));
	if (!(filler->map = (t_obj*)ft_memalloc(sizeof(t_obj))))
		exit(1);
	bzero(filler->map, sizeof(t_obj));
	if (!(filler->piece = (t_obj*)ft_memalloc(sizeof(t_obj))))
		exit(1);
	bzero(filler->piece, sizeof(t_obj));
	if (!(filler->heat = (t_heat*)ft_memalloc(sizeof(t_heat))))
		exit(1);
	bzero(filler->heat, sizeof(t_heat));
	set_player_info(filler);
	set_map(filler->map);
//	set_piece(filler->piece);
//	set_heat_map(filler);
}

int		estimate_grad(t_obj *piece, t_heat *heat, int y, int x)
{
	int		can_set;
	int		i;
	int		j;
	int		res;

	can_set = -1;
	i = 0;
	res = 0;
	while (i < piece->height)
	{
		j = 0;
		while (j < piece->width)
		{
			if (piece->fig[i][j] == '*')
			{
				if (heat->fig[i + y][j + x] == 0 || (heat->fig[i + y][j + x] == -1 && can_set == 1))
					return (-1);
				if (heat->fig[i + y][j + x] == -1)
					can_set = 1;
				else
					res += heat->fig[i + y][j + x];
			}
			j++;
		}
		i++;
	}
	return (can_set == 1 ? res : -1);
}

void	set_grad(t_heat *grad, t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	grad->height = filler->heat->height - filler->piece->height + 1;
	grad->width = filler->heat->width - filler->piece->width + 1;
	if (!(grad->fig = (int **)malloc(sizeof(int *) * (grad->height + 1))))
		exit(1);
	while (i < grad->height)
	{
		j = 0;
		if (!(grad->fig[i] = (int *)malloc(sizeof(int) * (grad->width + 1))))
			exit(1);
		while (j < grad->width)
		{
			grad->fig[i][j] = estimate_grad(filler->piece, filler->heat, i, j);
			j++;
		}
		i++;
	}
}

void	count_coord(t_heat	*grad)
{
	t_point	coord;
	int		min;
	int		i;
	int		j;

	i = 0;
	coord.x = 0;
	coord.y = 0;
	min = 2147483647;
	while (i < grad->height)
	{
		j = 0;
		while (j < grad->width)
		{
			if (grad->fig[i][j] < min && grad->fig[i][j] >= 0)
			{
				min = grad->fig[i][j];
				coord.x = j;
				coord.y = i;
			}
			j++;
		}
		i++;
	}

//	FILE *fp;
//
//	fp = fopen("test.txt", "a+");
//	fprintf(fp, "%i %i\n\n", coord.y, coord.x);
//	fclose(fp);

//	ft_putnbr(8);
//	ft_putchar(' ');
//	ft_putnbr(2);
//	ft_putchar('\n');
}

void	place_piece(t_filler *filler)
{
	t_heat	*grad;

	if (!(grad = (t_heat*)ft_memalloc(sizeof(t_heat))))
		exit(1);
	bzero(grad, sizeof(t_heat));
	set_grad(grad, filler);
	count_coord(grad);
/*	FILE *fp;

	fp = fopen("test.txt", "a+");
	print_grad_map(grad, fp);
	fprintf(fp, "\n\n");
	fclose(fp);*/
	//to freee
}

int		main(void)
{
	t_filler	*filler;
//	char *line;
//	FILE *fp;

	if (!(filler = (t_filler*)ft_memalloc(sizeof(t_filler))))
		exit(1);
	set_filler(filler);
	place_piece(filler);
//	while (1)
//	{
//	}
/*	fp = fopen("test.txt", "a+");
	fprintf(fp, "PLAYER %c\n",filler->me);
	fprintf(fp, "MAP HEIGHT %i\n",filler->map->height);
	fprintf(fp, "MAP WIDTH %i\n",filler->map->width);
	fprintf(fp, "PIECE HEIGHT %i\n",filler->piece->height);
	fprintf(fp, "PIECE WIDTH %i\n",filler->piece->width);
	print_piece(filler->piece, fp);
	print_heat_map(filler, fp);
	get_next_line(0, &line);
	fprintf(fp, "%s\n\n",line);
	fclose(fp);*/
	return (0);
}