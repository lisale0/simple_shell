#include <stdlib.h>
char *_getline()
{
        char *buffer;
        int bufsize = 1024;
        int fdread;

        buffer = malloc(sizeof(char) * bufsize);
        fdread = read(0, buffer, bufsize);
        return (buffer);
}
