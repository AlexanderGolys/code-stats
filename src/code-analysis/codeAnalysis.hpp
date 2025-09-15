#pragma once
#include "isbell.hpp"



enum CppExtension {
	CPP, HPP, H, TPP, C
};


CppExtension extensionFromString(const string &extStr);
bool isHeaderExtension(CppExtension ext);
bool isCompatibleWithC(CppExtension ext2);
bool isCppExtension(const string &extStr);


class CppCodeFile : public CodeFileDescriptor {
	CppExtension ext;
	bool isHeader;
	bool isCCompatible;

public:
	explicit CppCodeFile(const Path &path);

	string extension() const;
	CppExtension getCppExtension() const;
	bool header() const;
	bool cCompatible() const;
	string filename() const;
};



class CppProject {
	DirectoryDescriptor root;

public:
	explicit CppProject(const Path &rootPath);

	static vector<CppCodeFile> listAllCppFiles(const vector<DirectoryDescriptor> &excludeDirs, const DirectoryDescriptor &subdir);
	vector<CppCodeFile> listAllCppFiles(const vector<DirectoryDescriptor> &excludeDirs) const;
};

class CppCode {
	CppExtension ext;
	string code;

public:
	explicit CppCode(const string &code, CppExtension ext) : code(code), ext(ext) {}

};
