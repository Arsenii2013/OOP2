#include <iostream>
#include <vector>

#include "sampler.hpp"

using namespace No_concept;

class QuadraticFn
{
    const double m_a, m_b, m_c;
public:
    QuadraticFn(double a, double b, double c)
            : m_a(a), m_b(b), m_c(c) {}

    std::string  operator () (double x) const {
        x++;
        return {};
    }
};

using namespace std;
int main()
{
    Sampler s; // класс сэмплирующий функцию

    //int i;
    //Sampler samp(i, 0, 10, 1);
    // инициализация через лямбда-функцию
    s.init([](double x) -> double { return (-1 * x + 2) * x - 5; }, 0, 10, 0.025);

    // инициализация через функтор
    QuadraticFn f(5, -3, 0);
    //s.init(f, 0, 10, 0.025);
    std::vector p{10, 10};

    // распечатка сэмплов
    return 0;
}
