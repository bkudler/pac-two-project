

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


	while(i > 0 && isspace(src[i]))
	{	
		lastPos = i;
		i--;
	}



	char currChar;

	for(int i = 0; i < lastPos; i++){
		if(!isspace(src[i]) || !isspace(src[lastAddedPos])){
			currChar = src[i];
			if(isspace(currChar)){
				currChar = ' ';
			} else if(isalpha(src[i])){
				currChar = tolower(currChar);
			}
			dest[i] = currChar;
		}
	}


	return dest;
}


int count(char *searchStr, char *compareStr, int k)
{

	int ctr = 0;
	// char *searchSubStr = malloc(1 + k);
	// char *foundSubStr = malloc(1 + k);
	// char *searchSubStr = malloc(k);
	// char *foundSubStr = malloc(k);

	char *searchSubStr = calloc(k, sizeof(char));
	char *foundSubStr = calloc(k, sizeof(char));

	if(searchSubStr == NULL || foundSubStr == NULL){
		printf("can’t allocate enough memory: %m\n");
		return -1;
	}

	// printf("%s %s\n", searchStr, compareStr);

	for(int i = 0; i <= (strlen(searchStr) - k); i++){

		searchSubStr = memcpy(searchSubStr, &searchStr[i], k );

		// printf("%s %s\n", searchSubStr, "HERE");

		for(int j = 0; j <= (strlen(compareStr) - k); j++){

			foundSubStr = memcpy(foundSubStr, &compareStr[j], k );

			// printf("%s       %s\n", searchSubStr, foundSubStr);

			if(strcmp(searchSubStr, foundSubStr) == 0){
				ctr++;
				// printf("%d", ctr);
				printf("%s       %s\n", searchSubStr, foundSubStr);

				break;
			}
		}
	}

	free(searchSubStr);
	free(foundSubStr);

	return ctr;

}

 
int main(int argc, char *argv[])
{
	int k = atoi(argv[1]);
	char *fileNameOne = argv[2];
	double fileOneSize = atoi(argv[3]);
	char *fileNameTwo = argv[4];
	int fileTwoSize = atoi(argv[5]);
	// char *fileOneString = malloc(1 + fileOneSize);
	// char *fileTwoString = malloc(1 + fileTwoSize);
	char *fileOneString = calloc(1 + fileOneSize, sizeof(char));
	char *fileTwoString = calloc(1 + fileTwoSize, sizeof(char));
	FILE *fptr1;
	FILE *fptr2;

	if(fileOneString == NULL || fileTwoString == NULL){
		printf("can’t allocate enough memory: %m\n");
		return -1;
	}

	fptr1 = fopen(fileNameOne, "r");

	if(fptr1 == NULL){
		printf("cannot read file");
		return -1;
	}
	

	// if(fgets(fileOneString, fileOneSize + 1, fptr1) != NULL){}


	// for(int i = 0; i < (fileOneSize + 1); i++){
	// 	fileOneString[i] = '\0';
	// }


	while( fscanf(fptr1, "%s", &fileOneString[strlen(fileOneString)] ) == 1){
		// printf("%d %s\n", strlen(fileOneString), fileOneString);
		fileOneString[strlen(fileOneString)] = ' ';
	}

	// printf("HI %s\n", fileOneString);


	fclose(fptr1);


	fptr2 = fopen(fileNameTwo, "r");

	if(fptr2 == NULL){
		printf("Could not open %s\n", fileNameTwo);
		return -1;
	}

	// if(fgets(fileTwoString, fileTwoSize + 1, fptr2) != NULL){}

	// for(int i = 0; i < (fileTwoSize + 1); i++){
	// 	fileTwoString[i] = '\0';
	// }

	while( fscanf(fptr2, "%s", &fileTwoString[strlen(fileTwoString)] ) == 1){
		// printf("%d %s\n", strlen(fileTwoString), fileTwoString);
		fileTwoString[strlen(fileTwoString)] = ' ';
	}

	// printf("HELLOooBEN.   %s\n", fileTwoString);


	fclose(fptr2);	

	// printf("%s\n%s\n", fileOneString, fileTwoString);

	char *fileOneCleanString = calloc(1 + fileOneSize, sizeof(char));

	if(fileOneCleanString == NULL){
		printf("can’t allocate enough memory: %m\n");
		return -1;
	}

	fileOneCleanString = preProcess(fileOneString, fileOneCleanString);

	free(fileOneString);

	char *fileTwoCleanString = calloc(1 + fileTwoSize, sizeof(char));

	if(fileTwoCleanString == NULL){
		printf("can’t allocate enough memory: %m\n");
		return -1;
	}

	fileTwoCleanString = preProcess(fileTwoString, fileTwoCleanString);

	// printf("THIS IS WHERE %s\n", fileTwoCleanString);

	free(fileTwoString);

	int ctr;
	// printf("%s\n%s\n%d\n", fileOneCleanString, fileTwoCleanString, ctr);

	ctr = count(fileOneCleanString, fileTwoCleanString,k);

	printf("%s\n%s\n%d\n", fileOneCleanString, fileTwoCleanString, ctr);

	free(fileOneCleanString);
	free(fileTwoCleanString);

	double similarity = ctr / ( (fileOneSize - k) + 1);

	printf("%lf\n", similarity);



	return similarity;


}