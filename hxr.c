#include <stdio.h>
#include <ctype.h>

static char x2d(unsigned char c) {
	return isdigit(c) ? c - '0' : tolower(c) - 'a' + 10;
}

int main(int argc, char* argv[]) {
	if (argc != 3)
		return fprintf(stderr, "Usage:\n" "\t" "hxr <source> <binary>\n"), 3;

	FILE* source = fopen(argv[1], "r");

	if (!source)
		return fprintf(stderr, "Could not open source file '%s'", argv[1]), 2;

	FILE* binary = fopen(argv[2], "wb");

	if (!binary)
		return fprintf(stderr, "Could not open binary file '%s'", argv[2]), 1;

	char byte;
	int c, nibble = 0;

	while ((c = fgetc(source)) != EOF) {
		switch (c) {
			case '#':
				while ((c = fgetc(source)) != '\n' && c != EOF);
				continue;
			case '<':
				while ((c = fgetc(source)) != '>' && c != EOF);
				continue;
		}

		if (!isxdigit(c))
			continue;

		if (nibble)
			fputc(byte + x2d((unsigned char) c), binary);
		else
			byte = x2d((unsigned char) c) << 4;

		nibble = !nibble;
	}

	return 0;
}
