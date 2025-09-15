#pragma once
#include "filesUtils.hpp"



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
	string getExtension() const;
	CppExtension getCppExtension() const;
	bool header() const;
	bool cCompatible() const;
	string filename() const;
};


struct CppMacro {
	string identifier;
	vector<string> parameters;
	bool dots;
	string replacement;

	CppMacro(const string &id, const vector<string> &params, const string &rep, bool dots = false);
};


class CppProject {
	DirectoryDescriptor root;

public:
	explicit CppProject(const Path &rootPath);

	static vector<CppCodeFile> listAllCppFiles(const vector<DirectoryDescriptor> &excludeDirs, const DirectoryDescriptor &subdir);
	vector<CppCodeFile> listAllCppFiles(const vector<DirectoryDescriptor> &excludeDirs) const;
};
