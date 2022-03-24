
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}") # 
set(CPACK_PACKAGE_VENDOR "Provider") # 提供商
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md") # 描述文件
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "README.md") # 描述
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE") # 许可文件
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}") # 从发布的包中安装时，安装位置
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_BINARY_DIR};.git;.gitignore") # 打包source 时忽略的文件
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ") # 列出了源码归档的打包生成器
set(CPACK_GENERATOR "ZIP;TGZ") # 二进制存档生成器
if(UNIX)
	if(CMAKE_SYSTEM_NAME MATCHES Linux)
		list(APPEND CPACK_GENERATOR "DEB")
		set(CPACK_DEBIAN_PACKAGE_MAINTAINER "maintainer")
		set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
		set(CPACK_DEBIAN_PACKAGE_DEPENDS "uuid-dev")

		list(APPEND CPACK_GENERATOR "RPM")
		set(CPACK_RPM_PACKAGE_RELEASE "1")
		# set(CPACK_RPM_PACKAGE_LICENSE "MIT")
		set(CPACK_RPM_PACKAGE_REQUIRES "uuid-dev")
	endif()
endif()
if(WIN32 OR MINGW)
	list(APPEND CPACK_GENERATOR "NSIS")
	set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_NSIS_CONTACT "contact") # maintainer
	set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
endif()
if(APPLE)
	list(APPEND CPACK_GENERATOR "Bundle")
	set(CPACK_BUNDLE_NAME "${PROJECT_NAME}")
	configure_file(${PROJECT_SOURCE_DIR}/cmake/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/Info.plist @ONLY)
	set(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
	set(CPACK_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/cmake/coffee.icns)
endif()
message(STATUS "CPack generators: ${CPACK_GENERATOR}")

include(CPack)
