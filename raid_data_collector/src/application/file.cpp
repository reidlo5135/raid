#include "application/file.hpp"

using namespace raid;

File::File()
{

}

File::~File()
{

}

void
File::write_csv(const std::string &path)
{
    std::ofstream file(path, std::ios::app);
    file.close();
}

