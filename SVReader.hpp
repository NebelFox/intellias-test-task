#ifndef INTELLIAS_TEST_TASK_SVREADER_HPP
#define INTELLIAS_TEST_TASK_SVREADER_HPP


#include <iostream>
#include <string>
#include <vector>

#include "Table.hpp"

using std::istream;
using std::string;
using std::vector;
using std::pair;


class SVReader
{
public:

private:
    const char _separator;
    const char _delimiter;

public:
    explicit SVReader(const char separator = ',',
                      const char delimiter = '\n') : _separator(separator), _delimiter(delimiter)
    {}

    Table<string> read(istream& stream) const
    {
        vector<string> columns = readRow(stream);
        Table<string> table(columns);
        while(stream.good())
            table.append(readRow(stream));

        return table;
    }

private:
    vector<string> readRow(istream& stream) const
    {
        string line;
        std::getline(stream, line, _delimiter);
        return split(line);
    }

    vector<string> split(const string& line) const
    {
        vector<string> values;
        size_t begin = 0, length = 0;
        while (begin + length < line.length())
        {
            while (begin + length < line.length() && line[begin + length] != _separator)
                ++length;
            values.push_back(line.substr(begin, length));
            begin += length + 1;
            length = 0;
        }
        return values;
    }
};


#endif //INTELLIAS_TEST_TASK_SVREADER_HPP
