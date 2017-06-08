#pragma once
#include "Cell.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	Chunk::Chunk(int initX, int initY);
	int chunkSize = 16;
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	
private:
	int x = 0;
	int y = 0;
	
	
	std::string chunkID;
};

