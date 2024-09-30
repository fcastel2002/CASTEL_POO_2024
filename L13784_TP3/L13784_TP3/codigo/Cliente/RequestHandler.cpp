
#include "RequestHandler.h"  
#include <stdexcept>  
#include <sstream>  

double RequestHandler::s_prev_ci = 0.0;
double RequestHandler::s_prev_cs = 0.0;
bool RequestHandler::s_prev_limits = false;

/**
 * @brief Convierte una cadena a un n�mero de punto flotante.
 * @param s La cadena a convertir.
 * @return El n�mero de punto flotante convertido.
 * @throws std::invalid_argument Si la cadena no es un n�mero v�lido.
 */
double RequestHandler::parseDouble(const std::string& s) const {
    try {
        return std::stod(s);
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: " + s + " no es un n�mero v�lido.");
    }
}

/**
 * @brief Constructor de RequestHandler.
 * @param alias El alias del usuario.
 * @param params Los par�metros de la petici�n.
 */
RequestHandler::RequestHandler(const std::string& alias, const std::vector <std::string>& params)
    :m_alias{ alias }
    , m_ci{ 0.0 }
    , m_cs{ 0.0 }
    , m_with_time{ false }
    , m_request()
{
    buildRequest(params);
}

/**
 * @brief Construye la petici�n seg�n los par�metros proporcionados.
 * @param params Los par�metros de la petici�n.
 * @throws std::invalid_argument Si los par�metros no son v�lidos.
 */
void RequestHandler::buildRequest(const std::vector <std::string>& params)
{
    m_newSequence = false;
    m_with_time = false;
    size_t cantParam = params.size();

    if (cantParam > 4) //sin incluir al Alias  
    {
        throw std::invalid_argument("Error: se esperaba entre 1 y 4 par�metros despu�s del alias.");
    }

    bool hasNS = false;
    bool hasT = false;
    double ci = 0.0;
    double cs = 0.0;

    for (size_t i = 0; i < cantParam; i++)
    {
        const std::string& param = params[i];

        if (param == "NS") {
            hasNS = true;
        }
        else if (param == "T") {
            hasT = true;
        }
        else
        {
            if (cantParam <= 2 || !hasNS)
            {
                if (i == 0) {
                    ci = parseDouble(param);
                }
                else if (i == 1) {
                    cs = parseDouble(param);
                }
            }
            else
            {
                if (i == 1) {
                    ci = parseDouble(param);
                }
                else if (i == 2) {
                    cs = parseDouble(param);
                }
                else {
                    throw std::invalid_argument("Error: se esperaba 'NS' o 'T' como tercer parametro.");
                }
            }
        }
    }

    if (cs < ci) throw std::invalid_argument("Error: el limite superior no puede ser menor que el limite inferior.");

    if (hasNS)
    {
        m_newSequence = true;

        if (cantParam >= 3)
        {
            ci = parseDouble(params[1]);
            cs = parseDouble(params[2]);
            updateLimits(ci, cs);
        }
        else
        {
            if (s_prev_limits)
            {
                ci = s_prev_ci;
                cs = s_prev_cs;
            }
            else {
                throw std::invalid_argument("Error: no hay limites establecidos, ingreselos al menos para la primer peticion");
            }
        }
    }
    else
    {
        if (cantParam >= 2)
        {
            ci = parseDouble(params[0]);
            cs = parseDouble(params[1]);
            updateLimits(ci, cs);
        }
        else if (s_prev_limits)
        {
            ci = s_prev_ci;
            cs = s_prev_cs;
        }
        else
        {
            throw std::invalid_argument("Error: no hay limites establecidos, ingreselos al menos para la primer peticion");
        }
    }

    if (hasT) m_with_time = true;

    // Determinar el tama�o final de la petici�n  
    int finalSize = 1; // Alias  

    if (m_newSequence) {
        finalSize += 1 + 2; // "NS", ci, cs  
    }
    else {
        finalSize += 2; // ci, cs  
    }

    if (m_with_time) {
        finalSize += 1; // "T"  
    }

    // Configurar el tama�o de la petici�n una sola vez  
    m_request.setSize(finalSize);

    // Asignar los valores en orden  
    int index = 0;
    m_request[index++] = m_alias;

    if (m_newSequence) {
        m_request[index++] = "NS";
    }

    m_request[index++] = ci;
    m_request[index++] = cs;

    if (m_with_time) {
        m_request[index++] = "T";
    }
}

/**
 * @brief Actualiza los limites de la distribuci�n.
 * @param ci El limite inferior.
 * @param cs El l�mite superior.
 */
void RequestHandler::updateLimits(double ci, double cs)
{
    m_ci = ci;
    m_cs = cs;
    s_prev_ci = ci;
    s_prev_cs = cs;
    s_prev_limits = true;
}

/**
 * @brief Obtiene la petici�n construida.
 * @return La petici�n en formato XmlRpcValue.
 */
XmlRpcValue RequestHandler::getRequest() const
{
    return m_request;
}
