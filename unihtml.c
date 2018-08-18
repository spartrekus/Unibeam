
// unimark converter: unihtml converts mrk files to html files

// Compile with GCC: gcc -o unihtml unihtml.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>


void runwith( char *thecmd , char *thefile )
{
       char cmdi[PATH_MAX];
       printf( "<CMD: %s>\n" , thecmd ) ; 
       printf( "<FILE: %s>\n" , thefile ) ; 
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
}





char *strcut( char *str , int myposstart, int myposend )
{  
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}




char *strtrim(char *str)
{  
      // right side to to finish
      char ptr[strlen(str)+1];
      int strposmax = strlen( str );
      int lastposchar = strposmax;
      int i,j=0;
      int foundspace = 1;

      /// find last char
      foundspace = 1;
      for( i= strposmax-1 ; i >= 0 ; i--)
      {
         //printf( "|%d-%d-%c| ", i , lastposchar , str[i] );
	 // find where to space
         if ( foundspace == 1 ) 
         if ( str[i] == ' ' ) 
   	    lastposchar = i-1;

         if ( str[i] != ' ' ) 
           foundspace = 0;
      } 

      // add the content
      foundspace = 1;
      for(i=0; i <= lastposchar ; i++)
      {
        if ( foundspace == 1 ) 
         if ( ( str[i] != ' ' )  && ( str[i] != 9 ) ) //added! with 9 for a TAB!!
          foundspace = 0;

        if ( foundspace == 0 ) 
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';

      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}





///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void filecat(  char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  char inputfield[PATH_MAX];

  int linecounter = 1;

  /////////////////////////////////////////////////
  {

    //printf( "\n" );

    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          fgets(fetchlinetmp, PATH_MAX, fp6); 
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];

	      //printf( "%d: %s", linecounter++, fetchline );
	      //printf( "\n" );


              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'p' )
              if ( fetchline[2] == 'a' )
              if ( fetchline[3] == 'r' )
              if ( fetchline[4] == 'a' )
              if ( fetchline[5] == ' ' )
              {
 	         printf( "<p>" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s", inputfield );
 	         printf( "</p>\n" );
              }

              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'l' )
              if ( fetchline[2] == 'i' )
              if ( fetchline[3] == 'n' )
              if ( fetchline[4] == 'e' )
              if ( fetchline[5] == ' ' )
              {
                 strncpy( inputfield, strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s", inputfield );
 	         printf( "<br>\n" );
              }


              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'h' )
              if ( fetchline[2] == 'l' )
              if ( fetchline[3] == 'i' )
              if ( fetchline[4] == 'n' )
              if ( fetchline[5] == 'e' )
              {
 	         printf( "<hr>\n" );
              }

              if ( fetchline[0] == '!' )
              if ( fetchline[1] == '=' )
              if ( fetchline[2] == ' ' )
              {
 	         printf( "<h1>", inputfield );
                 strncpy( inputfield, strtrim( strcut( fetchline, 2+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s", inputfield );
 	         printf( "</h1>\n", inputfield );
 	         printf( "<br>\n", inputfield );
              }


              if ( fetchline[0] == '!' )
              if ( fetchline[1] == '=' )
              if ( fetchline[2] == '=' )
              if ( fetchline[3] == ' ' )
              {
 	         printf( "<h2>", inputfield );
                 strncpy( inputfield, strtrim( strcut( fetchline, 3+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s", inputfield );
 	         printf( "</h2>\n", inputfield );
 	         printf( "<br>\n", inputfield );
              }

              // !fig
              if ( fetchline[0] == '!' ) 
              if ( fetchline[1] == 'f' )
              if ( fetchline[2] == 'i' )
              if ( fetchline[3] == 'g' )
              if ( fetchline[4] == ' ' )
              {
	         printf( "<img src=\"" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s", inputfield );
  	         printf( "\"", fp5 );
  	         printf( ">" );
  	         printf( "<br>" );
  	         printf( "\n" );
              }



              // !url
              if ( fetchline[0] == '!' ) 
              if ( fetchline[1] == 'u' )
              if ( fetchline[2] == 'r' )
              if ( fetchline[3] == 'l' )
              if ( fetchline[4] == ' ' )
              {
	         printf( "<a href=\"" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s", inputfield );
  	         printf( "\">", fp5 );
  	         printf( "Link" );
  	         printf( "</a>" );
  	         printf( "<br>" );
  	         printf( "\n" );
              }

     }
     fclose( fp6 );
   }
}





////////////////////////////////////////////////
int main( int argc, char *argv[])
{
    char cwd[PATH_MAX]; int i ; 

    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    if ( strcmp(argv[1], "--arg" ) == 0)
    {
          for( i = 1 ; i < argc ; i++) 
	     printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i] );
          return 0;
    }
    
    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
	     filecat( argv[ i ] );
          return 0;
    }

    return 0;
}


