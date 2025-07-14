#include "file_helper.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

int get_file_descriptor(const char *file_path, long *file_size) {
    int fd = _open(file_path, _O_RDONLY | _O_BINARY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    struct _stat file_stat;
    if (_fstat(fd, &file_stat) == 0) {
        *file_size = file_stat.st_size;
    } else {
        *file_size = 0;
    }

    return fd;
}


void send_file(SOCKET client_fd, int file_fd) {
    char buffer[4096]; 
    int bytes_read;

    while ((bytes_read = _read(file_fd, buffer, sizeof(buffer))) > 0) {
        int sent_bytes = send(client_fd, buffer, bytes_read, 0);
        if (sent_bytes == SOCKET_ERROR) {
            perror("Error sending file");
            break;
        }
    }

    _close(file_fd);
}

const char *get_file_extension(const char *file_name) {
    const char *dot = strrchr(file_name, '.');
    return (!dot || dot == file_name) ? "" : dot + 1;
}




