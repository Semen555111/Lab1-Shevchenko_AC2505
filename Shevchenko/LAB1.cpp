#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"
#include "pipe.h"
#include "ks.h"

using Pipes = std::unordered_map<int, Pipe>;
using Stations = std::unordered_map<int, KS>;
using Ids = std::unordered_set<int>;

void add_pipe(Pipes& pipes)
{
    Pipe p;
    std::cin >> p;
    pipes.emplace(p.get_id(), p);
    std::cout << "Труба #" << p.get_id() << " добавлена\n";
}

void add_station(Stations& stations)
{
    KS s;
    std::cin >> s;
    stations.emplace(s.get_id(), s);
    std::cout << "КС #" << s.get_id() << " добавлена\n";
}

void print_pipes(const Pipes& pipes)
{
    std::cout << "=== Трубы ===\n";
    if (pipes.empty())
    {
        std::cout << "список пуст\n";
        return;
    }
    for (const auto& [id, p] : pipes)
        std::cout << p << '\n';
}

void print_stations(const Stations& stations)
{
    std::cout << "=== КС ===\n";
    if (stations.empty())
    {
        std::cout << "список пуст\n";
        return;
    }
    for (const auto& [id, s] : stations)
        std::cout << s << '\n';
}

void print_found_pipes(const Pipes& pipes, const Ids& ids)
{
    std::cout << "Найдено: " << ids.size() << '\n';
    for (int id : ids)
        std::cout << pipes.at(id) << '\n';
}

void print_found_stations(const Stations& stations, const Ids& ids)
{
    std::cout << "Найдено: " << ids.size() << '\n';
    for (int id : ids)
        std::cout << stations.at(id) << '\n';
}

int ask_pipe_id(const Pipes& pipes)
{
    std::cout << "Введите id: ";
    int id = read_int(std::cin, 1, 1000000);
    if (!pipes.count(id))
    {
        std::cout << "Объекта с id " << id << " нет\n";
        return 0;
    }
    return id;
}

int ask_station_id(const Stations& stations)
{
    std::cout << "Введите id: ";
    int id = read_int(std::cin, 1, 1000000);
    if (!stations.count(id))
    {
        std::cout << "Объекта с id " << id << " нет\n";
        return 0;
    }
    return id;
}

void edit_pipe_by_id(Pipes& pipes)
{
    int id = ask_pipe_id(pipes);
    if (id == 0)
        return;
    pipes[id].edit();
    std::cout << pipes[id];
}

void edit_station_by_id(Stations& stations)
{
    int id = ask_station_id(stations);
    if (id == 0)
        return;
    stations[id].edit();
    std::cout << stations[id];
}

void remove_pipe_by_id(Pipes& pipes)
{
    int id = ask_pipe_id(pipes);
    if (id == 0)
        return;
    pipes.erase(id);
    std::cout << "Объект #" << id << " удалён\n";
}

void remove_station_by_id(Stations& stations)
{
    int id = ask_station_id(stations);
    if (id == 0)
        return;
    stations.erase(id);
    std::cout << "Объект #" << id << " удалён\n";
}

Ids find_pipes_by_name(const Pipes& pipes, const std::string& part)
{
    Ids found;
    for (const auto& [id, p] : pipes)
        if (p.get_name().find(part) != std::string::npos)
            found.insert(id);
    return found;
}

Ids find_pipes_by_status(const Pipes& pipes, bool working)
{
    Ids found;
    for (const auto& [id, p] : pipes)
        if (p.is_working() == working)
            found.insert(id);
    return found;
}

Ids find_stations_by_name(const Stations& stations, const std::string& part)
{
    Ids found;
    for (const auto& [id, s] : stations)
        if (s.get_name().find(part) != std::string::npos)
            found.insert(id);
    return found;
}

Ids find_stations_by_idle(const Stations& stations, double percent)
{
    Ids found;
    for (const auto& [id, s] : stations)
        if (s.idle_percent() >= percent)
            found.insert(id);
    return found;
}

Ids search_pipes(const Pipes& pipes)
{
    std::cout << "Поиск труб: 1 - по названию, 2 - по состоянию: ";
    if (read_int(std::cin, 1, 2) == 1)
    {
        std::cout << "Название или его часть: ";
        return find_pipes_by_name(pipes, read_line(std::cin));
    }
    std::cout << "Состояние (1 - в работе, 0 - в ремонте): ";
    return find_pipes_by_status(pipes, read_int(std::cin, 0, 1) == 1);
}

Ids search_stations(const Stations& stations)
{
    std::cout << "Поиск КС: 1 - по названию, 2 - по проценту незадействованных цехов: ";
    if (read_int(std::cin, 1, 2) == 1)
    {
        std::cout << "Название или его часть: ";
        return find_stations_by_name(stations, read_line(std::cin));
    }
    std::cout << "Минимальный процент незадействованных цехов (0-100): ";
    return find_stations_by_idle(stations, read_double(std::cin, 0.0, 100.0));
}

