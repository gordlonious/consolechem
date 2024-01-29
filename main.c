#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define HEADER 55 /* Line lengths include separators, but are later replaced with null terminators */
#define HYDROGEN 30
#define HELIUM 27

#define RDERR 1 /* Read error */
#define RDNAV 2 /* Read some data not available */

void readfn(int fd, char *line, int lineLen)
{
    ssize_t readcount = read(fd, line, lineLen);
    if (readcount == -1)
        _exit(RDERR);
    if (readcount < lineLen)
        _exit(RDNAV);
    line[lineLen - 1] = '\0';
}

int main(int argc, char *argv[])
{
    /* File is formatted as comma delimited with LF line separators */
    int fd = open("periodictable", O_RDONLY);
    char header[HEADER];
    readfn(fd, header, HEADER);
    printf("%s\n", header);

    char hydrogen[HYDROGEN];
    readfn(fd, hydrogen, HYDROGEN);
    printf("%s\n", hydrogen);

    char helium[HELIUM];
    readfn(fd, helium, HELIUM);
    printf("%s\n", helium);
    close(fd);
}
