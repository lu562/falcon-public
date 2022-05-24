
#pragma once
#include "Precompute.h"

/**
 * helper function to read csv files
 */

std::vector<std::pair<std::string, std::vector<myType>>> read_csv(std::string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<myType>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    myType val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){
            
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, std::vector<myType> {}});
        }
    }

    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);
        
        // Keep track of the current column index
        int colIdx = 0;
        
        // Extract each integer
        while(ss >> val){
            
            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);
            
            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();
            
            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}


Precompute::Precompute():blocks_with_bit_0(k - 1), blocks_with_bit_1(k - 1),blocks_with_bit_0_redundant(k - 1), blocks_with_bit_1_redundant(k - 1)
{
    //initialize();
}
Precompute::~Precompute(){}
void Precompute::initialize(){
	// load function table
    //offline phase
    std::string block_1_file_name;
    std::string tables_file_name;
    std::string config_file_name;
    std::string combination_file_name;

    if (partyNum == PARTY_A) {
        block_1_file_name = "block1_p1_001.csv";
        tables_file_name = "tables_p1_001.csv";
        config_file_name = "config_p1_001.csv";
        combination_file_name = "rectable_p1_001.csv";

    } else if (partyNum == PARTY_B) { 
        block_1_file_name = "block1_p2_001.csv";
        tables_file_name = "tables_p2_001.csv";
        config_file_name = "config_p2_001.csv";
        combination_file_name = "rectable_p2_001.csv";
    } else {
        block_1_file_name = "block1_p3_001.csv";
        tables_file_name = "tables_p3_001.csv";
        config_file_name = "config_p3_001.csv";
        combination_file_name = "rectable_p3_001.csv";
    }
    // if (partyNum == PARTY_C) {
    //     // offline party only need to store the result pairs.
    //     std::vector<std::pair<std::string, std::vector<myType>>> config_csv = read_csv(config_file_name);
    //     for (std::pair<std::string, std::vector<myType>> i: config_csv) {
    //         if (i.first.compare("z_1") == 0) {
    //             z_1 = i.second[0];
    //         } else if (i.first.compare("z_3") == 0) {
    //             z_3 = i.second[0];
    //         }
    //     }
    //     return;
    // }

    // read config
    std::vector<std::pair<std::string, std::vector<myType>>> config_csv = read_csv(config_file_name);
    for (std::pair<std::string, std::vector<myType>> i: config_csv) {
        if (i.first.compare("r_1") == 0) {
            r_1 = i.second[0];
        } else if (i.first.compare("r_2") == 0) {
            r_2 = i.second[0];
        } 
    }

    // read the first block
    std::vector<std::pair<std::string, std::vector<myType>>> first_block_csv = read_csv(block_1_file_name);
    int block_size = first_block_csv[0].second.size();
    for (int i = 0; i < block_size; i++) {
        block_1[first_block_csv[0].second[i]] = first_block_csv[3].second[i];
        block_1_redundant[first_block_csv[0].second[i]] = first_block_csv[4].second[i];
        bit_b_list[first_block_csv[0].second[i]] = first_block_csv[1].second[i];
        bit_b_list[first_block_csv[0].second[i]] = first_block_csv[2].second[i];
    }
    
    // read the following blocks
    std::vector<std::pair<std::string, std::vector<myType>>> tables_csv = read_csv(tables_file_name);
    int tables_size = tables_csv[0].second.size();
    for (int i = 0; i < tables_size; i++) {
        if (tables_csv[0].second[i] == 0) {

            blocks_with_bit_0[tables_csv[1].second[i] - 1][tables_csv[2].second[i]] = tables_csv[3].second[i];
            blocks_with_bit_0_redundant[tables_csv[1].second[i] - 1][tables_csv[2].second[i]] = tables_csv[4].second[i];
        } else {
            blocks_with_bit_1[tables_csv[1].second[i] - 1][tables_csv[2].second[i]] = tables_csv[3].second[i];
            blocks_with_bit_1_redundant[tables_csv[1].second[i] - 1][tables_csv[2].second[i]] = tables_csv[4].second[i];
        }
    }

    // read the combination table
    std::vector<std::pair<std::string, std::vector<myType>>> combination_csv = read_csv(combination_file_name);
    int table_size = combination_csv[0].second.size();
    for (int i = 0; i < table_size; i++) {
        std::string string_input = std::to_string(combination_csv[0].second[i]);
        if (string_input.size() < k) {
            std::string prefix_0(k - string_input.size(), '0');
            string_input = prefix_0 + string_input;
        }
        combination_table[string_input] = combination_csv[1].second[i];
        combination_table_redundant[string_input] = combination_csv[2].second[i];
    }
}

