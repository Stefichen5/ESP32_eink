set(COMPONENT_SRCS "main.cpp \
    app/eInkDisplayBase.cpp \
    app/eInkDisplay2in9.cpp \
    app/gui_paint.cpp \
    app/epd_image \
    hw_interface/spi_manager.cpp \
    hw_interface/gpio_pin.cpp \
    app/Fonts/font8.c \
    app/Fonts/font12.c \
    app/Fonts/font16.c \
    app/Fonts/font20.c \
    app/Fonts/font24.c ")
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()

# Build static library, do not build test executables
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTING OFF)
