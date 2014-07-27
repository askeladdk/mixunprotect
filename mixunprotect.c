/**
 *	Red Alert 2 mix unprotector.
 *	Drag-n-drop mix files on mixunprotect.exe to unprotect them.
 *
 *	Based on instructions given at:
 *	http://www.modenc.renegadeprojects.com/Unprotecting_a_protected_MIX
 */
#include <stdio.h>

typedef struct __attribute__((packed))
{
	unsigned int flags;
	unsigned short file_count;
	unsigned int body_size;
} mix_header;

int main(int argc, char** argv)
{
	FILE* mix;
	int i, file_size;
	mix_header header;

	if(argc < 2)
	{
		printf("usage: mixunprotect <file1> <file2> ... <fileN>\n");
		printf(" file1...N: mix files to unprotect.\n");
		return 0;
	}

	for(i = 1; i < argc; ++i)
	{
		if( !(mix = fopen(argv[i], "rb+")) )
		{
			printf("error: file \"%s\" does not exist!\n", argv[i]);
			continue;
		}

		fseek(mix, 0, SEEK_END);
		file_size = ftell(mix);

		fseek(mix, 0, SEEK_SET);
		fread(&header, sizeof(header), 1, mix);

		if(header.flags & 0x00020000)
		{
			printf("error: file \"%s\" is encrypted!\n", argv[i]);
		}
		else
		{
			header.flags = 0;
			header.body_size = file_size - (12 * header.file_count) - 10;

			fseek(mix, 0, SEEK_SET);
			fwrite(&header, sizeof(header), 1, mix);
		}

		fclose(mix);
	}

	return 0;
}
