set(COMPONENT_SRCS "main.cpp app/eInkDisplay.cpp hw_interface/spi_manager.cpp hw_interface/gpio_pin.cpp")
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()

# Build static library, do not build test executables
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTING OFF)
