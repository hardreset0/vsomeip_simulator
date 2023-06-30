


#ifndef _IFILE_READER_
#define _IFILE_READER_

#include <utility>
#include <cstdio>
#include <string>

class IFileHandler
{
    public:
    //ISSUE: Coupled to cstdio library.
    virtual bool openFile(const std::string & path) = 0;
    virtual const std::string getData() const = 0;

};




#endif
