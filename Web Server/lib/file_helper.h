#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>  
    #include <io.h>        
    #include <fcntl.h>    
    #define close _close   
    #define read _read     
    #define open _open     
    #define O_RDONLY _O_RDONLY  
    #define O_BINARY _O_BINARY  
#else
    #include <unistd.h>    
    #include <fcntl.h>     
#endif

int get_file_descriptor(const char *file_path, long *file_size);
void send_file(SOCKET client_fd, int file_fd);
const char *get_file_extension(const char *file_name);

#endif 


