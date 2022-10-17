/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:00:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 00:02:59 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* Necessary (and permitted) inclusions */
# include <string.h>
# include <stdint.h>
# include "ft_string.h"

/* Linked list declaration */
typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/* Memory manipulation */
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memrchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);

/* Math */
double		ft_pow(double base, double exp);
long double	ft_powl(long double base, long double exp);
float		ft_powf(float base, float exp);
int			ft_powi(int base, int exp);
uint64_t	ft_exp10(int exp);
int			ft_abs(int x);
long		ft_labs(long x);
long long	ft_llabs(long long x);
double		ft_fabs(double x);
long double	ft_fabsl(long double x);
long double	ft_truncl(long double x);
long double	ft_roundl(long double x);

/* Generic list functions */
t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list		*ft_lstcpyone(t_list *link);
void		ft_del(void *content, size_t content_size);

/* Voluntary functions (for testing) */
size_t		ft_count_digs(int n);

/* Additional functions added after completion */
size_t		ft_nat_sqrt(unsigned int n);

#endif