// Currently, r = 3 and rPrime = 3 * 2^d
// TODO: ReLU produces a bug with this. Why? funcRELU does not even call getDividedShares()
void Precompute::getDividedShares(RSSVectorMyType &r, RSSVectorMyType &rPrime, int d, size_t size)
{
	assert(r.size() == size && "r.size is incorrect");
	assert(rPrime.size() == size && "rPrime.size is incorrect");

	for (int i = 0; i < size; ++i)
	{
		r[i].first = 0;
		r[i].second = 0;
		rPrime[i].first = 0;
		rPrime[i].second = 0;
		// r[i].first = 1;
		// r[i].second = 1;
		// rPrime[i].first = d;
		// rPrime[i].second = d;		
	}
}

void Precompute::getRandomBitShares(RSSVectorSmallType &a, size_t size)
{
	assert(a.size() == size && "size mismatch for getRandomBitShares");
	for(auto &it : a)
		it = std::make_pair(0,0);
}


//m_0 is random shares of 0, m_1 is random shares of 1 in RSSMyType. 
//This function generates random bits c and corresponding RSSMyType values m_c
void Precompute::getSelectorBitShares(RSSVectorSmallType &c, RSSVectorMyType &m_c, size_t size)
{
	assert(c.size() == size && "size mismatch for getSelectorBitShares");
	assert(m_c.size() == size && "size mismatch for getSelectorBitShares");
	for(auto &it : c)
		it = std::make_pair(0,0);

	for(auto &it : m_c)
		it = std::make_pair(0,0);
}

//Shares of random r, shares of bits of that, and shares of wrap3 of that.
void Precompute::getShareConvertObjects(RSSVectorMyType &r, RSSVectorSmallType &shares_r, 
										RSSVectorSmallType &alpha, size_t size)
{
	assert(shares_r.size() == size*BIT_SIZE && "getShareConvertObjects size mismatch");
	for(auto &it : r)
		it = std::make_pair(0,0);

	for(auto &it : shares_r)
		it = std::make_pair(0,0);

	for(auto &it : alpha)
		it = std::make_pair(0,0);
}


//Triplet verification myType
void Precompute::getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, 
						size_t rows, size_t common_dim, size_t columns)
{
	assert(((a.size() == rows*common_dim) 
		and (b.size() == common_dim*columns) 
		and (c.size() == rows*columns)) && "getTriplet size mismatch");
	
	for(auto &it : a)
		it = std::make_pair(0,0);

	for(auto &it : b)
		it = std::make_pair(0,0);

	for(auto &it : c)
		it = std::make_pair(0,0);
}

//Triplet verification myType
void Precompute::getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, size_t size)
{
	assert(((a.size() == size) and (b.size() == size) and (c.size() == size)) && "getTriplet size mismatch");
	
	for(auto &it : a)
		it = std::make_pair(0,0);

	for(auto &it : b)
		it = std::make_pair(0,0);

	for(auto &it : c)
		it = std::make_pair(0,0);
}

//Triplet verification smallType
void Precompute::getTriplets(RSSVectorSmallType &a, RSSVectorSmallType &b, RSSVectorSmallType &c, size_t size)
{
	assert(((a.size() == size) and (b.size() == size) and (c.size() == size)) && "getTriplet size mismatch");
	
	for(auto &it : a)
		it = std::make_pair(0,0);

	for(auto &it : b)
		it = std::make_pair(0,0);

	for(auto &it : c)
		it = std::make_pair(0,0);
}



void Precompute::getBlock1(std::unordered_map<myType, myType> &a)
{
    a = block_1;
}

void Precompute::getBitBList(std::unordered_map<myType, myType> &a)
{
    a = bit_b_list;
}

void Precompute::getBlockWithBit0(std::vector<std::unordered_map<myType, myType>> &a)
{
    a = blocks_with_bit_0;
}


void Precompute::getBlockWithBit1(std::vector<std::unordered_map<myType, myType>> &a)
{
    a = blocks_with_bit_1;
}

void Precompute::getCombinationTable(std::unordered_map<std::string, myType> &a)
{
    a = combination_table;
}