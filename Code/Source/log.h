#include "uzl/common.h"
#include <fmt/format.h>

namespace uzl
{

	std::ostream& getOutputStream();

}

#define logInfo(...) do { ::uzl::getOutputStream() << fmt::format("UzL::Info:  {}", fmt::format(__VA_ARGS__)); } while(0)
#define logWarn(...) do { ::uzl::getOutputStream() << fmt::format("UzL::Warn:  {}", fmt::format(__VA_ARGS__)); } while(0)
#define logError(...) do { ::uzl::getOutputStream() << fmt::format("UzL::Error: {}", fmt::format(__VA_ARGS__)); } while(0)