#include <iostream>
#include <vector>
#include "Point.cpp"

void test_Point_get_pos();
void test_Point_get_distance();

int main() {
    std::cout << "test Point constructor and get_pos() method\n";
    std::cout << "expected value will be:\tx = 0; y = 0\n";
    std::cout << "\t\t\tx = 2; y = 3;";
    std::cout << "\n";
    test_Point_get_pos();

    std::cout << "test Point's get_distance() method\n";
    test_Point_get_distance();
    std::cout << "asd";
    return 0;
}

void test_Point_get_distance() {
    Point* p = new Point(1.0, 2.0);
    Point* p1 = new Point(-1.0, 2.0);
    double result = p->get_distance(p1);
    std::cout << "The result equals: " << p->get_distance(p1) << "\n";

}

void test_Point_get_pos() {
    std::cout << "the value equals: \n";

    Point* p = new Point();
    std::vector<double> a = p->get_pos();
    std::cout <<"\t\t\t" << "x = " << a[0] << " y = " << a[1];
    std::cout << "\n";
    delete p;

    p = new Point(2.0, 3.0);
    a = p->get_pos();
    std::cout <<"\t\t\t" << "x = " << a[0] << " y = " << a[1];
    std::cout << "\n";
    delete p;
}