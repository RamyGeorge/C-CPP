#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstddef>
#include <new>
#include <string>
#include <memory>
#include <fstream>
#include <vector>

class Resource {
public:
    virtual void acquire() = 0; // = 0 entails a pure virtual function to be overriden by derived classes
    virtual void release() = 0;
    virtual std::string getname() const = 0;

    virtual ~Resource() = default;
};

class FileResource : public Resource {
public:
    std::string path;
    std::unique_ptr<std::fstream> upf;

    FileResource(std::string& path);

    void acquire() override;
    void release() override;
    std::fstream& getStream();
    std::string getname() const  override;
};

struct MemoryDeleter {
    std::size_t alignment;

    void operator()(void* ptr) const noexcept {
        ::operator delete(ptr, std::align_val_t{alignment}); //Needed to keep alignment in mind
    }
};

class MemoryResource : public Resource {
    public:
		std::unique_ptr<void,MemoryDeleter> upm; // Store a unqiue pointer pointing at result of mem allocation via ::operator new
		MemoryResource(std::size_t, std::size_t);

		void acquire() override;
		void release() override;
        std::string getname() const override;
        void* getMemBlock();
    private:
        std::size_t alignment;
        std::size_t bytes;
};


class ResourceManager {
    public:
        ResourceManager();
        void AddResource(std::string& path);
        void AddResource(std::size_t, std::size_t);
        void acquireAll();
        void releaseAll();
        Resource& getResource(std::size_t);
    private:
        std::vector<std::unique_ptr<Resource>> Resources;

};


#endif
