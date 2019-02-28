#include <cstdio>
#include <iostream>
#include <string.h>

#define BUFFER_LENGTH 4
int main()
{
	std::cout<< " file operation\n";
	
	// Functions
	// Operations on files:
	// tmpfile
	// Open a temporary file (function )
	
	{
		char buffer[BUFFER_LENGTH];
		FILE* fp;
		fp = tmpfile(); 
		
		std::cout << "buffer size:" << sizeof(buffer) << " \n";
		do {
			if(!fgets(buffer,BUFFER_LENGTH,stdin)) break;
			fputs(buffer,fp);
			
		}while(strlen(buffer)>1);
		
		std::cout<< "read input :\n";
		rewind(fp);
		while(!feof(fp)) {
			if(fgets(buffer,BUFFER_LENGTH,fp) == NULL) break;
			fputs(buffer,stdout);
		}
		fclose(fp);
	
	}
	// tmpnam
	// Generate temporary filename (function )
	{
		
	}
	
	// remove
	// Remove file (function )
	{
		
	}
	
	// rename
	// Rename file (function )
	{
		
	}
	



	return 0;
}



// File access:
// fclose
// Close file (function )
// fflush
// Flush stream (function )
// fopen
// Open file (function )
// freopen
// Reopen stream with different file or mode (function )
// setbuf
// Set stream buffer (function )
// setvbuf
// Change stream buffering (function )

// Formatted input/output:
// fprintf
// Write formatted data to stream (function )
// fscanf
// Read formatted data from stream (function )
// printf
// Print formatted data to stdout (function )
// scanf
// Read formatted data from stdin (function )
// snprintf 
// Write formatted output to sized buffer (function )
// sprintf
// Write formatted data to string (function )
// sscanf
// Read formatted data from string (function )
// vfprintf
// Write formatted data from variable argument list to stream (function )
// vfscanf 
// Read formatted data from stream into variable argument list (function )
// vprintf
// Print formatted data from variable argument list to stdout (function )
// vscanf 
// Read formatted data into variable argument list (function )
// vsnprintf 
// Write formatted data from variable argument list to sized buffer (function )
// vsprintf
// Write formatted data from variable argument list to string (function )
// vsscanf 
// Read formatted data from string into variable argument list (function )

// Character input/output:
// fgetc
// Get character from stream (function )
// fgets
// Get string from stream (function )
// fputc
// Write character to stream (function )
// fputs
// Write string to stream (function )
// getc
// Get character from stream (function )
// getchar
// Get character from stdin (function )
// gets
// Get string from stdin (function )
// putc
// Write character to stream (function )
// putchar
// Write character to stdout (function )
// puts
// Write string to stdout (function )
// ungetc
// Unget character from stream (function )

// Direct input/output:
// fread
// Read block of data from stream (function )
// fwrite
// Write block of data to stream (function )

// File positioning:
// fgetpos
// Get current position in stream (function )
// fseek
// Reposition stream position indicator (function )
// fsetpos
// Set position indicator of stream (function )
// ftell
// Get current position in stream (function )
// rewind
// Set position of stream to the beginning (function )

// Error-handling:
// clearerr
// Clear error indicators (function )
// feof
// Check end-of-file indicator (function )
// ferror
// Check error indicator (function )
// perror
// Print error message (function )

// Macros
// BUFSIZ
// Buffer size (constant )
// EOF
// End-of-File (constant )
// FILENAME_MAX
// Maximum length of file names (constant )
// FOPEN_MAX
// Potential limit of simultaneous open streams (constant )
// L_tmpnam
// Minimum length for temporary file name (constant )
// NULL
// Null pointer (macro )
// TMP_MAX
// Number of temporary files (constant )
// Additionally: _IOFBF, _IOLBF, _IONBF (used with setvbuf)
// and SEEK_CUR, SEEK_END and SEEK_SET (used with fseek).

// Types
// FILE
// Object containing information to control a stream (type )
// fpos_t
// Object containing information to specify a position within a file (type )
// size_t
// Unsigned integral type (type )