#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
//#include <math.h>
#include <cmath>

using namespace std;

class Figure {
public:
    Figure(const string& name) : name_(name) {}
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;

    const string name_;
};

class Triangle : public Figure {
public:
    Triangle(string name, double a, double b, double c)
        : Figure(name)
        , a_(a), b_(b), c_(c) {}

    string Name() const override {
        return name_;
    }

    double Perimeter() const override {
        return a_ + b_ + c_;
    }

    double Area() const override {
        double p = Perimeter() / 2.0;
        double s = sqrt(p * (p - a_) * (p - b_) * (p - c_));
        return s;
    }

private:
    double a_, b_, c_;
};

class Rect : public Figure {
public:
    Rect(string name, double width, double height)
        : Figure(name)
        , width_(width), height_(height) {}

    string Name() const override {
        return name_;
    }

    double Perimeter() const override {
        return (width_ + height_) * 2;
    }

    double Area() const override {
        return width_ * height_;
    }

private:
    double width_, height_ ;
};

class Circle : public Figure {
public:
    Circle(string name, double r)
        : Figure(name), r_(r) {}

    string Name() const override {
        return name_;
    }

    double Perimeter() const override {
        return 2 * 3.14 * r_;
    }

    double Area() const override {
        return 3.14 * r_ * r_;
    }

private:
    double r_ = 0;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string type;
    is >> type;
    if (type == "RECT") {
        double width, height;
        is >> width >> height;
        return make_shared<Rect>(type, width, height);
    }
    else if (type == "TRIANGLE") {
        double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(type, a, b, c);
    }
    else { //if (type == "Circle") {
        double r;
        is >> r;
        return make_shared<Circle>(type, r);
    }
    //return make_shared<Figure>(type);
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
