#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "Table.hpp"
#include "SVReader.hpp"
#include "SVWriter.hpp"
#include "Utils.hpp"


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
using std::stoi;


Table<string> getTotalHoursByMonth(const Table<string>& table)
{
    const string nameColumn = "Name";
    const string dateColumn = "date";
    const string hoursColumn = "logged hours";
    using Key = pair<string, string>;
    map<Key, size_t> hours;

    const size_t rows_count = table.height();
    cout << "Table height: " << rows_count << '\n';

    for (size_t i = 0; i < rows_count; ++i)
    {
        stringstream builder;
        const string& date = table.at(i, dateColumn);
        builder << getMonthName(getMonth(date)) << ' ' << getYear(date);
        Key key(table.at(i, nameColumn), builder.str());
        hours[key] += std::stoi(table.at(i, hoursColumn));
    }

    Table<string> result(vector<string>{"Name", "Month", "Total hours"});
    for (const auto& item: hours)
    {
        result.append(vector<string>{item.first.first,
                                     item.first.second,
                                     itos((long long) item.second)});
    }

    return result;
}


void demo(const string& filepath)
{
    SVReader reader(';');
    SVWriter writer(',');
    ifstream file(filepath);
    Table<string> table = reader.read(file);
    file.close();

    Table<string> result = getTotalHoursByMonth(table);

    writer.write(result, cout);
}


int main()
{
    const string filepath("input.csv");
    demo(filepath);
    return 0;
}
