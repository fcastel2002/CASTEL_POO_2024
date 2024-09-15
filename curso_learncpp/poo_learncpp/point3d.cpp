//
// Created by Usuario on 12/09/2024.
//
#include <iostream>

class Point3D {
private:
    int m_x{};
    int m_y{};
    int m_z{};
public:
    void setValues(const int x, const int y, const int z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    void print() const {
        std::cout << "<" <<m_x<<", "<<m_y<<", "<<m_z<<'>';
    }
    bool isEqual(const Point3D& point) const {
        if (m_x == point.m_x && m_y == point.m_y && m_z == point.m_z) {
            return true;
        }
        return false;
        /*
         *una mejor manera de resolver esto, era mediante un return sencillo, ya que la funcion es de tipo booleana...

        return (m_x == point.m_x) && (m_y == point.m_y) && (m_z == point.m_z)

        */
    }
};

int main() {
    Point3D point1{};
    point1.setValues(1,2,3);

    Point3D point2{};
    point2.setValues(1,2,3);
    std::cout << "point 1 and point 2 are" << (point1.isEqual(point2)? "" : " not") << " equal\n";

    Point3D point3{};
    point3.setValues(3,4,5);
    std::cout << "point 1 and point 3 are" << (point1.isEqual(point3)? "" : " not") << " equal\n";

    return 0;
}