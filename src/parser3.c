/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:53:49 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 01:03:53 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"
#include "parser.h"
#include "utils.h"
#include "vec3.h"
#include <stdbool.h>

// Sets str head via ref
bool	parse_numb(const char** strref, int* i)
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
	*strref = str;
	return(!*str);
}

bool	parse_int(const char* str, int* i)
{
	return (parse_numb(&str, i));
}

bool	parse_float(const char *str, float* f)
{
	int			dec;
	float		mag;

	parse_numb(&str, &dec);
	if (*(str++) != '.')
	{
		print_err("Malformed float value");
		return (false);
	}
	*f = (float)dec;
	mag = 0.1f;
	while (ft_isdigit(*str))
	{
		*f += (float)(*str - '0') * mag;
		mag /= 10.0f;
		++str;
	}
	return (!*str);
}

bool	parse_vec3(const char *str, t_vec3 *f)
{
	char const	**strs = (char const **)ft_split(str, ',');
	float		tmp;
	int			i;
	bool		valid;

	i = 0;
	valid = true;
	while (strs[i] && i < 3)
	{
		if (!parse_float(strs[i], &tmp))
		{
			print_err("Malformed rgb value");
			valid = false;
			break ;
		}
		if (i == 0)
			f->x = tmp;
		else if (i == 1)
			f->y = tmp;
		else if (i == 2)
			f->z = tmp;
		++i;
	}
	if (i < 2 || strs[i] != NULL)
		valid = false;
	free_ptrarr((void **)strs);
	return (valid);
}

bool	parse_rgb(const char *str, t_argb *f)
{
	char const	**strs = (char const **)ft_split(str, ',');
	int			i;
	bool		valid;
	t_argb		tmp;

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
		*f += tmp << (8 * i);
		++i;
	}
	if (i < 2 || strs[i] != NULL)
		valid = false;
	free_ptrarr((void **)strs);
	return (valid);
}
