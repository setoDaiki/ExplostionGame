#pragma once

class File {
public:
	File();
	const char* LoadFile(const char* fileName);
	void SaveFile();
	inline int GetSize() { return mFileSize; }
	inline int GetWidth() { return mWidth; }
	inline int GetHeight() { return mHeight; }
private:
	int mFileSize;
	int mHeight;
	int mWidth;
};