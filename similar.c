

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//argc -- numnber of arguments
//argv[0] == similar (file name)
//argv[1] == k
//argv[2] == file1
//argv[3] == file1 size
//argv[4] == file2
//argv[5] == file2 size


char * preProcess(char *src, char *dest)
{
	int lastAddedPos = 0;
	int lastPos = strlen(src);
	int i = strlen(src) - 1;

	// printf("%d %s\n", lastPos, src);

	while(i > 0 && isspace(src[i]))
	{	
		lastPos = i;
		i--;
	}

	// printf("%d %s\n", lastPos, src);
	// printf("%d\n", sizeof(dest));


	char currChar;

	for(int i = 0; i < lastPos; i++){
		// printf("%d %d\n", i,lastPos);
		if(!isspace(src[i]) || !isspace(src[lastAddedPos])){
			currChar = src[i];
			// printf("%c %s\n", currChar, dest);
			if(isspace(currChar)){
				// dest[i] = " ";
				currChar = ' ';
			} else if(isalpha(src[i])){
				// dest[i] = tolower(src[i]);
				currChar = tolower(currChar);
			}

			// strcat( dest, currChar);
			// printf("HEY %d \n", i);
			// printf("HEY %d %c\n", i, currChar);

			dest[i] = currChar;
		}
	}

	// printf("%s\n", src);


	return dest;
}


// int count(char *searchStr, char *compareStr)
// {

// 	int ctr = 0;
// 	char *searchSubStr = malloc(1 + k);
// 	char *foundSubStr = malloc(1 + k);
// 	for(int i = 0; i <= (strlen(fileOneCleanString) - k), i++){
// 		searchSubStr = memcpy(searchSubStr, &fileOneCleanString[i], k );
// 		for(int j = 0; j <= (strlen(fileTwoCleanString) - k), j++){
// 			foundSubStr = memcpy(searchSubStr, &fileOneCleanString[i], k );
// 			if(searchSubStr == foundSubStr){
// 				ctr++;
// 			}
// 		}
// 	}

// 	free(searchSubStr);
// 	free(searchSubStr);
// 	return ctr;

// }

 
int main(int argc, char *argv[])
{
	int k = atoi(argv[1]);
	char *fileNameOne = argv[2];
	int fileOneSize = atoi(argv[3]);
	char *fileNameTwo = argv[4];
	int fileTwoSize = atoi(argv[5]);
	char *fileOneString = malloc(1 + fileOneSize);
	char *fileTwoString = malloc(1 + fileTwoSize);
	FILE *fptr1;
	FILE *fptr2;

	fptr1 = fopen(fileNameOne, "r");

	if(fptr1 == NULL){
		printf("Could not open %s\n", fileNameOne);
		return -1;
	}
	

	// if(fgets(fileOneString, fileOneSize + 1, fptr1) != NULL){}


	for(int i = 0; i < (fileOneSize + 1); i++){
		fileOneString[i] = '\0';
	}

	while( fscanf(fptr1, "%s", &fileOneString[strlen(fileOneString)] ) == 1){
		// printf("%d %s\n", strlen(fileOneString), fileOneString);
		fileOneString[strlen(fileOneString)] = ' ';
	}

	fclose(fptr1);


	fptr2 = fopen(fileNameTwo, "r");

	if(fptr2 == NULL){
		printf("Could not open %s\n", fileNameTwo);
		return -1;
	}

	// if(fgets(fileTwoString, fileTwoSize + 1, fptr2) != NULL){}

	for(int i = 0; i < (fileTwoSize + 1); i++){
		fileTwoString[i] = '\0';
	}

	while( fscanf(fptr2, "%s", &fileTwoString[strlen(fileTwoString)] ) == 1){
		// printf("%d %s\n", strlen(fileTwoString), fileTwoString);
		fileTwoString[strlen(fileTwoString)] = ' ';
	}

	fclose(fptr2);	

	// printf("%s\n%s\n", fileOneString, fileTwoString);

	char *fileOneCleanString = malloc(1 + fileOneSize);
	fileOneCleanString = preProcess(fileOneString, fileOneCleanString);


	char *fileTwoCleanString = malloc(1 + fileOneSize);
	fileTwoCleanString = preProcess(fileTwoString, fileTwoCleanString);

	// int ctr;
	// ctr = count(fileOneCleanString, fileTwoCleanString);

	printf("%s\n%s\n", fileOneCleanString, fileTwoCleanString);



	free(fileOneString);
	free(fileTwoString);

	free(fileOneCleanString);
	free(fileTwoCleanString);

}