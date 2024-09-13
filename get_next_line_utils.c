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

void *ft_strchr(const void *str, unsigned char c) {
	unsigned char *it;

	it = (unsigned char *)str;
	while (*it){
		if (*it == c)
			return (void *)it;
		++it;
	}
	return(NULL);
}

static void clear_cache(t_cache *cache) {
	if (cache->bdata.buf) {
		free(cache->bdata.buf);
		cache->bdata.buf = NULL;
	}
	cache->bdata.size = 0;
	cache->bdata.type_size = 0;
	cache->bdata.cap = 0;
}

void copy_buffer_data_to_cache(t_cache *cache, t_buffer_data *bdata){
	clear_cache(cache);
	cache->bdata.buf = bdata->buf;
	cache->bdata.cap = bdata->cap;
	cache->bdata.size = bdata->size;
	cache->bdata.type_size = bdata->type_size;
}

// // for testing ft_strchr
// int main(int argc, char **argv){
// 	void *ptr;

// 	if (argc != 2){
// 		printf("give an arg, bitch!\n");
// 		return 1;
// 	}
// 	else {
// 		ptr = ft_strchr((const void *)argv[1], '\n');
// 		if (ptr == NULL){
// 			printf("no newline found in %s\n", argv[1]);
// 		} else {
// 			printf ("newline found: %s", (unsigned char *)ptr);
// 		}
// 	}
// 	return 0;
// }

// // for testing ft_memcpy
// int main(int argc, char **argv){
// 	void *ptr;

// 	if (argc != 2){
// 		printf("give one arg, bitch!\n");
// 		return 1;
// 	}
// 	else {
// 		ptr = malloc(sizeof(unsigned char) * 100);
// 		ptr = ft_memcpy(ptr, (const void *)argv[1], strlen(argv[1]));
// 		printf("orig: %s\n", argv[1]);
// 		printf("copy: %s\n", (unsigned char *)ptr);
// 	}
// 	return 0;
// }

// quick calc check
// int main(){

// 	unsigned char src[] = "0123456789";
// 	unsigned char *ptr = &src[4];
// 	printf("size of new buf: %ld\n", ptr - src + 2);
// 	printf("src loc: %ld\n", (unsigned long)src);
// 	printf("ptr loc: %ld\n", (unsigned long)ptr);
// }