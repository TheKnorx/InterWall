#pragma once


#define THROW_ERROR(MSG, ...) do {		\
	fprintf(stderr, MSG "\n", ##__VA_ARGS__);  \
	return -1;  \
}while (0);

#define THROW_PERROR(MSG) do {		\
	perror(MSG "\n");  \
	return -1;  \
}while (0);
