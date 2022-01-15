#ifndef INTELLIAS_TEST_TASK_UTILS_HPP
#define INTELLIAS_TEST_TASK_UTILS_HPP

#include <iostream>
#include <sstream>
#include <string>

using std::ostream;
using std::string;
using std::stringstream;

template <typename TInputIterator>
void join(ostream& stream,
          const char separator,
          TInputIterator begin,
          TInputIterator end)
{
    stream << *begin++;
    while(begin != end)
        stream << separator << *begin++;
}

template <typename TCollection>
void join(ostream& stream,
          const char separator,
          const TCollection& collection)
{
    join(stream, separator, collection.cbegin(), collection.cend());
}

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
    return monthNames[index - 1];
}

#endif //INTELLIAS_TEST_TASK_UTILS_HPP
