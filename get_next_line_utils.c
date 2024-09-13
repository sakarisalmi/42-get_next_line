#include "get_next_line.h"

#include <string.h>
#include <stdio.h>

void *ft_memcpy(void *dst, const void *src, size_t n){
	size_t	chunks;
	void	*tmp_ptr;

	if (dst == src || (!dst || !src) || n == 0)
		return(dst);
	chunks = n / sizeof(unsigned long);
	n -= chunks * sizeof(unsigned long);

	tmp_ptr = dst;
	while (chunks--){
		*(unsigned long *)tmp_ptr = *(const unsigned long *)src;
		tmp_ptr = (unsigned long *)tmp_ptr + 1;
		src = (const unsigned long *)src + 1;
	}
	while (n--) {
		*(unsigned char *)tmp_ptr = *(const unsigned char *)src;
		tmp_ptr = (unsigned char *)tmp_ptr + 1;
		src = (const unsigned char *)src + 1;
	}
	return(dst);
}

void *ft_strchr(const void *str, const unsigned char c) {
	unsigned char *it;

	it = (unsigned char *)str;
	while (*it){
		if (*it == c)
			return (void *)it;
		++it;
	}
	return(NULL);
}
