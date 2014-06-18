/* who3.c - who with buffered reads 
 *        - surpresses empty records
 *        - formats time nicely
 *        - buffers input (using utmplib)
 */
#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
  
#define SHOWHOST  
  
void show_info(struct utmp *);
void showtime(time_t);

int main(void)
{
  struct utmp *utbufp, 			/* holds pointer to next rec */
	  *utmp_next();			/* returns pointer to next */
  
  if ( utmp_open( UTMP_FILE ) == -1 )
  {
    perror( UTMP_FILE );
    exit(1);
  }
  
  while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
    show_info( utbufp );
  
  utmp_close();
  return 0;
}

/*
 *  show info()
 * 		display the contents of the utmp struct
 * 		in human readable from
 * 		* display nothing if record has no user name
 */
void show_info(struct utmp * utbufp)
{
  if (utbufp->ut_type != USER_PROCESS)
    return ;
  
  printf("%-8.8s", utbufp->ut_name);	/* the logname */
  printf(" ");				/* a space */
  printf("%-8.8s", utbufp->ut_line);	/* display time */
  printf(" ");				/* a space */
  showtime(utbufp->ut_time);		/* display name */
#ifdef SHOWHOST
  if(utbufp->ut_host[0] != '\0')
    printf("(%s)", utbufp->ut_host);	/* the host */
#endif 
    printf("\n");			/* newline */
}


/*
 *  display time in a format fit for human consumption 
 *  uses ctime to build a string then picks parts out of it
 *  Note: %12.12s prints a string 12 chars wide and LIMITS
 *  it to 12chars
 */
void showtime(long timeval)
{
  char *cp;				/* to hold address of time */
  cp = ctime(&timeval);			/* convert time to string */
					/* string look like */
					/* Mon Feb 4 00:46:40 EST 1991 */
					/* 0123456789012345. */
  printf("%12.12s", cp + 4);		/* pick 12 chars from pos 4 */  
}
