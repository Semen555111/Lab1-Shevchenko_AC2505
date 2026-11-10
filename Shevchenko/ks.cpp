#include <algorithm>
#include "ks.h"
#include "utils.h"

int KS::next_id = 1;

KS::KS() : id(0), name(""), workshops(0), active_workshops(0), efficiency(0) {}

int KS::get_id() const { return id; }
std::string KS::get_name() const { return name; }
void KS::reset_ids() { next_id = 1; }

double KS::idle_percent() const
{
    return (workshops - active_workshops) * 100.0 / workshops;
}

void KS::edit()
{
    std::cout << "Новое число цехов в работе (от 0 до " << workshops << "): ";
    active_workshops = read_int(std::cin, 0, workshops);
}

std::ostream& operator<<(std::ostream& out, const KS& s)
{
    out << "КС #" << s.id << '\n'
        << "  Название: " << s.name << '\n'
        << "  Цехов всего: " << s.workshops << '\n'
        << "  Цехов в работе: " << s.active_workshops << '\n'
        << "  Незадействовано цехов: " << s.idle_percent() << " %" << '\n'
        << "  Эффективность: " << s.efficiency << " %" << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, KS& s)
{
    s.id = KS::next_id++;
    std::cout << "Название КС: ";
    s.name = read_line(in);
    std::cout << "Число цехов: ";
    s.workshops = read_int(in, 1, 1000);
    std::cout << "Из них в работе: ";
    s.active_workshops = read_int(in, 0, s.workshops);
    std::cout << "Эффективность, % (0-100): ";
    s.efficiency = read_double(in, 0.0, 100.0);
    return in;
}

std::ofstream& operator<<(std::ofstream& file, const KS& s)
{
    file << s.id << '\n'
         << s.name << '\n'
         << s.workshops << ' ' << s.active_workshops << ' ' << s.efficiency << '\n';
    return file;
}

std::ifstream& operator>>(std::ifstream& file, KS& s)
{
    file >> s.id;
    std::getline(file >> std::ws, s.name);
    file >> s.workshops >> s.active_workshops >> s.efficiency;
    KS::next_id = std::max(KS::next_id, s.id + 1);
    return file;
}