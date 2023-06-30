


#include "FileHandler.hpp"
#include <iostream>
#include <streambuf>
#include <utility>
#include <iostream>
#include <iterator>
#include <sstream>

bool FileHandler::openFile(const std::string & path)
{
    std::cout << "Try to open file: " << path << std::endl;
    
    if (this->m_file.is_open()) this->m_file.close();

    // open a new file.
    this->m_file.open(path);

    return this->m_file.is_open();
}

const std::string FileHandler::getData() const
{
    // data.
    std::ostringstream oss;
    oss << this->m_file.rdbuf();
    std::string data  = oss.str();
    return data;
}

FileHandler::~FileHandler()
{
    if (this->m_file.is_open()) {
        this->m_file.close();
    }
}