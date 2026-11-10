#pragma once
#include <iostream>
#include <fstream>
#include <string>

class KS
{
private:
    static int next_id;

    int id;
    std::string name;
    int workshops;
    int active_workshops;
    double efficiency;

public:
    KS();

    int get_id() const;
    std::string get_name() const;
    double idle_percent() const;
    void edit();
    static void reset_ids();

    friend std::ostream& operator<<(std::ostream& out, const KS& s);
    friend std::istream& operator>>(std::istream& in, KS& s);
    friend std::ofstream& operator<<(std::ofstream& file, const KS& s);
    friend std::ifstream& operator>>(std::ifstream& file, KS& s);
};