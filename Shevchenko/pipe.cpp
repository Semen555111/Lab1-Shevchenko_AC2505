#include <algorithm>
#include "pipe.h"
#include "utils.h"

int Pipe::next_id = 1;

Pipe::Pipe() : id(0), name(""), length(0), diameter(0), working(true) {}

int Pipe::get_id() const { return id; }
std::string Pipe::get_name() const { return name; }
bool Pipe::is_working() const { return working; }
void Pipe::set_working(bool value) { working = value; }
void Pipe::reset_ids() { next_id = 1; }

void Pipe::edit()
{
    std::cout << "Новое состояние трубы (1 - в работе, 0 - в ремонте): ";
    set_working(read_int(std::cin, 0, 1) == 1);
}

std::ostream& operator<<(std::ostream& out, const Pipe& p)
{
    out << "Труба #" << p.id << '\n'
        << "  Название: " << p.name << '\n'
        << "  Длина, км: " << p.length << '\n'
        << "  Диаметр, мм: " << p.diameter << '\n'
        << "  Состояние: " << (p.working ? "в работе" : "в ремонте") << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, Pipe& p)
{
    p.id = Pipe::next_id++;
    std::cout << "Название трубы: ";
    p.name = read_line(in);
    std::cout << "Длина, км: ";
    p.length = read_double(in, 0.1, 10000.0);
    std::cout << "Диаметр, мм: ";
    p.diameter = read_double(in, 1.0, 5000.0);
    std::cout << "Труба в работе? (1 - да, 0 - в ремонте): ";
    p.working = read_int(in, 0, 1) == 1;
    return in;
}

std::ofstream& operator<<(std::ofstream& file, const Pipe& p)
{
    file << p.id << '\n'
         << p.name << '\n'
         << p.length << ' ' << p.diameter << ' ' << p.working << '\n';
    return file;
}

std::ifstream& operator>>(std::ifstream& file, Pipe& p)
{
    file >> p.id;
    std::getline(file >> std::ws, p.name);
    file >> p.length >> p.diameter >> p.working;
    Pipe::next_id = std::max(Pipe::next_id, p.id + 1);
    return file;
}