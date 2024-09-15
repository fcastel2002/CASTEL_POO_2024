//
// Created by Usuario on 11/09/2024.
//

#ifndef XMLWRITER_H
#define XMLWRITER_H
#include <string>
#include <vector>

class XMLWriter {
public:
    static void escribirXML(const std::string &nombreArchivo, const std::vector<std::vector<std::string>> &data);
};
#endif //XMLWRITER_H
