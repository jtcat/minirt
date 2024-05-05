/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:53:49 by jcat              #+#    #+#             */
/*   Updated: 2024/05/05 16:40:20 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../datatypes/argb.h"

// Sets str head via ref
bool	parse_numb(const char **strref, int *i, int *outsign)
{
	const char	*str;
	int			numb;
	int			sign;

	str = *strref;
	numb = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign *= (*str == '-') * -2 + 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		numb *= 10;
		numb += (int)(*str - '0');
		str++;
	}
	*i = sign * numb;
	if (outsign)
		*outsign = sign;
	*strref = str;
	return (!*str);
}

bool	parse_int(const char *str, int *i)
{
	if (!str)
		return (false);
	return (parse_numb(&str, i, NULL));
}

bool	parse_double(const char *str, double *f)
{
	int			dec;
	int			sign;
	double		mag;

	if (!str)
		return (false);
	parse_numb(&str, &dec, &sign);
	*f = (double)dec;
	if (!*str)
		return (true);
	if (*(str++) != '.')
	{
		print_err("Malformed double value");
		return (false);
	}
	mag = 0.1f;
	while (ft_isdigit(*str))
	{
		*f += (double)(*str - '0') *mag * sign;
		mag /= 10.0f;
		++str;
	}
	if (*str)
		print_err("Malformed double value");
	return (!*str);
}

bool	parse_vec3(const char *str, t_vec3 *v)
{
	char const		**strs = (char const **)ft_split(str, ',');
	double *const	comp[] = {&v->x, &v->y, &v->z};
	double			tmp;
	int				i;
	bool			valid;

	if (!str)
		return (false);
	i = 0;
	valid = true;
	while (strs[i] && i < 3)
	{
		if (!parse_double(strs[i], &tmp))
		{
			print_err("Malformed vec3 value");
			valid = false;
			break ;
		}
		*(comp[i]) = tmp;
		++i;
	}
	if (i < 2 || strs[i] != NULL)
		valid = false;
	free_ptrarr((void **)strs);
	return (valid);
}

bool	parse_rgb(const char *str, t_color3 *color)
{
	char const		**strs = (char const **)ft_split(str, ',');
	double *const	comp[] = {&color->r, &color->g, &color->b};
	int				i;
	int				tmp;
	bool			valid;

	if (!str)
		return (false);
	i = 0;
	valid = true;
	while (strs[i] && i < 3)
	{
		if (!parse_int(strs[i], &tmp) || tmp < 0 || tmp > 255)
		{
			print_err("Malformed rgb value");
			valid = false;
			break ;
		}
		*(comp[i]) = (double)tmp / 255.f;
		++i;
	}
	if (i < 2 || strs[i] != NULL)
		valid = false;
	free_ptrarr((void **)strs);
	return (valid);
}
