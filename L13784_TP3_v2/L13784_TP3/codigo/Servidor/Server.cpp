
#include "Server.h"  

using namespace XmlRpc;

/**
 * @brief Obtiene la cadena de tiempo actual en formato "YYYY-MM-DD HH:MM:SS".
 * @return Cadena de tiempo actual.
 */
std::string Users::getCurrentTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_time);

    std::ostringstream timeStream;
    timeStream << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return timeStream.str();
}

/**
 * @brief Ejecuta la generación de números y actualiza el resultado.
 * @param params Parámetros de entrada para la generación de números.
 * @param result Resultado de la operación, incluyendo el número generado y estadísticas.
 */
void Numbers::execute(XmlRpcValue& params, XmlRpcValue& result) {
    std::string alias = params[0];

    // Verificar si el segundo parámetro es "NS" o parte de las cotas  
    bool newSequence = false;
    bool hasTime = false;
    double ci, cs;

    if (params.size() > 2 && params[1] == "NS") {
        newSequence = true;  // Nueva secuencia  
        ci = params[2];  // Cota inferior  
        cs = params[3];  // Cota superior  
    }
    else {
        ci = params[1];  // Cota inferior (cuando no hay "NS")  
        cs = params[2];  // Cota superior  
    }

    for (int i = 0; i < params.size(); i++) {
        if (params[i] == "T") {
            hasTime = true;
        }
    }
    // Obtener usuario  
    User* user = m_userManager.getUser(alias);
    if (!user) {
        m_userManager.addUser(alias, "127.0.0.1");
        user = m_userManager.getUser(alias);
    }

    // Si es una nueva secuencia, limpiar la secuencia anterior  
    if (newSequence) {
        user->clearSequence();
    }

    // Actualizar los limites de ci y cs  
    try
    {
        this->updateDistribution(ci, cs);
    }
    catch (const std::exception& e) {
        throw std::invalid_argument("Limites invalidos");
    }
    double generatedNumber = this->generate();

    // Agregar el número generado a la secuencia  
    user->addNumberToSequence(generatedNumber);

    // Formar el mensaje de respuesta en un string  
    std::ostringstream response;
    if (hasTime)
    {
        response << "Fecha y hora: " << Users::getCurrentTimeString() << "\n";
    }
    response << "Numero generado: " << generatedNumber << "\n";
    AdminInterface::showMessage(response.str());

    response << "Suma acumulada: " << user->getSum() << "\n";
    AdminInterface::showMessage(response.str());

    response << "Promedio: " << user->getAverage() << "\n";
    AdminInterface::showMessage(response.str());

    response << "Numeros en la secuencia: ";

    std::vector<double> sequence = user->getSequence();

    std::sort(sequence.begin(), sequence.end());

    for (double num : sequence) {
        response << num << " ";
    }
    response << "\n";
    AdminInterface::showMessage(response.str());

    // Asignar el string resultante a `result`  
    result = response.str();
}
