#include "codeAnalysis.hpp"

CppExtension extensionFromString(const string &extStr) {
	return
			extStr == ".cpp" ? CPP :
			extStr == ".hpp" ? HPP :
			extStr == ".h" ? H :
			extStr == ".c" ? C :
			extStr == ".tpp" ? TPP :

			throw ValueError("Unknown C++ file extension: " + extStr, __FILE__, __LINE__);
}

bool isHeaderExtension(CppExtension ext) {
	return ext == HPP || ext == H || ext == TPP;
}

bool isCompatibleWithC(CppExtension ext2) {
	return ext2 == H || ext2 == C;
}

bool isCppExtension(const string &extStr) {
	return extStr == ".cpp" || extStr == ".hpp" || extStr == ".h" || extStr == ".tpp" || extStr == ".c";
}

CppCodeFile::CppCodeFile(const Path &path)
: CodeFileDescriptor(path, false)
{
	auto extStr = this->extension();
	ext = extensionFromString(extStr);
	isHeader = isHeaderExtension(ext);
	isCCompatible = isCompatibleWithC(ext);
}

string CppCodeFile::getExtension() const {
	return extension();
}

CppExtension CppCodeFile::getCppExtension() const {
	return ext;
}

bool CppCodeFile::header() const {
	return isHeader;
}

bool CppCodeFile::cCompatible() const {
	return isCCompatible;
}

string CppCodeFile::filename() const {
	return getFilename();
}


CppProject::CppProject(const Path &rootPath)
: root(rootPath)
{
	if (!root.exists())
		throw FileSystemError("Project root directory " + rootPath.to_str() + " does not exist.", __FILE__, __LINE__);
}

vector<CppCodeFile> CppProject::listAllCppFiles(const vector<DirectoryDescriptor> &excludeDirs, const DirectoryDescriptor &subdir) {
	vector<CppCodeFile> files;

	for (auto &excl : excludeDirs)
		if (excl == subdir)
			return files;

	auto allFiles = subdir.listFiles();

	for (const auto &file : allFiles)
		if (isCppExtension(file.getExtension()))
			files.emplace_back(file.getPath());

	auto allSubdirs = subdir.listDirectories();

	for (const auto &dir : allSubdirs)
		addAll(files, listAllCppFiles(excludeDirs, dir));

	return files;
}

vector<CppCodeFile> CppProject::listAllCppFiles(const vector<DirectoryDescriptor> &excludeDirs) const {
	return listAllCppFiles(excludeDirs, root);
}
