#ifndef INTELLIAS_TEST_TASK_SVWRITER_HPP
#define INTELLIAS_TEST_TASK_SVWRITER_HPP


#include <iostream>
#include <string>
#include <vector>

#include "Table.hpp"
#include "Utils.hpp"

using std::ostream;
using std::string;
using std::vector;
using std::pair;


class SVWriter
{
private:
    const char _separator;
    const char _delimiter;

public:
    explicit SVWriter(const char separator = ',',
                      const char delimiter = '\n') : _separator(separator), _delimiter(delimiter)
    {}

    template<typename T>
    void write(const Table<T>& table, ostream& stream) const
    {
        join(stream,
             _separator,
             table.getColumnNames());
        stream << _delimiter;

        const size_t height = table.height();
        for (size_t i = 0; i < height; ++i)
        {
            join(stream,
                 _separator,
                 table.getRow(i));
            stream << _delimiter;
        }

    }
};


#endif //INTELLIAS_TEST_TASK_SVWRITER_HPP
