// NM_lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;

double f(double x)
{
    return x * x * x * x - x * x * x - 2 * x * x + 3 * x - 3;
}

double df(double x)
{
    return 4 * x * x * x - 3 * x * x - 4 * x + 3;
}

void getDataFromFile(ifstream& file, double& x_0, double& e, int& k) {
    if (!file.is_open())
    {
        cerr << "Невозможно открыть файл\n\n\n\n" << endl;
        system("pause");
        exit(1);
    }
    else {
        file >> x_0 >> e >> k;
    }
}

void setDataToFile(ofstream& file, int l, double xx) {

    file << "IER = 0 - нет ошибки.\nРезультат:" << endl;
    file << "Число итераций = " << l << '\n' << "Найденное решение xx = " << xx << '\n' << "f(xx) = " << f(xx) << endl;
}

int main() {

    setlocale(LC_ALL, "RUS");

    cout << "Лабораторная работа №5:\n\nРешение нелинейных уравнений. Метод Ньютона.\n";
    cout << "Проверила: Медведева О.А.\nПодготовил: Сафонов Н.С.\n\n\n";

    double x0, xn = 0.0, e;
    int k, l = 0;
    bool errorFlag = false;
    ifstream fileInput("in.txt");
    ofstream fileOutput("out.txt");

    getDataFromFile(fileInput, x0, e, k);

    if (df(x0) == 0) {
        fileOutput << "IER = 2 - деление на ноль" << endl;
        errorFlag = true;
    }
    else {
        xn = x0 - f(x0) / df(x0); // считаем первое приближение
        l++;
        while (fabs(x0 - xn) > e) // пока не достигнем необходимой точности, будет продолжать вычислять
        {
            if (l >= k) {
                fileOutput << "IER = 1 - превышено число итераций" << endl;
                errorFlag = true;
                break;
            }
            else {
                x0 = xn;
                xn = x0 - f(x0) / df(x0); // формула Ньютона
                l++;
            }
        }
    }

    if (!errorFlag) 
        setDataToFile(fileOutput, l, xn);
    return 0;
}
