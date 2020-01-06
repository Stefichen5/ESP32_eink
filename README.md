# ESP32 Waveshare eInk Library

This is my slightly modified version of the waveshare eInk library for the esp32.

## My take on the project

Waveshare provides a good sample code. I copied a big portion of what they provide and slightly modified it to use some of the benefits of C++ (mainly classes/objects).

I'm not 100% satisfied with the structure yet (especially the implementation of the specific display commands), but it's working (for me at least).

## Usage

First, create an SPI object and gpio_pin objects for the pins DC, RST, BUSY.

```c++
gpio_pin pin_dc(GPIO_NUM_27);
gpio_pin pin_rst(GPIO_NUM_26);
gpio_pin pin_busy(GPIO_NUM_25);

spi_manager spi(GPIO_NUM_14, GPIO_NUM_13, GPIO_NUM_15, HSPI_HOST);
```

Then create an instance of your eInk Display:

```c++
eInkDisplay2in9 display(&spi, &pin_dc, &pin_busy, &pin_rst);
```

Now you can create a new painter-object, as well as an image:

```c++
gui_paint paint(display.get_width(), display.get_height());
epd_image image(display.get_width(), display.get_height(), epd_image::e_rotate_90, WHITE);
```

Next step: draw something:

```c++
paint.draw_string(&image, 0,0,"hello world", &Font12, BLACK, WHITE);
```

And finally, bring it to the display:

```c++
display.draw_image(&image);
```



## Structure

The base eInk display is modelled by the class "eInkDisplayBase". To implement a specific display (let's say, 2.9", BW), there will be a derived class that implements all the specific commands that need to be sent (just look at the code, it's easier than explaining).

I tried to keep the namings and parameters as close to the stock implementation from Waveshare as possible. However, I changed some things a little bit to better fit my personal preferences/style. 

## Todo

Since I currently only own the 2.9" eInk display, I can only implement and test that. I might add more in the future (or you - and then send me the patch so I can merge it)