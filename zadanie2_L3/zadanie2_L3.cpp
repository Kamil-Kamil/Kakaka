#include <iostream>
#include <memory>
#include <string>

// Klasa bazowa Robot
class Robot {
public:
    virtual ~Robot() = default;
    virtual void operacja() const = 0;
};

// Klasa RobotPodstawowy
class RobotPodstawowy : public Robot {
public:
    void operacja() const override {
        std::cout << "Robot podstawowy porusza się." << std::endl;
    }
};

// Klasa abstrakcyjna RobotDekorator
class RobotDekorator : public Robot {
protected:
    std::shared_ptr<Robot> robot;
public:
    RobotDekorator(std::shared_ptr<Robot> r) : robot(std::move(r)) {}
    virtual ~RobotDekorator() = default;
};

// Klasa RobotZKamera
class RobotZKamera : public RobotDekorator {
public:
    RobotZKamera(std::shared_ptr<Robot> r) : RobotDekorator(std::move(r)) {}

    void operacja() const override {
        robot->operacja();
        std::cout << "Robot teraz ma kamerę, może nagrywać." << std::endl;
    }
};

// Klasa RobotZCzujnikiemTemperatury
class RobotZCzujnikiemTemperatury : public RobotDekorator {
public:
    RobotZCzujnikiemTemperatury(std::shared_ptr<Robot> r) : RobotDekorator(std::move(r)) {}

    void operacja() const override {
        robot->operacja();
        std::cout << "Robot teraz ma czujnik temperatury." << std::endl;
    }
};

// Klasa RobotZDzwiekiem
class RobotZDzwiekiem : public RobotDekorator {
public:
    RobotZDzwiekiem(std::shared_ptr<Robot> r) : RobotDekorator(std::move(r)) {}

    void operacja() const override {
        robot->operacja();
        std::cout << "Robot teraz ma system dźwiękowy." << std::endl;
    }
};

// Funkcja testowa
int main() {
    std::shared_ptr<Robot> robot = std::make_shared<RobotPodstawowy>();
    robot->operacja();

    std::cout << "\nDodajemy kamerę do robota:" << std::endl;
    robot = std::make_shared<RobotZKamera>(robot);
    robot->operacja();

    std::cout << "\nDodajemy czujnik temperatury:" << std::endl;
    robot = std::make_shared<RobotZCzujnikiemTemperatury>(robot);
    robot->operacja();

    std::cout << "\nDodajemy system dźwiękowy:" << std::endl;
    robot = std::make_shared<RobotZDzwiekiem>(robot);
    robot->operacja();

    return 0;
}
