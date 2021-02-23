#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/PointOptimized.hpp"

void test_Point_get_pos();
void test_Point_get_distance();
void test_Point_sort();

int main() {
    std::cout << "test Point constructor and get_pos() method\n";
    std::cout << "expected value will be:\tx = 0; y = 0\n";
    std::cout << "\t\t\tx = 2; y = 3;";
    std::cout << "\n";
    test_Point_get_pos();

    std::cout << "test Point's get_distance() method\n";
    test_Point_get_distance();

    std::cout << "test Point's comparator() method\n";
    test_Point_sort();

    return 0;
}

void test_Point_get_distance() {
    Point p(1.0, 2.0);
    Point p1(-1.0, 2.0);
    std::cout << "The result equals: " << p.get_distance(p1) << "\n";

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

bool test_comparator(Point rhs, Point lhs) {
    return rhs.get_distance(0, 0) < lhs.get_distance(0, 0);
}

void test_Point_sort() {
    std::vector<Point> v;
    
    Point a(0, 1);
    Point b(1, 2);
    Point c(2, 3);

    v.push_back(a);
    v.push_back(c);
    v.push_back(b);
    std::sort(v.begin(), v.end(), test_comparator);

    for (Point i : v) {
        std::cout << i.get_x() << ", " << i.get_y() <<'\n';
    }
    std::cout << "\n";
}