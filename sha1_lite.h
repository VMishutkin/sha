#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <fstream>
                                                                     //Для string
#include <iostream>                                                                     //Для cout
#include <sstream>   
using namespace std;
typedef unsigned char byte;
typedef unsigned long dword;
typedef uint64_t dword64;
typedef unsigned int uint;



class SHA1{

	union{
		dword abcde[5];		//!< данные для образования хеша
		byte output[20];	//!< данные для считывания
	};
	union{
		byte buffer[64];	//!< буффер для принятых данных
		dword data[80];		//!< место для расширенныя данных
	};
	uint size;				//!< заполнение буфера
	uint total_size;		//!< общее число принятых данных
	void add(byte);			//!< добавление байта в буффер
	uint lrot( uint x, int bits );

	void init();
	void final(byte[20]);
	void hexPrinter( unsigned char* c, int l );
	void hash_block();		//!< обработка отдельного блока
public:
	char* mes;
	
	void hash(const char *str);
	bool ifopen(char* ifile);

};