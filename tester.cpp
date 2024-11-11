#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <cstdio>   // dla popen, pclose
#include <memory>   // dla unique_ptr
#include <stdexcept>
#include <array>
#include <chrono>   // dla pomiaru czasu
#include <numeric>  // dla std::accumulate

using namespace std;
using namespace std::chrono;

// Funkcja do uruchamiania zewnętrznego programu i uzyskiwania jego wyjścia
string run_external_program(const string& exe_path, const string& input_file) {
    string command = exe_path + " < " + input_file;

    // Używamy popen do uruchomienia programu i przechwycenia jego wyjścia
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw runtime_error("Nie mozna uruchomic programu");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Funkcja do sprawdzania testów
void check_tests(const string& exe_path) {
//    string input = "testy1/testy1";
//    string output = "testy1/testy1";
//    string input_folder = "C:/Users/lagan/Downloads/"+input;
//    string output_folder = "C:/Users/lagan/Downloads/"+output;
//    string input_folder = "C:/Users/lagan/Downloads/walocen/wal/in/";
//    string output_folder = "C:/Users/lagan/Downloads/walocen/wal/out/";
    string input_folder = "testy/walrob/input1/";
    string output_folder = "testy/walrob/output1/";
    string input_path = "C:/Users/lagan/Downloads/" + input_folder;
    string output_path = "C:/Users/lagan/Downloads/" + output_folder;
    // Otwórz katalog wejściowy
    DIR* dir = opendir(input_path.c_str());
    struct dirent* entry;

    if (dir == nullptr) {
        cerr << "Nie mozna otworzyc katalogu: " << input_path << endl;
        return;
    }

    bool passed = true;
    vector<double> test_times; // Vector to store times of each test

    int tests_passed = 0, tests_failed = 0;

    // Iteracja po plikach w katalogu
    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        if (filename.find(".in") != string::npos) { // Filtruj pliki .in
            string input_file = input_path + filename;
            string output_file = output_path + filename.substr(0, filename.size() - 3) + ".out"; // Odpowiedni plik wyjściowy

            // Odczytanie oczekiwanej odpowiedzi
            ifstream expected_output_stream(output_file);
            if (!expected_output_stream.is_open()) {
                cerr << "Nie mozna otworzyc pliku: " << output_file << endl;
                continue; // Przechodzimy do następnego pliku
            }

            string expected_output;
            getline(expected_output_stream, expected_output);
            expected_output_stream.close();

            // Uruchomienie zewnętrznego programu i uzyskanie wyniku
            auto start_time = high_resolution_clock::now(); // Start time measurement
            string output = run_external_program(exe_path, input_file);
            auto end_time = high_resolution_clock::now(); // End time measurement

            // Calculate the duration in seconds
            double duration = duration_cast<::duration<double>>(end_time - start_time).count();
            test_times.push_back(duration); // Store the time for this test

            output.erase(remove(output.begin(), output.end(), '\n'), output.end()); // Usuwanie nowej linii

            // Porównanie wyników
            if (output == expected_output) {
                cout << "Test " << filename << " - PRZESZEDL (Czas: " << duration << " s)" << endl;
                tests_passed++;
            } else {
                cout << "Test " << filename << " - NIE PRZESZEDL (Czas: " << duration << " s)" << endl;
                tests_failed++;
                passed = false;
            }
            cout << "Oczekiwany: " << expected_output << ", Uzyskany: " << output << endl;
        }
    }

    // Calculate and display average time
    double total_time = accumulate(test_times.begin(), test_times.end(), 0.0);
    double average_time = (test_times.empty()) ? 0.0 : total_time / test_times.size();

    cout<<endl<<"Tests passed: "<<tests_passed<<", Tests failed: "<<tests_failed<<endl;

    if (passed) {
        cout << "\nWszystkie testy przeszly pomyslnie!" << endl;
    } else {
        cout << "\nNie wszystkie testy przeszly pomyslnie!" << endl;
    }
    cout << endl << "Sredni czas testow: " << average_time << " s" << endl;

    closedir(dir); // Zamknięcie katalogu
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Podaj sciezke do pliku .exe jako argument." << endl;
        return 1;
    }

    string exe_path = argv[1];
    check_tests(exe_path); // Wywołanie funkcji sprawdzającej testy

    return 0;
}
