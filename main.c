/* Author: Marcus Ross
 * Description: This program has three options: -t, -b, -s.
 *   The -t option requires input and output filenames as arguments, respectively; the designated input file must contain one or more lines with a string of length at least 1 and at most 255 characters, a tab character, and a 32 bit unsigned integer as formatted text; for each line read from the input file, the length of the string, the string, and the integer will be written to the designated output file as unformatted data; the output file will be overwritten if it already exists.
 *   The -b option requires input and output filenames as arguments, respectively; the designated input file must contain one or more triplets including 1 byte holding the length of the following string, a string of at least 1 and at most 255 characters, and a 4 byte unsigned integer as unformatted data; for each triplet read from the input file, the string, a tab character, and the integer will be written to the designated output file as formatted data; the output file will be overwritten if it already exists.
 *   The -s option requires an input filename as an argument; the designated input file must contain one or more triplets including 1 byte holding the length of the following string, a string of at least 1 and at most 255 characters, and a 32 bit unsigned integer as unformatted data; the program will read the strings and integers in the file and produce a report giving the smallest and largest string lengths, and the smallest and largest integers.
 */

#include <stdio.h>
#include "proto.h"

int main(int argc, char **argv) {
	if (argv[1] && argv[1][0] == '-') { /* if the first argument exists and is prefixed by a hyphen */
		if (argv[1][1] == 's' && argv[1][2] == '\0') { /* if the first argument is exactly an s flag */
			if (argc != 3) { /* if there aren't three arguments */
				fprintf(stderr, "Exactly one filename is required if -s is set.\n");
				return -1; /* then kill program */
			}

			binIn(argv[2]); /* process the binary input file */
		}
		else { /* the first argument isn't an s flag */
			if (argv[1][1] == 't' && argv[1][2] == '\0') { /* if the first argument is exactly a t flag */
				if (argc != 4) { /* if there aren't four arguments */
					fprintf(stderr, "Exactly two filenames are required if -t is set.\n");
					return -1; /* then kill program */
				}

				txtInBinOut(argv[2], argv[3]); /* process the text input file and binary output file */
			}
			else { /* the first argument isn't a t flag */
				if (argv[1][1] == 'b' && argv[1][2] == '\0') { /* if the first argument is exactly a b flag */
					if (argc != 4) { /* if there aren't four arguments */
						fprintf(stderr, "Exactly two filenames are required if -b is set.\n");
						return -1; /* then kill program */
					}

					binInTxtOut(argv[2], argv[3]); /* process the binary input file and text output file */
				}
				else { /* the first argument isn't a b flag */ 
					fprintf(stderr, "Flag -t, -b, or -s is required.\n");
					return -1; /* so kill program */
				}
			}
		}
	}
	else { /* the first argument doesn't exist or isn't prefixed by a hyphen */
		fprintf(stderr, "Flag -t, -b, or -s is required.\n");
		return -1; /* so kill program */
	}
	
	return 0;
}
