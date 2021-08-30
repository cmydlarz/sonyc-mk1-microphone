# THIS FILE IS AUTOMATICALLY GENERATED
# Project: Z:\Users\Charlie\Documents\devel\sonyc\sonycmic\psoc5LP_firmware\PioneerKit_P5LP_USB_Audio\PioneerKit_P5LP_USB_Audio.cydsn\PioneerKit_P5LP_USB_Audio.cyprj
# Date: Fri, 14 Apr 2017 17:31:35 GMT
#set_units -time ns
create_clock -name {AudioClkGen_Clock_SCK(routed)} -period 88.888888888888886 -waveform {0 44.4444444444444} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {AudioClkGen_Ref} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_clock -name {CyPLL_OUT} -period 22.222222222222221 -waveform {0 11.1111111111111} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 22.222222222222221 -waveform {0 11.1111111111111} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 22.222222222222221 -waveform {0 11.1111111111111} [get_pins {ClockBlock/clk_bus_glb_ff}]
create_generated_clock -name {Clock_CIC} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {AudioClkGen_Clock_SCK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 5 9} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {AudioClkGen_Clock_I2S} -source [get_pins {ClockBlock/clk_sync}] -edges {1 9 17} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]


# Component constraints for Z:\Users\Charlie\Documents\devel\sonyc\sonycmic\psoc5LP_firmware\PioneerKit_P5LP_USB_Audio\PioneerKit_P5LP_USB_Audio.cydsn\TopDesign\TopDesign.cysch
# Project: Z:\Users\Charlie\Documents\devel\sonyc\sonycmic\psoc5LP_firmware\PioneerKit_P5LP_USB_Audio\PioneerKit_P5LP_USB_Audio.cydsn\PioneerKit_P5LP_USB_Audio.cyprj
# Date: Fri, 14 Apr 2017 17:31:15 GMT
