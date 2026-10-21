// Простые тесты для LAB1.cpp.
// Запуск из папки Shevchenko:
// c++ -std=c++17 LAB1_tests.cpp -o LAB1_tests && ./LAB1_tests

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// Подключаем код программы, но её main переименовываем: у тестов будет свой main.
#define main lab1_application_main
#include "LAB1.cpp"
#undef main

int failed = 0;

void check(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[OK] " << testName << '\n';
    } else {
        std::cout << "[FAIL] " << testName << '\n';
        ++failed;
    }
}

void writeFile(const std::string& filename, const std::string& contents) {
    std::ofstream file(filename);
    file << contents;
}

void testLoadCorrectPipe() {
    const std::string filename = "test_correct_pipe.txt";
    writeFile(filename, "Main pipe\n12.5\n500\n1\n");

    PIPE pipe{};
    std::ifstream file(filename);
    load_pipe(file, pipe);

    check(pipe.name == "Main pipe" && pipe.length == 12.5 &&
              pipe.diameter == 500 && pipe.isWorking,
          "Загрузка корректной трубы");
    std::remove(filename.c_str());
}

void testLoadIncorrectPipe() {
    const std::string filename = "test_incorrect_pipe.txt";
    writeFile(filename, "Broken pipe\n-10\n500\n1\n");

    PIPE pipe{"Old pipe", 8, 200, true};
    std::ifstream file(filename);
    load_pipe(file, pipe);

    // Некорректные данные не должны заменить уже существующую трубу.
    check(pipe.name == "Old pipe" && pipe.length == 8 &&
              pipe.diameter == 200 && pipe.isWorking,
          "Отказ от трубы с отрицательной длиной");
    std::remove(filename.c_str());
}



int main() {
    testLoadCorrectPipe();
    testLoadIncorrectPipe();

    std::cout << "\nНе пройдено тестов: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
