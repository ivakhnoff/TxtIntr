#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <getopt.h>
#include <cstring>

using namespace std;

// Функция для суммирования операндов
double summa(const vector<double>& operands) {
  double sum = 0;
  for (double operand : operands) {
    sum += operand;
  }
  return sum;
}

// Функция для вычитания из первого операнда всех остальных
double vychitanie(const vector<double>& operands) {
  double result = operands[0];
  for (size_t i = 1; i < operands.size(); ++i) {
    result -= operands[i];
  }
  return result;
}

// Функция для вывода справки
void show_help() {
  cout << "Аддитивный калькулятор." << endl;
  cout << "Использование:" << endl;
  cout << " ./calculator -o <operation> <operand1> <operand2> ... <operandN>" << endl;
  cout << "Допустимые операции:" << endl;
  cout << " -o summa: Суммирование операндов." << endl;
  cout << " -o vychitanie: Вычитание из первого операнда всех остальных." << endl;
  cout << "Количество операндов: от 4 до 6." << endl;
  cout << "Пример:" << endl;
  cout << " ./calculator -o summa 45 13 -2 10 5" << endl;
}

int main(int argc, char* argv[]) {
  // Проверка, есть ли аргумент "-h" или "--help"
  if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    show_help();
    return 0;
  }

  // Парсинг аргументов командной строки
  int option;
  string operation;
  vector<double> operands;

  while ((option = getopt(argc, argv, "o:")) != -1) {
    switch (option) {
      case 'o':
        operation = optarg;
        break;
      default:
        cerr << "Неверный аргумент: " << optarg << endl;
        return 1;
    }
  }

  // Проверка, есть ли операнды
  if (optind >= argc) {
    cerr << "Отсутствуют операнды." << endl;
    return 1;
  }

  // Чтение операндов
  for (int i = optind; i < argc; ++i) {
    double operand;
    istringstream iss(argv[i]);
    if (!(iss >> operand)) {
      cerr << "Неверный формат операнда: " << argv[i] << endl;
      return 1;
    }
    operands.push_back(operand);
  }

  // Проверка количества операндов
  if (operands.size() < 4 || operands.size() > 6) {
    cerr << "Неверное количество операндов. Должно быть от 4 до 6." << endl;
    return 1;
  }

  // Выполнение операции
  double result;
  if (operation == "summa") {
    result = summa(operands);
  } else if (operation == "vychitanie") {
    result = vychitanie(operands);
  } else {
    cerr << "Неизвестная операция: " << operation << endl;
    return 1;
  }

  // Вывод результата
  cout << "Результат: " << result << endl;
  return 0;
}
