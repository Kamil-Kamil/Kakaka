#include <iostream>
#include <cmath>

// Klasa RobotStary (stary system, współrzędne prostokątne)
class RobotStary {
public:
    virtual void idzDo(double x, double y) {
        std::cout << "Robot porusza się do punktu (x: " << x << ", y: " << y << ") w układzie prostokątnym." << std::endl;
    }
};

// Klasa RobotNowy (nowy system, współrzędne biegunowe)
class RobotNowy {
public:
    void idzDo(double kat, double odleglosc) {
        std::cout << "Robot porusza się pod kątem " << kat << " stopni na odległość " << odleglosc << " w układzie biegunowym." << std::endl;
    }
};

// Klasa AdapterRobota (adapter)
class AdapterRobota : public RobotStary {
private:
    RobotNowy* robotNowy; // Kompozycja z klasą RobotNowy
public:
    AdapterRobota(RobotNowy* nowyRobot) : robotNowy(nowyRobot) {}

    void idzDo(double x, double y) override {
        // Konwersja współrzędnych prostokątnych na biegunowe
        double kat = atan2(y, x) * 180 / M_PI; // Kąt w stopniach
        double odleglosc = sqrt(x * x + y * y); // Odległość
        robotNowy->idzDo(kat, odleglosc);
    }
};

// Funkcja testowa
int main() {
    RobotNowy nowyRobot;
    AdapterRobota adapter(&nowyRobot);

    // Przykład użycia
    double x = 3.0;
    double y = 4.0;
    adapter.idzDo(x, y);

    return 0;
}
