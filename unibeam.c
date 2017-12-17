

//////////////////////////////////
// AUTHOR: Spartrekus           //
// GNU LICENCE                  //
// Date: 2017 - June - 25       //
// Aim: 2017 - June - 25        //
//   For Making Thesis Easily   //
//   and more                   //
// Destined to Amiga, Sun, .... //
// Atari, CPC, ... having C     //
//////////////////////////////////


/// Note: include, tiny isn't it?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>



/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/// global vars which can be removed for better readability 
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
char slidebufferdata[200][PATH_MAX];
char slidebufferfigfile[PATH_MAX];
char slidebufferfigfile1[PATH_MAX];
char slidebufferfigfile2[PATH_MAX];
char slidebufferfignote[PATH_MAX];
int  slidebufferfig=0;
int  slidebuffernot=0;
int  foxy = 0;
int  mynumber = 1;


int  slidebufferfoundsection = 0;
char slidemysection[PATH_MAX];
char mygraphicspath[PATH_MAX];
char myinputspath[PATH_MAX];

int markup_output_format = 1; // 1:tex, 2:html, 
int markup_language = 1; // 1:english , 2:french, 3:german
int markup_item = 1;    //  1:default , 2:3pkt, 

int txtbeginreview = 0; 
int txtrawcode = 0; 
int beamercode = 0; 
int notercode  = 0; 
int contentcode = 0; 
int option_system_call = 0;           // this will be 0 by default (depreciated)
int option_strtxt2tex_linefeed = 1;   // this shall be 0 by default for compact documents






/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}







//////////////////
void ncp( char *filetarget,  char *  filesource )
{
  // fread
  char            buffer[1];
  size_t          n;
  size_t          m;
  FILE *fp;
  FILE *fp1; 
  FILE *fp2;
  int counter = 0 ; 
  int freader = 1 ; 
  int i , j ,posy, posx ; 
  if ( fexist( filesource ) == 1 )
  {
        fp = fopen( filesource, "rb");
        fp2 = fopen( filetarget, "wb");
        counter = 0; 
        while(  !feof(fp) && ( freader == 1)   ) {
           if (  feof(fp)   ) {
                freader = 0 ; 
            }
            n = fread(  buffer, sizeof(char), 1 , fp);
            m = fwrite( buffer, sizeof(char), 1,  fp2);
        }
        fclose(fp2);
        fclose(fp);
      }
}






/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strampersand2txt(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == '&' ) 
	{
          ptr[j++]=':';
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}






/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strtxt2tex(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {

        if ( str[i] == '{' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='{';
	}

        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}

        //    \newcommand{\lt}{\ensuremath{<}\thinspace}%
        //    \newcommand{\gt}{\ensuremath{>}\thinspace}%
        else if ( str[i] == '>' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='e';
          ptr[j++]='n';
          ptr[j++]='s';
          ptr[j++]='u';
          ptr[j++]='r';
          ptr[j++]='e';
          ptr[j++]='m';
          ptr[j++]='a';
          ptr[j++]='t';
          ptr[j++]='h';
          ptr[j++]='{';
          ptr[j++]='>';
          ptr[j++]='}';
          ptr[j++]=' ';
	}

        else if ( str[i] == '<' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='e';
          ptr[j++]='n';
          ptr[j++]='s';
          ptr[j++]='u';
          ptr[j++]='r';
          ptr[j++]='e';
          ptr[j++]='m';
          ptr[j++]='a';
          ptr[j++]='t';
          ptr[j++]='h';
          ptr[j++]='{';
          ptr[j++]='<';
          ptr[j++]='}';
          ptr[j++]=' ';
	}


        else if ( str[i] == '}' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='}';
	}
        else if ( str[i] == '_' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='_';
	}
        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}
        else if ( str[i] == '#' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='#';
	}

        else if ( str[i] == '&' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='&';
	}

        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}

        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}





/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strcsv2tex(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == ';' ) 
	{
          ptr[j++]=' ';
          ptr[j++]='&';
          ptr[j++]=' ';
	}
        else if ( str[i] == 9 ) 
	{
          ptr[j++]=' ';
          ptr[j++]='&';
          ptr[j++]=' ';
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}













char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}








///// some cat!! 
#include <fcntl.h>
#include <unistd.h>
static int cat_fd(int fd) 
{
  char buf[4096];
  ssize_t nread;

  while ((nread = read(fd, buf, sizeof buf)) > 0) 
  {
    ssize_t ntotalwritten = 0;
    while (ntotalwritten < nread) {
      ssize_t nwritten = write(STDOUT_FILENO, buf + ntotalwritten, nread - ntotalwritten);
      if (nwritten < 1)
        return -1;
      ntotalwritten += nwritten;
    }
  }

  return nread == 0 ? 0 : -1;
}




static int ncat_static(const char *fname) {
  int fd, success;
  if ((fd = open(fname, O_RDONLY)) == -1)
    return -1;

  success = cat_fd(fd);

  if (close(fd) != 0)
    return -1;

  return success;
}










///////////////////////////////
///////////////////////////////
///////////////////////////////
char *strtimestamp()
{
      long t;
      struct tm *ltime;
      time(&t);
      ltime=localtime(&t);
      char charo[50];  int fooi ; 
      fooi = snprintf( charo, 50 , "%04d%02d%02d%02d%02d%02d",
	1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, 
	ltime->tm_hour, ltime->tm_min, ltime->tm_sec 
	);
    size_t siz = sizeof charo ; 
    char *r = malloc( sizeof charo );
    return r ? memcpy(r, charo, siz ) : NULL;
}





int strcount( char *str , int mychar )
{  
      int return_strcount = 0;
      char ptr[strlen(str)+1];
      int i,j = 0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == mychar ) return_strcount++;
      } 
      return return_strcount;
}






void nrunwith( char *thecmd , char *thefile ){
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







/////////////////////////////////////
void fileappendbegin( char *fileout)
{
    FILE *fp5;
    fp5 = fopen( fileout , "ab+");
      fputs( "\\documentclass{article}\n", fp5 );
      fputs( "\\begin{document}\n", fp5 );
    fclose( fp5 );
}
/////////////////////////////////////
void fileappendend( char *fileout)
{
    FILE *fp5;
    fp5 = fopen( fileout , "ab+");
      fputs( "\\end{document}\n", fp5 );
    fclose( fp5 );
}






/////////////////////////////////////
void filenew( char *fileout)
{
    FILE *fp5;
    fp5 = fopen( fileout , "wb+");
    fclose( fp5 );
}






///////////////////////////////////////////////////////////////////
void filerawcat(  char *fileout, char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];

  /////////////////////////////////////////////////
  if ( fexist( filein ) == 1 )
  {
    fp5 = fopen( fileout , "ab+");
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          fgets(fetchlinetmp, PATH_MAX, fp6); 
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];

         if ( !feof(fp6) )
         {
 	      fputs( fetchline , fp5 );
  	      fputs( "\n", fp5 );
	 }
     }
     fclose( fp5 );
     fclose( fp6 );
   }
}





/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
char *strrlf(char *str)
{  
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
char *strsplit(char *str , int mychar , int myitemfoo )
{  
      char ptr[strlen(str)+1];
      int myitem = myitemfoo +1;
      int i,j=0;
      int fooitem = 0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == mychar ) 
           fooitem++;
        //else if ( str[i] != mychar &&  fooitem == myitem-1  ) 
        else if ( str[i] != mychar &&  fooitem == myitem-2  ) 
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}






/// customed one
char *strdelimit(char *str , int mychar1, int mychar2,  int mycol )
{ 
      char ptr[strlen(str)+1];
      char ptq[strlen(str)+1];
      strncpy( ptr, strsplit( str, mychar1 , mycol+1 ), strlen(str)+1 );
      strncpy( ptq, strsplit( ptr, mychar2 , 1 ), strlen(str)+1 );
      size_t siz = sizeof ptq ; 
      char *r = malloc( sizeof ptq );
      return r ? memcpy(r, ptq, siz ) : NULL;
}







char *fbasename(char *name)
{
  char *base = name;
  while (*name)
    {
      if (*name++ == '/')
	{
	  base = name;
	}
    }
  return (base);
}




//////////////////////////////////
char *fextension(char *str)
{ 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=strlen(str)-1 ; str[i] !='.' ; i--)
      {
        if ( str[i] != '.' ) 
            ptr[j++]=str[i];
      } 
      ptr[j]='\0';

      char ptrout[strlen(ptr)+1];  
      j = 0; 
      for( i=strlen(ptr)-1 ;  i >= 0 ; i--)
            ptrout[j++]=ptr[i];
      ptrout[j]='\0';

      size_t siz = sizeof ptrout ; 
      char *r = malloc( sizeof ptrout );
      return r ? memcpy(r, ptrout, siz ) : NULL;
}









//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
char *cat_returnline( char *thefilefoo, int theline  )
{
  char catfetchlinetmp[PATH_MAX];
  char catfetchline[PATH_MAX];
  char buf[PATH_MAX];
  char ptr[PATH_MAX];
  ssize_t nread;
  int i,j,k;
  double linenbr = 0;
  i = 0; 
  j = 0;
  int beginend = 0;
    FILE *fp9;
    fp9 = fopen( thefilefoo , "rb");
    while( !feof(fp9) ) 
    {
          strncpy( catfetchline, "" , PATH_MAX );
          fgets(catfetchlinetmp, PATH_MAX, fp9); 
          linenbr++;
          for( i = 0 ; ( i <= strlen( catfetchlinetmp ) ); i++ )
            if ( catfetchlinetmp[ i ] != '\n' )
              catfetchline[i]=catfetchlinetmp[i];

         if ( !feof(fp9) )
         {
              if ( linenbr == theline ) 
                 strncpy( ptr, catfetchline, PATH_MAX );
	 }
     }
     fclose( fp9 );

     size_t siz = 1 + sizeof ptr ; 
     char *r = malloc( 1 +  sizeof ptr );
     return r ? memcpy(r, ptr, siz ) : NULL;
}











//////////////////////////
/// depreciated - will be replaced!!
//////////////////////////
char *filename_newext( char *str , char *newext )
{
      char ptr[strlen(str)+1];
      int i,j=0;
      int foundpoint = 0; 
      for(i=strlen(str)-1 ; i!=-1 ; i--)
      {
          if ( str[i] == '.' ) foundpoint = i; 
      } 

     if ( foundpoint >= 1 ){
      int maxsize = strlen(str)+1+strlen(newext) ;
      char ptrnew[ maxsize ];
      strncpy( ptrnew, strcut( str, 1, foundpoint+1 ),  maxsize  ); 

      ptrnew[ foundpoint ] = '.';
      for(i=0 ; i<= strlen( newext)-1 ; i++)
         ptrnew[ foundpoint+1 +i ] = newext[ i ];
      ptrnew[ foundpoint +i+1] = '\0';

       size_t siz = sizeof ptrnew ; 
       char *r = malloc( sizeof ptrnew );
       return r ? memcpy(r, ptrnew, siz ) : NULL;
    } else return ""; 
}








