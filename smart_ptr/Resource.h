#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <memory>
#include <fstream>

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
    std::string getname() const  override;
};

#endif
