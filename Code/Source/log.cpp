#include "log.h"
#include <iostream>

namespace uzl
{

	std::ostream* out_stream = &std::cout;

	std::ostream& getOutputStream()
	{
		return *out_stream;
	}

	void initLogging(std::ostream& str)
	{
		out_stream = &str;
		logInfo("Initialized logging");
	}

}
