#ifndef INTELLIAS_TEST_TASK_TABLE_HPP
#define INTELLIAS_TEST_TASK_TABLE_HPP


#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::pair;
using std::map;


template <typename T>
class Table
{
public:
    using Row = vector<T>;
//    using Iterator = vector<vector<T>>::const_iterator;

private:
    vector<Row> _content;
    map<string, size_t> _columnToIndex;
    vector<string> _indexToColumn;

public:
    Table(const vector<string>& columns)
    {
        _indexToColumn = columns;
        for(size_t i=columns.size(); i; --i)
            _columnToIndex[columns[i-1]] = i-1;
    }

    size_t height() const
    {
        return _content.size();
    }

    size_t width() const
    {
        return _columnToIndex.size();
    }

    size_t size() const
    {
        return height() * width();
    }

    string getColumnName(const size_t column) const
    {
        return _indexToColumn[column];
    }

    const vector<string>& getColumnNames() const
    {
        return _indexToColumn;
    }

    size_t getColumnIndex(const string& column) const
    {
        return _columnToIndex.at(column);
    }

    const T& at(const size_t row, const string& column) const
    {
        return _content[row][getColumnIndex(column)];
    }

    T& at(const size_t row, const string& column)
    {
        return _content[row][getColumnIndex(column)];
    }

    const T& at(const size_t row, const size_t column) const
    {
        return _content[row][column];
    }

    T& at(const size_t row, const size_t column)
    {
        return _content[row][column];
    }

    const vector<string>& getRow(const size_t index) const
    {
        return _content[index];
    }

    typename vector<Row>::const_iterator cbegin() const
    {
        return _content.cbegin();
    }

    typename vector<Row>::const_iterator cend() const
    {
        return _content.cend();
    }

    void append(const Row& row)
    {
        _content.push_back(row);
    }
};


#endif //INTELLIAS_TEST_TASK_TABLE_HPP
