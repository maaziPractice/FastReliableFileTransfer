#include <stdio.h>
#include <iostream>
#include <set>
using namespace std;


unsigned int currentSeqNumber;

typedef struct
{
	unsigned int chunkSeqNumber;
	char actualFileChunkBytes[1450+sizeof currentSeqNumber];
	unsigned int actualChunkBytesReadFromWire;

}SingleFileChunk;




int main()
{
    SingleFileChunk singleFileChunk;

    unsigned int source=0, desti=1450;

    *(unsigned int *) (singleFileChunk.actualFileChunkBytes +1450) = desti;

    source = *(unsigned int *) (singleFileChunk.actualFileChunkBytes +1450);

   printf("Source sis %u\n",source);
   printf ("Characters: %c %c \n", 'a', 65);
   printf ("Decimals: %d %ld\n", 1977, 650000L);
   printf ("Preceding with blanks: %10d \n", 1977);
   printf ("Preceding with zeros: %010d \n", 1977);
   printf ("Some different radixes: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
   printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
   printf ("Width trick: %*d \n", 5, 10);
   printf ("%s \n", "A string");


   set<int> myset;
     set<int>::iterator it;

     // set some initial values:
     for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

     it=myset.find(20);
     myset.erase (it);
     myset.erase (myset.find(40));

     cout << "myset contains:";
     for (it=myset.begin(); it!=myset.end(); it++)
       cout << " " << *it;
     cout << endl;

     if( myset.find(500) == myset.end())  cout << "myset does not contain 500\n";


     char NAK[85];
     int i=0;
     it=myset.begin();
     *  (unsigned int *) (NAK +(i*4)) = *it ;


     printf("the final value is %u\n", *  (unsigned int *) (NAK +(i*4)));








     return 0;


}
