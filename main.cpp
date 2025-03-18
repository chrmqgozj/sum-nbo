#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t ntohl(uint32_t n) {
        return (n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) | ((n & 0xff) << 24);
}

uint32_t read_file(const char* fname) {
	FILE* fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("%s: file not open\n", fname);
		exit(0);
	}

	uint32_t buf;
	if (fread(&buf, 4, 1, fp) != 1) {
		printf("%s: not 4byte\n", fname);
		exit(0);
	}

	fclose(fp);

	return ntohl(buf);	
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("input more than 1 file\n");
		return 0;
	}

	int n = argc - 1;
	uint32_t value[n];
	uint32_t sum = 0;

	for(int i = 0;i < n;i++) {
		value[i] = read_file(argv[i + 1]);
		sum += value[i];
		
		if (i == n - 1) {
			if (value[i] < 0x10000) {
				printf("%u(0x%04x) = %u(0x%04x)\n", value[i], value[i], sum, sum);
			}
			else {
				printf("%u(0x%08x) = %u(0x%08x)\n", value[i], value[i], sum, sum);
			}
		}
		else {
			if (sum < 0x10000) {
                        	printf("%u(0x%04x) + ", value[i], value[i]);
			}
                        else {
				printf("%u(0x%08x) + ", value[i], value[i]);
                        }
		}

	}	

	return 0;

}
