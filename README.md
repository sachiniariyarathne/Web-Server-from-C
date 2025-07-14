# 🌐 Custom Web Server in C

This project is a **custom-built web server written in C** for Windows, designed to handle HTTP requests and serve static files such as HTML, CSS, JS, images, PDFs, and media. It was developed to gain hands-on experience in system-level programming, networking, multithreading, and file handling.

---

## 🛠️ Features

- ✅ Handles **HTTP GET requests**
- ✅ Serves multiple content types: `.html`, `.css`, `.js`, `.jpg`, `.png`, `.pdf`, `.mp3`, `.mp4`, etc.
- ✅ Displays **custom 404 error page**
- ✅ Supports **multi-threading** using `_beginthread`
- ✅ Real-time logging of requests and responses in terminal
- ✅ MIME type detection based on file extension
- ✅ Lightweight, no third-party frameworks

---

## 🚀 Technologies Used

| Category        | Technology               |
|----------------|--------------------------|
| Programming     | C                        |
| Networking      | Windows Sockets API (Winsock2) |
| Threading       | `<process.h>` (`_beginthread`) |
| OS              | Windows 10+              |
| Protocol        | HTTP 1.1 (GET requests)  |
| Compilation     | GCC via MinGW/MSYS2      |

---

## 📁 Folder Structure
Web-Server-Project/
│
├── server.c # Main server logic
├── utils.c # Utility functions
├── Makefile # Build script
├── src/ # Static files (HTML, CSS, PDF, etc.)
│ ├── index.html
│ ├── about.html
│ ├── 404.html
│ └── sample.pdf
├── lib/
│ ├── file_helper.c
│ ├── file_helper.h
│ ├── http_helper.c
│ ├── http_helper.h
│ └── ...


## ⚙️ How to Compile and Run

### ✅ Requirements

- GCC (MinGW or MSYS2)
- Windows OS
- Terminal or CMD

### 🔧 Build

Using Makefile:

```bash
mingw32-make
Or 
manual compilation: gcc -Wall -Wextra -Ilib -o server.exe server.c utils.c lib/file_helper.c lib/http_helper.c -lws2_32

▶️ Run the Server
./server.exe
Visit in your browser: 
http://localhost:9090/index.html

🖥️ Demo Highlights
Works on Microsoft Edge and Google Chrome.
Displays live logs of client requests and server responses.
Supports downloading and viewing files like PDFs and images.
Redirects to 404.html for missing resources.

📚 Lessons Learned
Socket programming using Winsock2.
Efficient file handling with _open, _read, _stat.
HTTP protocol basics and MIME type mapping.
Debugging segmentation faults and compilation errors.
Building multi-threaded C applications on Windows.

📅 Date Created
January 2025

