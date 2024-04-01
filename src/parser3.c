/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:53:49 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 02:22:01 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdbool.h>

// Sets str head via ref
bool	parse_numb(const char** strref, int* i, bool checksign)
{
	const char 	*str;
	int			numb;
	int			sign;

	str = *strref;
	numb = 0;
	sign = 1;
	if (checksign && (*str == '-' || *str == '+'))
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
	return (parse_numb(&str, i, true));
}

bool	parse_float(const char *str, float* f)
{
	int	dec;
	int frac;

	if (!parse_numb(&str, &dec, true) || *str != '.' || !parse_numb(&str, &frac, false))
	{
		print_err("Malformed float value");
		return (false);
	}
}
