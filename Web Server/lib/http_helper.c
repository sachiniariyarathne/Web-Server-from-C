#include "http_helper.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char *get_mime_type(const char *file_ext) {
    if (_stricmp(file_ext, "html") == 0) return "text/html";
    if (_stricmp(file_ext, "css") == 0) return "text/css";
    if (_stricmp(file_ext, "js") == 0) return "application/javascript";
    if (_stricmp(file_ext, "jpg") == 0 || _stricmp(file_ext, "jpeg") == 0) return "image/jpeg";
    if (_stricmp(file_ext, "png") == 0) return "image/png";
    if (_stricmp(file_ext, "gif") == 0) return "image/gif";
    if (_stricmp(file_ext, "mp4") == 0) return "video/mp4";
    if (_stricmp(file_ext, "pdf") == 0) return "application/pdf";
    if (_stricmp(file_ext, "txt") == 0) return "text/plain";
    if (_stricmp(file_ext, "mp3") == 0) return "audio/mp3";
    if (_stricmp(file_ext, "wav") == 0) return "audio/wav";
    if (_stricmp(file_ext, "webp") == 0) return "image/webp";

    return "application/octet-stream";
}

