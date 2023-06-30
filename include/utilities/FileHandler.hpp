


#ifndef _FILE_HANDLER_
#define _FILE_HANDLER_


#include "IFileHandler.hpp"
#include <fstream>


class FileHandler : public IFileHandler
{
    public:
    FileHandler() = default;
    bool openFile(const std::string & path) override;
    const std::string getData() const override;
    ~FileHandler();

    private:
    std::ifstream m_file {};
};



#endif