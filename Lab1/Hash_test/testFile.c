#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

char** storeChar(const char* charArray)
{
	char** wordArray;
	char* temp = NULL;
	int i = 0;
	int j = 0;
	int arrayLen = strlen(charArray);
	int flag = 0;
	int subLen = 0;
	int wcount = (int)(arrayLen/(4.49*0.75));
	int charcount = 0;
	int findex = 0;
	
	wordArray = (char **)malloc(sizeof(char *) * wcount);
	int wordPos = 0;
	for(i=0; i<arrayLen; i++){
		charcount++;
		if(isspace(charArray[i])){
			if (charcount < 2){
				findex += charcount;
				charcount = 0;
				continue;
			}
			temp = malloc(sizeof(char) * charcount);
			wordArray[wordPos] = (char *)malloc(sizeof(char) * charcount);
			for(j = 0; j<charcount; j++){
				temp[j] = *(charArray + findex+j);
				wordArray[wordPos][j] = temp[j];
			}
			temp[charcount-1] = '\0';
			//printf("%s\n", temp);
			findex += charcount;
			charcount = 0;
			free(temp);
			wordPos ++;
		}
	}
	wordArray[wordPos] = '\0';
	return wordArray;
}


int
main(int argc, char *argv[])
{
	int fd;
	void *addr;
	struct stat sb;
	//struct wc *wc;
	struct mallinfo minfo;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}
	/* open file */
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	/* obtain file size */
	if (fstat(fd, &sb) < 0) {
		fprintf(stderr, "fstat: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	/* map the whole file, sb.st_size is the file size. after this call, the
	   file can be accessed as an array of characters, at address addr. */
	addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (addr == MAP_FAILED) {
		fprintf(stderr, "mmap: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	/* close the file */
	close(fd);
	const char* addr1;
	addr1 = (char *)addr;
	for(int ii = 0; ii<strlen(addr1); ii++)
	{
		printf("%c\n", *(addr1+ii));
	}

	char ** wordArray;
	wordArray = storeChar(addr1);
	for (int i = 0; wordArray[i]!='\0'; i++)
	{
		printf("%s\n", *(wordArray+i));
	}
	for (int i = 0; wordArray[i]!='\0'; i++)
	{
		free(wordArray[i]);
	}
	free(wordArray);

	/* check for memory leaks */
	minfo = mallinfo();
	assert(minfo.uordblks == 0);
	assert(minfo.hblks == 0);
	printf("No memory leaks!\n");
	exit(0);
}
