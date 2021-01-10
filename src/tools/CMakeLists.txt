project(chargersvr_tools VERSION 0.1.0)

pkg_check_modules(LIBSYSTEMD REQUIRED libsystemd)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIO REQUIRED gio-2.0)
pkg_check_modules(LIBGIO_UNIX REQUIRED gio-unix-2.0)

#gdbus-codegen --generate-c-code=dbus_generate_client --c-generate-object-manager dbus.xml
include_directories(${LIBGIO_INCLUDE_DIRS})
include_directories(${LIBGIO_UNIX_INCLUDE_DIRS})

set (CHARGER_CMD_SRCS dbus_generate_client.c dbus_client.cpp charger_cmd.cpp)

message(${LIBGIO_INCLUDE_DIRS})

add_executable(charger_cmd ${CHARGER_CMD_SRCS})

target_compile_options(charger_cmd PUBLIC ${LIBGIO_CFLAGS_OTHER} ${LIBSYSTEMD_CFLAGS_OTHER})
target_link_libraries(charger_cmd  pthread ${LIBGIO_LIBRARIES} ${LIBSYSTEMD_LIBRARIES} )

install(TARGETS charger_cmd RUNTIME DESTINATION bin)
