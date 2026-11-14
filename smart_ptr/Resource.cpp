#include "Resource.h"
#include <stdexcept>
#include <utility>

FileResource::FileResource(std::string& fpath){
	this->path = fpath;
};

void FileResource::acquire(){
	if (!this->upf) {
		auto upfInternal = std::make_unique<std::fstream>(path);
		// forward path to make_unique and get a upf and open file
		if (!upfInternal->is_open()) { 
			upf.reset(); // delete the source pointed to by upf and upf = nullptr 
			throw std::runtime_error("File opening failed!.");
		};
		this->upf = std::move(upfInternal);
		/* The entire premise of unique_ptr is the exclusivitiy in their ownership. a naive this->upf = upfInternal would nullify the entire purpose of smart_ptr. A copy for exclusive ownership meaning two pointers thinking they own the resource exclusivly. std::move is needed here to move ownership ( upfInternal is deleted ) */
		return;
	}
	else return;

};

void FileResource::release(){
	this->upf.reset();
	return;
};

std::string FileResource::getname() const {
	std::string ret = "FileResource";
	return ret;
};
