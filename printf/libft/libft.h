/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:45:56 by dgerard           #+#    #+#             */
/*   Updated: 2017/07/07 08:21:12 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 12
# define MAX_FD 4096

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_putchar(char c);
void				ft_putstr(const char *str);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *s1, const char *s2);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void(*f)(char *));
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
char				*ft_strmap(const char *s, char(*f)(char));
char				*ft_strmapi(const char *s, char(*f)(unsigned int, char));
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char*s1, const char *s2, size_t n);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_putnbr(int nbr);
void				ft_putendl(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *str, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int nbr, int fd);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_itoa(int n);
int					ft_numlen(int value, int base);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				**ft_strsplit(const char *s, char c);
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *list, t_list *(*f)(t_list *elem));
char				*ft_customtrim(const char *s, char c);
char				*ft_strrev(char *s);
char				*ft_strjoini(const char *s1, const char *s2, size_t i);
char				**ft_2dstrnew(size_t x, size_t y);
void				*ft_realloc(void *ptr, size_t size);
int					**ft_2dintarray(size_t y, size_t x);
int					*ft_intarraynew(size_t x);
void				ft_2dfreearray(void **array, int n);
int					get_next_line(const int fd, char **line);
void				ft_bitswap(unsigned char *a, unsigned char *b, size_t size);
char				*ft_itoa_base(int value, int base);
float				*ft_floatarraynew(size_t x);
int					ft_power(int nbr, int power);
int					ft_numlen_ll(intmax_t value, int base);
int					ft_numlen_ull(uintmax_t value, unsigned int base);
intmax_t			ft_power_ll(intmax_t nbr, intmax_t power);
uintmax_t			ft_power_ull(uintmax_t nbr, uintmax_t power);

#endif
