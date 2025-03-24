#ifndef APPLICATION_FILE_HPP
#define APPLICATION_FILE_HPP

#include <fstream>
#include <vector>
#include <memory>

namespace raid
{
    class File final
    {

    public:
        explicit File();
        virtual ~File();
        void write_csv(const std::string &path);

    public:
        using SharedPtr = std::shared_ptr<File>;

    };
}

#endif // APPLICATION_FILE_HPP
