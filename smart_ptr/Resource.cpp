#include "Resource.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
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
		/* The entire premise of unique_ptr is the exclusivitiy in their ownership. a naive this->upf = upfInternal would nullify the entire purpose of smart_ptr.
		 A copy for exclusive ownership meaning two pointers thinking they own the resource exclusivly. std::move is needed here to move ownership ( upfInternal is deleted ) */
		return;
	}
	else return;

};

void FileResource::release(){
	this->upf.reset();
	return;
};

std::fstream& FileResource::getStream(){
	return *upf;
}

std::string FileResource::getname() const {
	std::string ret = "FileResource";
	return ret;
};

MemoryResource::MemoryResource(std::size_t b, std::size_t a): 
	  upm(nullptr, MemoryDeleter{a}),
      alignment(a),
      bytes(b) {};

void MemoryResource::acquire(){
	if (!upm) {
		upm.reset(::operator new(this->bytes, std::align_val_t(this->alignment)));
	}
};

void MemoryResource::release(){
	if (upm) {
		upm.reset();
	}
}


void* MemoryResource::getMemBlock(){
	return upm.get();
}

std::string MemoryResource::getname() const {
	return ("Allocated memory");
}


ResourceManager::ResourceManager(): Resources() {};


void ResourceManager::AddResource(std::string& path){
	// we cannot directly add a filesource because the std::vector is of unique_ptr<resource>
	// instead we store a unique pointer to a created file source and insert it into that list
	this->Resources.push_back(std::make_unique<FileResource>(path));
}

void ResourceManager::AddResource(std::size_t b, std::size_t a) {
	this->Resources.push_back((std::make_unique<MemoryResource>(b,a)));
}

void ResourceManager::acquireAll() {
	for (std::size_t rsrc = 0; rsrc < this->Resources.size(); ++rsrc) {
		this->Resources[rsrc]->acquire();
	}
}

void ResourceManager::releaseAll(){
	for (std::size_t rsrc = 0; rsrc < this->Resources.size(); ++rsrc) {
		this->Resources[rsrc]->release();
	}
}

Resource& ResourceManager::getResource(std::size_t idx) {
    return *Resources.at(idx);
}