//
// Created by Usuario on 17/09/2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include "medicion.h"

class Logger {
public:
    virtual ~Logger() = default;
    virtual void logMediciones(const std::vector<Medicion> &mediciones) const = 0;
    virtual void logMessage(const std::string& mensaje) const = 0;
};
#endif //LOGGER_H
