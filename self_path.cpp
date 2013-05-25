#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>

ssize_t self_path_c(char ** const buf);
ssize_t self_path(std::string &result);

int main(void)
{
	std::string str;
	ssize_t r = self_path(str);
	if (r >= 0) {
		std::cout << str << std::endl;
	}
	return 0;
}

// http://stackoverflow.com/questions/933850
// http://stackoverflow.com/questions/9385386
// http://stackoverflow.com/questions/1023306
// http://stackoverflow.com/questions/12468104
// readlink("/proc/self/exe", buf, bufsize) // Linux
// readlink("/proc/self/path/a.out", buf, bufsize) // Solaris
// getexecname() // Solaris
// readlink("/proc/curproc/file", buf, bufsize) // BSD with procfs
// sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1 // FreeBSD
// GetModuleFileName(NULL, buf, bufsize) // Windows
// _NSGetExecutablePath() // Mac OS X
ssize_t self_path_c(char ** const buf)
{
#if defined(__linux__) // Linux
	if (!buf || *buf) {
		// buf should not be NULL
		// *buf should be NULL to remove possiblity of memory leak
		return -1;
	}
	size_t size = 4096;
	*buf = NULL;
	ssize_t result = -1;
	do {
		free(*buf); // free(NULL) is legal
		*buf = (char*) malloc(size);
		if (!(*buf)) {
			//errno = ENOMEM; // aleady done by malloc (?)
			perror("error");
			break;
		}
		result = readlink("/proc/self/exe", *buf, size - 1);
		if (result == -1 && errno != ENAMETOOLONG) {
			perror("error: readlink");
			break;
		}
		if (result >= (size - 1)) {
			size *= 2;
			result = -1; // continue loop
		}
	} while (result == -1);
	if (result >= 0) {
		// readlink doesn't terminate string
		(*buf)[result] = '\0';
	}
	return result;
//#elif defined(_WIN32) // Windows 32-bit and 64-bit
//#elif defined(__FreeBSD__) // FreeBSD
//#elif defined(__sun) && defined(__SVR4) // Solaris
//#elif defined(__APPLE__) // Apple
#else
	// TODO
	return -1;
#endif
}

ssize_t self_path(std::string &result)
{
	char *buf = NULL;
	ssize_t r = self_path_c(&buf);
	if (r >= 0) {
		result = buf;
	}
	free(buf);
	return r;
}
