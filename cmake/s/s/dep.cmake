find_package(PkgConfig REQUIRED)
pkg_check_modules(
	UUID
	REQUIRED
	uuid
	IMPORTED_TARGET
)
# link PkgConfig::ffmpeg
if(NOT TARGET PkgConfig::UUID)
	message(FATAL_ERROR "UUID_NOT_FOUND")
endif()
include(CheckCSourceRuns)
#include(CheckCXXSourceRuns) # CXX
set(_test_uuid
"
#include <stdio.h>
#include <uuid/uuid.h>

int main()
{
	uuid_t uuid;
	uuid_generate(uuid);
	return 0;
}
")
set(CMAKE_REQUIRED_LIBRARIES ${UUID_LIBRARIES}) # PkgConfig::UUID
check_c_source_runs("${_test_uuid}" _runs)
unset(CMAKE_REQUIRED_LIBRARIES)
if(NOT _runs)
	message(FATAL_ERROR "UUID_ERROR")
endif()

find_package(OpenMP)
if(NOT OpenMP_FOUND)
	message(FATAL_ERROR "OpenMP_NOT_FOUND")
endif()
