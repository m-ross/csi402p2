/* Author: Marcus Ross
 *         MR867434
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"

/* This function takes a string for an argument that contains a filename of an unformatted input file, reads the file, and produces a report to the console on the data therein. */
void binIn(char *inFilename) {
	/* declarations */
	FILE* inFile = fopen(inFilename, "r");
	char stringIn[MAX_LEN + 1]; /* array size 256 */
	unsigned int intIn;
	unsigned int intMax;
	unsigned int intMin;
	unsigned char strLen; /* used as 1 byte integer */
	unsigned char strLenMax = 0; /* used as 1 byte integer */
	unsigned char strLenMin = 0; /* used as 1 byte integer */

	if (!inFile) { /* if failed to open input file */
		perror("Failed to open input file");
		exit(-1); /* then kill program */
	}

	while (fread(&strLen, sizeof(strLen), sizeof(char), inFile) == 1) { /* loop until a number isn't read into strLen */
		if (strLen > strLenMax) { /* strLen is new high if it's greater than the old high */
			strLenMax = strLen;
		}

		if (strLen < strLenMin || strLenMin == 0) { /* strLen is new low if it's lesser than the old low */
			strLenMin = strLen;
		}

		fseek(inFile, strLen, SEEK_CUR); /* skip the actual string because it's unnecessary */
		fread(&intIn, sizeof(intIn), 1, inFile); /* read four bytes as int */

		if (intIn > intMax) { /* intIn is new high if it's greater than the old high */
			intMax = intIn;
		}

		if (intIn < intMin || intMin == 0) { /* intIn is new low if it's lesser than the old low */
			intMin = intIn;
		}
	}

	printf("Shortest string: %u\n", strLenMin);
	printf("Longest string: %u\n", strLenMax);
	printf("Smallest int: %u\n", intMin);
	printf("Largest int: %u\n", intMax);

	close(inFile);
}

/* This function takes two strings as arguments, the former containing the filename of a text input file, the latter containing the filename of an output file that will be overwritten. The contents of the text file are essentially converted to unformatted data. */
void txtInBinOut(char *inFilename, char *outFilename) {
	/* declarations */
	FILE* inFile = fopen(inFilename, "r");
	FILE* outFile = fopen(outFilename, "w");
	char stringIn[MAX_LEN + 1]; /* array size 256 */
	unsigned int intIn;
	unsigned char strLen; /* used as 1 byte integer */

	if (!inFile) { /* if failed to open input file */
		perror("Failed to open input file");
		exit(-1); /* then kill program */
	}

	if (!outFile) { /* if failed to open output file */
		perror("Failed to open output file");
		exit(-1); /* then kill program */
	}

// 	while (fscanf(inFile, "%s", stringIn) == 1) { /* loop until fscanf fails to read a string to stringIn */
	while (fscanf(inFile, "%s\t%u", stringIn, &intIn) == 2) { /* loop until fscanf fails to read a string to stringIn and int to intIn */
		strLen = strlen(stringIn); /* get the length of the string */

		fwrite(&strLen, sizeof(strLen), sizeof(char), outFile); /* write the length of the string to file */
		fwrite(stringIn, strLen, sizeof(char), outFile); /* write the string to file */
		fwrite(&intIn, sizeof(intIn), 1, outFile); /* write the int to file */
	}

	close(inFile);
	close(outFile);
}

/* This function takes two strings as arguments, the former containing the filename of an unformatted input file, the latter containing the filename of an output file that will be overwritten. The contents of the unformatted file are basically converted to formatted text. */
void binInTxtOut(char *inFilename, char *outFilename) {
	/* declarations */
	FILE* inFile = fopen(inFilename, "r");
	FILE* outFile = fopen(outFilename, "w");
	char stringIn[MAX_LEN + 1]; /* array size 256 */
	unsigned int intIn;
	unsigned char strLen; /* used as 1 byte integer */
	char terminator = '\0'; /* to be appended onto stringIn */

	if (!inFile) { /* if failed to open input file */
		perror("Failed to open input file");
		exit(-1); /* then kill program */
	}

	if (!outFile) { /* if failed to open output file */
		perror("Failed to open output file");
		exit(-1); /* then kill program */
	}
	

	while (fread(&strLen, sizeof(strLen), 1, inFile) == 1) { /* loop until a byte is not read to strLen */
		fread(stringIn, strLen, 1, inFile); /* read string */
		stringIn[strLen] = terminator; /* put string terminator after last char */
		fread(&intIn, sizeof(intIn), 1, inFile); /* read four bytes as int */

		if (ftell(outFile) != 0) { /* print newline only if not at beginning of file; this was added to avoid printing a newline at the end of the file */
			fprintf(outFile, "\n");
		}

		fprintf(outFile, "%s\t%u", stringIn, intIn); /* write formatted string, tab, and int to file */
	}

	close(inFile);
	close(outFile);
}