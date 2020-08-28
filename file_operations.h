#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <vector>

namespace file_operations {

    void delete_transaction(int m, int y, std::vector<std::string>);

    void delete_category(std::string filename, std::vector<std::string>);

    std::vector<std::string> readfile(std::string filename);

    void writefile(std::string filename, std::vector<std::string>);

}

#endif // FILE_OPERATIONS_H
