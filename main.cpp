#include <iostream>
#include <bitset>
#include "PUF.h"

using namespace std;

int main() {
	//srand(time(NULL));
	PUF puf;
	bitset<100> input = 0;
	for (int i = 0; i < 100; i++) {
		//input = puf.RANDOM(input);
		//cout << input << "\t" << puf.AUTH(input) << endl;
	}

	
	int br1 = 0, br0 = 0, br_tot1=0,br_tot0=0;
	for (int exp = 0; exp < 1000; exp++)
	{
		input = puf.RANDOM(input);
		for (int i = 0; i < 32; i++)
		{
			bitset<5> ii = bitset<5>(i);

			for (int i = 0; i < 5; i++)
			{
				input[i] = ii[i];
			}
			bool resp = puf.AUTH(input);
			if (resp == 1) br1++;
			else if (resp == 0) br0++;
			//cout << input << endl;
		}
		if (br1 > br0) br_tot1++;
		else if (br0 > br1) br_tot0++;
		if (br0>>20 || br1>20) cout<< "resp 0: " << br0 << ", resp 1: " << br1 << "    "<<input<<endl;
		//cout << "resp 0: " << br0 << ", resp 1: " << br1 << endl;
		br1 = 0; br0 = 0;
	}
	cout << "Total br0: " << br_tot0 << " , br1: " << br_tot1 << endl;
	//x/all*p1+ y/all*p2 = 244/1000 *0.5 + 443/1000*?
    return 0;
}
