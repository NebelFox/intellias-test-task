#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using std::istream;
using std::ostream;
using std::ifstream;
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::stringstream;

using Series = vector<string>;
using Column = pair<string, Series>;
using Table = vector<Column>;

string itos(const long long i)
{
    stringstream stream;
    stream << i;
    return stream.str();
}

size_t getMonth(const string& date)
{
    return std::stoi(date.substr(5, 2));
}

size_t getYear(const string& date)
{
    return std::stoi(date.substr(0, 4));
}

const string& getMonthName(const size_t index)
{
    static const string monthNames[12]{
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
    };
    return monthNames[index-1];
}

Series split(const string& line,
             const char separator)
{
    Series values;
    size_t begin = 0;
    size_t length = 0;
    while (begin + length < line.length())
    {
        while (begin + length < line.length() && line[begin + length] != separator)
        {
            ++length;
        }
        values.push_back(line.substr(begin, length));
        begin += length + 1;
        length = 0;
    }
    return values;
}

Series readRow(istream& stream,
               const char separator,
               const char delimiter)
{
    string line;
    std::getline(stream, line, delimiter);
    return split(line, separator);
}

Table readCSV(istream& stream,
              const char separator = ';',
              const char delimiter = '\n')
{
    Table table;
    Series column_names = readRow(stream, separator, delimiter);
    for (const string& column_name: column_names)
    {
        table.push_back(Column(column_name, Series()));
    }
    while (stream)
    {
        Series row = readRow(stream, separator, delimiter);
        for (size_t i = row.size(); i; --i)
        {
            table[i - 1].second.push_back(row[i - 1]);
        }
    }
    return table;
}

size_t getColumnIndex(const Table& table, const string& name)
{
    for (size_t i = table.size(); i; --i)
    {
        if (table[i - 1].first == name)
        {
            return i - 1;
        }
    }
    return table.size();
}

void writeCSV(const Table& table,
              ostream& stream,
              const char separator = ';',
              const char delimiter = '\n')
{
    const size_t rows_count = table[0].second.size();
    const size_t columns_count = table.size();

    size_t i, j;
    stream << table[0].first;
    for (i = 1; i < columns_count; ++i)
    {
        stream << separator << table[i].first;
    }
    stream << delimiter;


    for (i = 0; i < rows_count; ++i)
    {
        stream << table[0].second[i];
        for (j = 1; j < columns_count; ++j)
        {
            stream << separator << table[j].second[i];
        }
        stream << delimiter;
    }
}

Table getColumns(const Table& source, const Series& column_names)
{
    Table table;
    for (const string& column_name: column_names)
    {
        table.push_back(source[getColumnIndex(source, column_name)]);
    }
    return table;
}

int main()
{
    const string filepath("input.csv");
    ifstream file(filepath);
    Table origin = readCSV(file);
    file.close();

    Table table = getColumns(origin, Series{"Name", "date", "logged hours"});
    const size_t rows_count = table[0].second.size();

    const size_t nameIndex = getColumnIndex(table, "Name");
    const size_t dateIndex = getColumnIndex(table, "date");
    const size_t hoursIndex = getColumnIndex(table, "logged hours");
    using Key = pair<string, string>;
    map<Key, size_t> hours;
    for(size_t i=0; i<rows_count; ++i)
    {
        stringstream builder;
        const string& date = table[dateIndex].second[i];
        builder << getMonthName(getMonth(date)) << ' ' << getYear(date);
        Key key (table[nameIndex].second[i], builder.str());
        hours[key] += std::stoi(table[hoursIndex].second[i]);
    }

    Table result;
    result.push_back(Column("Name", Series()));
    result.push_back(Column("Month", Series()));
    result.push_back(Column("Total hours", Series()));
    for(const auto& item : hours)
    {
        result[0].second.push_back(item.first.first);
        result[1].second.push_back(item.first.second);
        result[2].second.push_back(itos((long long)item.second));
    }

    writeCSV(result, cout);
    return 0;
}
