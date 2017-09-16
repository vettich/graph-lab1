#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include "graph.h"

using namespace std;

void print_menu() {
    cout << "Доступные команды:" << endl;
    cout << "\t0 - Выход" << endl;
    cout << "\t1 - Прочитать граф из файла" << endl;
    cout << "\t2 - Записать граф в файл" << endl;
    cout << "\t3 - Вывести тип графа" << endl;
    cout << "\t4 - Трансформировать граф" << endl;
    cout << "\t5 - Вывести граф на экран" << endl;
}

inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

int main()
{
    Graph graph;
    Graph spaing;

    print_menu();
    cout << endl;
    int status;
    int substatus;
    string filename;
    while(true) {
        cout << "Введите номер команды: ";
        cin >> status;
        cout << endl;

        switch(status) {
        case 0:
            cout << "Выходим..." << endl;
            goto _exit_label;

        case 1:
            cout << "Введите путь к файлу [input.txt]: ";
            getline(cin, filename);
            getline(cin, filename); // не знаю, но тут надо читать дважды, иначе не работает
            if(filename.empty()) filename = "input.txt";
            if(file_exists(filename)) {
                graph.readGraph(filename);
                cout << "successful" << endl;
            } else
                cout << "fail" << endl;
            break;

        case 2:
            cout << "Введите путь к файлу [output.txt]: ";
            getline(cin, filename);
            getline(cin, filename); // тут тоже надо читать дважды...
            if(filename.empty()) filename = "output.txt";
            if(file_exists(filename)) {
                graph.writeGraph(filename);
                cout << "successful" << endl;
            } else
                cout << "fail" << endl;
            break;

        case 3:
            cout << "Тип графа: " << graph.type() << endl;
            break;

        case 4:
            if(graph.type() == '~') {
                cout << "Граф не инициализирован" << endl;
                break;
            }
            cout << "Выберите в какой тип трансформировать:" << endl;
            if(graph.type() != 'C')
                cout << "\t1 - Матрица смежности" << endl;
            if(graph.type() != 'L')
                cout << "\t2 - Список смежности" << endl;
            if(graph.type() != 'E')
                cout << "\t3 - Список ребер" << endl;
            cout << "Тип: ";
            cin >> substatus;
            switch (substatus) {
            case 1:
                if(graph.type() == 'C')
                    cout << "Граф уже и так уже типа матрицы смежности" << endl;
                else
                    graph.transformToAdjMatrix();
                break;
            case 2:
                if(graph.type() == 'L')
                    cout << "Невозможно трансформировать из списка смежности в список смежности" << endl;
                else
                    graph.transformToAdjList();
                break;
            case 3:
                if(graph.type() == 'E')
                    cout << "Что!?" << endl;
                else
                    graph.transformToListOfEdges();
                break;
            default:
                cout << "Выбран неверный тип" << endl;
                break;
            }
            break;

        case 5:
            if(graph.isGraph())
                graph.print();
            else
                cout << "Граф не инициализирован." << endl;
            break;

        case 6:
            if(graph.type() == '~') {
                cout << "Граф не инициализирован" << endl;
                break;
            }
            cout << "Выберите алгоритм:" << endl;
            cout << "\t1 - Прима" << endl;
            cout << "\t2 - Крускал" << endl;
            cout << "\t3 - Борувка" << endl;
            cout << "Тип: ";
            cin >> substatus;
            switch(substatus) {
            case 1:
                spaing = graph.getSpainingTreePrima();
                break;
            case 2:
                spaing = graph.getSpainingTreeKruscal();
                break;
            case 3:
                spaing = graph.getSpainingTreeBoruvka();
                break;
            default:
                cout << "Неверно выбран алгоритм" << endl;
            }
            spaing.print();
            break;

        default:
            cout << "Номер команды неверный." << endl;
            print_menu();
        }
        cout << endl;
    }
    _exit_label:
    return 0;
}