Ids pick_ids(const Ids& found)
{
    Ids chosen;
    while (true)
    {
        std::cout << "id из найденных (0 - закончить): ";
        int id = read_int(std::cin, 0, 1000000);
        if (id == 0)
            break;
        if (!found.count(id))
            std::cout << "Такого id нет среди найденных\n";
        else if (chosen.count(id))
            std::cout << "Этот id уже выбран\n";
        else
            chosen.insert(id);
    }
    return chosen;
}

void batch_edit_pipes(Pipes& pipes)
{
    Ids found = search_pipes(pipes);
    print_found_pipes(pipes, found);
    if (found.empty())
        return;

    std::cout << "Применить к: 1 - всем найденным, 2 - выбранным по id: ";
    Ids targets;
    if (read_int(std::cin, 1, 2) == 1)
        targets = found;
    else
        targets = pick_ids(found);

    if (targets.empty())
    {
        std::cout << "Ничего не выбрано\n";
        return;
    }

    std::cout << "Действие: 1 - в работу, 2 - в ремонт, 3 - удалить: ";
    int action = read_int(std::cin, 1, 3);
    for (int id : targets)
    {
        if (action == 3)
            pipes.erase(id);
        else
            pipes[id].set_working(action == 1);
    }
    std::cout << "Обработано труб: " << targets.size() << '\n';
}

void save_to_file(const Pipes& pipes, const Stations& stations)
{
    std::cout << "Имя файла для сохранения: ";
    std::ofstream file(read_line(std::cin));
    if (!file)
    {
        std::cout << "Не удалось открыть файл\n";
        return;
    }
    file << pipes.size() << '\n';
    for (const auto& [id, pipe] : pipes)
        file << pipe;
    file << stations.size() << '\n';
    for (const auto& [id, station] : stations)
        file << station;
    std::cout << "Сохранено труб: " << pipes.size() << ", КС: " << stations.size() << '\n';
}

bool load_pipes(std::ifstream& file, Pipes& pipes)
{
    int count = 0;
    if (!(file >> count))
        return false;
    for (int i = 0; i < count; ++i)
    {
        Pipe p;
        if (!(file >> p))
            return false;
        pipes.emplace(p.get_id(), p);
    }
    return true;
}

bool load_stations(std::ifstream& file, Stations& stations)
{
    int count = 0;
    if (!(file >> count))
        return false;
    for (int i = 0; i < count; ++i)
    {
        KS s;
        if (!(file >> s))
            return false;
        stations.emplace(s.get_id(), s);
    }
    return true;
}

void load_from_file(Pipes& pipes, Stations& stations)
{
    std::cout << "Имя файла для загрузки: ";
    std::ifstream file(read_line(std::cin));
    if (!file)
    {
        std::cout << "Не удалось открыть файл\n";
        return;
    }
    pipes.clear();
    stations.clear();
    Pipe::reset_ids();
    KS::reset_ids();

    if (load_pipes(file, pipes) && load_stations(file, stations))
        std::cout << "Загружено труб: " << pipes.size() << ", КС: " << stations.size() << '\n';
    else
        std::cout << "Файл повреждён, загружено частично: труб " << pipes.size()
                  << ", КС " << stations.size() << '\n';
}

std::string log_file_name()
{
    std::time_t now = std::time(nullptr);
    char stamp[32];
    std::strftime(stamp, sizeof(stamp), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    return std::string("logs/session_") + stamp + ".txt";
}

void print_menu()
{
    std::cout << "\n1. Добавить трубу\n"
              << "2. Добавить КС\n"
              << "3. Показать все объекты\n"
              << "4. Редактировать трубу по id\n"
              << "5. Редактировать КС по id\n"
              << "6. Удалить трубу по id\n"
              << "7. Удалить КС по id\n"
              << "8. Поиск труб\n"
              << "9. Поиск КС\n"
              << "10. Пакетное редактирование труб\n"
              << "11. Сохранить в файл\n"
              << "12. Загрузить из файла\n"
              << "0. Выход\n"
              << "Выбор: ";
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    std::filesystem::create_directories("logs");
    std::ofstream log_file(log_file_name());
    LogRedirect log(std::cerr);
    if (log_file)
        log.to(log_file);

    Pipes pipes;
    Stations stations;

    while (true)
    {
        print_menu();
        switch (read_int(std::cin, 0, 12))
        {
        case 1: add_pipe(pipes); break;
        case 2: add_station(stations); break;
        case 3:
            print_pipes(pipes);
            print_stations(stations);
            break;
        case 4: edit_pipe_by_id(pipes); break;
        case 5: edit_station_by_id(stations); break;
        case 6: remove_pipe_by_id(pipes); break;
        case 7: remove_station_by_id(stations); break;
        case 8: print_found_pipes(pipes, search_pipes(pipes)); break;
        case 9: print_found_stations(stations, search_stations(stations)); break;
        case 10: batch_edit_pipes(pipes); break;
        case 11: save_to_file(pipes, stations); break;
        case 12: load_from_file(pipes, stations); break;
        case 0: return 0;
        }
    }
}