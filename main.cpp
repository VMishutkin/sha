#include "sha1_lite.h"  



int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << endl << "Использование: ./sha1 file_in" << endl << endl;
    
    return -1;
    }    

SHA1 sha1;
if(sha1.ifopen(argv[1]))
{
printf("Hash for %s\n",sha1.mes);
    SHA1().hash(sha1.mes);
}
else
 printf("не удалось считать файл %s",argv[1]);


/*
char fname[]="./text";
char* mes=SHA1().ifopen(fname);
printf("Hash for %s\n",mes);
    SHA1().hash(mes);
*/



}
