#include <iostream>

#include "graph.h"

using namespace std;

void print_menu() {
    cout << "Доступные команды:" << endl;
    cout << "\t0 - Выход" << endl;
    cout << "\t1 - Прочитать граф из файла" << endl;
    cout << "\t2 - Записать граф в файл" << endl;
    cout << "\t3 - Вывести тип графа" << endl;
    cout << "\t4 - Трансформировать граф" << endl;
}

int main()
{
    Graph *graph = new Graph;

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
        case 0: goto _exit_label;

        case 1:
            cout << "Введите путь к файлу [input.txt]: ";
            getline(cin, filename);
            getline(cin, filename);
            if(filename.empty()) filename = "input.txt";
            if(graph->readGraph(filename))
                cout << "successful" << endl;
            else
                cout << "fail" << endl;
            break;

        case 2:
            cout << "Введите путь к файлу [output.txt]: ";
            getline(cin, filename);
            getline(cin, filename);
            if(filename.empty()) filename = "output.txt";
            if(graph->writeGraph(filename))
                cout << "successful" << endl;
            else
                cout << "fail" << endl;
            break;

        case 3:
            cout << "Тип графа: " << graph->type() << endl;
            break;

        case 4:
            if(graph->typeChar() == '~') {
                cout << "Граф не инициализирован" << endl;
                break;
            }
            cout << "Выберите в какой тип трансформировать:" << endl;
            if(graph->typeChar() != 'C')
                cout << "\t1 - Матрица смежности" << endl;
            if(graph->typeChar() != 'L')
                cout << "\t2 - Список смежности" << endl;
            if(graph->typeChar() != 'E')
                cout << "\t3 - Список ребер" << endl;
            cout << "Тип: ";
            cin >> substatus;
            switch (substatus) {
            case 1:
                graph->transformToAdjMatrix();
                break;
            case 2:
                graph->transformToAdjList();
                break;
            case 3:
                graph->transformToListOfEdges();
                break;
            default:
                cout << "Неверная команда" << endl;
                break;
            }
            break;

        default:
            cout << "Номер команды неверный." << endl;
            print_menu();
        }
        cout << endl;
    }
    _exit_label:
    delete graph;
    return 0;
}

