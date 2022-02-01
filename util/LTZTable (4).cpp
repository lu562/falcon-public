//import time
//start = time.time()
//basic param
//n = 64

#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

void f(int howmany){
for(int a00 = 0; a00 < howmany; a00++){
	const int64_t k = 4;
	//const int64_t l = 8;
	constexpr int64_t l[k] = {8, 8, 8, 8};
	//const int64_t n = k*l;
	const int64_t n = 32;

	int64_t p = (int64_t)(pow(2,n));
	int64_t p2 = (int64_t)(pow(2,8));
	p2 = 67;
	int64_t p3 = (int64_t)(pow(2,8));
	p3 = 67;
	
	//Party 3
	int64_t z_1 = (2 + (rand() % 2)) %2;
	int64_t z_3 = (2 + (rand() % 2)) %2;
	z_1 = 0;
	z_3 = 0;


	//ENUM for output
	int64_t POS = 1;
	int64_t NEG = 2;
	int64_t UNK = 0;

	//Random values
	int64_t r = (p + (rand() % p)) %p;
	//r = 0;
	int64_t b = (2 + (rand() % 2)) %2;
	b = 0;
	int64_t rArr[k];

	for(int i = 0; i < k; i++){
		rArr[i] = (3 + (rand() % 3)) %3;
		rArr[i] = 0;
	}

	//Function tables
	//table1 = [rArr[0]]*(2^l)
	int64_t table1[(int64_t)(pow(2, l[0]))];
	for(int i = 0; i < sizeof(table1)/sizeof(table1[0]); i++){
		table1[i] = rArr[0];
	}
	//int64_t bTable = [b]*(2^l)
	int64_t bTable[(int64_t)(pow(2, l[0]))];
	for(int i = 0; i < sizeof(bTable)/sizeof(bTable[0]); i++){
		bTable[i] = b;
	}
	//sofsoft = [ [[]]*(k-1) ,  [[]]*(k-1)]
	int64_t sofsoft[2][k-1][(int64_t)(pow(2,l[0]))];
	for(int i = 0; i < k-1; i++){
		//sofsoft[0][i] = [rArr[i+1]]*(2^l)
		//sofsoft[1][i] = [rArr[i+1]]*(2^l)
		for(int j = 0; j < (int64_t)(pow(2,l[0])); j++){
			sofsoft[0][i][j] = rArr[i+1];
			sofsoft[1][i][j] = rArr[i+1];
		}

	}

	string Unk0 = "";
	string Unk1 = "";
	int64_t end1 = 0;
	int64_t end2 = (int64_t)(p/2);

	//Begin filling the function tables

	//first block
	for(int i = 0; i < (int64_t)(pow(2,l[0])); i++){
		//const int64_t ll = l[0];
		string inp = bitset<l[0]>(i).to_string();
		
		//inp = "0"*(l-len(bin(i)[2:])) + bin(i)[2:]
		int64_t res = UNK;
		//minstr = inp + "0"*(n-len(inp))
		string minstr = inp + bitset<n-l[0]>(0).to_string();
		//minstr = minstr + "\0";
		int64_t minv = stoull(minstr, nullptr, 2);
		
		//maxstr = inp + "1"*(n-len(inp))
		string maxstr = inp;
		while (maxstr.length() < n){
			maxstr = maxstr + "1";
		}
		//maxv = min(int64_t(maxstr, 2), p-1)
		int64_t maxv = stoull(maxstr, nullptr, 2);
		int64_t minr = NEG;
		int64_t maxr = NEG;
		////////////////////////////////////////////////////
		//minv = int64_t(F(minv) - r)
		minv = (p + ((minv - r) % p)) %p;
		//maxv = int64_t(F(maxv) - r)
		maxv = (p + ((maxv - r) % p)) %p;
		
		if (minv >= end1 && minv < end2){
			minr = POS;
		}
		if (maxv >= end1 && maxv < end2){
			maxr = POS;
		}
		
		if (minr == NEG && maxr == POS){
			Unk0 = inp;
			res = UNK;
		}
		if (minr == POS && maxr == NEG){
			Unk1 = inp;
			bTable[i] = 1-b;
			res = UNK;
		}
		
		if (minr == POS && maxr == POS){
			res = POS;
		}
		if (minr == NEG && maxr == NEG){
			res = NEG;
		}
		table1[i] = (3 + ((table1[i] + res) % 3)) %3;
		
		//cout << "i: " << i << "  inp: " << inp << "\n";
		//cout << "minstr: " << minstr << "  ";
		//cout << "maxstr: " << maxstr << "\n";
		//cout << "minv: " << minv << "  ";
		//cout << "maxv: " << maxv << "\n";
	}

	if (Unk0 == ""){
		Unk0 = Unk1;
	}
	if (Unk1 == ""){
		Unk1 = Unk0;
	}


	//all other blocks
	string newUnk0 = "";
	string newUnk1 = "";
	for(int i = 0; i < k-1; i++){
		Unk0 = Unk0 + newUnk0;
		newUnk0 = "";
		const int64_t llone = l[0];
		const int64_t lltwo = l[k-1];
		int64_t llen = 0;
		for(int c = 0; c < i+1; c++){
			llen = llen + l[c];
		}
		for(int j = 0; j < (int64_t)(pow(2,l[i+1])); j++){
			//string inp = "0"*(l-len(bin(j)[2:])) + bin(j)[2:]
			string inp = "";
			if(l[i+1] == llone){
				inp = bitset<llone>(j).to_string();
			}
			else{
				inp = bitset<lltwo>(j).to_string();
			}
						
			//Unk0
			if (Unk0.length() < llen){
				break;
			}
			//Function to determine results
			int64_t res = UNK;
			string minstr = Unk0 + inp;
			for(int c = 0; c < (n-(Unk0+inp).length()); c++){
				minstr = minstr + "0";
			}
			//minstr = minstr + "\0";
			int64_t minv = stoull(minstr, nullptr, 2);

			string maxstr = Unk0 + inp;
			while (maxstr.length() < n){
				maxstr = maxstr + "1";
			}
			//maxstr = maxstr + "\0";
			int64_t maxv = stoull(maxstr, nullptr, 2);
			
			//cout << minv << "\n";
			minv = (p + ((minv - r) % p)) %p;
			maxv = (p + ((maxv - r) % p)) %p;
			
			int64_t minr = NEG;
			int64_t maxr = NEG;
			if (minv >= end1 && minv < end2){
				minr = POS;
			}
			if (maxv >= end1 && maxv < end2){
				maxr = POS;
			}
			if (minr == POS && maxr == POS){
				res = POS;
			}
			if (minr == NEG && maxr == NEG){
				res = NEG;
			}
			
			//cout << "res: " << res << "\n";
			//cout << "minr: " << minr << "\n";
			//cout << "maxr: " << maxr << "\n";

			//cout << "i: " << i << "  j: " << j << "  inp: " << inp << "\n";
			//cout << "minstr: " << minstr << "  ";
			//cout << "maxstr: " << maxstr << "\n";
			//cout << "minv: " << minv << "  ";
			//cout << "maxv: " << maxv << "\n";
			
			sofsoft[b][i][j] = (3 + ((sofsoft[b][i][j] + res) % 3)) %3;
			if (res == UNK){
				newUnk0 = inp;
			}
		}
		
		Unk1 = Unk1 + newUnk1;
		newUnk1 = "";
		for(int j = 0; j < (int64_t)(pow(2,l[i+1])); j++){
			//string inp = "0"*(l-len(bin(j)[2:])) + bin(j)[2:]
			string inp = "";
			if(l[i+1] == llone){
				inp = bitset<llone>(j).to_string();
			}
			else{
				inp = bitset<lltwo>(j).to_string();
			}
			//string inp = bitset<ll>(j).to_string();
			//Unk1
			if (Unk1.length() < llen){
				break;
			}
			//Function to determine results
			int64_t res = UNK;
			string minstr = Unk1 + inp;
			for(int c = 0; c < (n-(Unk1+inp).length()); c++){
				minstr = minstr + "0";
			}
			//minstr = minstr + "\0";
			int64_t minv = stoull(minstr, nullptr, 2);

			string maxstr = Unk1 + inp;
			while (maxstr.length() < n){
				maxstr = maxstr + "1";
			}
			//maxstr = maxstr + "\0";
			int64_t maxv = stoull(maxstr, nullptr, 2);
			
			minv = (p + ((minv - r) % p)) %p;
			maxv = (p + ((maxv - r) % p)) %p;
			
			int64_t minr = NEG;
			int64_t maxr = NEG;
			if (minv >= end1 && minv < end2){
				minr = POS;
			}
			if (maxv >= end1 && maxv < end2){
				maxr = POS;
			}
			if (minr == POS && maxr == POS){
				res = POS;
			}
			if (minr == NEG && maxr == NEG){
				res = NEG;
			}
			
			
			
			sofsoft[1-b][i][j] = (3 + ((sofsoft[1-b][i][j] + res) % 3)) %3;
			
			if (res == UNK){
				newUnk1 = inp;
			}
		}
	}


	int64_t recTable[(int64_t)(pow(3,k))];
	for(int i = 0; i < sizeof(recTable)/sizeof(recTable[0]); i++){
		recTable[i] = 0;
	}

	for(int i = 0; i < k; i++){
		string negstr = "";
		for(int j = 0; j < i; j++){
			negstr = negstr + to_string((3 + ((UNK - rArr[j]) % 3)) %3);
		}
		negstr = negstr + to_string((3 + ((NEG - rArr[i]) % 3)) %3);
		
		for(int j = 0; j < (int64_t)(pow(3,(k-1-i))); j++){
			string jst = "";
			int64_t t = j;
			while(t > 0){
				jst = to_string(t%3) + jst;
				t = t/3;
			}
			string tailstr = "";
			for(int c = 0; c < k-1-i-(jst).length(); c++){
				tailstr = "0" + tailstr;
			}
			tailstr = tailstr + jst;
			//recTable[stoull(negstr + tailstr + "\0", nullptr, 3)] = 1;
			recTable[stoull(negstr + tailstr, nullptr, 3)] = 1;
		}
	}


	//Secret Sharing the Tables
	int64_t bTable_1[(int64_t)(pow(2,l[0]))];
	int64_t bTable_2[(int64_t)(pow(2,l[0]))];
	for(int i = 0; i < (int64_t)(pow(2,l[0])); i++){
		int64_t a = (p2+ (rand() % p2)) %p2;
		bTable_1[i] = a;
		bTable_2[i] = (p2+((bTable[i] - a) % p2)) %p2;
	}

	int64_t table1_1[(int64_t)(pow(2,l[0]))];
	int64_t table1_2[(int64_t)(pow(2,l[0]))];
	for(int i = 0; i < (int64_t)(pow(2,l[0])); i++){
		int64_t a = (p3 + (rand() % p3)) %p3;
		table1_1[i] = a;
		table1_2[i] = (p3 + ((table1[i] - a) % p3)) %p3;
	}

	int64_t sofsoft_1[2][k-1][(int64_t)(pow(2,l[0]))];
	int64_t sofsoft_2[2][k-1][(int64_t)(pow(2,l[0]))];
	for(int i = 0; i < k-1; i++){
		for(int j = 0; j < (int64_t)(pow(2,l[i+1])); j++){
			int64_t a = (p3 + (rand() % p3)) %p3;
			sofsoft_1[0][i][j] = a;
			sofsoft_2[0][i][j] = (p3 + ((sofsoft[0][i][j] - a) % p3)) %p3;
			a = (p3 + (rand() % p3)) %p3;
			sofsoft_1[1][i][j] = a;
			sofsoft_2[1][i][j] = (p3 + ((sofsoft[1][i][j] - a) % p3)) %p3;
		}
	}

	int64_t recTable_0[(int64_t)(pow(3,k))];
	for(int i = 0; i < (int64_t)(pow(3,k)); i++){
		recTable_0[i] = (2 + ((recTable[i] - z_1 - z_3) % 2)) %2;
	}
	
	int64_t recTable_1[(int64_t)(pow(3,k))];
	int64_t recTable_2[(int64_t)(pow(3,k))];
	for(int i = 0; i < (int64_t)(pow(3,k)); i++){
		int64_t a = (p2+ (rand() % p2)) %p2;
		recTable_1[i] = a;
		recTable_2[i] = (p2 + ((recTable_0[i] - a) % p2)) %p2;
	}

	int64_t r_1 = (p + (rand() % p)) %p;
	int64_t r_2 = (p + ((r - r_1) % p)) %p;
}
}











int main() {
	auto starttime = chrono::high_resolution_clock::now();
	int total = 8000;
	//int howmany = total/8;
	int howmany = 1000;
	
	thread t1(f, howmany);
	thread t2(f, howmany);
	thread t3(f, howmany);
	thread t4(f, howmany);
	thread t5(f, howmany);
	thread t6(f, howmany);
	thread t7(f, howmany);
	thread t8(f, howmany);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	
	auto endtime1 = chrono::high_resolution_clock::now();
	auto duration1 = chrono::duration_cast<chrono::seconds>(endtime1 - starttime);
	auto duration2 = chrono::duration_cast<chrono::minutes>(endtime1 - starttime);
	cout << duration1.count() << "seconds\n";
	cout << duration2.count() << "minutes\n";

	return 0;
}
