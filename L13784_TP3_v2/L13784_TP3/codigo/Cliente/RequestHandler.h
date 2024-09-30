#pragma once
#include <string>
#include <vector>
#include "../XMLRPC++/XmlRpc.h"
using namespace XmlRpc;

class RequestHandler
{
public:

	RequestHandler(const std::string& alias, const std::vector <std::string> &params);
	XmlRpcValue getRequest() const;	

private:
	std::string m_alias{};
	double m_ci{};
	double m_cs{};
	bool m_with_time;
	bool m_newSequence;
	XmlRpcValue m_request;

	static double s_prev_ci;
	static double s_prev_cs;
	static bool s_prev_limits;

	double parseDouble(const std::string& s) const;
	void buildRequest(const std::vector <std::string>& params);
	void updateLimits(double ci, double cs);

	
};