///////////////////////////////////////////////////////////////////
void nfileunimark( char *fileout, char *filein )
{
  char poolfilename[PATH_MAX];

  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinefoo[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  char fetchcmdline[PATH_MAX];
  int fetchcmdlinelen = 0;

  char charin[PATH_MAX];
  char charout[PATH_MAX];
  char lineout[PATH_MAX];

  char mkdirdir[PATH_MAX];
  char ndirfig[PATH_MAX];
  char usertextfieldone[PATH_MAX];
  char usertextfieleps[PATH_MAX];
  char usertextfieldtwo[PATH_MAX];
  char wgetcmd[PATH_MAX];
  char extcmd[PATH_MAX];
  int fooc; 
  char fooccharo[PATH_MAX];

  int foundcode = 0; 
  int advancedcode = 1; 
  int commenton = 0; 
  int beginitemize = 0; 

  int itemlevel = 0; 

  int beamerlevel = 0; 
  int numberinglevel = 0; 
  int unilistemptyline = 0; 
  int fooi; 
  //int fetchcmdpos=0;
  int foundcmd = 0;

  char mycurrenttag[PATH_MAX];
  strncpy( mycurrenttag, "", PATH_MAX );

  /////////////////////////////////////////////////
  if ( fexist( filein ) == 1 )
  {
    fp5 = fopen( fileout , "ab");
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          // vars
	  foundcode = 0; 
	  foundcmd = 0; 

	  // this fgets is there to be easy to port to any systems
	  // fgets can be easily ported to things such as PHP !!

          fgets( fetchlinetmp, PATH_MAX, fp6); 
          strncpy( fetchline , "" , PATH_MAX );
          strncpy( fetchcmdline , "" , PATH_MAX );


          // 20170811-180203
          // remove lf and more
          // there is only two modifiers !
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
	    {
              fetchline[fetchi]=fetchlinetmp[fetchi];
              if ( fetchlinetmp[ fetchi ] == '!' ) 
	         foundcmd = 1 ;
              else if ( fetchlinetmp[ fetchi ] == '|' ) 
	         foundcmd = 1 ;
	    }

          /////// txtrawcode, activated with !beginraw
          if ( txtrawcode == 1 )
          {
             if ( fetchline[0] != '!' ) 
             if ( fetchline[0] != '|' )  // there is only 2 modifiers
             {
                 strncpy( fetchlinefoo, fetchline , PATH_MAX );
                 strncpy( fetchline , strtxt2tex( fetchlinefoo ) , PATH_MAX );
             }
          }



          //// make a cmdline
          strncpy( fetchcmdline, strtrim( fetchline ) , PATH_MAX );
          fetchcmdlinelen = strlen(fetchcmdline);




          if ( !feof(fp6) )
          {
            /////////////////////////////////////
            ////  for comment mycomment
	    ////  type 1 like in C language
            //////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '/' )
            if ( fetchline[1] == '/' )
            {
  	      foundcode = 1;
            }


            ///////////////////////////////////
            ///////////////////////////////////
            //// !tex, quicker, faster and easier
            if ( foundcode == 0 )  // !btex 
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 't' )
            if ( fetchline[3] == 'e' )
            if ( fetchline[4] == 'x' )
            {
  	      fputs( "\n", fp5 );
              fputs( "\\documentclass[11pt]{article}", fp5 );
  	      fputs( "\n", fp5 );
              fputs( "\\begin{document}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            } 



            if ( foundcode == 0 )
            if ( fetchline[0] == '#' )
            if ( strstr( fetchline, "#include" ) == 0 )
            if ( strstr( fetchline, "#input" ) == 0 )
            {
  	      foundcode = 1;
            }

            //////////////////////////////////
            //////////////////////////////////
            //////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '/' )
            if ( fetchcmdline[1] == '/' )
            {
  	      foundcode = 1;
            }



            /////////////////////////////////////
            if ( foundcode == 0 )
            if (( fetchcmdline[0] == '/' ) && ( fetchcmdline[1] == '*' ))
            {
  	      commenton = 1;
    	      foundcode = 1;
            }
            ////////////////////////////////////
            if ( foundcode == 0 )
            if ( ( fetchcmdline[ fetchcmdlinelen -2 ] == '*' ) && ( fetchcmdline[ fetchcmdlinelen -1 ] == '/' ))
            {
  	      commenton = 0;
    	      foundcode = 1;
            }

            ////////////////////////////////////
            if ( foundcode == 0 )
            if ( ( fetchcmdline[0] == '*' ) && ( fetchcmdline[1] == '/' ))
            {
  	      commenton = 0;
    	      foundcode = 1;
            }

	    //// active if needed
            if ( commenton == 1 )
            {
    	      foundcode = 1;
            }

            // =================================
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '=' ) 
	    if ( fetchcmdline[1] == '=' ) 
	    if ( fetchcmdline[2] == '=' ) 
	    if ( fetchcmdline[3] == '=' ) 
	    if ( fetchcmdline[4] == '=' ) 
	    if ( fetchcmdline[5] == '=' ) 
	    if ( fetchcmdline[6] == '=' ) 
	    if ( fetchcmdline[7] == '=' ) 
	    if ( fetchcmdline[8] == '=' )
            {
  	      foundcode = 1;
            }
            // =================================
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '-' ) 
	    if ( fetchcmdline[1] == '-' ) 
	    if ( fetchcmdline[2] == '-' ) 
	    if ( fetchcmdline[3] == '-' ) 
	    if ( fetchcmdline[4] == '-' ) 
	    if ( fetchcmdline[5] == '-' )
	    if ( fetchcmdline[6] == '-' ) 
	    if ( fetchcmdline[7] == '-' ) 
	    if ( fetchcmdline[8] == '-' )
            {
  	      foundcode = 1;
            }



           ////////////////////////////////////
           if ( strcmp( fetchline, "" ) == 0 )
	        unilistemptyline++;
	      else
	        unilistemptyline = 0;



            // !institute text 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 'n' )
            if ( fetchline[3] == 's' )
            if ( fetchline[4] == 't' )
            if ( fetchline[5] == 'i' )
            if ( fetchline[6] == 't' )
            if ( fetchline[7] == 'u' )
            if ( fetchline[8] == 't' )
            if ( fetchline[9] == 'e' )
            if ( fetchline[10] == ' ' )
            {
 	      fputs( "\\institute{" , fp5 );
 	      fputs( strcut( fetchline, 10+2, strlen(fetchline)) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }


            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 'n' )
            if ( fetchline[3] == 'p' )
            if ( fetchline[4] == 'u' )
            if ( fetchline[5] == 't' )
            if ( fetchline[6] == 'l' )
            if ( fetchline[7] == 'i' )
            if ( fetchline[8] == 'n' )
            if ( fetchline[9] == 'e' )
            if ( fetchline[10] == '{' )
            {
              char fooreturnchar[PATH_MAX];
              char foofilefound[PATH_MAX];
              strncpy( foofilefound, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
              if ( fexist( foofilefound ) == 1 ) 
              {
                strncpy( fooreturnchar , cat_returnline(  foofilefound , atoi( strdelimit( fetchline,  '{' ,'}' ,  2 )))  , PATH_MAX );
 	        fputs(   fooreturnchar , fp5 );
  	        fputs( "\n", fp5 );
              }
  	      foundcode = 1;
            }


            // !author text 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'a' )
            if ( fetchline[2] == 'u' )
            if ( fetchline[3] == 't' )
            if ( fetchline[4] == 'h' )
            if ( fetchline[5] == 'o' )
            if ( fetchline[6] == 'r' )
            if ( fetchline[7] == ' ' )
            {
 	      fputs( "\\author{" , fp5 );
 	      fputs( strcut( fetchline, 7+2, strlen(fetchline)) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }

            // !date text 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'd' )
            if ( fetchline[2] == 'a' )
            if ( fetchline[3] == 't' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == ' ' )
            {
 	      fputs( "\\date{" , fp5 );
 	      fputs( strcut( fetchline, 5+2, strlen(fetchline)) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }


            // !title text 
            if ( foundcode == 0 )
            if ( (( fetchline[0] == '!' )
            && ( fetchline[1] == 't' )
            && ( fetchline[2] == 'i' )
            && ( fetchline[3] == 't' )
            && ( fetchline[4] == 'l' )
            && ( fetchline[5] == 'e' )
            && ( fetchline[6] == ' ' )))
            {
 	      fputs( "\\title{" , fp5 );
              if ( fetchline[0] == '!' )
 	        fputs( strcut( fetchline, 6+2, strlen(fetchline)) , fp5 );
              else
 	        fputs(  strtxt2tex( strcut( fetchline, 7+2, strlen(fetchline)) ) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }
            // !|title text 
            if ( foundcode == 0 )
          if ( ( fetchline[0] == '!' )
            && ( fetchline[1] == '|' )
            && ( fetchline[2] == 't' )
            && ( fetchline[3] == 'i' )
            && ( fetchline[4] == 't' )
            && ( fetchline[5] == 'l' )
            && ( fetchline[6] == 'e' )
            && ( fetchline[7] == ' ' ))
            {
 	      fputs( "\\title{" , fp5 );
 	      fputs(  strtxt2tex( strcut( fetchline, 7+2, strlen(fetchline)) ) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }




            // !maketitle
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'm' )
            if ( fetchcmdline[2] == 'a' )
            if ( fetchcmdline[3] == 'k' )
            if ( fetchcmdline[4] == 'e' )
            if ( fetchcmdline[5] == 't' )
            if ( fetchcmdline[6] == 'i' )
            if ( fetchcmdline[7] == 't' )
            if ( fetchcmdline[8] == 'l' )
            if ( fetchcmdline[9] == 'e' )
            {
 	      fputs( "\\maketitle" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }



            /////////////////////////////////////
            /// for CSV or tables !!!!!!!!!!!!
            /////////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'c' )
            if ( fetchline[2] == 's' )
            if ( fetchline[3] == 'v' )
            if ( fetchline[4] == ' ' )
            {
 	      fputs( strcsv2tex(  strcut(   fetchline , 4+2, strlen(  fetchline )) )   , fp5 );
  	      fputs( " ", fp5 );
  	      fputs( "\\", fp5 );
  	      fputs( "\\", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }








            /////////////////////////////////////
            /// for RAW or reviews !!!!!!!!!!!!
            /////////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '|' )
            if ( fetchline[1] == ' ' )
            {
 	      fputs(  strtxt2tex(   strcut(   fetchline , 1+2, strlen(  fetchline )) )   , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }

            /////////////////////////////////////
            /// for RAW or reviews !!!!!!!!!!!!
            /////////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '|' )
            if ( fetchline[1] == '|' )
            if ( fetchline[2] == ' ' )
            {
 	      fputs(  strtxt2tex(   strcut(   fetchline , 2+2, strlen(  fetchline )) )   , fp5 );
  	      fputs( "\\", fp5 );
  	      fputs( "\\", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }


            /////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'v' )
            if ( fetchline[2] == 's' )
            if ( fetchline[3] == 'p' )
            if ( fetchline[4] == ' ' )
            {
 	      fputs( "\\vspace{" , fp5 );
 	      fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
 	      fputs( "}" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }




            ///////// FORCE RAW   //  !raw: bla 
            ///////// FORCE RAW   //  !raw bla 
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'r' ) 
            if ( fetchline[2] == 'a' ) 
            if ( fetchline[3] == 'w' ) 
            if ( fetchline[4] == ' ' ) 
            {
 	      fputs( strcut( fetchline, 4+2, strlen(fetchline)) , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }




            //// !toc
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( fetchcmdline, "!toc" ) == 0 )
            {
 	      fputs( "\\tableofcontents" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            } 




            /////////////////////////////////
            /////////////////////////////////
            // \usepackage{url}
            // \usepackage{hyperref}
            // \usepackage{graphicx}
            // \usepackage{grffile}
            //  xcolor ? for xfig fig2dev
            /////////////////////////////////
            /////////////////////////////////
            if ( foundcode == 0 )   // !gfx 
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'g' )
            if ( fetchline[2] == 'f' )
            if ( fetchline[3] == 'x' )
            {
 	      fputs( "\n" , fp5 );
 	      fputs( "\\usepackage{url}\n" , fp5 );
 	      fputs( "\\usepackage{hyperref}\n" , fp5 );
 	      fputs( "\\usepackage{graphicx}\n" , fp5 );
 	      fputs( "\\usepackage{grffile}\n" , fp5 );
 	      fputs( "\\usepackage{xcolor}\n" , fp5 );
 	      fputs( "\n" , fp5 );
  	      foundcode = 1;
            }


            if ( foundcode == 0 )   // !tikz 
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 't' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'k' )
            if ( fetchline[4] == 'z' )
            {
 	      fputs( "\n" , fp5 );
 	      fputs( "\\usepackage{tikz}\n" , fp5 );
 	      fputs( "\n" , fp5 );
  	      foundcode = 1;
            }


            //////////////////////////////////
            //// !package
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) // for left at 0 char pos
            if ( fetchline[1] == 'p' )
            if ( fetchline[2] == 'a' )
            if ( fetchline[3] == 'c' )
            if ( fetchline[4] == 'k' )
            if ( fetchline[5] == 'a' )
            if ( fetchline[6] == 'g' )
            if ( fetchline[7] == 'e' )
	    //if ( strcmp( fetchline, "!packages" ) == 0 )
            {
 	      fputs( "\n" , fp5 );
 	      fputs( "\\usepackage{url}\n" , fp5 );
 	      fputs( "\\usepackage{hyperref}\n" , fp5 );
 	      fputs( "\\usepackage{graphicx}\n" , fp5 );
 	      fputs( "\\usepackage{grffile}\n" , fp5 );
 	      fputs( "\\usepackage{pdfpages}\n" , fp5 );
 	      fputs( "\\usepackage{wallpaper}\n" , fp5 );
 	      fputs( "\n" , fp5 );
 	      fputs( "\\usepackage{epstopdf}\n" , fp5 );
 	      fputs( "\\usepackage{enumitem}\n" , fp5 );  // for >>
 	      fputs( "\n" , fp5 );
              fputs( "\\sloppy\n", fp5 );
              fputs( "\\usepackage[none]{hyphenat}\n", fp5 );
  	      foundcode = 1;
            } 




            //////////////////////////////////
            //// !utf
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( fetchcmdline, "!utf" ) == 0 )
            {
              fputs( "\\usepackage[utf8]{inputenc}", fp5 );
  	      fputs( "\n", fp5 );
              fputs( "\\usepackage{textcomp}", fp5 ); //for deg
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            } 


            /////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '\\' ) 
            if ( fetchline[1] == 'm' )
            if ( fetchline[2] == 'y' )
            if ( fetchline[3] == 's' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == 'c' )
            if ( fetchline[6] == 't' )
            if ( fetchline[7] == 'i' )
            if ( fetchline[8] == 'o' )
            if ( fetchline[9] == 'n' )
            if ( fetchline[10] == '{' )
            {
 	      fputs( "\\section{" , fp5 );
 	      fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
 	      fputs( "}" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            } 




            // !beginraw, useful for reviewers
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == 'i' )
            if ( fetchline[5] == 'n' )
            if ( fetchline[6] == 'r' )
            if ( fetchline[7] == 'a' )
            if ( fetchline[8] == 'w' )
            {
	      txtrawcode = 1;
  	      foundcode = 1;
            }
            // !endraw
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'e' )
            if ( fetchline[2] == 'n' )
            if ( fetchline[3] == 'd' )
            if ( fetchline[4] == 'r' )
            if ( fetchline[5] == 'a' )
            if ( fetchline[6] == 'w' )
            {
	      txtrawcode = 0;
  	      foundcode = 1;
            }







            // !input 
            if ( foundcode == 0 )
	    if ( 
            ( (  fetchline[0] ==  '!' ) || (  fetchline[0] ==  '#' ) )
            && ( fetchline[1] == 'i' )
            && ( fetchline[2] == 'n' )
            && ( fetchline[3] == 'p' )
            && ( fetchline[4] == 'u' )
            && ( fetchline[5] == 't' )
            && ( fetchline[6] == '{' )
	    )
            {
              fclose( fp5 );                 /// writer
              long saved = ftell( fp6 );     /// reader
              fclose( fp6 );                 /// reader

              printf( ">COMMAND INPUT<\n"); 
	      char fileinputsrc[PATH_MAX];
	      strncpy( fileinputsrc,  myinputspath , PATH_MAX );
              strncat( fileinputsrc , strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
              printf( ">COMMAND INPUT Src %s<\n", fileinputsrc ); 

	        if ( fileinputsrc[0] == '~' )
	        {
	         strncpy( fileinputsrc, "" , PATH_MAX );
                 strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
                 strncat( fileinputsrc , strdelimit( fetchline,  '~' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
	        }
                //filetexiex( fileout, strdelimit( fetchline,  '{' ,'}' ,  1 ) );
		printf( "!input{%s} (fexist:%d) (...)\n", fileinputsrc , fexist( fileinputsrc ) );
                printf( "> READ FROM IPATH: %s\n", myinputspath );
                nfileunimark( fileout, fileinputsrc );
              fp5 = fopen( fileout , "ab+"); /// writer
              fp6 = fopen( filein , "r");  /// reader
              fseek( fp6 , saved , SEEK_SET); // reader 
  	      foundcode = 1;
            }



            //////////////////
            if ( foundcode == 0 )
	    if ( 
            ( (  fetchline[0] ==  '!' ) || (  fetchline[0] ==  '#' ) )
            && ( fetchline[1] == 'i' )
            && ( fetchline[2] == 'n' )
            && ( fetchline[3] == 'c' )
            && ( fetchline[4] == 'l' )
            && ( fetchline[5] == 'u' )
            && ( fetchline[6] == 'd' )
            && ( fetchline[7] == 'e' )
            && ( fetchline[8] == '{' )
	    )
            {
              fclose( fp5 );                 /// writer
              long saved = ftell( fp6 );     /// reader
              fclose( fp6 );                 /// reader

	      char fileinputsrc[PATH_MAX];
	      strncpy( fileinputsrc, "", PATH_MAX );
              strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
              strncat( fileinputsrc , "/include/mrk/" , PATH_MAX - strlen( fileinputsrc ) -1 );
              strncat( fileinputsrc , strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
 	      printf( " =>!include{%s} (fexist:%d) (...)\n", fileinputsrc , fexist( fileinputsrc ) );
              nfileunimark( fileout, fileinputsrc );
              fp5 = fopen( fileout , "ab+"); /// writer
              fp6 = fopen( filein , "r");  /// reader
              fseek( fp6 , saved , SEEK_SET); // reader 
  	      foundcode = 1;
            }



	    /////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( fetchcmdline, "!begin" ) == 0 )
            {
	      contentcode = 1;
 	      fputs( "\\begin{document}" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }
            ////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( fetchcmdline, "!enddoc" ) == 0 )
            {
	      contentcode = 0;
 	      fputs( "\\end{document}" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }






            //// !beamer
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == 'a' )
            if ( fetchline[4] == 'm' )
            if ( fetchline[5] == 'e' )
            if ( fetchline[6] == 'r' )
            {
	      beamercode = 1;
  	      foundcode = 1;
            }
            //// !:set beamer=0
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == ':' )
            if ( fetchline[2] == 'b' )
            if ( fetchline[3] == 'e' )
            if ( fetchline[4] == 'a' )
            if ( fetchline[5] == 'm' )
            if ( fetchline[6] == 'e' )
            if ( fetchline[7] == 'r' )
            if ( fetchline[8] == '=' )
            if ( fetchline[9] == '0' )
            {
	      beamercode = 0;
  	      foundcode = 1;
            }
            //// !noter
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'n' )
            if ( fetchline[2] == 'o' )
            if ( fetchline[3] == 't' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == 'r' )
            {
	      notercode = 1;
  	      foundcode = 1;
            }
            ///////////////////////////////////
            //// !bhtml
            if ( foundcode == 0 )  //!bhtml 
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 'h' )
            if ( fetchline[3] == 't' )
            if ( fetchline[4] == 'm' )
            if ( fetchline[5] == 'l' )
            {
              markup_output_format = 2;
  	      foundcode = 1;
            } 





   ////////////////////////////////////
   if ( foundcode == 0 )
   if ( beamercode == 1 )
   {
	    // opener !clr
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if ( ( fetchline[0] == '!' ) || ( fetchline[0] == '$' ) )
            if ( fetchline[1] == 'c' )
            if ( fetchline[2] == 'l' )
            if ( fetchline[3] == 'r' )
            {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{frame}" , PATH_MAX );
	      beamerlevel = 0;
  	      foundcode = 1;
            }



            ////////////////////
            // 20170930-175843 this is the default, without auto section numbering
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'h' )
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == 'a' )
            if ( fetchline[4] == 'd' )
            if ( fetchline[5] == 'e' )
            if ( fetchline[6] == 'r' )
            if ( fetchline[7] == ' ' )
	    if ( beamercode == 1 ) 
            {
              foxy++;
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\frametitle{"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 7+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , "}"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
  	      foundcode = 1;
            }

            ////////////////////
            // this is the short !header default
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'h' )
            if ( fetchline[2] == 'd' )
            if ( fetchline[3] == ' ' )
	    if ( beamercode == 1 ) 
            {
              foxy++;
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\frametitle{"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 3+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , "}"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
  	      foundcode = 1;
            }





            if ( foundcode == 0 )
	    if ( beamercode == 1 ) 
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'n' )
            if ( fetchline[2] == 'o' )
            if ( fetchline[3] == 't' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == ' ' )
            {
              foxy++;
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\note{"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 5+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , "}"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
  	      foundcode = 1;
            }




            /////////////////////////////
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if ( fetchline[0] == '>' )
            if ( fetchline[1] == ' ' )
            {
	      if ( beamerlevel == 1)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
	      }
	      else if ( beamerlevel == 2)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\end{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
	        beamerlevel = 1;
	      }
	      else if ( beamerlevel == 0)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////

	        beamerlevel = 1;
	      }
  	      foundcode = 1;
            }

            //////////////////////////////////
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if ( fetchline[0] == '*' )
            if ( fetchline[1] == ' ' )
            {
	      if ( beamerlevel == 2)  
	      {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
		beamerlevel = 3;
	      }
	      else if ( beamerlevel == 3)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
	        beamerlevel = 3;
	      }
	      else if ( beamerlevel == 1)  
	      {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////

	        beamerlevel = 3;
	      }
	      else if ( beamerlevel == 0)  
	      {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
	        beamerlevel = 3;
	      }
  	      foundcode = 1;
            }





            /// beamer  for txt to tex !
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if (   (( fetchline[0] == '-' ) && ( fetchline[1] == ' ' ))
            || (( fetchline[0] == '|' )  && ( fetchline[1] == '-' ) && ( fetchline[2] == ' ' )) )   // |- blabla
            {
	      if ( beamerlevel == 1)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              /////////////////////////////////
              char goofetchline[PATH_MAX];
              strncpy( goofetchline,  fetchline  , PATH_MAX);
              if ( fetchline[0] == '|' )  
                 strncat( slidebufferdata[foxy] , strtxt2tex( strtrim( strcut( goofetchline, 1+2, strlen( goofetchline )))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              else
                 strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////

		beamerlevel = 2;
	      }
	      else if ( beamerlevel == 2)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              /////////////////////////////////
              char goofetchline[PATH_MAX];
              strncpy( goofetchline,  strampersand2txt( fetchline ) , PATH_MAX);
              strncpy( goofetchline,  fetchline  , PATH_MAX);
              if ( fetchline[0] == '|' )  
                 strncat( slidebufferdata[foxy] , strtxt2tex( strtrim( strcut( goofetchline, 1+2, strlen( goofetchline )))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              else
                 strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////

	        beamerlevel = 2;
	      }
	      else if ( beamerlevel == 3)  
	      {
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\end{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              /////////////////////////////////
              char goofetchline[PATH_MAX];
              strncpy( goofetchline,  strampersand2txt( fetchline ) , PATH_MAX);
              strncpy( goofetchline,  fetchline  , PATH_MAX);
              if ( fetchline[0] == '|' )  
                 strncat( slidebufferdata[foxy] , strtxt2tex( strtrim( strcut( goofetchline, 1+2, strlen( goofetchline )))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              else
                 strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
	        beamerlevel = 2;
	      }
	      else if ( beamerlevel == 0)  
	      {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "\\begin{itemize}" , PATH_MAX );
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\item "  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              /////////////////////////////////
              char goofetchline[PATH_MAX];
              strncpy( goofetchline,  strampersand2txt( fetchline ) , PATH_MAX);
              strncpy( goofetchline,  fetchline  , PATH_MAX);
              if ( fetchline[0] == '|' )  
                 strncat( slidebufferdata[foxy] , strtxt2tex( strtrim( strcut( goofetchline, 1+2, strlen( goofetchline )))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              else
                 strncat( slidebufferdata[foxy] , strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              strncat( slidebufferdata[foxy] , ""  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
	        beamerlevel = 2;
	      }
  	      foundcode = 1;
            }

            // !info bla for beamer
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
	    if ( beamerlevel >= 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 'n' )
            if ( fetchline[3] == 'f' )
            if ( fetchline[4] == 'o' )
            if ( fetchline[5] == ' ' )
            {
              ///////////////
              strncpy( slidebufferfignote,  strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
              slidebuffernot = 1;
  	      foundcode = 1;
            }

            // !info{ for beamer
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
	    if ( beamerlevel >= 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 'n' )
            if ( fetchline[3] == 'f' )
            if ( fetchline[4] == 'o' )
            if ( fetchline[5] == '{' )
            {
              ///////////////
              strncpy( slidebufferfignote,  ""  , PATH_MAX );
              strncat( slidebufferfignote , "{\\small " , PATH_MAX - strlen( slidebufferfignote  ) -1 );
              strncat( slidebufferfignote , fbasenoext( strtxt2tex( strdelimit( fetchline,  '{' ,'}' ,  1 ) )) , PATH_MAX - strlen( slidebufferfignote  ) -1 );

              strncat( slidebufferfignote , " (Left) and " , PATH_MAX - strlen( slidebufferfignote  ) -1 );

              strncat( slidebufferfignote , fbasenoext(strtxt2tex( strdelimit( fetchline,  '{' ,'}' ,  2 ) ) ) , PATH_MAX - strlen( slidebufferfignote  ) -1 );

              strncat( slidebufferfignote , " (Right)" , PATH_MAX - strlen( slidebufferfignote  ) -1 );
              strncat( slidebufferfignote , "}" , PATH_MAX - strlen( slidebufferfignote  ) -1 );
              slidebuffernot = 1;
  	      foundcode = 1;
            }


            // !fig for beamer
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
	    if ( beamerlevel >= 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'f' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == '{' )
            {
              slidebufferfig = 1; 
              ///////////////
              char foofilefound[PATH_MAX];
              strncpy( foofilefound, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
              if ( strstr( foofilefound , "/" ) != 0 ) 
              if ( fexist( foofilefound ) == 1 ) 
              {
              }
              strncpy( slidebufferfigfile, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
  	      foundcode = 1;
              slidebufferfig = 1; 
            }


            // !figab for beamer
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
	    if ( beamerlevel >= 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'f' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == 'a' )
            if ( fetchline[5] == 'b' )
            if ( fetchline[6] == '{' )
            {
              ///////////////
              char foofilefound[PATH_MAX];
              strncpy( foofilefound, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
              if ( strstr( foofilefound , "/" ) != 0 ) 
              {
              }
              strncpy( slidebufferfigfile1 , strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
              strncpy( slidebufferfigfile2 , strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
  	      foundcode = 1;
              slidebufferfig = 2; 
            }


            // !maketitle
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'm' )
            if ( fetchcmdline[2] == 'a' )
            if ( fetchcmdline[3] == 'k' )
            if ( fetchcmdline[4] == 'e' )
            if ( fetchcmdline[5] == 't' )
            if ( fetchcmdline[6] == 'i' )
            if ( fetchcmdline[7] == 't' )
            if ( fetchcmdline[8] == 'l' )
            if ( fetchcmdline[9] == 'e' )
            {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\begin{frame}\\maketitle\\end{frame}"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
  	      foundcode = 1;
            }





            // !linefeed (beamer)
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'l' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'n' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == 'f' )
            if ( fetchline[6] == 'e' )
            if ( fetchline[7] == 'e' )
            if ( fetchline[8] == 'd' )
            {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\bigskip"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
  	      foundcode = 1;
            }

            // !bigskip (beamer)
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
            if ( fetchcmdline[0] == '!' ) 
            if ( fetchcmdline[1] == 'b' )
            if ( fetchcmdline[2] == 'i' )
            if ( fetchcmdline[3] == 'g' )
            if ( fetchcmdline[4] == 's' )
            if ( fetchcmdline[5] == 'k' )
            if ( fetchcmdline[6] == 'i' )
            if ( fetchcmdline[7] == 'p' )
            {
              ///////////////
              foxy++;//
              strncpy( slidebufferdata[foxy] , "" , PATH_MAX );
              strncat( slidebufferdata[foxy] , "\\bigskip"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
              ///////////////
  	      foundcode = 1;
            }



	    // closer
            if ( foundcode == 0 )
	    if ( beamercode == 1 )
	    if ( contentcode == 1 )
	    if ( beamerlevel >= 1 )
	    if ( unilistemptyline >= 1 )
            {
	      printf ( " Found unilistemptyline (closer): beamer level %d \n", beamerlevel );
	      for ( fooi = 1 ; fooi <= beamerlevel ; fooi++)
	      {
                 foxy++;//
                 strncpy( slidebufferdata[foxy] , "\\end{itemize}" , PATH_MAX );
	      }

              //////////////////////////////////////////////
              slidebufferfoundsection = 0;
	      for ( fooi = 1 ; fooi <= foxy ; fooi++)
	      {
                   if ( strstr( slidebufferdata[ fooi ] , "\\frametitle" ) != 0 )
                   if ( slidebufferdata[ fooi ][0] != '%' ) 
                   {
                      printf( "a frametitle found.\n" );
                      slidebufferfoundsection = 1;
                   }
              }

              if ( strcmp( slidemysection , "" ) != 0 )
              {
                      fputs( "\n" , fp5 );
                      fputs( "\\section{"  , fp5 );
                      fputs( slidemysection , fp5 );
                      fputs( "}\n"  , fp5 );
              }
             
              ////////////////////////////////////////////////
	      printf ( " Print out foxy \n" );
	      for ( fooi = 1 ; fooi <= foxy ; fooi++)
	      {
                 fputs( slidebufferdata[ fooi ] , fp5 );

                 if ( slidebufferfig >= 1 )
                 if ( strcmp( slidebufferdata[ fooi ] , "\\begin{frame}" ) == 0 )
                 {
                      fputs( "\n" , fp5 );
                      if ( slidebufferfig == 1 )
                         fputs( "\\fitimage{"  , fp5 );
                      else if ( slidebufferfig == 2 )
                         fputs( "\\fitimageab{"  , fp5 );
                 }

                 if ( slidebufferfoundsection == 0 ) 
                 {
                      fputs(  "\n" , fp5 );
                      fputs(  "\\frametitle{\\thesection.~\\insertsection}"  , fp5 );
                      slidebufferfoundsection = 1; 
                 }
                 fputs( "\n" , fp5 );
	      } // end of loop


              /// add fig fitimage if indicated
              if ( slidebufferfig == 1 )
	      {
                foxy++;//
                strncpy( slidebufferdata[foxy] , "}{" , PATH_MAX );
                strncat( slidebufferdata[foxy] ,  slidebufferfigfile  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 ); 
                strncat( slidebufferdata[foxy] , "}["  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
                if ( slidebuffernot == 1 ) strncat( slidebufferdata[foxy] , slidebufferfignote  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
                strncat( slidebufferdata[foxy] , "]"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );

                fooi = foxy ; 
                fputs( slidebufferdata[ fooi ] , fp5 );
                fputs( "\n" , fp5 );
                slidebufferfig=0;
	      }
              else if ( slidebufferfig == 2 )
	      {
                foxy++;//
                strncpy( slidebufferdata[foxy] , "}{" , PATH_MAX );
                strncat( slidebufferdata[foxy] ,  slidebufferfigfile1  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 ); 
                strncat( slidebufferdata[foxy] , "}"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
                strncat( slidebufferdata[foxy] ,  "{"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 ); 
                strncat( slidebufferdata[foxy] ,  slidebufferfigfile2  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 ); 
                strncat( slidebufferdata[foxy] , "}["  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
                if ( slidebuffernot == 1 ) strncat( slidebufferdata[foxy] , slidebufferfignote  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );
                strncat( slidebufferdata[foxy] , "]"  , PATH_MAX - strlen( slidebufferdata[foxy]  ) -1 );

                fooi = foxy ; 
                fputs( slidebufferdata[ fooi ] , fp5 );
                fputs( "\n" , fp5 );
                slidebufferfig=0;
	      }

              /// close the frame
 	      fputs( "\\end{frame}\n" , fp5 );
 	      fputs( "\n" , fp5 );
 	      fputs( "\n" , fp5 );

              /// reset slide values
              foxy = 0;
              slidebufferfig=0;
              slidebuffernot=0;
              strncpy( slidemysection, "", PATH_MAX );

	      beamerlevel = 0;
  	      foundcode = 1;
            }
            //// debugger
	    if ( beamerlevel <= 0 ) beamerlevel = 0;
      }
     // end of beamer
     // end of beamer





            /////////////////////////////////////////////////////////////////
            if ( notercode == 1 ) 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == '=' ) 
            if ( fetchline[2] == ' ' ) 
            {
 	        fputs( "\\section{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 2+2, strlen( fetchline ))) , fp5 );
  	        fputs( "}\n", fp5 );
  	      foundcode = 1;
            }
            /////////////////////////////
            if ( notercode == 1 ) 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 's' ) 
            if ( fetchline[2] == 'e' ) 
            if ( fetchline[3] == 'c' ) 
            if ( fetchline[4] == 't' ) 
            if ( fetchline[5] == 'i' ) 
            if ( fetchline[6] == 'o' ) 
            if ( fetchline[7] == 'n' ) 
            if ( fetchline[8] == ' ' ) 
            {
 	        fputs( "\\section{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 8+2, strlen( fetchline ))) , fp5 );
  	        fputs( "}\n", fp5 );
  	      foundcode = 1;
            }





            /////////////////////////////
            //////// notercode
            if ( notercode == 1 ) 
            if ( foundcode == 0 ) // !note bla   , activated with !noter 
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'n' ) 
            if ( fetchline[2] == 'o' ) 
            if ( fetchline[3] == 't' ) 
            if ( fetchline[4] == 'e' ) 
            if ( fetchline[5] == ' ' ) 
            {
  	      fputs( "- ", fp5 );
 	      fputs( strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , fp5 );
  	      fputs( "\\\\", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }
            /////////////////////////////
            //////// notercode
            //////// notercode
            if ( notercode == 1 ) 
            if ( foundcode == 0 ) 
            if ( fetchline[0] == '\\' ) 
            if ( fetchline[1] == 'm' ) 
            if ( fetchline[2] == 'y' ) 
            if ( fetchline[3] == 's' ) 
            if ( fetchline[4] == 'e' ) 
            if ( fetchline[5] == 'c' ) 
            if ( fetchline[6] == 't' ) 
            if ( fetchline[7] == 'i' ) 
            if ( fetchline[8] == 'o' ) 
            if ( fetchline[9] == 'n' ) 
            if ( fetchline[10] == '{' ) 
            {
  	        fputs( "\\section{", fp5 );
 	        fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
  	        fputs( "}\n", fp5 );
  	        foundcode = 1;
            }
            /////////////////////////
            if ( notercode == 1 ) 
            if ( foundcode == 0 )
            {
  	      foundcode = 1;
            }
            //////// notercode
            //////// notercode
            /// anti note
            if ( notercode == 0 ) 
            if ( foundcode == 0 ) // !note bla
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'n' ) 
            if ( fetchline[2] == 'o' ) 
            if ( fetchline[3] == 't' ) 
            if ( fetchline[4] == 'e' ) 
            if ( fetchline[5] == ' ' ) 
            {
  	      foundcode = 1;
            }
     // end of noter
     // end of noter
     // end of noter
     // end of noter








            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            if ( foundcode == 0 )  // deprecated, but ok, that's too modern
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == '=' ) 
            if ( fetchline[2] == ' ' ) 
            {
              if ( markup_output_format == 2 )
              {
 	        fputs( "<h1>" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 2+2, strlen( fetchline ))) , fp5 );
  	        fputs( "</h1>\n", fp5 );
              }
              else
              {
 	        fputs( "\\section{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 2+2, strlen( fetchline ))) , fp5 );
  	        fputs( "}\n", fp5 );
              }
  	      foundcode = 1;
            }

            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            if ( foundcode == 0 ) // deprecated, but ok, that's too modern
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == '=' ) 
            if ( fetchline[2] == '=' ) 
            if ( fetchline[3] == ' ' ) 
            {
              if ( markup_output_format == 2 )
              {
 	        fputs( "<h2>" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 3+2, strlen( fetchline ))) , fp5 );
  	        fputs( "</h2>\n", fp5 );
              }
              else
              {
    	        fputs( "\\subsection{" , fp5 );
    	        fputs( strtrim( strcut( fetchline, 3+2, strlen( fetchline ))) , fp5 );
     	        fputs( "}\n", fp5 );
              }
  	      foundcode = 1;
            }


            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            if ( foundcode == 0 ) // deprecated, but ok, that's too modern
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == '=' ) 
            if ( fetchline[2] == '=' ) 
            if ( fetchline[3] == '=' ) 
            if ( fetchline[4] == ' ' ) 
            {
              if ( markup_output_format == 2 )
              {
 	        fputs( "<h3>" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , fp5 );
  	        fputs( "</h3>\n", fp5 );
              }
              else
              {
    	        fputs( "\\subsubsection{" , fp5 );
    	        fputs( strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , fp5 );
     	        fputs( "}\n", fp5 );
              }
  	      foundcode = 1;
            }














            ///////////////////////////////
            ///////////// regular !subsection 
            ///////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 's' )
            if ( fetchline[2] == 'u' )
            if ( fetchline[3] == 'b' )
            if ( fetchline[4] == 's' )
            if ( fetchline[5] == 'e' ) 
            if ( fetchline[6] == 'c' )
            if ( fetchline[7] == 't' )
            if ( fetchline[8] == 'i' )
            if ( fetchline[9] == 'o' )
            if ( fetchline[10] == 'n' )
            if ( fetchline[11] == ' ' )
            {
 	      fputs( "\\subsection{" , fp5 );
 	      fputs( strtrim( strcut( fetchline, 11+2, strlen(fetchline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }















            /////////////////////////////////////// set language
            /////////////////////////////////////// set language
            /////////////////////////////////////// set language
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( strcmp( strrlf( fetchline ) , "!:set lang=none" ) == 0 )
            {
                markup_language = 0;
  	        foundcode = 1;
            }
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( strcmp( strrlf( fetchline ) , "!:set lang=en" ) == 0 )
            {
                markup_language = 1;
  	        foundcode = 1;
            }
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( strcmp( strrlf( fetchline ) , "!:set lang=fr" ) == 0 )
            {
                markup_language = 2;
  	        foundcode = 1;
            }
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( strcmp( strrlf( fetchline ) , "!:set lang=de" ) == 0 )
            {
                markup_language = 3;
  	        foundcode = 1;
            }
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( strcmp( strrlf( fetchline ) , "!set item=1" ) == 0 )
            {
                markup_item = 1;
  	        foundcode = 1;
            }
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( strcmp( strrlf( fetchline ) , "!set item=2" ) == 0 )
            {
                markup_item = 2;
  	        foundcode = 1;
            }













            ///////////// !figab{myfigure.png} regular fig 
            ///////////// the regular figab to place figures side by side
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'f' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == 'a' )
            if ( fetchline[5] == 'b' )
            if ( fetchline[6] == '{' )
            {
  	        fputs( "\\begin{center}\n", fp5 );
  	        fputs( "\\begin{figure}\n", fp5 );
  	        fputs( "\\centering\n", fp5 );
  	        fputs( "\\includegraphics[width=0.48\\linewidth]{" , fp5 );
 	        fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
  	        fputs( "}\n", fp5 );
  	        fputs( "~\n", fp5 );
  	        fputs( "\\includegraphics[width=0.48\\linewidth]{" , fp5 );
 	        fputs( strdelimit( fetchline,  '{' ,'}' ,  2 ) , fp5 );
  	        fputs( "}\n", fp5 );
  	        fputs( "\\end{figure}\n", fp5 );
  	        fputs( "\\end{center}\n", fp5 );
  	        foundcode = 1;
            }



 



            ///////////// !fig{myfigure.png} regular fig 
            ///////////// the regular fig to place figures 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'f' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == '{' )
            {
	      //if ( strcount( fetchline, '}' ) >= 3 )
	      if ( strcount( fetchline, '}' ) >= 2 )
	      {
 	        fputs( "\\unifigplus{" , fp5 );
 	        fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
  	        fputs( "}{", fp5 );
	        fputs( strtxt2tex( strdelimit(  fetchline  ,  '{' ,'}' , 2 ) ) , fp5 );
  	        fputs( "}", fp5 );
  	        fputs( "{", fp5 );
 	        fputs( strdelimit( fetchline,  '{' ,'}' , 3 ) , fp5 );
		fputs( "}", fp5 );
		fputs( "{", fp5 ); //size
 	        fputs( strdelimit( fetchline,  '{' ,'}' , 4 ) , fp5 );
		fputs( "}", fp5 ); //size
		fputs( "{", fp5 ); //bottom note
 	        fputs( strdelimit( fetchline,  '{' ,'}' , 5 ) , fp5 );
		fputs( "}", fp5 ); //bottom note
  	        fputs( "\n", fp5 );
	      }
	      else
	      {
  	        fputs( "\\begin{center}\n", fp5 );
  	        fputs( "\\includegraphics[width=1.0\\textwidth]{" , fp5 );
 	        fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
  	        fputs( "}\n", fp5 );
  	        fputs( "\\end{center}\n", fp5 );
	      }
  	      foundcode = 1;
            }




            // !background{file.pdf}
            //fputs( "\\usepackage{wallpaper}\n", fp5 );
            //\CenterWallPaper{1}{background.pdf}
            if ( foundcode == 0 )
            if ( fetchline[0] ==  '!' ) 
            if ( fetchline[1] ==  'b' )
            if ( fetchline[2] ==  'a' )
            if ( fetchline[3] ==  'c' )
            if ( fetchline[4] ==  'k' ) 
            if ( fetchline[5] ==  'g' ) 
            if ( fetchline[6] ==  'r' )
            if ( fetchline[7] ==  'o' )
            if ( fetchline[8] ==  'u' )
            if ( fetchline[9] ==  'n' )
            if ( fetchline[10] == 'd' )
            if ( fetchline[11] == '{' )
            {
  	      fputs( "\\CenterWallPaper{1}{", fp5 );
 	      //fputs( strtrim( strcut( fetchline, 11+2, strlen(fetchline))) , fp5 );
 	      fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }





            ///////////// !fig fig.png Quick fig !! (workaround)
            ///////////// !fig myfigure.png  //this is a fast fig 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' ) 
            if ( fetchline[1] == 'f' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == ' ' )
            {
  	        fputs( "\\begin{center}\n", fp5 );
  	        fputs( "\\includegraphics[width=1.0\\textwidth]{" , fp5 );
 	        //fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
 	        //fputs(  strsplit(    strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
  	        fputs( "}\n", fp5 );
  	        fputs( "\\end{center}\n", fp5 );
  	      foundcode = 1;
            }









            /////////////////////////////
            /////////////////////////////
            ///////////////////////////// for items
            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == '-' )
            if ( fetchline[3] == ']' )
            if ( fetchline[4] == ' ' )
            {
 	        fputs( "\\begin{itemize}\n", fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
 	        fputs( "\\end{itemize}\n", fp5 );
  	        foundcode = 1;
            }


            /////////////////////////////
            /////////////////////////////
            ///////////////////////////// for items, tabbed
            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == 't' )
            if ( fetchline[3] == ']' )
            if ( fetchline[4] == ' ' )
            {
	      if ( numberinglevel == 1)  
	      {
       	        fputs( "\\item[ ] " , fp5 );
       	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
       	        fputs( "\n" , fp5 );
		numberinglevel = 1;
	      }
	      else if ( numberinglevel == 0)  
	      {
       	        fputs( "\\item[ ] " , fp5 );
       	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
       	        fputs( "\n" , fp5 );
		numberinglevel = 1;
	      }
 	      foundcode = 1;
            }











            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '>' )
            if ( fetchline[1] == ' ' )
            {
	      if ( itemlevel == 1)  
	      {
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	      }
	      else if ( itemlevel == 2)  
	      {
 	        fputs( "\\end{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 1;
	      }
	      else if ( itemlevel == 3)  
	      {
 	        fputs( "\\end{itemize}\n" , fp5 );
 	        fputs( "\\end{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 1;
	      }
	      else if ( itemlevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 1;
	      }
  	      foundcode = 1;
             }


            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '<' )
            if ( fetchline[2] == ' ' )
            {
	      if ( itemlevel == 0)  
	      {
 	        fputs( "\\begin{itemize}[leftmargin=0cm,label={}]\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 2+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 1;
	      }
  	      foundcode = 1;
             }

            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '>' )
            if ( fetchline[1] == '>' )
            if ( fetchline[2] == ' ' )
            {
	      if ( itemlevel == 0)  
	      {
 	        fputs( "\\begin{itemize}[leftmargin=0cm,label={}]\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 2+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 1;
	      }
  	      foundcode = 1;
             }



            /// new!
            if ( foundcode == 0 )
            if ( fetchline[0] == '*' )
            if ( fetchline[1] == ' ' )
            {
	      if ( itemlevel == 1)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
		itemlevel = 3;
	      }
	      else if ( itemlevel == 2)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
		itemlevel = 3;
	      }
	      else if ( itemlevel == 3)  
	      {
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 3;
	      }
	      else if ( itemlevel == 4)  
	      {
 	        fputs( "\\end{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 3;
	      }
	      else if ( itemlevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 3;
	      }
  	      foundcode = 1;
            }



            /// kinda for looking like tabulation for items 
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 't' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == ' ' )
            {
	      if ( itemlevel == 1)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item[ ] " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 3+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
		itemlevel = 2;
	      }
	      else if ( itemlevel == 2)  
	      {
 	        fputs( "\\item[ ] " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 3+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 2;
	      }
	      else if ( itemlevel == 3)  
	      {
 	        fputs( "\\end{itemize}\n" , fp5 );
 	        fputs( "\\item[ ] " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 3+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 2;
	      }
	      else if ( itemlevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item[ ] " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 3+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 2;
	      }
  	      foundcode = 1;
            }






            /// old and ok
            /// the most useful part
            if ( foundcode == 0 )
            if ( fetchline[0] == '-' )
            if ( fetchline[1] == ' ' )
            {
	      if ( itemlevel == 1)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
                if ( markup_item == 2 ) fputs( " (3 Pkt.)" , fp5 );
 	        fputs( "\n" , fp5 );
		itemlevel = 2;
	      }
	      else if ( itemlevel == 2)  
	      {
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
                if ( markup_item == 2 ) fputs( " (3 Pkt.)" , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 2;
	      }
	      else if ( itemlevel == 3)  
	      {
 	        fputs( "\\end{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 2;
	      }
	      else if ( itemlevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item " , fp5 );
 	        fputs( strtrim( strcut( fetchline, 1+2, strlen(fetchline))) , fp5 );
 	        fputs( "\n" , fp5 );
	        itemlevel = 2;
	      }
  	      foundcode = 1;
            }



	    // closer
            if ( foundcode == 0 )
	    if ( itemlevel >= 1 )
	    //if ( unilistemptyline >= 1 )
            {
	      for ( fooi = 1 ; fooi <= itemlevel ; fooi++)
	      {
	         fputs( "\\end{itemize}\n" , fp5 );
	      }
 	      //fputs( "\\end{frame}\n" , fp5 );
 	      fputs( "\n" , fp5 );
 	      fputs( "\n" , fp5 );
	      itemlevel = 0;
  	      foundcode = 1;
            }







            //////////////////////////////////
            //// !tex
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( fetchcmdline, "!tex" ) == 0 )
            {
              fputs( "\\documentclass[11pt]{article}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            } 













            ///////////////////////////// for questions with points
            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == 'q' )
            if ( fetchline[3] == 't' )  // for question topics
            if ( fetchline[4] == ']' )
            if ( fetchline[5] == ' ' )
            {
              fputs( "\\iexflechelf{{\\bfseries ", fp5 );
 	      fputs( strtrim( strcut( fetchline, 5+2, strlen(fetchline))) , fp5 );
              fputs( "}}\\\\", fp5 );
 	      fputs( "\n" , fp5 );
  	      numberinglevel = 1;
  	      foundcode = 1;
            }


            ///////////////////////////// for questions with points
            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == 'q' ) // used for english type of questions (single question list, with pts)
            if ( fetchline[3] == ']' )
            if ( fetchline[4] == ' ' )
            {
	      if ( numberinglevel == 1)  
	      {
 	        fputs( "\\item[{\\bfseries {\\arabic{unibullcounter}}}.)]{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
                if ( markup_language == 1 )      fputs( " (3 Points)}" , fp5 );
                else if ( markup_language == 2 ) fputs( " (3 Pts.)}" , fp5 );
                else if ( markup_language == 3 ) fputs( " (3 Pkt.)}" , fp5 );
                else if ( markup_language == 0 ) fputs( "}" , fp5 );
 	        fputs( "\n" , fp5 );
                fputs( "\\addtocounter{unibullcounter}{1}\n" , fp5 );
		numberinglevel = 1;
	      }
	      else if ( numberinglevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item[{\\bfseries {\\arabic{unibullcounter}}}.)]{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
                if ( markup_language == 1 )      fputs( " (3 Points)}" , fp5 );
                else if ( markup_language == 2 ) fputs( " (3 Pts.)}" , fp5 );
                else if ( markup_language == 3 ) fputs( " (3 Pkt.)}" , fp5 );
                else if ( markup_language == 0 ) fputs( "}" , fp5 );
 	        fputs( "\n" , fp5 );
                fputs( "\\addtocounter{unibullcounter}{1}\n" , fp5 );
		numberinglevel = 1;
	      }
  	      foundcode = 1;
            }




            ///////////////////////////// ![nu] clause
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == 'n' ) 
            if ( fetchline[3] == 'u' )
            if ( fetchline[4] == ']' )
            if ( fetchline[5] == ' ' )
	    {
	        if ( numberinglevel == 0) fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item[{\\bfseries " , fp5 );
                fooc = snprintf( fooccharo, 50 , "%d", mynumber );
 	        fputs( fooccharo , fp5 );
 	        fputs( ".}]{" , fp5 );
 	        fputs( strcut( fetchline, 5+2, strlen(fetchline)) , fp5 );
                fputs( "}" , fp5 );
 	        fputs( "\n" , fp5 );
                mynumber++;
		numberinglevel = 1;
  	        foundcode = 1;
            }





            ///////////////////////////// 
            /// free numbering question
            /// for exr !! (example: ...)
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == ']' )
            if ( fetchline[4] == ' ' )
            {
	      if ( numberinglevel == 1)  
	      {
 	        fputs( "\\item[{\\bfseries {\\arabic{unibullcounter}}}.)]{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
 	        fputs( "}\n" , fp5 );
                fputs( "\\addtocounter{unibullcounter}{1}\n" , fp5 );
		numberinglevel = 1;
	      }
	      else if ( numberinglevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item[{\\bfseries {\\arabic{unibullcounter}}}.)]{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
 	        fputs( "}\n" , fp5 );
 	        fputs( "\n" , fp5 );
                fputs( "\\addtocounter{unibullcounter}{1}\n" , fp5 );
		numberinglevel = 1;
	      }
  	      foundcode = 1;
            }






            /////////////////////////////
            /////////////////////////////
            /////////////////////////////
            // old default
            /////////////////////////////
            /////////////////////////////
            /////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '[' )
            if ( fetchline[2] == '#' )
            if ( fetchline[3] == ']' )
            if ( fetchline[4] == ' ' )
            {
	      if ( numberinglevel == 1)  
	      {
 	        fputs( "\\item[{\\arabic{unibullcounter}}.]{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
 	        fputs( "}\n" , fp5 );
                fputs( "\\addtocounter{unibullcounter}{1}\n" , fp5 );
		numberinglevel = 1;
	      }
	      else if ( numberinglevel == 0)  
	      {
 	        fputs( "\\begin{itemize}\n" , fp5 );
 	        fputs( "\\item[{\\arabic{unibullcounter}}.]{" , fp5 );
 	        fputs( strtrim( strcut( fetchline, 4+2, strlen(fetchline))) , fp5 );
 	        fputs( "}" , fp5 );
 	        fputs( "\n" , fp5 );
                fputs( "\\addtocounter{unibullcounter}{1}\n" , fp5 );
		numberinglevel = 1;
	      }
  	      foundcode = 1;
            }



            //// closer
            if ( foundcode == 0 )
	    if ( contentcode == 1 )
	    if ( numberinglevel >= 1 )
	    //if ( unilistemptyline >= 2 )  //numbering
	    if ( unilistemptyline >= 1 )  //numbering
            {
	      for ( fooi = 1 ; fooi <= numberinglevel ; fooi++)
	      {
	         fputs( "\\end{itemize}\n" , fp5 );
	      }
              //fputs( "\\setcounter{unibullcounter}{1}\n" , fp5 );
 	      fputs( "\n" , fp5 );
 	      fputs( "\n" , fp5 );
	      numberinglevel = 0;
  	      foundcode = 1;
            }
            //// debugger
	    if ( numberinglevel <= 0 ) numberinglevel = 0;
	    ///]]]








            if ( foundcode == 0 )  // deprecated, but ok, that's too modern
            if ( fetchcmdline[0] == '!' ) 
            if ( fetchcmdline[1] == 'p' ) 
            if ( fetchcmdline[2] == 'd' ) 
            if ( fetchcmdline[3] == 'f' ) 
            if ( fetchcmdline[4] == '{' ) 
            {
 	      fputs( "\\includepdf{" , fp5 );
              fputs( strdelimit( fetchcmdline,  '{' ,'}' ,  1 ) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }


            /// new mysection
            // (why !, because it can be into the standard 250 chars)  
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' ) 
	    if ( strcmp( strcut(fetchcmdline, 2, 9) , "section " ) == 0 )
            {
 	      fputs( "\\section{" , fp5 );
 	      fputs( strtrim( strcut( fetchcmdline, 8+2, strlen(fetchcmdline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }
            ///////////////////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' ) 
            if ( fetchcmdline[1] == '=' ) 
            if ( fetchcmdline[2] == ' ' ) 
            {
 	      fputs( "\\section{" , fp5 );
 	      fputs( strtrim( strcut( fetchcmdline, 2+2, strlen(fetchcmdline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }



            ///////////////////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' ) 
	    if ( strcmp( strcut(fetchcmdline, 2, 9+3) , "!subsection " ) == 0 )
            {
 	      fputs( "\\subsection{" , fp5 );
 	      fputs( strtrim( strcut( fetchcmdline, 8+3+2, strlen(fetchcmdline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }

            ///////////////////////////////
            if ( foundcode == 0 )
            if ( ( fetchcmdline[0] == '!' ) || ( fetchcmdline[0] == '$' ))
	    if ( strcmp( strcut(fetchcmdline, 2, 5+3) , "subsec " ) == 0 )
            {
 	      fputs( "\\subsection{" , fp5 );
 	      fputs( strtrim( strcut( fetchcmdline, 4+3+2, strlen(fetchcmdline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }



	    /////////////////
            if ( foundcode == 0 )
            if ( ( fetchcmdline[0] == '!' ) || ( fetchcmdline[0] == '$' ))
	    if ( strcmp( strcut(fetchcmdline, 2, 9+3+3) , "!subsubsection " ) == 0 )
            {
 	      fputs( "\\subsubsection{" , fp5 );
 	      fputs( strtrim( strcut( fetchcmdline, 8+3+3+2, strlen(fetchcmdline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }
	    ////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( strcut(fetchcmdline, 1, 8) , "!chapter" ) == 0 )
            {
 	      fputs( "\\chapter{" , fp5 );
 	      fputs( strtrim( strcut( fetchcmdline, 8+2, strlen(fetchcmdline))) , fp5 );
  	      fputs( "}\n", fp5 );
  	      foundcode = 1;
            }




	    /////////////////
            if ( foundcode == 0 ) // !- item into script
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == '-' )
            if ( fetchline[2] == ' ' )
            {
 	      fputs( "- " , fp5 );
 	      fputs( strcut( fetchline, 2+2, strlen(fetchline)) , fp5 );
  	      fputs( "\\\\", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }
	    /////////////////
            if ( foundcode == 0 ) // !- item into script
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == '-' )
            if ( fetchcmdline[2] == ' ' )
            {
 	      fputs( "- " , fp5 );
 	      fputs( strcut( fetchcmdline, 2+2, strlen(fetchcmdline)) , fp5 );
  	      fputs( "\\\\", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }







	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 ) // !blue
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'b' )
            if ( fetchcmdline[2] == 'l' )
            if ( fetchcmdline[3] == 'u' )
            if ( fetchcmdline[4] == 'e' )
            if ( fetchcmdline[5] == ' ' )
            {
 	      fputs( "{\\color{blue}" , fp5 );
 	      fputs( strcut( fetchcmdline, 5+2, strlen(fetchcmdline)) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }

	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 ) // !red
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'r' )
            if ( fetchcmdline[2] == 'e' )
            if ( fetchcmdline[3] == 'd' )
            if ( fetchcmdline[4] == ' ' )
            {
 	      fputs( "{\\color{red}" , fp5 );
 	      fputs( strcut( fetchcmdline, 4+2, strlen(fetchcmdline)) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }

	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 ) // !red
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'g' )
            if ( fetchcmdline[2] == 'r' )
            if ( fetchcmdline[3] == 'e' )
            if ( fetchcmdline[4] == 'e' )
            if ( fetchcmdline[5] == 'n' )
            if ( fetchcmdline[6] == ' ' )
            {
 	      fputs( "{\\color{green}" , fp5 );
 	      fputs( strcut( fetchcmdline, 6+2, strlen(fetchcmdline)) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }






	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 ) // !linefeed (small space) (better than medskip)
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'l' )
            if ( fetchline[2] == 'i' )
            if ( fetchline[3] == 'n' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == 'f' )
            if ( fetchline[6] == 'e' )
            if ( fetchline[7] == 'e' )
            if ( fetchline[8] == 'd' )
            {
 	      fputs( "\\vskip " , fp5 );
  	      fputs( "0.05in", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }





	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 ) // !bold, without line feed of tex !
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'b' )
            if ( fetchcmdline[2] == 'o' )
            if ( fetchcmdline[3] == 'l' )
            if ( fetchcmdline[4] == 'd' )
            if ( fetchcmdline[5] == ' ' )
            {
 	      fputs( "{\\bfseries " , fp5 );
 	      fputs( strcut( fetchcmdline, 5+2, strlen(fetchcmdline)) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }






	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'b' )
            if ( fetchcmdline[2] == 'c' )
            if ( fetchcmdline[3] == 'o' )
            if ( fetchcmdline[4] == 'd' )
            if ( fetchcmdline[5] == 'e' )
            {
 	      fputs( "\\begin{verbatim}\n" , fp5 );
  	      foundcode = 1;
            }
	    /////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
            if ( fetchcmdline[1] == 'e' )
            if ( fetchcmdline[2] == 'c' )
            if ( fetchcmdline[3] == 'o' )
            if ( fetchcmdline[4] == 'd' )
            if ( fetchcmdline[5] == 'e' )
            {
 	      fputs( "\\end{verbatim}\n" , fp5 );
  	      foundcode = 1;
            } 




	    /////////////////
	    /////////////////
	    /////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 't' )
            if ( fetchline[2] == 'o' )
            if ( fetchline[3] == 'r' )
            {
                 fputs( "\\bibliography{mybib}{}\n", fp5 );
                 fputs( "\\bibliographystyle{ieeetr}\n", fp5 );
  	         foundcode = 1;
            } 





            ////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'r' ) 
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == 'v' ) 
            if ( fetchline[4] == ' ' ) 
            ///////// new! for review !rev my-review
            {
       	         fputs( "\\textcolor{red}{\\hl{" , fp5 );
       	         fputs( strcut( fetchline, 4+2, strlen(fetchline)) , fp5 );
        	 fputs( "}}", fp5 );
        	 fputs( "\n", fp5 );
  	         foundcode = 1;
            }
            ///////// new! for review !r my-review
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'r' )
            if ( fetchline[2] == ' ' )
            {
       	         fputs( "\\textcolor{red}{\\hl{" , fp5 );
       	         fputs( strcut( fetchline, 2+2, strlen(fetchline)) , fp5 );
        	 fputs( "}}", fp5 );
        	 fputs( "\n", fp5 );
  	         foundcode = 1;
            }






	    /////////////////
            /// for easy reviewer work
            ////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '|' )
            if ( fetchcmdline[1] == ' ' ) // <- this help to have nice code
            {
 	      fputs( strtxt2tex(  strcut( fetchcmdline, 1-1+2, strlen(fetchcmdline))) , fp5 );
              if ( option_strtxt2tex_linefeed == 1 )
              {
  	         fputs( "\\", fp5 );
  	         fputs( "\\", fp5 );
              }
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }





	    /////////////////
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' )
	    if ( strcmp( fetchcmdline, "!bigskip" ) == 0 )
            {
	      //contentcode = 1;  <-- to check
 	      fputs( "\\bigskip" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }




            //// !maketitle
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' ) 
	    if ( strcmp( fetchcmdline, "!maketitle" ) == 0 ) //here begin
            {
 	      fputs( "\\maketitle" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }




            //// !clr
            if ( foundcode == 0 )
            if ( fetchcmdline[0] == '!' ) 
	    if ( strcmp( fetchcmdline, "!clr" ) == 0 ) //here begin
            {
 	      fputs( "\\clearpage" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }
            //// $clr  <-- to be remove in some years
            if ( foundcode == 0 )
            if ( fetchline[0] == '$' ) 
	    if ( strcmp( fetchline , "$clr" ) == 0 )  //here begin
            {
 	      fputs( "\\clearpage" , fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
            }











            if ( foundcode == 0 ) // !gpath{}
            if (
            (( fetchline[0] ==  '!' ) && ( fetchline[1] == 'g' ) && ( fetchline[2] == 'p' ) && ( fetchline[3] == 'a' ) && ( fetchline[4] == 't' ) && ( fetchline[5] == 'h' ) && ( fetchline[6] == '{' ))

            || ( ( fetchline[0] ==  '!' ) && ( fetchline[1] == 'g' ) && ( fetchline[2] == 'f' ) && ( fetchline[3] == 'x' ) && ( fetchline[4] == 'p' ) && ( fetchline[5] == 'a' )  && ( fetchline[6] == 't' ) && ( fetchline[7] == 'h' )  && ( fetchline[8] == '{' ))
            )
            {
	      char fileinputsrc[PATH_MAX];
	      strncpy( fileinputsrc, "", PATH_MAX );
              strncat( fileinputsrc , strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
	      if ( fileinputsrc[0] == '~' )
	      {
	         strncpy( fileinputsrc, "", PATH_MAX );
                 strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
                 strncat( fileinputsrc , strdelimit( fetchline,  '~' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
	      }
                
              if ( fileinputsrc[ strlen( fileinputsrc) -1 ] != '/' )
              {
                printf( "graphicspath: PC must add / for tailing\n" );
                strncat( fileinputsrc , "/" , PATH_MAX - strlen( fileinputsrc ) -1 );
              }
              fputs( "\\graphicspath{{", fp5 );
  	      fputs( fileinputsrc  , fp5 );
  	      fputs( "}}", fp5 );
  	      fputs( "\n", fp5 );

              strncpy( mygraphicspath, fileinputsrc , PATH_MAX );
  	      foundcode = 1;
            }





            if ( foundcode == 0 ) // !ipath{}
            if (( fetchline[0] ==  '!' ) && ( fetchline[1] == 'i' ) && ( fetchline[2] == 'p' ) && ( fetchline[3] == 'a' ) && ( fetchline[4] == 't' ) && ( fetchline[5] == 'h' ) && ( fetchline[6] == '{' ))

            { 
	      char fileinputsrc[PATH_MAX];
	      strncpy( fileinputsrc, "", PATH_MAX );
              strncat( fileinputsrc , strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
	      if ( fileinputsrc[0] == '~' )
	      {
	         strncpy( fileinputsrc, "", PATH_MAX );
                 strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
                 strncat( fileinputsrc , strdelimit( fetchline,  '~' ,'}' ,  1 ) , PATH_MAX - strlen( fileinputsrc ) -1 );
	      }
              if ( fileinputsrc[ strlen( fileinputsrc) -1 ] != '/' )
              {
                printf( "> path: PC must add / for tailing\n" );
                strncat( fileinputsrc , "/" , PATH_MAX - strlen( fileinputsrc ) -1 );
              }
              strncpy( myinputspath, fileinputsrc , PATH_MAX );
              printf( "> SET IPATH: %s\n", myinputspath );
  	      foundcode = 1;
            }
















        //////////////////////////////////////////////
	/// always working
        //////////////////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'm' )
            if ( fetchline[2] == 's' )
            if ( fetchline[3] == 'g' )
            if ( fetchline[4] == '{' )
            {
	      // !msg   
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
 	      strncpy( usertextfieldtwo, strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      if ( strcmp( usertextfieldtwo, "0" ) != 0 )
	        printf( "<USER MSG: %s>\n", usertextfieldone );
  	      foundcode = 1;
            }







        //////////////////////////////////////////////
            if ( foundcode == 0 )
	    if ( option_system_call == 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == 'x' )
            if ( fetchline[4] == '{' )
            {
	      // !iex for texiex     (it will convert an iex to tex, and create its tex) 
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
 	      strncpy( usertextfieldtwo, strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      if ( strcmp( usertextfieldtwo, "0" ) != 0 )
	      {
                 strncpy( wgetcmd, "",  PATH_MAX );
                 strncat( wgetcmd , " texiex  " , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "  \""  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  usertextfieldone  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "\""  , PATH_MAX - strlen( wgetcmd ) -1 );
   	         printf( " texiex : %s\n" , wgetcmd );
	         // secured or unsecured??
                 if ( option_system_call == 1 )
		    system( wgetcmd );
	      }
  	      foundcode = 1;
            }




        //////////////////////////////////////////////
            if ( foundcode == 0 )
	    if ( option_system_call == 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'x' )
            if ( fetchline[2] == 'm' )
            if ( fetchline[3] == 's' )
            if ( fetchline[4] == 'g' )
            if ( fetchline[5] == '{' )
            {
	      // !xmsg   
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
 	      strncpy( usertextfieldtwo, strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      if ( strcmp( usertextfieldtwo, "0" ) != 0 )
	      {
                 strncpy( wgetcmd, "",  PATH_MAX );
                 strncat( wgetcmd , " xmsg  " , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "  \""  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  usertextfieldone  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "\""  , PATH_MAX - strlen( wgetcmd ) -1 );
   	         printf( " xmsg : %s\n" , wgetcmd );
	         // secured or unsecured??
                 if ( option_system_call == 1 )
		    system( wgetcmd );
	      }
  	      foundcode = 1;
            }





        //////////////////////////////////////////////
            if ( foundcode == 0 )
	    if ( option_system_call == 1 )
            if ( fetchline[0] == '!' )
            if ( fetchline[1] == 'w' )
            if ( fetchline[2] == 'g' )
            if ( fetchline[3] == 'e' )
            if ( fetchline[4] == 't' )
            if ( fetchline[5] == '{' )
            {
	      // !wget
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
 	      strncpy( usertextfieldtwo, strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      if ( strcmp( usertextfieldtwo, "" ) != 0 )
	      if ( fexist( usertextfieldtwo ) == 0 )
	      {
                 strncpy( wgetcmd, "",  PATH_MAX );
                 strncat( wgetcmd , " wget " , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "  \""  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  usertextfieldone  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "\""  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd , " -O "  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "  \""  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  usertextfieldtwo  , PATH_MAX - strlen( wgetcmd ) -1 );
                 strncat( wgetcmd ,  "\" "  , PATH_MAX - strlen( wgetcmd ) -1 );
   	         printf( " wgetcmd: %s\n" , wgetcmd );
	         // secured or unsecured??
                 if ( option_system_call == 1 )
   	         system( wgetcmd );
	      }
  	      foundcode = 1;
            }



        //////////////////////////////////////////////
            if ( foundcode == 0 )
	    if ( option_system_call == 1 )
            if ( ( ( fetchline[0] == '!' )
            && ( fetchline[1] == 'd' )
            && ( fetchline[2] == 'i' )
            && ( fetchline[3] == 'r' )
            && ( fetchline[4] == 'f' )
            && ( fetchline[5] == 'i' )
            && ( fetchline[6] == 'g' )
            && ( fetchline[7] == '{' ))
            ||
            ( ( fetchline[0] == '!' )   // figdir if you want to
            && ( fetchline[1] == 'f' )
            && ( fetchline[2] == 'i' )
            && ( fetchline[3] == 'g' )
            && ( fetchline[4] == 'd' )
            && ( fetchline[5] == 'i' )
            && ( fetchline[6] == 'r' )
            && ( fetchline[7] == '{' ))
            )
            {
   	      printf( "EXTCMD: dirfig\n" );
	      // !dirfig{directory/}{1}  to active or not
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
 	      strncpy( usertextfieldtwo, strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      if ( strcmp( usertextfieldtwo, "0" ) != 0 )
	      if ( fexist( usertextfieldone ) == 2 )
	      {
   	         printf( " dirfig found directory: %s \n", usertextfieldone );
                 strncpy( extcmd, "",  PATH_MAX );
                 strncat( extcmd , " dirfig " , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "  \""  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  usertextfieldone  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "\""  , PATH_MAX - strlen( extcmd ) -1 );
   	         printf( " ndirfig: %s\n" , extcmd );
	         // secured or unsecured??
                 if ( option_system_call == 1 ){
   	           printf( "CMD:%s\n", extcmd );
   	           system( extcmd ); }
	      }
  	      foundcode = 1;
            }







        //////////////////////////////////////////////
            if ( foundcode == 0 ) // xfig
            if ( ( ( fetchline[0] == '!' )
            && ( fetchline[1] == 'x' )
            && ( fetchline[2] == 'f' )
            && ( fetchline[3] == 'i' )
            && ( fetchline[4] == 'g' )
            && ( fetchline[5] == '{' ))
            )
            {
   	      printf( "EXTCMD: xfig\n" );
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
 	      //strncpy( usertextfieldtwo, strdelimit( fetchline,  '{' ,'}' ,  2 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      if ( fexist( usertextfieldone ) == 1 )
	      {
                 strncpy( usertextfieleps , fbasenoext( usertextfieldone ) , PATH_MAX );
                 strncat( usertextfieleps , ".eps" , PATH_MAX - strlen( usertextfieleps ) -1 );
   	         printf( " xfig found file: %s \n", usertextfieldone );
                 strncpy( extcmd, "",  PATH_MAX );
                 strncat( extcmd , " fig2dev -L eps " , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "  \""  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  usertextfieldone  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "\""  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "  \""  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  usertextfieleps  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "\""  , PATH_MAX - strlen( extcmd ) -1 );
   	         printf( " xfig: %s\n" , extcmd );
                 {
   	           printf( "CMD:%s\n", extcmd );
   	           system( extcmd ); 
                 }
                 if ( fexist( usertextfieleps ) == 1 )
                 {
         	        fputs( "\\begin{center}\n", fp5 );
         	        fputs( "\\includegraphics[width=1.0\\textwidth]{" , fp5 );
        	        fputs( usertextfieleps , fp5 );
         	        fputs( "}\n", fp5 );
         	        fputs( "\\end{center}\n", fp5 );
                 }
	      }
  	      foundcode = 1;
            }







  /*
        //////////////////////////////////////////////
        // pstoedit  -f fig file.eps  > file.fig
            if ( foundcode == 0 )  // eps2xfig from directory ~/pool/figs/ to local directory
            if ( ( ( fetchline[0] == '!' )
            && ( fetchline[1] == 'e' )
            && ( fetchline[2] == 'p' )
            && ( fetchline[3] == 's' )
            && ( fetchline[4] == '2' )
            && ( fetchline[5] == 'f' )
            && ( fetchline[6] == 'i' )
            && ( fetchline[7] == 'g' )
            && ( fetchline[8] == '{' ))
            )
            {
   	      printf( "EXTCMD: eps2fig script from pool to local dir \n" );
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      //if ( fexist( usertextfieldone ) == 1 )  // to be updated
	      {
                 strncpy( usertextfieleps , fbasenoext( usertextfieldone ) , PATH_MAX );
                 strncat( usertextfieleps , ".fig" , PATH_MAX - strlen( usertextfieleps ) -1 );  // target
   	         printf( " pstoedit found file: %s \n", usertextfieldone );
                 strncpy( extcmd, "",  PATH_MAX );
                 strncat( extcmd , " pstoedit -f fig  " , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "  ~/pool/figs/\""  , PATH_MAX - strlen( extcmd ) -1 );  // to be updated
                 strncat( extcmd ,  usertextfieldone  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "\""  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "  \""  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  usertextfieleps  , PATH_MAX - strlen( extcmd ) -1 );
                 strncat( extcmd ,  "\""  , PATH_MAX - strlen( extcmd ) -1 );
   	         printf( "CMD:%s\n", extcmd );
   	         system( extcmd ); 
	      }
  	      foundcode = 1;
            }
    */



        //////////////////////////////////////////////
        // fetch from ~/pool/figs  // !fetch 
        //////////////////////////////////////////////
            if ( foundcode == 0 )  
            if ( ( ( fetchline[0] == '!' )
            && ( fetchline[1] == 'f' )
            && ( fetchline[2] == 'e' )
            && ( fetchline[3] == 't' )
            && ( fetchline[4] == 'c' )
            && ( fetchline[5] == 'h' )
            && ( fetchline[6] == '{' ))
            )
            {
   	      printf( "Int cmd: fetch with ncp script for image from pool to local dir \n" );
 	      strncpy( usertextfieldone, strdelimit( fetchline,  '{' ,'}' ,  1 ) , PATH_MAX );
   	      printf( "  => file: %s\n", usertextfieldone ); 
	      if ( strcmp( usertextfieldone, "" ) != 0 )
	      {
                  strncpy( usertextfieleps , fbasename( usertextfieldone ) , PATH_MAX );
                  //strncpy( usertextfieleps , fbasenoext( usertextfieldone ) , PATH_MAX );
                  //strncat( usertextfieleps , ".fig" , PATH_MAX - strlen( usertextfieleps ) -1 );  // target
    	          char filencp[PATH_MAX];
    	          strncpy( filencp, "", PATH_MAX );
                  strncat( filencp , getenv( "HOME" ) , PATH_MAX - strlen( filencp ) -1 );
                  strncat( filencp , "/pool/figs/" , PATH_MAX - strlen( filencp ) -1 );
                  strncat( filencp ,  usertextfieldone  , PATH_MAX - strlen( filencp ) -1 );
                  printf( " [ncp] dest:%s <= src:%s \n", usertextfieleps, filencp );  
                  if ( fexist( filencp ) == 1 )
                  if ( fexist( usertextfieleps ) != 2 )
                  {
                    ncp( usertextfieleps, filencp ); 
                  }
                  else 
                  {
                    printf( " file not found: %s \n", filencp ); 
                  }
	      }
  	      foundcode = 1;
            }




            // !fin !fin 
	    if ( foundcode == 0 )
	    {
	        if ( beginitemize == 1 )
		{
		  fputs( "\\iexitemend\n" , fp5 ); 
		  fputs( "\n" , fp5 ); 
		}
 	        fputs( fetchline , fp5 );
  	        fputs( "\n", fp5 );
	        beginitemize = 0;
            }

	 }
     }
     fclose( fp5 );
     fclose( fp6 );
   }
}










///////////////////////////////////
int question_continue()
{
	    char c;
	    int foo;
	    printf("Do you want to continue (y/n)? ");
	    scanf(" %c",&c); 
	    c = toupper(c);
	    if   ( ( c == 'Y' ) ||    ( c == 'y' ) )
	    {
	       printf( "Yes\n");
	       foo = 1;
	    }
	    else if ( c == '1' ) 
	    {
	       printf( "Yes\n");
	       foo = 1;
	    }
	    else  
	    {
	      printf( "No\n");
	      foo = 0;
	    }
	    return foo; 
}



void show_unimark_logo()
{
         printf("================= \n");
         printf("|||- UNIMARK -||| \n");
         printf("================= \n");
}







////////////////////////////////
/// check for enddoc 
////////////////////////////////
int cat_fdinfo( char *filein )
{
  char fetchlinetmp[4096];
  char fetchline[4096];
  char buf[4096];
  char ptr[4096];
  ssize_t nread;
  int i,j,k;
  i = 0 ; j = 0;
  int beginend = 0;
    FILE *fp6;
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          fgets(fetchlinetmp, 4096, fp6); 
          strncpy( fetchline, "" , 4096 );
          for( i = 0 ; ( i <= strlen( fetchlinetmp ) ); i++ )
            if ( fetchlinetmp[ i ] != '\n' )
              fetchline[i]=fetchlinetmp[i];

         if ( !feof(fp6) )
         {
              if ( strcmp( fetchline , "!enddoc" ) == 0 )
                   beginend++;
              else if ( strcmp( fetchline , "\\end{document}" ) == 0 ) 
                   beginend++;
	 }
     }
     fclose( fp6 );

  printf( "Info Begin+End: %d \n" , beginend );
  return beginend;
}











//////////////////////////////
 void npdflatex( char *thefile ) 
 {
       char tfileout[PATH_MAX];
       strncpy( tfileout ,   fbasenoext( thefile ) , PATH_MAX );
       strncat( tfileout , ".tex" , PATH_MAX - strlen( tfileout ) -1 );
       nrunwith( " unibeam ", thefile );
       nrunwith( " pdflatex -shell-escape ", tfileout );
 }

//////////////////////////////
 void ntexmake( char *thefile , int ntexmakemode )
 {
       ///////////////////////////
       /*
       unibeam article.mrk article.tex 
       pdflatex article ;
       bibtex article 
       pdflatex article 
       pdflatex article 
       mupdf article.pdf   */
       //strncpy( theout, strtimestamp() , PATH_MAX );
       //char theout[PATH_MAX];
       ///////////////////////////
       char targetfile[PATH_MAX];
       char tfilein[PATH_MAX];
       char tfileout[PATH_MAX];
       char cmdi[PATH_MAX];
         strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
         strncpy( tfileout,   fbasenoext( thefile ) , PATH_MAX );
         strncat( tfileout , ".pdf" , PATH_MAX - strlen( tfileout ) -1 );
         if ( ntexmakemode == 1 )       nrunwith( " unibeam ",  thefile );
         else if ( ntexmakemode == 2 )  nrunwith( " ./unibeam ",  thefile );
         nrunwith( " pdflatex ", targetfile );
         nrunwith( " bibtex ",   targetfile );
         nrunwith( " pdflatex ", targetfile );
         nrunwith( " pdflatex ", targetfile );
         nrunwith( " mupdf ",    tfileout );
 }











////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
    char targetfile[PATH_MAX];
    strncpy( slidemysection, "", PATH_MAX );
    strncpy( mygraphicspath, "" , PATH_MAX );
    strncpy( myinputspath , "" , PATH_MAX );
    FILE *fpout;
    int i ; 

    //////////////////////////////////////////
    if ( argc >= 2)
    if ( strcmp( argv[ 1 ] , "--debug"  ) == 0  ) 
    if ( strcmp( argv[ 2 ] , "hello"  ) == 0  ) 
    {
	  printf( "(Unibeam Command For Dev - Debug.)\n" );
	  printf( "Hello World\n" );
          return 0; 
    }



    ///////////////////////////////////////////
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    //system( " unibeam article.mrk article.tex ; pdflatex article ; bibtex article ; pdflatex article ; pdflatex article ; mupdf article.pdf " );
    // you may visit for examples: https://github.com/spartrekus/Unibeam-Article-Example
    if ( argc >= 2)
    if ( strcmp( argv[ 1 ] , "--make"  ) == 0  ) 
    {
          for( i = 2 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
            if ( fexist( argv[ i ] ) == 1 ) ntexmake( argv[ i ] , 1 );
          }
          return 0;
    }
    //////////////////////////////////////////
    if ( argc >= 2)
    if ( strcmp( argv[ 1 ] , "--local-make"  ) == 0  ) 
    {
          for( i = 2 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
            if ( fexist( argv[ i ] ) == 1 ) ntexmake( argv[ i ] , 2 );
          }
          return 0;
    }



    if ( argc >= 2)
    if ( strcmp( argv[ 1 ] , "--pdflatex"  ) == 0  ) 
    {
          for( i = 2 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
            if ( fexist( argv[ i ] ) == 1 ) 
                npdflatex( argv[ i ] );
          }
          return 0;
    }


   ///////////////////////////////////////////
   ///////////////////////////////////////////
    if ( argc == 4)
      if ( strcmp( argv[ 1 ] , "--new"  ) == 0  )
      if ( strcmp( argv[ 2 ] , "beamer"  ) == 0  ) 
      if ( strcmp( argv[ 3 ] , ""  ) != 0  ) 
      {
          printf( "Create example beamer\n");
          fpout = fopen( argv[3] , "ab+");
            fputs( "#include{beamer.mrk}\n", fpout );
            fputs( "!gpath{figs}\n", fpout );
            fputs( "!beamer\n", fpout );
            fputs( "!begin\n", fpout );
            fputs( "!clr\n", fpout );
            fputs( "!= Section\n", fpout );
            fputs( "> Header\n", fpout );
            fputs( "- this is an example\n", fpout );
            fputs( "// !fig{pic.png}\n", fpout );
            fputs( "\n", fpout );
          fclose( fpout );
          return 0;
      } 






   ///////////////////////////////////////////
   ///////////////////////////////////////////
    if ( argc == 3)
      if (( strcmp( argv[ 1 ] , "--create"  ) == 0  ) 
      || ( strcmp( argv[ 1 ] , "--new"  ) == 0  ))
      if ( ( strcmp( argv[ 2 ] , "beamer"  ) == 0  ) 
      || ( strcmp( argv[ 2 ] , "slides"  ) == 0  ) )
      {
          printf( "Create example beamer\n");
          fpout = fopen( "example.bmr" , "ab+");
            fputs( "#include{beamer.mrk}\n", fpout );
            fputs( "//!gpath{figs}\n", fpout );
            fputs( "!beamer\n", fpout );
            fputs( "!begin\n", fpout );
            fputs( "!section Section\n", fpout );
            fputs( "!clr\n", fpout );
            fputs( "> Header\n", fpout );
            fputs( "- this is an example\n", fpout );
            fputs( "// !fig{pic.png}\n", fpout );
            fputs( "\n", fpout );
          fclose( fpout );
          return 0;
      } 




   ///////////////////////////////////////////
   ///////////////////////////////////////////
   ///////////////////////////////////////////
   // EXAMPLE OF Universal UNIMARK DOCUMENT
   ///////////////////////////////////////////
   ///////////////////////////////////////////
   ///////////////////////////////////////////
    if ( argc == 2)
      if ( ( strcmp( argv[ 1 ] , "--create"  ) == 0  ) 
      || ( strcmp( argv[ 1 ] , "--new"  ) == 0  )
      || ( strcmp( argv[ 1 ] , "-new"  ) == 0  )
      || ( strcmp( argv[ 1 ] , "--example"  ) == 0  )
      )
      {
          printf( "Create example\n");
          fpout = fopen( "example.mrk" , "ab+");
            fputs( "!tex\n", fpout );
            fputs( "!gfx\n", fpout );
            fputs( "//!gpath{figs}\n", fpout );
            fputs( "!ipath{~/pool/mrkdir/}\n", fpout );
            fputs( "// \\usepackage[margin=0.5cm]{geometry}\n", fpout );
            fputs( "// \\pagestyle{headings}\n", fpout );
            fputs( "!begin\n", fpout );
            fputs( "!bold Example \n", fpout );
            fputs( "// \\begin{center}\n", fpout );
            fputs( "// \\includegraphics[width=1.0\\textwidth]{pic.png}\n", fpout );
            fputs( "// \\end{center}\n", fpout );
          fclose( fpout );
          return 0;
      } 




    ////////////////////////////////////////////////////////
    //// this is a test for developers
    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( strcmp( argv[ 1 ] , "filename.tst"  ) == 0  ) 
      {
          strncpy( targetfile, fbasenoext( argv[ 1 ] ) , PATH_MAX );
          strncat( targetfile , ".tex" , PATH_MAX - strlen( targetfile ) -1 );
          printf( "checker <%s> \n", targetfile );
          return 0;
      } 
    
    ////////////////////////////////////////////////////////
    //// this is a test for developers
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "--fdinfo" ) ==  0 ) 
      {
         cat_fdinfo( argv[ 2 ] );
         return 0;
      }





    ////////////////////////////////////////////////////////
    /// rescue and debugging function
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "--cat" ) ==  0 ) 
      if ( fexist( argv[2] )  == 1 )
      {
         ncat_static( argv[ 2 ] );
         return 0;
      }




    char cwd[PATH_MAX];
    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( ( strcmp( argv[1] , "--readme" ) ==  0 ) 
    || ( strcmp( argv[1] , "--help" ) ==  0 ) 
    || ( strcmp( argv[1] , "-help" ) ==  0 ) )
    {
        
	 show_unimark_logo();
         return 0;
    }








    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    printf("================= \n");
    printf("|||- UNIMARK -||| \n");
    printf("================= \n");
    printf("- An Universal Markup Language - \n");
    printf("- Cross-Platform, using plain C language - \n");
    printf("- Author: GITHUB Spartrekus - \n");
    printf("- LICENCE : GNU - \n");


    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 3)
    {
     printf("- Please do not modify unimark too much, since \n" );
     printf("- it is intentionally made to be universal, largely portable, and minimalist.\n" );
     printf("- Choosen Style Output : TEX -\n" );
     printf("- (Currently there is only TeX available)-\n" );
     printf("- (Future: HTML to be available)-\n" );
    }





    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( fexist( argv[1] ) == 1 )
      {
          printf( "STEP:Catinfo \n" );
          int therebeginend = cat_fdinfo( argv[ 1 ] );
          printf( "STEP: info \n" );
          printf("  >SRC: %s => TRG: %s \n", argv[1] , argv[2] );
          printf( "STEP: filenew \n" );
          filenew( argv[2] );
          printf( "STEP: unimark \n" );
          nfileunimark( argv[2] , argv[1] );
          printf( "STEP: fileappend \n" );
          strncpy( targetfile,  argv[ 2 ]  , PATH_MAX );
          printf( "Target: %s\n" , targetfile );

          if ( markup_output_format == 1 ) 
            if ( therebeginend == 0 )  
            {
               printf( "File Append: End (TeX) \n" );
               fileappendend( targetfile );
            }
          printf( "-End of Unimark/Unibearm (OK).-\n" );
          printf( "===============================\n" );
          printf( "\n" );
          return 0;
      }





    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( fexist( argv[1] ) == 1 )
      {
          strncpy( targetfile, fbasenoext( argv[ 1 ] ) , PATH_MAX );
          strncat( targetfile , ".tex" , PATH_MAX - strlen( targetfile ) -1 );
          printf( "Target: %s\n" , targetfile );
          int therebeginend = cat_fdinfo( argv[ 1 ] );
          printf("  >SRC: %s => TRG: %s \n", argv[1] , targetfile  );
          filenew( targetfile );
          nfileunimark( targetfile , argv[1] );

          if ( markup_output_format == 1 ) 
            if ( therebeginend == 0 )  
            {
               printf( "File Append: End (TeX) \n" );
               fileappendend( targetfile );
            }
          printf( "-End of Unimark/Unibearm (OK).-\n" );
          printf( "===============================\n" );
          printf( "\n" );

          return 0;
      }





    if ( argc == 2)      printf( "Usage: unimark filein.mrk fileout.tex \n" );
    else if ( argc == 1) printf( "Usage: unimark filein.mrk fileout.tex \n" );

    return 0;

}




