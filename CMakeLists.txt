cmake_minimum_required(VERSION 3.1.0)
#set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(PROJECT_BATTERY_MANAGEMENT charger_battery_management)
project(${PROJECT_BATTERY_MANAGEMENT} VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DQT_NO_DEBUG_OUTPUT)
#add_definitions(-DQT_NO_INFO_OUTPUT)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
message(${CMAKE_INSTALL_RPATH})

find_package(PkgConfig QUIET)
pkg_check_modules(PC_SYSTEMD QUIET libsystemd)
find_library(SYSTEMD_LIBRARIES NAMES systemd ${PC_SYSTEMD_LIBRARY_DIRS})
find_path(SYSTEMD_INCLUDE_DIRS systemd/sd-login.h HINTS ${PC_SYSTEMD_INCLUDE_DIRS})

pkg_check_modules(LIBGIO REQUIRED gio-2.0)
pkg_check_modules(LIBGIO_UNIX REQUIRED gio-unix-2.0)

include_directories(${LIBGIO_INCLUDE_DIRS})
include_directories(${LIBGIO_UNIX_INCLUDE_DIRS})

find_package(Qt5 REQUIRED COMPONENTS Core Sql Network Test)
SET(QT_DONT_USE_QTGUI TRUE)

message(${LIBGIO_INCLUDE_DIRS})

# == Project PROJECT_BATTERY_SERVICE begin ==
set(PROJECT_BATTERY_SERVICE battery_charger_service)

set(BATTERY_SERVICE_SRC
  src/battery_charger_service/service.cpp
  src/battery_charger_service/dbus_generate_server.c
  src/battery_charger_service/dbus_server.cpp
  src/battery_charger_service/battery.cpp
  src/battery_charger_service/charger.cpp
  src/battery_charger_service/log.cpp
  src/battery_charger_service/battery_dbus.cpp
)

add_executable(${PROJECT_BATTERY_SERVICE} ${BATTERY_SERVICE_SRC})
target_link_libraries(${PROJECT_BATTERY_SERVICE} Qt5::Core Qt5::Sql Qt5::Network)
target_compile_options(${PROJECT_BATTERY_SERVICE} PUBLIC ${LIBSYSTEMD_CFLAGS_OTHER} ${LIBGIO_CFLAGS_OTHER})
target_link_libraries(${PROJECT_BATTERY_SERVICE} pthread ${LIBGIO_LIBRARIES}  ${LIBSYSTEMD_LIBRARIES})
install(TARGETS ${PROJECT_BATTERY_SERVICE} RUNTIME DESTINATION bin)

##################### tools begin###################
set (CHARGER_CMD charger_cmd)
set (CHARGER_CMD_SRCS
    src/tools/dbus_generate_client.c
    src/tools/dbus_client.cpp
    src/tools/charger_cmd.cpp)

add_executable(${CHARGER_CMD} ${CHARGER_CMD_SRCS})

target_compile_options(${CHARGER_CMD} PUBLIC ${LIBGIO_CFLAGS_OTHER} ${LIBSYSTEMD_CFLAGS_OTHER})
target_link_libraries(${CHARGER_CMD}  pthread ${LIBGIO_LIBRARIES} ${LIBSYSTEMD_LIBRARIES} )
install(TARGETS ${CHARGER_CMD} RUNTIME DESTINATION bin)




