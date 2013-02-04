/*
 	Copyright (c) 2013 Peter Sherman
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>

FILE *f_input;
FILE *f_output;

int bufsize = 512;
void *buffer;

FILE *attempt_open(char *, char *);
int handle_opts(int, char **);

int main(int argc, char *argv[])
{
	int status;
	int excess;

	f_input = stdin;
	f_output = stdout;

	if(handle_opts(argc, argv) == -1)
		return EXIT_FAILURE;

	for(;;) {
		status = fread(buffer, bufsize, 1, f_input);
		
		if(status == 0)
			break;
		
		if(status == -1) {
			printf("Error reading from file: %s", strerror(errno));
			return EXIT_FAILURE;
		}
		status = fwrite(buffer, bufsize, 1, f_output);
		
		if(status == -1) {
			printf("Error writing to file: %s", strerror(errno));
			return EXIT_FAILURE;
		}
	}
	excess = ftell(f_input) % bufsize;
	status = fwrite(buffer, excess, 1, f_output);
	
	fclose(f_input);
	fclose(f_output);
	free(buffer);
	return 0;
}

FILE *attempt_open(char *path, char *mode) //just opens it and does error checking
{
	FILE *target = fopen(path, mode); 
	if(!target) {
		fprintf(stderr, "Error opening %s: %s\n", path, strerror(errno));
		return NULL;
	}
	return target;
}

int handle_opts(int argc, char *argv[]) //option processing - sets flags, attempts to open files, and allocates the buffer.
{
	char *in_path = 0, *out_path = 0;
	int i;
	for(i = 1; i < argc; i++) {

		if(*argv[i] != '-') {
			fprintf(stderr, "Unrecognized option: %s \n", argv[i]);
			return -1;
		}

		if(!strcmp(argv[i], "-i")) {
			in_path = argv[++i];
			continue;
		}
		
		if(!strcmp(argv[i], "-o")) {
			out_path = argv[++i];
			continue;
		}
		
		if(!strcmp(argv[i], "-bs")) {
			bufsize = atoi(argv[++i]);
			continue;
		}

		else {
			fprintf(stderr, "Unrecognized option: %s \n", argv[i]);
			return -1;
		}

	}

	buffer = malloc(bufsize);

	if(in_path)
		if(!(f_input = attempt_open(in_path, "r")))
			return -1;
	if(out_path)
		if(!(f_output = attempt_open(out_path, "w")))
			return -1;
	return 0;
}
