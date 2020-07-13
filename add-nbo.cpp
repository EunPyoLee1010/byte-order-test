#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <fstream> // for open()
//#include <Winsock2.h>

using namespace std;

uint32_t my_ntohl(uint32_t n) {
	uint32_t n1 = (n & 0xFF000000) >> 24;
	uint32_t n2 = (n & 0x00FF0000) >> 8;
	uint32_t n3 = (n & 0x0000FF00) << 8;
	uint32_t n4 = (n & 0x000000FF) << 24;
	//printf("%04X\n", n1);
	//printf("%04X\n", n2);
	return (n4 | n3 | n2 | n1);
}

void read_binary(FILE* bin_file, uint32_t& n){
	uint8_t network_buffer[4];
	fread(network_buffer, sizeof(uint8_t), 4, bin_file);
	uint32_t* p = reinterpret_cast<uint32_t*>(network_buffer);
	n = my_ntohl(*p);
	//printf("32 bit number=0x%x\n", n);
}

int main(int argc, char *argv[]) {
	if(argc != 3){
		printf("You must input only 2 binary files, but you entered %d\n", argc - 1);
		return -1;
	}
	FILE* bin_1;
	bin_1 = fopen(argv[1], "rb");
	if(bin_1 == NULL){
		printf("failed to open bin_1\n");
		return -1;
	}
	uint32_t operand1;
	read_binary(bin_1, operand1);
	fclose(bin_1);
	
	FILE* bin_2;
	bin_2 = fopen(argv[2], "rb");
	if(bin_2 == NULL){
		printf("failed to open bin_2\n");
		return -1;
	}
	uint32_t operand2;
	read_binary(bin_2, operand2);
	fclose(bin_2);

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", int(operand1), operand1, int(operand2), operand2, int(operand1+operand2), operand1 + operand2);
	return 0;
}

