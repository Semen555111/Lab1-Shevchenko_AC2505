#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Pipe
{
private:
    static int next_id;

    int id;
    std::string name;
    double length;
    double diameter;
    bool working;

public:
    Pipe();

    int get_id() const;
    std::string get_name() const;
    bool is_working() const;
    void set_working(bool value);
    void edit();
    static void reset_ids();

    friend std::ostream& operator<<(std::ostream& out, const Pipe& p);
    friend std::istream& operator>>(std::istream& in, Pipe& p);
    friend std::ofstream& operator<<(std::ofstream& file, const Pipe& p);
    friend std::ifstream& operator>>(std::ifstream& file, Pipe& p);
};