
set(target_source_dir ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/tests ${PROJECT_SOURCE_DIR})
set(target_default_hidden_shared ON)
set(target_default_package ON)
set(target_auto_link_object ON)

if(NOT target_bindir)
	include(GNUInstallDirs)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

	set(target_bindir ${CMAKE_INSTALL_BINDIR})
	set(target_libdir ${CMAKE_INSTALL_LIBDIR})
	set(target_includedir ${CMAKE_INSTALL_INCLUDEDIR})
	if(WIN32 AND NOT CYGWIN)
		set(_dir CMake)
	else()
		set(_dir share/cmake/${PROJECT_NAME})
	endif()
	set(target_cmakedir ${_dir})
	unset(_dir)
endif()

if(NOT target_default_include)
	set(target_default_include ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src/include)
	foreach(_dir IN LISTS target_default_include)
		if(NOT EXISTS ${_dir})
			list(REMOVE_ITEM target_default_include ${_dir})
		endif()
	endforeach()
	list(APPEND target_default_include ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/${target_includedir})
endif()

macro(_target_set list state)
	foreach(_item IN LISTS ${list})
		set(_target_${_item} ${state})
		# message(STATUS "_target_${_item}: ${_target_${_item}}")
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

if(CMAKE_VERSION LESS 3.12)
	set(target_object_auto_link ON)
endif()


include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

function(add_target)
	set(_options)
	set(_oneValueArgs name version epport_name sources_dir)
	set(_multiValueArgs depends sources include options link properties files install definitions public_header on off)

	set(_target_default_on auto_sources auto_sources_dir independent auto_include auto_definitions rpath auto_version)
	set(_target_default_off static module shared object executable auto_test export  auto_include_p)

	cmake_parse_arguments(_target "${_options}" "${_oneValueArgs}" "${_multiValueArgs}" ${ARGN})
	_target_set(_target_default_on ON)
	_target_set(_target_default_off OFF)
	_target_set(_target_on ON)
	_target_set(_target_install ON)
	_target_set(_target_off OFF)
	foreach(_t IN LISTS _target_install)
		set(_target_install_${_t} ON)
	endforeach()
	# message(STATUS "options: ${options}")
	message(STATUS "name: ${_target_name}")
	if(NOT _target_name)
		if(_target_files)
			install(
				FILES ${_target_files}
				DESTINATION ${target_includedir}
			)
		endif()
		return()
	endif()
	if(_target_auto_sources)
		foreach (_d IN LISTS target_source_dir)
			if(EXISTS ${_d}/${_target_name} AND NOT _target_sources_dir)
				set(_target_sources_dir ${_d}/${_target_name}) # _target_source_dir
				# break() # 失效
			endif()
		endforeach()
		unset(_d)
	endif()
	if(_target_sources_dir)
		file(GLOB_RECURSE _s ${_target_sources_dir}/*.c*) # c cc cpp cxx
		if(_target_auto_sources_dir)
			set(_remove_dirname win32 unix ignore)
			if(WIN32)
				list(REMOVE_ITEM _remove_dirname win32)
			elseif(UNIX)
				list(REMOVE_ITEM _remove_dirname unix)
			endif()
			foreach(_rd ${_remove_dirname})
				if(EXISTS ${_target_sources_dir}/${_rd})
					file(GLOB _ss ${_target_sources_dir}/${_rd}/*.c*)
					if(_ss)
						list(REMOVE_ITEM _s ${_ss})
					endif()
				endif()
			endforeach()
		endif()
		# list(REMOVE_DUPLICATES _s 1 -1) # 去重
		list(APPEND _target_sources ${_s})
		if(target_object_targets AND _target_link AND CMAKE_VERSION LESS 3.12)
			foreach(_v IN LISTS target_object_targets)
				list(FIND _target_link ${_v} _out)
				if(NOT _out EQUAL -1)
					list(REMOVE_AT _target_link ${_out})
					list(APPEND _target_sources $<TARGET_OBJECTS:${_v}>)
				endif()
			endforeach()
		endif()
		unset(_s)
	endif()
	# message(STATUS "sources: ${_target_sources}")
	set(_targets)
	foreach(_t IN ITEMS object static shared module)
		if(_target_${_t}) # AND NOT TARGET ${_target_name}-${_t})
			string(TOUPPER "${_t}" _tt)
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
			elseif(target_auto_link_object AND _t MATCHES object)
				set(target_object_targets ${target_object_targets} ${_target_name}-${_t} PARENT_SCOPE)
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
					# POSITION_INDEPENDENT_CODE 1
					SKIP_BUILD_RPATH OFF
					BUILD_WITH_INSTALL_RPATH OFF
					INSTALL_RPATH "${target_rpath}"
					INSTALL_RPATH_USE_LINK_PATH ON
					MAXOSX_RPATH ON
			)
		endif()
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
				if(_v MATCHES "PROJECT_VERSION")
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
			set(_target_export_name ${_target_name})
		endif()
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
				if(target_default_hidden_${_t})
					set_target_properties(
						${_target_name}-${_t}
						PROPERTIES
							POSITION_INDEPENDENT_CODE 1
								C_VISIBILITY_PRESET hidden
								CCX_VISIBILITY_PRESET hidden
								VISIBILITY_INLINES_HIDEN 1
					)
				endif()
			endif()
		endforeach()
		if(_target_install_export)
			install(
				FILES
					${CMAKE_BINARY_DIR}/${target_cmakedir}/${_target_export_name}Export.h
				DESTINATION ${target_include_dir}
				COMPONENT dev
			)
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
	if(target_object_targets AND NOT CMAKE_VERSION LESS 3.12) # GREATER
		foreach(_t IN LISTS target_object_targets)
			list(TRANSFORM _target_link REPLACE ${_t} $<BUILD_INTERFACE:${_t}>)
		endforeach()
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
		if(_target_link)
			target_link_libraries(${_t}
				${_target_link}
			)
		endif()
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
	endforeach()
	if(_target_install_targets)
		set(target_install_targets ${target_install_targets} ${_target_install_targets} PARENT_SCOPE)
		# target_install()
	endif()
endfunction()

macro(target_install)
	if(target_install_targets)
		install(
			TARGETS
				${target_install_targets}
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
				DESTINATION ${target_includedir}
				COMPONENT dev
		)
		if(target_default_package)
			install(
				EXPORT
					${PROJECT_NAME}Targets
  			NAMESPACE
					"${PROJECT_NAME}::"
  			DESTINATION
   		 		${target_cmakedir}
  			COMPONENT
   			 dev
 			 )
			list(APPEND target_packages ${target_install_targets})
			string(REPLACE ";" " " target_packages_ "${target_packages}") # 替换分隔符
			write_basic_package_version_file(
				${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
				VERSION ${PROJECT_VERSION}
				COMPATIBILITY SameMajorVersion
			)
			configure_package_config_file(
				${PROJECT_SOURCE_DIR}/cmake/DefaultConfig.cmake.in
				${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
				INSTALL_DESTINATION ${target_cmakedir}
			)
			install(
				FILES
					${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
					${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
				DESTINATION ${target_cmakedir}
				# COMPONENT dev
			)
			unset(target_packages_)
		endif()
		set(target_install_targets)
	endif()
endmacro()

# include(${PROJECT_SOURCE_DIR}/cmake/check.cmake)


target_update_rpath()
