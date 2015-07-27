#include <stdio.h>
#include <string.h>


// function has to be called with three arguments:
// 1. input (output)
// 2. dictionary file (dict)
// 3. new output (newout)
int main ( int argc, char *argv[] )
{
	// variable to check the data afterwards
	int strcmpi(const char *string1, const char *string2);	
	char dictword[100];
	char approved[100];
	char compare1[3];
	char compare2[3];
	char space[1] = {","};

	int i;
	int j;

  // dictionary file (dict)
  FILE *fileDict = fopen( argv[2], "r" );	
  // output to write keyword - here only creating new file
  FILE *fileNewOutCreate = fopen( argv[3], "w" );
  fclose( fileNewOutCreate ); //close it immeditately

  FILE *fileOut = fopen( argv[3], "a" );  //open output file to append the keyword and message

  // reduce output file by only accepting strings with at least 3 char the same at the beginning 
  while(fgets(dictword,sizeof(dictword),fileDict) != NULL)//start while fileDict second run
   {
      // strip trailing '\n' if it exists
      int len = strlen(dictword)-1;
      if(dictword[len] == '\n') 
         dictword[len] = 0;
//printf("var is %s \n",dictword);

      // open and go through the created output file
      FILE *fileOutput = fopen( argv[1], "r" );
      while(fgets(approved,sizeof(approved),fileOutput) != NULL)//start while output file go through
        {

      // strip trailing '\n' if it exists
      int len = strlen(approved)-1;
      if(approved[len] == '\n') 
         approved[len] = 0;	
//printf("var is %s \n",approved);

	for(i=0; i<strlen(approved);i++){
          if(approved[i] == space[0]){ //copy the first chars after the comma
	    for(j=0; j<3;j++){ //only copy the amound of char fitting in the variable
	      //copy the actual decoded string towards the comparing variable 
	      //(removing the first part which is the keyword)
	      compare2[j] = approved[i+1+j];
//printf("approved is now %c\n", compare2[j]);
            }//end for 
	  }//end if
        }//end for

	// compare first chars to find matching dict and message
	i = 0;
	for(j=0;j<3;j++){
	 if(dictword[j]==compare2[j]) i++;
	 
	 if(i==3){
	 //if first chars are a match open file and write out the keyword and message for further study 
         fprintf(fileOut, "%s,", approved);	//write out the keyword and message
	 }//end if with opening file and writing out new reduced words
        }//end for loop

      }//end while output file go through
fclose( fileOutput );
   }//end while fileDict - second run


   fclose( fileDict );   //clean up 
   fclose( fileOut );	 //clean up 
}
