/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SquareMatrix.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:57:08 by joaoteix          #+#    #+#             */
/*   Updated: 2024/01/31 18:13:07 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUAREMATRIX_H
# define SQUAREMATRIX_H

typedef s_SquareMatrix {
	int		N;
	float	*m;
}	t_SquareMatrix;

t_SquareMatrix	*newSquareMatrixId(int N);
t_SquareMatrix	*newSquareMatrixZero(int N);

#endif
