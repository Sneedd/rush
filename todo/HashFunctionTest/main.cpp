#include <iostream>
#include <time.h>
#include <stdlib.h>


typedef unsigned int uint;




uint HashFunctions(std::string strg, int func, unsigned int hash_size)
{
    if (func == 0) {
        // Adler 32 HashFunktion
        size_t s1 = 1;
        size_t s2 = 0;
        for (size_t i=0; i<strg.length(); ++i)
        {
            s1 = (s1 + strg[i]) % 65521;
            s2 = (s2 + s1)     % 65521;
        }
        return ((s2 << 16) + s1) % hash_size;
    }
    else if (func == 1)
    {
       // Robert Sedgwicks
       unsigned int b    = 378551;
       unsigned int a    = 63689;
       unsigned int hash = 0;
       unsigned int i    = 0;

       for(i = 0; i < strg.length(); i++)
       {
          hash = hash * a + (strg[i]);
          a    = a * b;
       }

       return hash % hash_size;
    }
    else if (func == 2)
    {
        // Standard Hash (ALDA)
        unsigned int k = 0;
        int l = strg.length();
        for (int i=0;i<l;++i)
        {
            k = ((k<<7) + strg[i]) % hash_size;
        }
        return k;
    }
    else if (func == 3)
    {
       // Justin Sobel
       unsigned int hash = 1315423911;
       unsigned int i    = 0;

       for(i = 0; i < strg.length(); i++)
       {
          hash ^= ((hash << 5) + (strg[i]) + (hash >> 2));
       }

       return hash % hash_size;
    }
    else if (func == 4)
    {
       // Daniel J. Bernstein
       unsigned int hash = 5381;
       unsigned int i    = 0;

       for(i = 0; i < strg.length(); i++)
       {
          hash = ((hash << 5) + hash) + (strg[i]);
       }

       return hash % hash_size;
    }
    else if (func == 5)
    {
       //Donald E. Knuth
       unsigned int hash = strg.length();
       unsigned int i    = 0;

       for(i = 0; i < strg.length(); i++)
       {
          hash = ((hash << 5) ^ (hash >> 27)) ^ (strg[i]);
       }
       return hash % hash_size;
    }
    else if (func == 6)
    {
       // Steffen Ott
       unsigned int hash = 0;
       for(int i = 0; i < strg.length(); i++)
       {
          hash += (strg[i]);
       }
       return hash % hash_size;
    }
}

void TestHash(uint strgs_size, uint size_size)
{
    std::cout << "Initalize ..." << std::endl;
    // Größe des String Arrays
    uint strg_count = strgs_size;
    // Hashtable Größe 2
    uint size = size_size;
    // Initalisieren der Strings
    std::string* strgs = new std::string[strg_count];
    // Initalisieren der HashTable
    uint* array = new uint[size];
    // Strings füllen mit Werten
    for (int i=0; i<strg_count; ++i) {
        char buffer [50];
        sprintf(buffer, "%i", i);
        strgs[i] = buffer;
        //std::cout << strgs[i] << std::endl;
    }
    // Array leeren
    for (int i=0; i<size; ++i) array[i] = 0;
    std::cout << "Nr of Keys: " << strg_count << std::endl;
    std::cout << "Hashsize: " << size << std::endl;
    std::cout << "Initalize done." << std::endl;
    for (int i=0; i<7; ++i)
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Testen der Hashfunction ";
        if (i == 0) std::cout << "Adler 32";
        else if (i == 1) std::cout << "Robert Sedgwicks";
        else if (i == 2) std::cout << "ALDA";
        else if (i == 3) std::cout << "Justin Sobel";
        else if (i == 4) std::cout << "Daniel J. Bernstein";
        else if (i == 5) std::cout << "Donald E. Knuth";
        else if (i == 6) std::cout << "Steffen Ott";
        std::cout << std::endl;
        clock_t time = clock();
        for (int j=0; j<strg_count; ++j)
        {
            //uint k = (HashFunctions(strgs[j],i,size) + j*j) % size;
            uint k = HashFunctions(strgs[j],i,size);
            array[k]++;
        }
        time = clock() - time;
        std::cout << "Dauer: " << (double)time / CLOCKS_PER_SEC << std::endl;
        int vert = 0;
        int max = 0;
        for (int j=0; j<size; ++j)
        {
            if (array[j] == 1 || array[j] == 0) continue;
            //if (j != 0 && array[j-1] == 0 && array[j] != 0) vert--;
            if (max < array[j]) max = array[j];
            vert += array[j];
            //std::cout << j << "=" << array[j] << ",";
        }
        std::cout << std::endl;
        std::cout << "Verteilung: " << vert << "(max=" << max << ")" << std::endl;
        for (int i=0; i<size; ++i) array[i] = 0;
    }
}

int findPrim(int range)
// Sucht die nächste Primzahl begonnen ab range
{
    for (;;)
	{
	    bool divisible = false;
        for (int i=2; i<range; ++i)
		{
		    if ((range%i) == 0)
			{
			    divisible = true;
				break;
			}
        }
		if (!divisible) return range;
		range++;
    }
}


int main()
{
	TestHash(500000,findPrim(500000*2));
	return 0;
}
