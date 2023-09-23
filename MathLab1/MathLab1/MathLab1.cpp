// MathLab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
#include <math.h>

using namespace std;
const int n = 2;
const double t0 = 0;
const double tmax = 10;
double y[n];
double y_start[n] = {0.0, 1.0/12.0};
double yy[n], yyy[n], k[4][n];
double t_start, t_end;
const double tau = 0.0000001;


double func(double* y, double time, int i)
{
    double w = 0;
    switch (i)
    {
    case 0:
        w = y[1];
        break;
    case 1:
        w = -0.1 * time * y[1] - time * time * y[0];
    }
    return w;
}

//double runge(double* y, double time, int i)
//{
//    for (double t = t0; t < tmax; t += tau)
//    {
//        for (int i = 0; i < n; i++)
//        {
//            yy[i] = y[i] + tau/2 * func(y, t, i);
//        }
//        for (int i = 0; i < n; i++)
//        {
//            yy[i] = y[i] + tau * func(y, time+tau/2, i);
//        }
//        for (int i = 0; i < n; i++)
//        {
//            y[i] = yy[i];
//        }
//    }
//
//}

int main()
{
    double time = 0;
    double f[n];

    for (int i = 0; i < n; i++)
    {
        y[i] = y_start[i];
    }
    t_start = omp_get_wtime();
    for (double  t = t0; t < tmax; t += tau)
    {
        for (int i = 0; i < n; i++)
        {
            yy[i] = y[i] + tau * func(y, t, i);
        }
        for (int i = 0; i < n; i++)
        {
            y[i] = yy[i];
        }
    }

    t_end = omp_get_wtime();
    time = t_end - t_start;
    std::cout << "Euler method" << std::endl;
    std::cout << "Total time:" << time << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "y[" << i << "] = " << y[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        y[i] = y_start[i];
    }
    t_start = omp_get_wtime();
    for (double t = t0; t < tmax; t += tau)
    {
        for (int i = 0; i < n; i++)
        {
            yy[i] = y[i] + tau * 0.5 * func(y, t, i);
        }

        for (int i = 0; i < n; i++)
        {
            yyy[i] = y[i] + tau * func(yy, t + tau * 0.5, i);
        }

        for (int i = 0; i < n; i++)
        {
            y[i] = yyy[i];
        }
    }
    t_end = omp_get_wtime();
    time = t_end - t_start;
    std::cout << "Runge-Kutte method" << std::endl;
    std::cout << "Total time:" << time << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "y[" << i << "] = " << y[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        y[i] = y_start[i];
    }
    t_start = omp_get_wtime();
    for (double t = t0; t < tmax; t += tau)
    {
        for (int i = 0; i < n; i++)
        {
            f[i] = func(y, t, i);
            yy[i] = y[i] + tau * f[i];
        }

        for (int i = 0; i < n; i++)
        {
            yyy[i] = y[i] + tau * (func(yy, t + tau, i) + f[i]) / 2.0;
        }

        for (int i = 0; i < n; i++)
        {
            y[i] = yyy[i];
        }
    }
    t_end = omp_get_wtime();
    time = t_end - t_start;
    std::cout << "Corrector method" << std::endl;
    std::cout << "Total time:" << time << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "y[" << i << "] = " << y[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        y[i] = y_start[i];
    }
    t_start = omp_get_wtime();
    for (double t = t0; t < tmax; t += tau)
    {
        for (int i = 0; i < n; i++)
        {
            k[0][i] = tau * func(y, t, i);
            yy[i] = y[i] + 0.5 * k[0][i];
        }

        for (int i = 0; i < n; i++)
        {
            k[1][i] = tau * func(yy, t + tau * 0.5, i);
            yy[i] = y[i] + 0.5 * k[1][i];
        }

        for (int i = 0; i < n; i++)
        {
            k[2][i] = tau * func(yy, t + tau * 0.5, i);
            yy[i] = y[i] + k[2][i];
        }

        for (int i = 0; i < n; i++)
        {
            k[3][i] = tau * func(yy, t + tau, i);
            y[i] += (k[3][i] + 2 * k[2][i] + 2 * k[1][i] + k[0][i]) / 6.0;
        }

    }
    t_end = omp_get_wtime();
    time = t_end - t_start;
    std::cout << "Euler4 method" << std::endl;
    std::cout << "Total time:" << time << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "y[" << i << "] = " << y[i] << endl;
    }
    
    
    system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
