#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <mutex>

// Klasa bazowa dla logów
class Log {
public:
    virtual ~Log() = default;
    virtual std::string getMessage() const = 0;
};

// Konkretne klasy logów
class InfoLog : public Log {
    std::string message;
public:
    explicit InfoLog(const std::string& msg) : message("INFO: " + msg) {}
    std::string getMessage() const override {
        return message;
    }
};

class WarningLog : public Log {
    std::string message;
public:
    explicit WarningLog(const std::string& msg) : message("WARNING: " + msg) {}
    std::string getMessage() const override {
        return message;
    }
};

class ErrorLog : public Log {
    std::string message;
public:
    explicit ErrorLog(const std::string& msg) : message("ERROR: " + msg) {}
    std::string getMessage() const override {
        return message;
    }
};

// Fabryka logów
class LogFactory {
public:
    static std::unique_ptr<Log> createLog(const std::string& type, const std::string& message) {
        if (type == "info") {
            return std::make_unique<InfoLog>(message);
        } else if (type == "warning") {
            return std::make_unique<WarningLog>(message);
        } else if (type == "error") {
            return std::make_unique<ErrorLog>(message);
        }
        throw std::invalid_argument("Unknown log type");
    }
};

// Klasa Singleton Logger
class Logger {
private:
    static std::shared_ptr<Logger> instance;
    static std::mutex mutex;

    std::vector<std::unique_ptr<Log>> logs;

    Logger() = default;

public:
    static std::shared_ptr<Logger> getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!instance) {
            instance = std::shared_ptr<Logger>(new Logger());
        }
        return instance;
    }

    void logMessage(const std::string& type, const std::string& message) {
        logs.push_back(LogFactory::createLog(type, message));
    }

    void displayLogs() const {
        for (const auto& log : logs) {
            std::cout << log->getMessage() << std::endl;
        }
    }
};

std::shared_ptr<Logger> Logger::instance = nullptr;
std::mutex Logger::mutex;

// Funkcja testowa
int main() {
    auto logger = Logger::getInstance();

    logger->logMessage("info", "Aplikacja uruchomiona");
    logger->logMessage("warning", "Niski poziom pamięci");
    logger->logMessage("error", "Błąd krytyczny");

    std::cout << "Zapisane logi:" << std::endl;
    logger->displayLogs();

    return 0;
}
