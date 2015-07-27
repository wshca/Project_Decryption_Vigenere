#include <stdio.h>
#include <string.h>

// function has to be called with three arguments:
// 1. cipher text (assignment)
// 2. dictionary file (dict)
// 3. output file (output)
int main ( int argc, char *argv[] )
{
	// variables to build the actual string
	char output[100];
	char send1[24] = {"gcipher -C Vigenere -k "}; //length 24
	char send2[3] = {" "};
	char send3[4] = {" >> "};
	char send4[3] = {" \n"};	
	char sendall[150];

	// dictionary file (dict)
	FILE *fileDict = fopen( argv[2], "r" );
	// output to write keyword - here only creating new file
	FILE *fileOutCreate = fopen( argv[3], "w" );
	fclose( fileOutCreate ); //close it immeditately

  // create output file by requesting another program to do the decoding with the keywords from the dictionary
  while(fgets(output,sizeof(output),fileDict) != NULL)//start while fileDict first run
   {
      // strip trailing '\n' if it exists
      int len = strlen(output)-1;
      if(output[len] == '\n') 
         output[len] = 0;

	// output to write keyword
	FILE *fileOut = fopen( argv[3], "a" );  //open output file to append the keyword
	fprintf(fileOut, "%s,", output);	//write out the keyword so we have keyword and decoded string in one line
	fclose( fileOut );			//close file so we now can append the decoded string from the external program

	// create string to send out to system to call external software cipher from 
	// the command line and let it put into the output file 
	strcpy(sendall, send1);     //copy first part with program name and instruction to string
	strcat(sendall, output);    //copy dictionary word to string
	strcat(sendall, send2);     //copy on space into the string
	strcat(sendall, argv[1]);   //copy the first argument of the call into string which is the cipher
	strcat(sendall, send3);     //copy >> to string
	strcat(sendall, argv[3]);   //copy the output filename to string
	strcat(sendall, send4);     //copy the new line to string
	// call other program gcipher with parameter to have a decryption
	system(sendall);

   }//end while fileDict - first run
   fclose( fileDict );   //clean up 
}
