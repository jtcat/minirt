/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:07:50 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/07 14:56:39 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline double	calc_el(double a[4][4],
		double b[4][4],
		int row, int col)
{
	return (a[row][0] * b[0][col]
		+ a[row][1] * b[1][col]
		+ a[row][2] * b[2][col]
		+ a[row][3] * b[3][col]);
}

// In-place matrix multiplication does not work
// like this you stupid ape
void	mat_mult(double a[4][4], double b[4][4], double d[4][4])
{
	d[0][0] = calc_el(a, b, 0, 0);
	d[0][1] = calc_el(a, b, 0, 1);
	d[0][2] = calc_el(a, b, 0, 2);
	d[0][3] = calc_el(a, b, 0, 3);
	d[1][0] = calc_el(a, b, 1, 0);
	d[1][1] = calc_el(a, b, 1, 1);
	d[1][2] = calc_el(a, b, 1, 2);
	d[1][3] = calc_el(a, b, 1, 3);
	d[2][0] = calc_el(a, b, 2, 0);
	d[2][1] = calc_el(a, b, 2, 1);
	d[2][2] = calc_el(a, b, 2, 2);
	d[2][3] = calc_el(a, b, 2, 3);
	d[3][0] = calc_el(a, b, 3, 0);
	d[3][1] = calc_el(a, b, 3, 1);
	d[3][2] = calc_el(a, b, 3, 2);
	d[3][3] = calc_el(a, b, 3, 3);
}
