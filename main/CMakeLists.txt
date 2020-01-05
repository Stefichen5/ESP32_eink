set(COMPONENT_SRCS "main.cpp \
    app/eInkDisplayBase.cpp \
    app/eInkDisplay2in9.cpp \
    app/gui_paint.cpp \
    app/epd_image \
    hw_interface/spi_manager.cpp \
    hw_interface/gpio_pin.cpp")
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()

# Build static library, do not build test executables
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTING OFF)
