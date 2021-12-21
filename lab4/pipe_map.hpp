#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

typedef struct pipe_map
{
	char name[20];
	int Fd;
	void* buffer;
} pipe_map;

int pipe_map_create (char* name, pipe_map* pip) {
	pip->Fd = open(name, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	if (pip->Fd == -1)
		return -1;
	if (ftruncate(pip->Fd, sizeof(char)) == -1)
		return -1;
	pip->buffer = mmap(NULL, sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, pip->Fd, 0);
	if (pip->buffer == (void*)-1)
		return -1;
	return 0;
}

int pipe_map_connect (char* name, pipe_map* pip) {
	pip->Fd = open(name, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	if (pip->Fd == -1)
		return -1;
	pip->buffer = mmap(NULL, sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, pip->Fd, 0);
	if (pip->buffer == (void*)-1)
		return -1;
	return 0;
}

void pipe_map_write (const void *src, void* dest, size_t n) {
    memcpy(dest, src, n);
}

void pipe_map_read (const void *src, void* dest, size_t n) {
    memcpy(dest, src, n);
}
