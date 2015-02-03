#include "sha1_lite.h"  



void SHA1::init()
{
size=total_size=0;
	abcde[0]=0x67452301; 
	abcde[1]=0xefcdab89;
	abcde[2]=0x98badcfe; 
	abcde[3]=0x10325476;
	abcde[4]=0xc3d2e1f0;	
}


uint SHA1::lrot( uint x, int bits )
{
	return (x<<bits) | (x>>(32 - bits));
};

void SHA1::add(byte x)
{
	total_size++;
	buffer[size++^3]=x; 
	if(size>=64) hash_block(),size=0;
}


void SHA1::final(byte res[20]) 
{
	uint n;
	dword64 total=dword64(total_size)*8;
	// дополняем буфер нулями
	add(0x80); while(size!=56) add(0); 
	// дополняем буфер полным размером данных в битах
	const byte *t=(byte*)&total;
	for(n=8; n;) add(t[--n]);
	// последний блок дополнен, отдаём результат
	for(n=0; n<20; n++) res[n]=output[n^3];	//#
}


void SHA1::hash_block() 
{
	uint n;
	dword a=abcde[0];
	dword b=abcde[1];
	dword c=abcde[2];
	dword d=abcde[3];
	dword e=abcde[4];
	// дополняем буфер (расширение)
	for(n=16; n<80; n++) data[n]=lrot(data[n-3]^data[n-8]^data[n-14]^data[n-16],1);
	// обработка блока
	for(n= 0; n<80; n++) {
		dword t,p;
		switch(n/20) {
		case 0: t=(c^d)&b^d;   p=0x5a827999; break;
		case 1:	t=b^c^d;       p=0x6ed9eba1; break;
		case 2: t=b&c|d&(b|c); p=0x8f1bbcdc; break;
		case 3: t=b^c^d;       p=0xca62c1d6; break;
		}
		t+=lrot(a,5)+e+data[n]+p;
		e=d,d=c,c=lrot(b,30),b=a,a=t;
	}
	abcde[0]+=a;
	abcde[1]+=b;
	abcde[2]+=c;
	abcde[3]+=d;
	abcde[4]+=e;
}


void SHA1::hexPrinter( unsigned char* c, int l )
{
	assert( c );
	assert( l > 0 );
	while( l > 0 )
	{
		printf( " %02x", *c );
		l--;
		c++;
	}
	printf("\n");
}


void SHA1::hash(const char* str)
{
	
	init();
	byte res[20];
	while(*str) add(*str++);
	final(res);
	hexPrinter( res, 20 );
}


bool SHA1::ifopen(char* ifile)
{
ifstream in(ifile, ios::binary);                                                     

    if (in.fail())                                                                         
        return false;                                                                      
    
    in.seekg(0, ios::end);                                                                  
    unsigned int file_size = (unsigned int)in.tellg();                                     
    in.seekg(0, ios::beg);                                                                 

    mes = new char[file_size]; 
    
    in.read(mes, file_size);                                                                                                      
    in.close();                                                                            
    return true;
 
}


/*
SHA1::SHA1()
{
	size=total_size=0;
	abcde[0]=0x67452301; 
	abcde[1]=0xefcdab89;
	abcde[2]=0x98badcfe; 
	abcde[3]=0x10325476;
	abcde[4]=0xc3d2e1f0;
}
*/