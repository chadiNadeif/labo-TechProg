#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labo.h"


/* This code is public domain -- Will Hartung 4/9/09 */
static size_t getline(char** lineptr, size_t* n, FILE* stream) {
	char* bufptr = NULL;
	char* p = bufptr;
	size_t size;
	int c;

	if (lineptr == NULL) {
		return -1;
	}
	if (stream == NULL) {
		return -1;
	}
	if (n == NULL) {
		return -1;
	}
	bufptr = *lineptr;
	size = *n;

	c = fgetc(stream);
	if (c == EOF) {
		return -1;
	}
	if (bufptr == NULL) {
		bufptr = malloc(128);
		if (bufptr == NULL) {
			return -1;
		}
		size = 128;
	}
	p = bufptr;
	while (c != EOF) {
		if ((p - bufptr) > (size - 1)) {
			size = size + 128;
			bufptr = realloc(bufptr, size);
			if (bufptr == NULL) {
				return -1;
			}
		}
		*p++ = c;
		if (c == '\n') {
			break;
		}
		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}

int test_code(FILE* f) {
	char* ligne = NULL;
	size_t len = 0;
	size_t read;
	int ligneCount = 0;
	int result = 0;
	static char lastLine[1024] = { 0 };
	static int numbers[256] = { 0 };
	static size_t num_len = 0;
	int from = -1;
	int ot = -1;
	String str = { 0 };
	while ((read = getline(&ligne, &len, f)) != -1) {
		if (ligneCount <= 2) {
			if (ligneCount == 1) {
				char text[512] = { 0 };
				int i = 0;
				char chr = ligne[i];
				while (i < read) {
					while (chr != ',' && chr != '\0') {
						text[strlen(text)] = chr;
						++i;
						chr = ligne[i];
					}
					if (from == -1) {
						from = atoi(text);
						memset(text, 0, len);
					}
					else if (ot == -1) {
						ot = atoi(text);
						memset(text, 0, len);
					}
					chr = ligne[++i];
				}

			}
			else if (ligneCount == 2) {
				char* sous = sousTexte(lastLine, from, from + ot);
				sous[strlen(sous)] = '\n';
				if (strcmp(ligne, sous) == 0) {
					printf("Tu as bien programmer: sousTexte !\n");
				}
				else {
					printf("Tu as un erreur dans: sousTexte !\n");
					result = 1;
				}
			}
			else {
				strcpy(lastLine, ligne);
			}
		}
		else if (ligneCount <= 4) {
			static size_t isGood = 0;
			strcpy(lastLine, ligne);
			size_t len = strlen(lastLine)-1;
			lastLine[len] = '\0';
			set_String(lastLine, &str);
			if (strcmp(str.characters, lastLine) == 0 && len == str.length) {
				printf("Tu as bien programmer: set_String !\n");
			}
			else {
				printf("Tu as un erreur dans: set_String !\n");
				if (len != str.length) {
					printf("[ERREUR]: Tu n'as pas la bonne length pour ton string\n");
				}
				result = 1;
			}
			isGood = String_is_palindrome(&str);
			if (isGood == 1) {
				printf("Tu as bien programmer: String_is_palindrome !\n");
			}
			else {
				printf("Tu as un erreur dans: String_is_palindrome !\n");
				result = 1;
			}
		}
		else if (ligneCount <= 6) {
			static int sorted_nums[256] = { 0 };
			char text[512] = { 0 };
			int i = 0;
			char chr = ligne[i];
			while (i < read) {
				while (chr != ',' && chr != '\0') {
					text[strlen(text)] = chr;
					++i;
					chr = ligne[i];
				}
				if (ligneCount == 5)
					numbers[num_len] = atoi(text);
				else
					sorted_nums[num_len] = atoi(text);
				memset(text, 0, len);
				num_len++;
				chr = ligne[++i];
			}
			if (ligneCount == 6) {
				static int isGood = 1;
				bubbleSort(numbers, num_len);
				for (int i = 0; i < num_len; ++i) {
					if (numbers[i] != sorted_nums[i]) {
						isGood = 0;
						break;
					}
				}
				if (isGood) {
					printf("Tu as bien programmer: bubbleSort !\n");
				}
				else {
					printf("Tu as un erreur dans: bubbleSort !\n");
					result = 1;
				}
			}
			else {
				num_len = 0;
			}
		}
		ligneCount++;
	}

}
int main(int argc, char** argv) {


	FILE* input = fopen("test_input.txt","r");
	int result = 1;
	if (input != NULL) {
		result = test_code(input);
	}

	if(input != NULL)
		fclose(input);

	return result;
}
