/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:53:49 by jcat              #+#    #+#             */
/*   Updated: 2024/04/08 10:47:17 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../datatypes/argb.h"

char **error_helper(char *msg)
{
	print_err(msg);
	return (NULL);
}

// Sets str head via ref
bool	parse_numb(const char** strref, int* i, int *outsign)
{
	const char 	*str;
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
	return(!*str);
}

bool	parse_int(const char* str, int* i)
{
	if (!str)
		return (false);
	return (parse_numb(&str, i, NULL));
}

bool	parse_float(const char *str, float* f)
{
	int			dec;
	int			sign;
	float		mag;

	if (!str)
		return (false);
	parse_numb(&str, &dec, &sign);
	*f = (float)dec;
	if (!*str)
		return (true);
	if (*(str++) != '.')
	{
		print_err("Malformed float value");
		return (false);
	}
	mag = 0.1f;
	while (ft_isdigit(*str))
	{
		*f += (float)(*str - '0') * mag * sign;
		mag /= 10.0f;
		++str;
	}
	if(*str)
		print_err("Malformed float value");
	return (!*str);
}

bool	parse_vec3(const char *str, t_vec3 *v)
{
	char const		**strs = (char const **)ft_split(str, ',');
	float * const	comp[] = {&v->x, &v->y, &v->z};
	float			tmp;
	int				i;
	bool			valid;

	if (!str)
		return (false);
	i = 0;
	valid = true;
	while (strs[i] && i < 3)
	{
		if (!parse_float(strs[i], &tmp))
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
	char const	**strs = (char const **)ft_split(str, ',');
	int * const	comp[] = {&color->r, &color->g, &color->b};
	int			i;
	int			tmp;
	bool		valid;

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
		*(comp[i]) = tmp;
		++i;
	}
	if (i < 2 || strs[i] != NULL)
		valid = false;
	free_ptrarr((void **)strs);
	return (valid);
}
