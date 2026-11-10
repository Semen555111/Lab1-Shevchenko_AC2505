#pragma once
#include <iostream>
#include <string>
#include <limits>

class LogRedirect
{
    std::ostream& target;
    std::streambuf* saved;
public:
    LogRedirect(std::ostream& stream) : target(stream), saved(stream.rdbuf()) {}
    ~LogRedirect() { target.rdbuf(saved); }
    void to(std::ostream& dest)
     { target.rdbuf(dest.rdbuf()); }
};

inline std::string read_line(std::istream& in)
{
    std::string text;
    std::getline(in >> std::ws, text);
    std::cerr << text << std::endl;
    return text;
}

inline int read_int(std::istream& in, int low, int high)
{
    int value = 0;
    while (!(in >> value) || in.peek() != '\n' || value < low || value > high)
    {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите число от " << low << " до " << high << ": ";
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << value << std::endl;
    return value;
}

inline double read_double(std::istream& in, double low, double high)
{
    double value = 0;
    while (!(in >> value) || in.peek() != '\n' || value < low || value > high)
    {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите число от " << low << " до " << high << ": ";
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << value << std::endl;
    return value;
}