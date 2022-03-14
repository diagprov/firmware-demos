cmake_minimum_required(VERSION 3.20.5)

#set(BOARD nucleo_f411re)
set(BOARD nrf52840dk_nrf52840)
list(APPEND SHIELD "dfrobot_can_bus_v2_0")
list(APPEND SHIELD "adafruit_2_8_tft_touch_v2")

find_package(Zephyr)
project(haldisplaynode)

FILE(GLOB app_sources
            src/main.c 
            #src/sensor.c 
            src/lcd.c)
        #)#src/canbus.c)
target_sources(app PRIVATE ${app_sources})
