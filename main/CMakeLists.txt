set(SOURCES "main.c" "app_main_activity.c" "apps/app_led.c")

idf_component_register(SRCS "${SOURCES}" INCLUDE_DIRS ".")
