#include <EagleCore/Environment.hh>
#include <string>

namespace Eagle::Core {
	std::string getEnvironmentVariable(const char* name) {
#if defined (_GNU_SOURCE)
		if(const char* var = ::secure_getenv(name)) return var;
#else
		if(const char* var = ::getenv(name)) return var;
#endif
		return {};
	}
}
