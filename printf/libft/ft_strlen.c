/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 12:00:13 by dgerard           #+#    #+#             */
/*   Updated: 2017/03/02 19:27:19 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlen(const char *s)
{
	size_t c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}