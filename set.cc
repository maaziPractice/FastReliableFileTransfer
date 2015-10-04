// set::begin/end
#include <iostream>
#include <set>
using namespace std;

 int main ()
{
	 unsigned int myints[] = {75,23,65,42,13};
	   set<unsigned int> myset (myints,myints+5);

	   set<unsigned int>::iterator it;

	   cout << "myset contains:";
	   for ( it=myset.begin() ; it != myset.end(); it++ )
	    printf("%u  ",*it);

	   cout << endl;

	   unsigned int i=90000;
	   char  dummy[sizeof i];

	   *(unsigned int *) dummy = i;


	   printf("%u  ",*(unsigned int *) dummy);

	   if(  myset.find(65) != myset.end() )    //    singleFileChunk.seqNoOfFileChunk IS IN in the Lost_List)
				{
				   cout << "\n\n\nmyset contains:";
				}



  return 0;
}
