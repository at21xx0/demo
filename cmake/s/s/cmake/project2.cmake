
set(target_source_dir ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/tests ${CMAKE_SOURCE_DIR})
# set(target_cmake_package ON)
set(target_final_link ON)
set(target_auto_win_object ON)
set(target_fix_win_object ON) # all_dllimport -Werror
set(target_macro ON)
set(target_check ON)
set(target_dev ON)

set(target_base_dir "${CMAKE_CURRENT_LIST_DIR}")
set(target_lib)
set(target_pkglib)

# set_property(DIRECTORY PROPERTY EP_BASH ${CMAKE_BINARY_DIR}/subprojects)
# include(ExternalProject)
include(FetchContent)






if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if(target_check)
	include(CheckTypeSize)
	include(CheckFunctionExists)
	include(CheckIncludeFiles)
	include(CheckLibraryExists)
	if(CMAKE_CXX_COMPILER)
		include(CheckCXXCompilerFlag)
	endif()
	if(CMAKE_C_COMPILER)
		include(CheckCCompilerFlag)
	endif()
endif()


if(target_macro)
	# set(source ${CMAKE_SOURCE_DIR})
	# set(binary ${CMAKE_BINARY_DIR})
endif()

if(NOT DEFINED target_default_labels)
	set(target_default_labels "quick")
endif()
if(NOT DEFINED target_bindir)
	include(GNUInstallDirs)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

	set(target_bindir ${CMAKE_INSTALL_BINDIR})
	set(target_libdir ${CMAKE_INSTALL_LIBDIR})
	set(target_includedir ${CMAKE_INSTALL_INCLUDEDIR})
endif()

if(NOT target_default_include)
	set(target_default_include ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src/include ${CMAKE_CURRENT_SOURCE_DIR}/tests/include)
	foreach(_dir IN LISTS target_default_include)
		if(NOT EXISTS ${_dir})
			list(REMOVE_ITEM target_default_include ${_dir})
		endif()
	endforeach()
	list(APPEND target_default_include ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/${target_includedir})
endif()

macro(_switch_set prefix list state)
	foreach(_item IN LISTS ${list})
		set(${prefix}${_item} ${state})
	endforeach()
endmacro()

macro(_upper_append prefix out_list)
	foreach(_t23 IN ITEMS ${ARGN})
		if(${prefix}${_t23})
			string(TOUPPER ${_t23} _t43)
			list(APPEND ${out_list} ${_t43} ${${prefix}${_t23}})
		endif()
	endforeach()
endmacro()

macro(_upper_append2 prefix out_list)
	foreach(_t23 IN ITEMS ${ARGN})
		if(${prefix}${_t23})
			foreach(_t24 IN LISTS ${prefix}${_t23})
				string(TOUPPER ${_t23} _t43)
				list(APPEND ${out_list} ${_t43} ${_t24})
			endforeach()
		endif()
	endforeach()
endmacro()


macro(_target_private_include _include _output)
	foreach(_file IN LISTS ${_include})
		list(APPEND ${_output} PRIVATE ${_file})
	endforeach()
endmacro()

macro(target_update_rpath)
	file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${target_bindir} ${CMAKE_INSTALL_PREFIX})
	if(APPLE)
		set(_rpath "@loader_path/${_rel}")
	else()
		set(_rpath "\$ORIGIN/${_rel}")
	endif()
	file(TO_NATIVE_PATH "${_rpath}/${target_libdir}" target_rpath)
endmacro()

macro(_target_link_ link sources)
	if(WIN32 AND target_auto_win_object AND NOT target_fix_win_object AND "${link}" MATCHES "-(shared|moudle)$")
		set(_s "_windll")
	else()
		set(_s "")
	endif()
	if(target_object_targets AND CMAKE_VERSION LESS 3.12)
		foreach(_v IN LISTS target_object_targets)
			list(FIND ${link} ${_v} _out)
			if(NOT _out EQUAL -1)
				list(REMOVE_AT ${link} ${_out})
				list(APPEND ${sources} $<TARGET_OBJECTS:${_v}${_s}>)
			endif()
		endforeach()
	elseif(target_object_targets AND NOT CMAKE_VERSION LESS 3.12) # GREATER
		foreach(_v IN LISTS target_object_targets)
			list(TRANSFORM ${link} REPLACE ${_v} $<BUILD_INTERFACE:${_v}${_s}>)
		endforeach()
	endif()
endmacro()

macro(_target_libstr prefix str)
	string(REGEX MATCH "^[^:]+" ${${prefix}name} "${str}")
	# string(REPLACE "|" ";" str ${str})
	set(_arg_one name ori)
	string(REGEX MATCHALL "|[^|]+" _str_list "${str}")
	foreach(_str IN LISTS _str_list)
	endforeach()
endmacro()


include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

