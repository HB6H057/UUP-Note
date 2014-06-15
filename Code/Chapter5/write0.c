#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  int fd;
  char bufp[BUFSIZ];
  /* check args */
  if (ac != 2)
  {
    fprintf(stderr, "usage:write0 ttyname\n");
    exit(1);
  }
  
  /* open devices */
  fd = open(argv[1], O_WRONLY);
  if ( fd == -1 )
  {
    perror(argv[1]);
    exit(1);
  }
  
  /* loop until EOF on input */
  while( fgets(buf, BUFSIZ, stdin) != NULL )
  {
    if ( write(fd, buf, strlen(buf)) == -1 )
      break;
  }
  
  close( fd );
  
  return 0;
}
