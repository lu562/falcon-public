
#ifndef PRECOMPUTE_H
#define PRECOMPUTE_H

#pragma once
#include "globals.h"
#include <sstream> // std::stringstream
#include <iostream>
#include <fstream>

extern int partyNum;
const int k = 4;
const int l = 8;

class Precompute
{
private:


public:
	// offline vars for lTZ()
	myType r_raw;
	myType r_1;
	myType r_2;
    std::unordered_map<myType, myType> block_1;
    std::unordered_map<myType, myType> block_1_redundant;
    std::unordered_map<myType, myType> bit_b_list;
    std::unordered_map<myType, myType> bit_b_list_redundant;
    std::vector<std::unordered_map<myType, myType>> blocks_with_bit_0;
    std::vector<std::unordered_map<myType, myType>> blocks_with_bit_1;	
    std::vector<std::unordered_map<myType, myType>> blocks_with_bit_0_redundant;
    std::vector<std::unordered_map<myType, myType>> blocks_with_bit_1_redundant;	
    std::unordered_map<std::string, myType> combination_table;
    std::unordered_map<std::string, myType> combination_table_redundant;
	Precompute();
	~Precompute();

	void initialize();
	void getDividedShares(RSSVectorMyType &r, RSSVectorMyType &rPrime, int d, size_t size);
	void getRandomBitShares(RSSVectorSmallType &a, size_t size);
	void getSelectorBitShares(RSSVectorSmallType &c, RSSVectorMyType &m_c, size_t size);
	void getShareConvertObjects(RSSVectorMyType &r, RSSVectorSmallType &shares_r, RSSVectorSmallType &alpha, size_t size);
	void getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, 
					size_t rows, size_t common_dim, size_t columns);
	void getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, size_t size);
	void getTriplets(RSSVectorSmallType &a, RSSVectorSmallType &b, RSSVectorSmallType &c, size_t size);
	myType getRraw();
	myType getZ_1();
	myType getZ_3();
	void getBlock1(std::unordered_map<myType, myType> &a);
	void getBitBList(std::unordered_map<myType, myType> &a);
	void getBlockWithBit0(std::vector<std::unordered_map<myType, myType>> &a);
	void getBlockWithBit1(std::vector<std::unordered_map<myType, myType>> &a);
	void getCombinationTable(std::unordered_map<std::string, myType> &a);
};


#endif