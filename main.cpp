#include <iostream>
#include <bitset>
#include <cmath>
#include "utils.h"
#include "PUF.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
	srand(time(NULL));
	PUF puf;
	utils util;
	unsigned long long ans = 0;
	bitset<100> input = 0;
	int br1 = 0, br0 = 0, br_tot1=0,br_tot0=0;
	for (int exp = 0; exp < 1; exp++)
	{
		input = puf.RANDOM(input);
		for (long long i = 0; i < (1<<25); i++)
		{
		    if(i % (1<<15) == 0)
		        cout << i << endl;
			bitset<25> ii = i;

			for (int i = 0; i < 25; i++)
			{
				input[75 + i] = ii[i];
			}
			bool resp = puf.AUTH(input);
			if (resp == 1) br1++;
			else if (resp == 0) br0++;
			//cout << input << endl;
		}
		if (br1 > br0) br_tot1++;
		else if (br0 > br1) br_tot0++;
		cout<< "resp 0: " << br0 << ", resp 1: " << br1 << "    "<<input<<endl;
		//cout << "resp 0: " << br0 << ", resp 1: " << br1 << endl;
		br1 = 0; br0 = 0;
	}
	cout << "Total br0: " << br_tot0 << " , br1: " << br_tot1 << endl;
	//x/all*p1+ y/all*p2 = 244/1000 *0.5 + 443/1000*?
    return 0;
}
