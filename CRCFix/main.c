#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int crc32(unsigned char *data, size_t length) {
	unsigned int byte, crc = 0xFFFFFFFF, mask;
	
	int i;
	for(i = 0; i < length; i++) {
		byte = data[i];				// Get next byte.
		crc = crc ^ byte;
		
		int j;
		for(j = 7; j >= 0; j--) {	 // Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
	}
	
	return ~crc;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("The Biggest Loser DS save CRC fixer\n");
		printf("Usage:\n");
		printf("%s save.sav\n", argv[0]);
		return 1;
	}
	
	FILE *f = fopen(argv[1], "rwb+");
	
	if(!f) {
		printf("Couldn't open %s!\n", argv[1]);
		return 1;
	}
	
	fseek(f, 0, SEEK_END);
	size_t length = ftell(f);
	unsigned char *save = malloc(length);
	rewind(f);
	fread(save, length, 1, f);
	
	unsigned char crcLength;
	memcpy(&crcLength, save + 8, 1);
	
	unsigned int oldCRC;
	memcpy(&oldCRC, save + 4, 4);
	
	unsigned int CRC = crc32(save + 8, crcLength);
	free(save);
	
	if(oldCRC != CRC) {
		fseek(f, 4, SEEK_SET);
		fwrite(&CRC, 1, 4, f);
		
		printf("Fixed!\n");
	}
	
	fclose(f);
	
	return 0;
}
