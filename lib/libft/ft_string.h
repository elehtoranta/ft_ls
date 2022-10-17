/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:37:25 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 23:11:29 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

// For EOF definition
# include <stdio.h>
// Integer macros
# include <stdint.h>

char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_strrclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strmodify(char const *initial, char *(*f)(char const *));
char		*ft_strgetset(char const *s, char *tset, char *dset, size_t maxlen);
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdjoin(char const *head, char const *delim, char const *tail);
char		*ft_freejoin(const char *a, const char *b, uint8_t select);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
size_t		ft_strspn(const char *s, const char *charset);
size_t		ft_strcspn(const char *s, const char *charset);
char		*ft_itoa(int n);
char		*ft_ltoa_unsigned(unsigned long long n);
char		*ft_ltoa(long long n);
int			ft_putchar(int c);
int			ft_putnbr(int n);
int			ft_putstr(char const *s);
int			ft_putendl(char const *s);
int			ft_putchar_fd(int c, int fd);
int			ft_putstr_fd(char const *s, int fd);
int			ft_putendl_fd(char const *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putbits(void *var, unsigned int bytes);
int			ft_putmem(char *s, size_t n);
char		*ft_strsep(char **p_string, int c);
char		*ft_charappend(char *str, char append);
size_t		ft_strlen(const char *s);
size_t		ft_strdlen(const char *s, const char delim);
size_t		ft_strnlen(const char *s, size_t maxlen);
char		*ft_basename(const char *path);
char		*ft_dirname(const char *path);
char		*ft_join_path(char *dirname, char *basename);
char		*ft_strip(const char *str, const char *charset);
char		*ft_lstrip(const char *str, const char *charset);
char		*ft_rstrip(const char *str, const char *charset);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strddup(const char *s, char d);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strdcpy(char *dst, const char *src, char d);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strrev(const char *str);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strpbrk(const char *s, const char *charset);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
int			ft_islower(int c);
int			ft_isupper(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_iswhite(int c);
char		ft_arechars(const char *str, const char *charset);

#endif
