/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 22:17:40 by dgerard           #+#    #+#             */
/*   Updated: 2018/03/10 16:44:39 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_wordcount(const char *s, char c)
{
	int words;

	words = 0;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		while (*s == c)
			s++;
		words++;
	}
	return (words);
}

static char			**ft_dyn2dstrnew(const char *s, char c)
{
	int		word_size;
	char	**res;
	char	**ret;

	if (!(res = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1))))
		return (NULL);
	ret = res;
	while (*s)
	{
		word_size = 0;
		while (*s && *s != c)
		{
			s++;
			word_size++;
		}
		while (*s == c)
			s++;
		if (!(*res = (char *)malloc(sizeof(char) * (word_size + 1))))
			return (NULL);
		res++;
	}
	return (ret);
}

char				**ft_strsplit(const char *s, char c)
{
	int		j;
	int		k;
	char	*trimd;
	char	**res;
	char	*tmp;

	j = 0;
	if (!(trimd = ft_customtrim(s, c)))
		return (NULL);
	tmp = trimd;
	if (!(res = ft_dyn2dstrnew(trimd, c)))
		return (NULL);
	while (*trimd)
	{
		k = 0;
		while (*trimd && *trimd != c)
			res[j][k++] = *trimd++;
		res[j][k] = '\0';
		while (c == *trimd)
			trimd++;
		j++;
	}
	free(tmp);
	res[j] = (NULL);
	return (res);
}
