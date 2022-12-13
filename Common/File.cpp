#include"File.h"
#include<fstream>
#include<iostream>
using namespace std;

File::File() 
	:mWidth(-1)
	,mHeight(1)
	,mFileSize(0)
{
	
}


const char* File::LoadFile(const char* fileName) {
	ifstream inputFile(fileName, ifstream::binary);
	inputFile.seekg(0, ifstream::end);
	mFileSize = static_cast<int>(inputFile.tellg());
	inputFile.seekg(0, ifstream::beg);
	char* stageData = new char[mFileSize];
	inputFile.read(stageData, mFileSize);

	int i = 0;
	while (stageData[i] != '\0') {
		if (stageData[i] == '\n') {
			mHeight++;
		}
		i++;
	}
	i = 0;
	while (stageData[i] != '\n') {
		mWidth++;
		i++;
	}

	return stageData;
}

void File::SaveFile() {

}