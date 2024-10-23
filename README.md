# rgb-control
Control MSI Mystic Light Motherboard

Addressable RGB fans

## Install udev rules
./setup_udev.sh

## Notes

Motherboard B550M-VC Pro Wifi (MS-7C95)

MSI Mystic Light 185 Controller (vendor: 0x1462, product: 0x7c95)

APROM FW Versions APROM 0.6, LDROM 1.5

Appears to be no onboard LEDs but onboard-led in packet might still be something

Ports active ports are jrgb1, jrgb2, jrainbow1, jrainbow2

However my motherboard only uses jrainbow1

LED addresses seem to be start at address 8

14cm thermalright fans have 9 LEDs
12cm thermalright fans have 8 LEDs

Sync mode repeats every X cycles so the fans have the same color, however this doesn't
work well for sharp rotating things because the mismatch in fan LED count (The 12 inch fan skips a cycle)

Sadly, my motherboard doesn't support individual LEDs so I'm just going to stick to the modes
