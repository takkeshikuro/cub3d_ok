/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marecarrayan <marecarrayan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:40:20 by marecarraya       #+#    #+#             */
/*   Updated: 2023/09/18 00:42:38 by marecarraya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_format(char *s)
{
	int		len;
	int		i;
	char	*cub;

	cub = ".cub";
	len = ft_strlen(s) - 1;
	i = 3;
	while (i >= 0)
	{
		if (cub[i] != s[len])
			return (0);
		i--;
		len--;
	}
	return (1);
}

int check_args(int argc, char *av[])
{
	int	fd;
	
	if (argc == 1 || argc > 2)
		return (printf("Error: Invalid number of arguments\n"));
	if (!check_format(av[1]))
		return (printf("Error: %s isn't a .cub file\n", av[1]));
	if ((fd = open(av[1], O_DIRECTORY) != -1))
		return (printf("Error: %s is a directory\n", av[1]));
	if ((fd = open(av[1], O_RDONLY) <= 0))
	{
		perror(av[1]);
		return (-1);
	}
	close(fd);
	return (0);
}

void	init_values(t_main *data)
{
	data->map = NULL;
	data->parse_map = malloc(sizeof(t_parse_map));
	data->parse_map->height = 0;
	data->parse_map->width = 0;
	data->parse_map->map_parse = NULL;
}

char	**map_to_tab(int fd)
{
	char	*s1;
	char	*s2;
	char	**tab;

	s1 = "\0";
	s2 = "a";
	while (s2)
	{
		s2 = get_next_line(fd);
		if (s2)
			s1 = ft_strjoin(s1, s2);
		free(s2);
	}
	tab = ft_split(s1, '\n');
	free(s1);
	return (tab);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	init_map(t_parse_map *parser, char *map_name)
{
	char	**map;
	parser->fd = open(map_name, O_RDONLY);
	if (open < 0)
	{
		perror(map_name);
		return (-1);
	}
	parser->map_parse = map_to_tab(parser->fd);
	if (parser->map_parse == NULL)
		return (-1);
	//parser->map = &(parser->map_parse[0]);
	//print_tab(map);
	print_tab(parser->map_parse);
	return (0);
}

int	init_data(t_main *data, char *map_name)
{
	init_values(data);
	if (init_map(data->parse_map, map_name) == -1)
		return (-1);
	return (0);
}

int parsing(int argc, char *argv[], t_main *data)
{
	if (check_args(argc, argv) != 0)
		return (-1);
	if (init_data(data, argv[1]) == -1)
		return (-1);
	return (0);
}