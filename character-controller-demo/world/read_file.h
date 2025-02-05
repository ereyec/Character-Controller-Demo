#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <iostream>
#include <vector>

#include "../common.h"

const int WORLD_SIZE  = 784;

int readFile(Common& common, const char* filename){

FILE* file = NULL;
file = fopen(filename, "r");
if(file == NULL){
	std::cout << "Could not open " << filename << std::endl;
	std::cout << "Please check that the file name is correct and that the file exists." << std::endl;
	return -1;
}

while(!feof(file)){ //use fscanf(...) == 1 instead of !feof(file)?
	char num[4];
	fscanf(file, "%s ", num); //buffer overflow risk!!!
	common.worldHeightmap.push_back(std::atoi(num));	
}

fclose(file);

//assert that the vector size is 
if(common.worldHeightmap.size() != 784) {
	std::cout << "Vector size does not match world dimensions." << std::endl;
	return -1;
}

return 0;

}
#endif