function(add_target)
	set(_options)
	set(_oneValueArgs name version export_name sources_dir labels includedir ban patch check_language url_hash git_remote_name git_tag)
	set(_multiValueArgs depends sources include options link properties files install definitions ignore public_header hidden conditions conditions_var var set check check_append check_append_list cmake pkg-config pkg_config repo cmake_arg imported_targets make_command configure_command build_command test_command install_command arg on off)

	set(_target_default_on auto_sources auto_sources_dir independent auto_include auto_definitions rpath auto_version export_hidden_static sources_rel_patch convert_to_interface check_replace_filename)
	set(_target_default_off static module shared object executable test export check_fatal check_merge_header)

	cmake_parse_arguments(_target "${_options}" "${_oneValueArgs}" "${_multiValueArgs}" ${ARGN})
	_switch_set(_target_ _target_default_on ON)
	_switch_set(_target_ _target_default_off OFF)
	_switch_set(_target_ _target_on ON)
	_switch_set(_target_ _target_install ON)
	_switch_set(_target_ _target_off OFF)
	_switch_set(_target_install_ _target_install ON)
	if(_target_ban)
		return()
	endif()
	if(_target_set)
		set(_quote "")
		set(_v "")
		set(_k "")
		foreach(_t IN LISTS _target_set)
			if(NOT _quote AND _t MATCHES "^[a-zA-Z0-9_+-]+=")
				string(REGEX MATCH "^[a-zA-Z0-9_+-]+" _k ${_t}) # ^[a-zA-Z0-9_-+]+(?!=))
				string(REPLACE "${_k}=" "" _v "${_t}")
				string(REGEX MATCH "^[\"']" _quote ${_v}) # ('(\\'|[^']+)+'|\"(\\\"|[^\\\"]+)+\")
				if(_quote)
					string(REGEX REPLACE "^[\"']" "" _t "${_v}")
					set(_v "")
				else()
					set(${_k} ${_v} PARENT_SCOPE)
					set(_v "")
				endif()
			endif()
			if(_quote)
				string(REPLACE "\\${_quote}" "" _tmp "${_t}")
				string(FIND "${_tmp}" "${_quote}" _out)
				if(_out EQUAL -1 OR _t MATCHES "\\[\"']$")
					list(APPEND _v ${_t})
				else()
					string(REGEX REPLACE "[\"']$" "" _tmp "${_t}")
					list(APPEND _v ${_tmp})
					set(${_k} ${_v} PARENT_SCOPE)
					set(_v "")
					set(_quote "")
				endif()
			endif()
		endforeach()
	endif()
	if(_target_conditions_var)
		set(or "or")
		set(not "not")
		set(and "and")
		foreach(_t IN LISTS _target_conditions_var)
			list(APPEND _target_conditions ${_t})
		endforeach()
		unset(or)
		unset(not)
	endif()
	if(_target_conditions)
		set(_status 0)
		set(_s "")
		foreach(_t IN LISTS _target_conditions)
			if(_t MATCHES "^not$")
				set(_t "!")
			elseif(_t MATCHES "^or$")
				set(_t "|")
			elseif(_t)
				set(_t "1")
			else()
				set(_t "0")
			endif()
			set(_s "${_s}${_t}")
		endforeach()
		string(REGEX REPLACE "([01](\\|[01])+)" "(\\1)" _s "${_s}")
		string(REGEX REPLACE "!((\\([01\\|]+\\))|([01]))" "(1^\\1)" _s "${_s}")
		string(REGEX REPLACE "([01\\)])([01\\(])" "\\1&\\2" _s "${_s}") # ([01\)](?=[01\(])) $1&
		string(REGEX REPLACE "([01\\)])([01\\(])" "\\1&\\2" _s "${_s}")
		math(EXPR _status "${_s}")
		# message(STATUS "${_target_name}_expr: ${_s} ${_status}")
		if(_status EQUAL 0)
			return()
		else()
		endif()
	endif()
	# message(STATUS "options: ${options}")
	if(NOT DEFINED _target_includedir)
		set(_target_includedir ${target_includedir})
	endif()
	# ???
	if(_target_check)
		if(NOT _target_name)
			message(FATAL_ERROR "NO_TARGET_NAME")
		endif()
		if(NOT _target_check_lang)
			set(_target_check_language c)
		else()
			string(TOLOWER _target_language ${_target_language})
		endif()
		if(_target_include)
			foreach(_t IN LISTS _target_include)
				list(APPEND _target_check -I${_t})
			endforeach()
		endif()
		if(_target_link)
			foreach(_t IN LISTS _target_link)
				list(APPEND _target_check -l${_t})
			endforeach()
		endif()
		string(REGEX REPLACE "(^[A-Za-z:/\\]*([^\\/]+[\\/])+|\\.cmake$|\\.hpp$|\\.h$)" "" _prefix ${_target_name})
		if(_target_name MATCHES "(\\.cmake|\\.hpp|\\.h)" AND _target_check_replace_filename)
			string(TOUPPER ${_prefix} _prefix)
			string(REPLACE "-" "_" _prefix ${_prefix})
			string(REPLACE "." "_" _prefix ${_prefix})
		elseif(_prefix MATCHES "\\.")
			message(STATUS "_prefix: ${_prefix}")
			message(FATAL_ERROR "filename_exists .")
		endif()
		if(TARGET ${_target_name})
			set(_prefix "${_prefix}_")
		endif()
		set(_file "")
		set(_file_prefix "")
		set(_file_suffix "")
		if(_target_name MATCHES "\\.cmake$")
			set(_file_prefix "set(")
			set(_file_suffix " ON)\n")
			file(WRITE ${_target_name} ${_out})
		elseif(_target_name MATCHES "(\\.h|\\.hpp)$")
			set(_file "#ifndef _${prefix}_H___\n#define _${prefix}_H___\n")
			set(_file_prefix "#define ")
			set(_file_suffix " \n")
		endif()
		if(_file_prefix AND EXISTS ${_target_name})
			return()
		endif()
		set(_pass "")
		set(_suffixes "")
		set(_multi FALSE)
		set(_prev "")
		set(_includedir "")
		foreach(_t IN LISTS _target_check)
			if(_prev)
				set(_t ${_prev}${_v})
				set(_prev "")
			elseif(_t MATCHES "^-[IiLl]$")
				set(_prev ${_v})
				continue()
			elseif(_t MATCHES "\]$")
				string(REGEX REPLACE "(^[\[\;]+|[\]\;]+$)" "" _t "${_t}")
				set(_multi TRUE)
			endif()
			if(_multi)
				set(CMAKE_REQUIRED_FLAGS "")
				set(CMAKE_REQUIRED_INCLUDES "")
				set(CMAKE_REQUIRED_DEFINITIONS "")
				foreach(_v IN LISTS _t)
					if(_v MATCHES "^-[iILl]")
						list(REMOVE_ITEM _t ${_v})
						list(APPEND CMAKE_REQUIRED_INCLUDES ${_v})
					endif()
				endforeach()
				set(_t ${CMAKE_REQUIRED_INCLUDES} ${_t})
			endif()
			foreach(_v IN ITEMS ${_t})
				if(NOT _v MATCHES "^-[iIL]")
					string(TOUPPER ${_v} _upper_suffix)
					string(REPLACE "/" "_" _upper_suffix ${_upper_suffix})
					string(REPLACE "-" "_" _upper_suffix ${_upper_suffix})
					string(REPLACE "." "_" _upper_suffix ${_upper_suffix})
				else()
					set(_upper_suffix)
				endif()
				if(_v MATCHES "(\.hpp|\.h)$")
					check_include_files(${_v} ${_prefix}${_upper_suffix})
				elseif(_v MATCHES "(\\.c[pcx]*)$")
					try_compile(
						${_prefix}${_upper_suffix}
						${CMAKE_CURRENT_BINARY_DIR}/try_compile
						SOURCES ${_v}
						# LINK_LIBRARIES link
						# INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}
					)
				elseif(_v MATCHES "^-[iIL]")
					string(REGEX REPLACE "^-[iILl]" "" _tmp _v)
					unset(_out)
					if(EXISTS ${_tmp})
						set(_out 1)
					endif()
					if(_multi AND _out)
						list(APPEND CMAKE_REQUIRED_INCLUDES ${_tmp})
					endif()
					set(${_prefix}${_upper_suffix} ${_out} PARENT_SCOPE)
				elseif(_v MATCHES "^-D")
					if(_multi)
						string(REGEX REPLACE "^-D" "" _def ${_v})
						list(APPEND CMAKE_REQUIRED_DEFINITIONS ${_def})
					endif()
				elseif(_v MATCHES "^(-|/)")
					if(_v MATCHES "^/" AND NOT MSVC)
					elseif(_target_check_language STREQUAL "c" AND CMAKE_C_COMPILER)
						check_c_compiler_flag("${_v}" ${_prefix}${_upper_suffix})
					else()
						check_cxx_compiler_flag("${_v}" ${_prefix}${_upper_suffix})
					endif()
					if(NOT ${_prefix}${_upper_suffix} AND _v MATCHES "^-l")
						string(REGEX REPLACE "^-l" "" _lib ${_v})
						unset(_out)
						if(TARGET ${_v})
							set(${_prefix}${_upper_suffix} ${_out} PARENT_SCOPE)
						else()
							check_library_exists("math" "" "" ${_prefix}${_upper_suffix})
						endif()
						if(_multi AND ${_prefix}${_upper_suffix})
							list(APPEND CMAKE_REQUIRED_LIBRARIES ${_lib})
						endif()
					elseif(_multi)
						list(APPEND CMAKE_REQUIRED_FLAGS "${_v}")
					endif()
				else()
					check_function_exists("${_v}" ${_prefix}${_upper_suffix})
				endif()
				if(${_prefix}${_upper_suffix})
					# list(APPEND _suffixes ${_upper_suffix})
					string(APPEND _file "${_file_prefix}${_prefix}${_upper_suffix}${_file_suffix}")
					list(APPEND _pass ${_v})
				elseif(_target_fatal AND NOT _v MATCHES "(^-[LiI])$")
					message(FATAL_ERROR "check: ${_v}")
				endif()
			endforeach()
			if(_multi)
				unset(CMAKE_REQUIRED_FLAGS)
				unset(CMAKE_REQUIRED_INCLUDES)
				unset(CMAKE_REQUIRED_LIBRARIES)
				unset(CMAKE_REQUIRED_DEFINITIONS)
				set(_multi FALSE)
			endif()
		endforeach()
		if(_file_suffix)
			if(_file_prefix STREQUAL "#define ")
				string(APPEND _file "#endif")
			endif()
			file(WRITE "${_target_name}" "${_file}")
		else()
			list(APPEND _target_check_append ${_prefix})
			set(_file "")
		endif()
		foreach(_p IN LISTS _target_check_append)
			string(REPLACE ";" " " _out "${${_p}};${_pass}")
			set(${_p} ${_out} PARENT_SCOPE)
		endforeach()
		foreach(_p IN LISTS _target_check_append_list)
			set(${_p} ${_p} ${_pass} PARENT_SCOPE)
		endforeach()
		if(NOT _target_souces AND NOT TARGET ${_target_name})
			return()
		endif()
		list(APPEND _target_definitions ${_pass})
	endif()
	if(_target_pkg-config)
		set(_target_pkg_config ${_target_pkg-config})
	endif()
	if(_target_repo OR _target_cmake OR _target_pkg_config)
		if(_target_cmake)
			if(_target_paths)
				set(_target_paths PATHS ${_target_sdir})
			endif()
			foreach(_tn IN LISTS _target_cmake)
				message(STATUS "_find: ${_tn}")
				find_package(${_tn} ${_target_version} ${_target_paths})
				if(NOT ${_tn}_FOUND)
					message(FATAL_ERROR "${_tn} NOT Found.")
					return()
				endif()
			endforeach()
			if(NOT TARGET ${_target_name})
				add_library(${_target_name} INTERFACE)
			endif()
		elseif(_target_pkg_config)
			if(NOT PkgConfig)
				find_package(PkgConfig REQUIRED)
			endif()
			foreach(_tn IN LISTS _target_pkg_config)
				pkg_config_module(${_target_name} IMPORTED_TARGETS ${_target_imported_targets})
				if(NOT TARGET PkgConfig::${_target_name})
					message(FATAL_ERROR "${_tn} Not Found.")
					return()
				endif()
			endforeach()
			if(NOT TARGET ${_target_name})
				add_library(${_target_name} INTERFACE)
			endif()
		endif()
		if(_target_repo MATCHES "\\.in$" AND _target_name)
			configure_file(${_target_name} ${_target_repo})
			return()
		endif()
		return()
		# coding
		if(_target_repo)
			if(_target_repo MATCHES "\\.in$" AND _target_name)
				configure_file(${_target_name} ${_target_repo})
				return()
			endif()
			set(_out)
			set(_first)
			set(_tn "")
			set(_others "")
			foreach(_first ${_target_repo})
				break()
			endforeach()
			foreach(_value IN LISTS _target_repo)
				if(_value MATCHES "://" OR _value MATCHES "^git@")
					if("${_target_repo}" MATCHES "\\.git$")
						set(_target_git_repository "${_value}")
					elseif(NOT _target_download_command)
						set(_target_url "${_value}")
					endif()
				elseif(_value MATCHES "(\\.so|\\.so[\\.0-9]+|\\.a|\\.o|\\.dll|\\.lib|\\.exe)$")
					list(APPEND _others ${_value})
				else()
					if(_value MATCHES "(\\.zip|\\.7z|\\.tar\\.gz|\\.tgz|\\.tar|\\.tar\\.xz|\\.bz2)$")
						if(EXISTS "${_value}")
							set(_target_url "${_value}")
							# set(_target_download_command "cmake -E echo arg")
						endif()
					elseif(IS_DIRECTORY "${_value}")
						set(_target_source_dir "${_value}")
					else()
						set(_common TRUE)
					endif()
				endif()
			endforeach()
			if(_target_url OR _target_source_dir OR _target_git_repository)
				if(CMAKE_VERSION LESS 3.11)
					message(FATAL_ERROR "CMAKE_VERSION LESS 3.11")
				endif()
				if(NOT _target_name)
					set(_tmp "${_target_url}${_target_source_dir}${_target_git_repository}")
					string(REGEX REPLACE "/*([^/]+/+)+([^/\\.]+)[^/]+" "\\2" _target_name "${_tmp}")
				endif()
				if(_taget_repo MATCHES "\;")
					list(REMOVE_ITEM _target_name "${_first}")
				endif()
				set(_tn "${_target_name}")
				set(_source "${CMAKE_BINARY_DIR}/subBuild")
				set(_binary "${_source}/${_tn}_build")
				# set(_source_dir "${CMAKE_BINARY_DIR}/subBuild/${_tn}")
				set(_download_dir "${CMAKE_BINARY_DIR}/subBuild/${_tn}")
				set(_binary_dir "${_binary}/binary")
				set(_install_prefix "${CMAKE_BINARY_DIR}/subBuild/${_tn}_prefix")
				set(_arg "DOWNLOAD_DIR;${_download_dir};BINARY_DIR;${_binary_dir};INSTALL_DIR;${_install_prefix}")
				_upper_append(_target_ _arg depends source_dir git_repository git_tag url url_hash git_remote_name download_command configure_command build_command test_command test_command)
				# string(REPLACE ";" " \n" _arg "${arg}")
				file(MAKE_DIRECTORY "${_source}" "${_source_dir}" "${_binary_dir}")
				if(NOT EXISTS ${_source}/CMakeLists.txt)
					file(COPY_FILE "${target_base_dir}/CMakeExternal.cmake" "${_source}/CMakeLists.txt")
				endif()
				set(_carg "-DCMAKE_INSTALL_PREFIX=\"${_install_prefix}\"")
				foreach(_n IN ITEMS CMAKE_TOOLCHAIN_FILE CMAKE_PREFIX_PATH CMAKE_C_COMPILER CMAKE_CXX_COMPILER CMAKE_BUILD_TYPE CMAKE_GENERATOR)
					if(${_n})
						list(APPEND _carg "-D${_n}=\"${${_n}}\"")
					endif()
				endforeach()
				string(REPLACE ";" "\\;" _arg "${_arg}")
				set(_out "")
				execute_process(
					COMMAND ${CMAKE_COMMAND} -S "${_source}" -B "${_binary}" ${carg} -DEXTERNAL_NAME:STRING=${_tn} -DEXTERNAL_ARG:STRING=${_arg} ${_target_cmake_arg}
					WORKING_DIRECTORY ${_source}
					RESULT_VARIABLE _status
					OUTPUT_VARIABLE _out
					ERROR_VARIABLE _err
					# OUTPUT_STRIP_TRAILING_WHITESPACE
					# ECHO_OUTPUT_VARIABLE
				)
				message(STATUS "${_status} \n${_out}")
				if(_err)
					message(FATAL_ERROR "${_err}")
				endif()
				execute_process(
					COMMAND ${CMAKE_COMMAND} --build "${_binary}"
					COMMAND ${CMAKE_COMMAND} --install "${_binary}"
					WORKING_DIRECTORY ${_source}
					RESULT_VARIABLE _status
					OUTPUT_VARIABLE _out
					ERROR_VARIABLE _err
					# OUTPUT_STRIP_TRAILING_WHITESPACE
					# ECHO_OUTPUT_VARIABLE
				)
				message(STATUS "${_status} \n${_out}")
				if(_err)
					message(FATAL_ERROR "${_err}")
				endif()
				#[[
				FetchContent_Declare(${_tn}
					${arg}
					CMAKE_ARGS
						# -DCMAKE_INSTALL_PREFIX=${STAGED_INSTALL_PREFIX}
						-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
						-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
						-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
						# -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
						# -DCMAKE_CXX_EXTENSIONS=${CMAKE_CXX_EXTENSIONS}
						# -DCMAKE_CXX_STANDARD_REQUIRED=${CMAKE_CXX_STANDARD_REQUIRED}
						# -DCMAKE_C_STANDARD=${CMAKE_C_STANDARD}
						# -DCMAKE_C_EXTENSIONS=${CMAKE_C_EXTENSIONS}
						# -DCMAKE_C_STANDARD_REQUIRED=${CMAKE_C_STANDARD_REQUIRED}
						# -D
						$<$<BOOL:${_target_cmake_arg}>:${_target_cmake_arg}>
					CMAKE_CACHE_ARGS
						-DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
						-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
						-DCMAKE_PREFIX_PATH:PATH=${CMAKE_PREFIX_PATH}
					BUILD_ALWAYS
						1
					LOG_CONFIGURE
						1
					LOG_BUILD
						1
					LOG_INSTALL
						1
				)
				if(CMAKE_VERSION LESS 3.14)
					FetchContent_GetProperties(${_tn})
					if(NOT ${_tn}_POPULATED)
						message(STATUS "${_tn} ${${_tn}_SOURCE_DIR} ${${_tn}_BINARY_DIR}")
						FetchContent_Populate(${_tn})
						add_subdirectory(${${_tn}_SOURCE_DIR} ${${_tn}_BINARY_DIR})
					endif()
				else()
					FetchContent_MakeAvailable(${_tn})
				endif()
				]]
			endif()
			if(_target_cmake)
				find_package(${_target_cmake} ${_target_version} ${_target_paths} REQUIRED)
			elseif(_target_pkg_config)
				pkg_config_module(${_target_name} REQUIRED IMPORTED_TARGETS $<$<BOOL:_target_imported_targets>:${_target_imported_targets}>)
			elseif(_common)
				set(_suffix_executable ".exe")
				set(_suffix_header ".h;.hpp")
				# set(_suffix_cmake ".cmake")
				# set(_suffix_source ".c;.cpp;.cc;.C;.cxx")
				set(_suffix_object ".o;.obj")
				set(_suffix_static ".a;.lib")
				set(_suffix_shared ".so;.dll")
				set(_type "exectable")
				set(_definitions)
				set(_include)
				set(_repo2)
				set(_implib)
				foreach(_file IN LISTS _target_repo)
					string(REGEX MATCH "\\.[a-zA-Z]+(\\.[0-9]+)*$" _suffix1 _file) # \.[a-zA-Z]+(?<![/.0-9]+)
					string(REGEX REPLACE "(\\.[0-9]+)*$" "" _suffix1 _suffix1)
					if(_file MATCHES "^-")
						list(APPEND _definitions "${_file}")
						continue()
					elseif(_file MATCHES "(\\.h|\\.hpp)$")
						list(APPEND _include "${_file}")
						continue()
					elseif(_file MATCHES ".dll.a$")
						list(APPEND _implib "${file}")
						continue()
					endif()
					foreach(_t IN ITEMS exectable header object static shared)
						list(FIND _suffix_${_t} _file _out)
						if(_out NOT EQUAL -1)
							break()
						endif()
					endforeach()
					if(_type NOT)
						set(_type ${_t})
						list(APPEND _repo2 "${_file}")
					endif()
				endforeach()
				if(TARGET ${_target_name})
				elseif(NOT _type OR _type MATCHES "executable")
					add_executable(${_target_name} IMPORTED)
				else()
					string(TOUPPER _type _TYPE)
					add_library(${_target_name} ${_TYPE} IMPORTED)
				endif()
				set_target_properties(${_target_name} PROPERTIES
					INTERFACE_COMPILE_DEFINITIONS $<$<BOOL:${_definitions}>:${_definitions}>
					INTERFACE_INCLUDE_DIRECTORIES $<$<BOOL:${_include}>:${_include}>
				)
				set_property(TARGET ${_target_name} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
				set_target_properties(${_target_name} PROPERTIES
					# IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
					IMPORTED_IMPLIB_RELEASE $<$<BOOL:${_implib}>:${_implib}>

					IMPORTED_LOCATION_RELEASE $<$<BOOL:${_repo2}>:${_repo2}>

				)
			else()
				# message(FATAL_ERROR "${_target_name} Not Found.")
			endif()
			if(NOT TARGET ${_target_name})
				add_library(${_target_name} INTERFACE)
			endif()
			foreach(_t IN ITEMS static shared executable object)
				if(_target_install_${_t})
				endif()
			endforeach()
			return()
		else()
			message(FATAL_ERROR "${_target_name} Not Found.")
		endif()
		return()
	endif()
	if(NOT _target_name)
		if(_target_patch)
			string(REGEX REPLACE "[/\\]$" "" _target_patch "${_target_patch}")
			string(REGEX MATCH "[a-zA-Z0-9+_-]+$" _target_name "${_target_patch}")
		else()
			if(_target_files)
				install(
					FILES ${_target_files}
					DESTINATION ${_target_includedir}
					)
			endif()
			return()
		endif()
	endif()
	if(_target_arg)
		set(_target_test ON)
		list(APPEND _target_on test)
	endif()
	if(NOT _target_static AND NOT _target_shared AND NOT _target_object AND NOT _target_moudle AND NOT _target_test)
		set(_target_executable ON)
		set(_target_on executable)
	endif()
	message(STATUS "${_target_name}: ${_target_on} ${_target_install}")
	foreach(_t IN ITEMS object static shared module)
		if(TARGET ${_target_name}-${_t})
			set(_target_${_t} OFF)
		endif()
	endforeach()
	if(TARGET ${_target_name})
		set(_target_executable OFF)
	endif()
	if(WIN32 AND target_auto_win_object AND _target_object AND NOT target_fix_win_object)
		set(_target_object_windll ON)
	endif()
	if(_target_auto_sources)
		if(_target_patch)
			if(EXISTS ${_target_patch}/${_target_name})
				set(_target_sources_dir ${_target_patch}/${_target_name})
			else()
				set(_target_sources_dir ${_target_patch})
			endif()
		else()
			foreach(_d IN LISTS target_source_dir _target_patch)
				if(EXISTS ${_d}/${_target_name} AND NOT _target_sources_dir)
					set(_target_sources_dir ${_d}/${_target_name}) # _target_source_dir
					# break() # 失效
				endif()
			endforeach()
			unset(_d)
		endif()
	endif()
	if(_target_sources)
		set(_target_auto_sources OFF)
		if(_target_sources_rel_patch)
			set(_s)
			foreach(_f IN LISTS _target_sources)
				if(IS_ABSOLUTE "${_f}")
					list(APPEND _s "${_f}")
				else()
					list(APPEND _s "${_target_sources_dir}/${_f}")
				endif()
			endforeach()
			set(_target_sources ${_s})
		endif()
	elseif(_target_sources_dir)
		file(GLOB_RECURSE _s ${_target_sources_dir}/*.c*) # c cc cpp cxx
		if(_target_auto_sources_dir)
			set(_remove_dirname win32 unix ignore ${_target_ignore})
			if(WIN32)
				list(REMOVE_ITEM _remove_dirname win32)
			elseif(UNIX)
				list(REMOVE_ITEM _remove_dirname unix)
			endif()
			foreach(_t ${_remove_dirname})
				if(IS_DIRECTORY "${_target_sources_dir}/${_t}")
					file(GLOB _t ${_target_sources_dir}/${_t}/*.c*)
				endif()
				if(_t)
					list(REMOVE_ITEM _s ${_t})
				endif()
			endforeach()
		endif()
		# list(REMOVE_DUPLICATES _s 1 -1) # 去重
		list(APPEND _target_sources ${_s})
	endif()
	# message(STATUS "sources: ${_target_sources}")
	set(_targets)
	foreach(_t IN ITEMS object object_windll static shared module)
		if(_target_${_t}) # AND NOT TARGET ${_target_name}-${_t})
			string(TOUPPER "${_t}" _tt)
			string(REGEX MATCH "^[a-zA-Z0-9]+" _tt "${_tt}")
			list(APPEND _targets ${_target_name}-${_t})
			add_library(${_target_name}-${_t} ${_tt} ${_target_sources})
			if(_target_install_${_t})
				list(APPEND _target_install_targets ${_target_name}-${_t})
				if(_target_auto_include)
					target_include_directories(${_target_name}-${_t}
						PUBLIC
							$<INSTALL_INTERFACE:${target_includedir}>
							$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${target_includedir}>
					)
				endif()
			endif()
		endif()
	endforeach()
	if(_target_executable)
		list(APPEND _targets ${_target_name})
		add_executable(${_target_name} ${_target_sources})
		if(_target_install_executable)
			list(APPEND _target_install_targets ${_target_name})
		endif()
		if(_target_rpath)
			set_target_properties(
				${_target_name}
				PROPERTIES
					POSITION_INDEPENDENT_CODE 1
					SKIP_BUILD_RPATH OFF
					BUILD_WITH_INSTALL_RPATH OFF
					INSTALL_RPATH "${target_rpath}"
					INSTALL_RPATH_USE_LINK_PATH ON
					MAXOSX_RPATH ON
			)
		endif()
	endif()
	if(_target_object)
		set(target_object_targets ${target_object_targets} ${_target_name}-object PARENT_SCOPE)
	endif()
	set(_target_include2)
	if(_target_auto_include)
		set(_status OFF)
		foreach(_t IN ITEMS PRIVATE INTERFACE PUBLIC)
			if(NOT _status)
				list(FIND _target_include ${_t} _status)
			endif()
		endforeach()
		if(_status EQUAL -1) # 需要特殊处理
			_target_private_include(_target_include _target_include2)
			set(_target_include)
		endif()
		if(_target_sources_dir)
			list(APPEND _target_include2 PRIVATE ${_target_sources_dir})
		endif()
		_target_private_include(target_default_include _target_include2)
	endif()
	if(_target_version OR _target_auto_version)
		if(NOT _target_version)
			set(_f ${_target_sources_dir}/version) # VERSION
			if(EXISTS ${_f} AND NOT _target_version)
				file(READ ${_f} _v) 
				if(_v MATCHES "^PROJECT_VERSION$")
					set(_v "${PROJECT_VERSION}")
				endif()
				string(STRIP "${_v}" _target_version)
			endif()
		endif()
		if(_target_version)
			string(REGEX MATCH "[0-9]+" _target_soversion "${_target_version}")
			foreach(_t IN ITEMS static shared module)
				if(_target_${_t})
					set_target_properties(
						${_target_name}-${_t}
						PROPERTIES
							VERSION "${_target_version}"
							SOVERSION "${_target_soversion}"
					)
				endif()
			endforeach()
		endif()
	endif()
	if(_target_export)
		if(NOT _target_export_name)
			string(REPLACE "-" "_" _target_export_name "${_target_name}")
		endif()
		set(target_all_exports ${target_all_exports} ${_target_export_name} PARENT_SCOPE)
		foreach(_t IN ITEMS shared module static)
			if(_target_${_t} AND NOT EXISTS ${CMAKE_BINARY_DIR}/${target_includedir}/${_target_export_name}Export.h)
				generate_export_header(
					${_target_name}-${_t}
					BASE_NAME "${_target_export_name}"
					EXPORT_MACRO_NAME "${_target_export_name}_EXPORT"
					EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/${target_includedir}/${_target_export_name}Export.h"
					DEPRECATED_MACRO_NAME "${_target_export_name}_DEPRECATED"
					NO_EXPORT_MACRO_NAME "${_target_export_name}_NO_EXPORT"
					STATIC_DEFINE "${_target_export_name}_STATIC_DEFINE"
					NO_DEPRECATED_MACRO_NAME "${_target_export_name}_NO_DEPRECATED"
					DEFINE_NO_DEPRECATED
				)
				if(target_hidden_${_t} OR _target_export_hidden_${_t})
					set_target_properties(
						${_target_name}-${_t}
						PROPERTIES
							POSITION_INDEPENDENT_CODE 1
							C_VISIBILITY_PRESET hidden
							CCX_VISIBILITY_PRESET hidden
							VISIBILITY_INLINES_HIDEN 1
					)
				endif()
				if(target_dev)
					if(NOT _target_description)
						set(_target_description "${_target_name}")
					endif()
					configure_file(${target_base_dir}/pkg.pc.in ${CMAKE_BINARY_DIR}/${_target_export_name}.pc @ONLY)
					if(NOT EXISTS ${CMAKE_BINARY_DIR}/${_target_export_name}.pc)
						message(FATAL_ERROR "err")
					endif()
					install(
						FILES
							${CMAKE_BINARY_DIR}/${_target_export_name}.pc
						DESTINATION ${target_libdir}/pkgconfig
					)
				endif()
			endif()
		endforeach()
		if(_target_install_export)
			install(
				FILES
					${CMAKE_BINARY_DIR}/${target_includedir}/${_target_export_name}Export.h
				DESTINATION ${_target_includedir}
				COMPONENT dev
			)
		endif()
		if(WIN32 AND target_fix_win_object AND _target_static)
			target_compile_definitions(${_target_name}-static PUBLIC ${_target_export_name}_shared_EXPORTS)
		endif()
	endif()
	if(_target_auto_definitions)
		foreach(_t IN ITEMS PRIVATE INTERFACE PUBLIC)
			if(NOT _status)
				list(FIND _target_definitions ${_t} _status)
			endif()
		endforeach()
		if(_status EQUAL -1) # 需要特殊处理
			_target_private_include(_target_definitions _target_definitions2)
			set(_target_definitions)
		endif()
		if(_target_version)
			list(APPEND _target_definitions2 PRIVATE "${_target_name}_VERSION=\"${_target_version}\"")
		endif()
		if(_target_static)
			target_compile_definitions(${_target_name}-static PUBLIC ${_target_export_name}_STATIC_DEFINE)
		endif()
	endif()
	foreach(_t IN LISTS _targets)
		set_target_properties(
			${_t}
			PROPERTIES
				POSITION_INDEPENDENT_CODE $<$<BOOL:${_target_independent}>,1>
				OUTPUT_NAME "${_target_name}"
				DEPENDS $<$<BOOL:${_target_depends}>:${_target_depends}>
				PUBLIC_HEADER "${_target_public_header}"
				${_target_properties}
		)
		if(_target_include2 OR _target_include)
			target_include_directories(
				${_t}
				${_target_include}
				${_target_include2}
			)
		endif()
		#[[
		if(_target_link)
			target_link_libraries(${_t}
				${_target_link}
			)
		endif()
		]]
		if(_target_options)
			target_compile_options(
				${_t}
				${_target_options}
			)
	endif()
		if(_target_link_options)
			target_link_options(
				${_t}
				${_target_link_options}
			)
		endif()
		if(_target_definitions OR _target_definitions2)
			target_compile_definitions(
				${_t}
				${_target_definitions}
				${_target_definitions2}
			)
		endif()
		# target_sources(${_t} PRIVATE ${_target_sources})
		set(target_link_${_t} ${_target_link} PARENT_SCOPE)
	endforeach()
	set(target_targets ${target_targets} ${_targets} PARENT_SCOPE)
	if(NOT target_final_link)
		target_link_all()
	endif()
	if(_target_install_targets)
		# dev
		install(
			TARGETS
				${_target_install_targets}
			EXPORT
				${PROJECT_NAME}Targets
			ARCHIVE
				DESTINATION ${target_libdir}
				COMPONENT lib
			LIBRARY
				DESTINATION ${target_libdir}
				COMPONENT lib
			RUNTIME
				DESTINATION ${target_bindir}
				COMPONENT bin
			PUBLIC_HEADER
				DESTINATION ${_target_includedir}
				COMPONENT dev
		)
		set(target_cmake_packages ${target_cmake_packages} ${_target_install_targets} PARENT_SCOPE)
	endif()
	if(_target_test)
		set(_v "${_target_name}")
		while(_v MATCHES "\\-")
			string(REGEX REPLACE "-[^-]*$" "" _v "${_v}")
			if(TARGET ${_v})
				break()
			endif()
		endwhile()
		if(NOT TARGET ${_v})
			message(FATAL_ERROR "name: ${_target_name}")
		endif()
		if(NOT DEFINED _target_labels)
			set(_target_labels ${target_default_labels})
		endif()
		if(_v STREQUAL _target_name)
			set(_target_name "${_target_name}-test")
		endif()
		if(NOT TARGET ${_target_name})
			add_test(
				NAME ${_target_name}
				# LABELS ${_target_labels}
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${target_bindir}
				COMMAND $<TARGET_FILE:${_v}> ${_target_arg}
			)
		endif()
	endif()
endfunction()

function(target_link_all)
	foreach(_t IN LISTS target_targets)
		if(target_link_${_t})
			set(_sources)
			_target_link_(target_link_${_t} _sources)
			if(_sources)
				target_sources(${_t} PRIVATE ${_sources})
			endif()
			target_link_libraries(${_t} ${target_link_${_t}})
			set(target_link_${_t} PARENT_SCOPE)
		endif()
	endforeach()
	if(target_auto_win_object AND target_object_targets)
		set(_exports_d)
		foreach(_t IN LISTS target_all_exports)
			list(APPEND _exports_d PRIVATE ${_t}_shared_EXPORTS)
		endforeach()
		foreach(_v IN LISTS target_object_targets)
			string(REGEX REPLACE "-object$" "" _tt "${_v}")
			string(REPLACE "-" "_" _tt "${_tt}")
			if(target_fix_win_object)
				set(_s "")
			else()
				set(_s "_windll")
			endif()
			target_compile_definitions(${_v}${_s} PRIVATE ${_tt}_shared_EXPORTS ${_exports_d})
			 
		endforeach()
	endif()
	unset(_sources)
endfunction()

macro(target_config_file)
	set(_out_f ${CMAKE_BINARY_DIR}/config_targets.cmake)
	set(_config_fn "CONFIG.txt")
	file(GLOB_RECURSE _fl ${CMAKE_CURRENT_SOURCE_DIR}/${_config_fn})
	if(NOT EXISTS ${_out_f})
		set(_t ON)
	else()
		foreach(_f IN LISTS _fl)
			if(${_f} IS_NEWER_THAN ${_out_f})
				set(_t ON)
				break()

			endif()
		endforeach()
	endif()
	if(_t)
		file(WRITE ${_out_f} "# ${_config_fn}\n")
		foreach(_f IN LISTS _fl)
			file(READ ${_f} _fv)
			string(REGEX REPLACE "/[^/]*$" "" _out ${_f})
			if(_fv MATCHES "^([^a-z0-9A-Z-_+]+[^\n]*\n)*patch:? ")
				set(_current_patch "")
			else()
				set(_current_patch "patch ${_out}\n")
			endif()
			string(REGEX REPLACE "(\n[a-zA-Z0-9-_+]+)(:)" "\\1" _t "\n${_current_patch}${_fv}\n") # \npatch "
			string(REPLACE ";" "__v__SEMI__v__" _t "${_t}")
			# string(REGEX MATCHALL "patch [.\n\\r]*?(?=patch)" _list ${_t}) # ???
			string(REGEX MATCHALL "[^\n]+\n" _lines "${_t}")
			set(_prefix_str "")
			foreach(_line IN LISTS _lines)
				if(_line MATCHES "^patch ")
					string(REGEX REPLACE "^patch[ \t]+" "" _t "${_line}")
					if(IS_ABSOLUTE "${_t}")
						set(_current_patch "${_line}")
					else()
						set(_current_patch "patch ${_out}/${_t}")
					endif()
					set(_prev_patch ON)
					file(APPEND ${_out_f} "${_prefix_str}add_target(\n${_current_patch}")
					set(_prefix_str ")\n")
					continue()
				elseif(_line MATCHES "^name " AND NOT _prev_patch)
					string(REGEX REPLACE "^name " ")\nadd_target(\n${_current_patch}name " _line ${_line})
				else()
					set(_prev_patch OFF)
				endif()
				string(REPLACE "__v__SEMI__v__" ";" _line "${_line}")
				file(APPEND ${_out_f} "${_line}")
			endforeach()
			file(APPEND ${_out_f} ")\n")
		endforeach()
	endif()
	if(EXISTS ${_out_f})
		include(${_out_f})
	endif()
	# file(REMOVE ${_out_f})
endmacro()

macro(target_final)
	target_config_file()
	target_link_all()
	if(target_cmake_package AND target_dev)
		if(target_cmakedir)
			set(_cmakedir ${target_cmakedir})
		elseif(WIN32 AND NOT CYGWIN)
			set(_cmakedir CMake)
		else()
			set(_cmakedir share/cmake/${PROJECT_NAME})
		endif()
		# set(_cmakedir "${target_libdir}/cmake")
		install(
			EXPORT
				${PROJECT_NAME}Targets
 			NAMESPACE
				"${PROJECT_NAME}::"
 			DESTINATION
 		 		${_cmakedir}
			COMPONENT
				dev
 		)
		string(REPLACE ";" " " target_packages_ "${target_cmake_packages}") # 替换分隔符
		set(target_packages_deps_ "")
		foreach(_f IN LISTS target_cmake_package_deps)
			file(READ ${_f} _fv)
			string(APPEND target_packages_deps_ "${_fv}\n")
		endforeach()
		write_basic_package_version_file(
			${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
			VERSION ${PROJECT_VERSION}
			COMPATIBILITY SameMajorVersion
		)
		configure_package_config_file(
			${target_base_dir}/DefaultConfig.cmake.in
			${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
			INSTALL_DESTINATION ${_cmakedir}
		)
		install(
			FILES
				${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
				${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
			DESTINATION ${_cmakedir}
			COMPONENT dev
		)
		unset(target_packages_)
		unset(target_packages_deps_)
	endif()
endmacro()

target_update_rpath()
enable_testing()

foreach(_f IN LISTS target_cmake_package_deps)
	include(${_f})
endforeach()


