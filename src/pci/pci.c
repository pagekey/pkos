#include "../common/types.h"

#define CONFIG_ADDRESS_PORT 0xCF8
#define CONFIG_DATA_PORT 0xCFC

void lspci() {
    println("hello pci");
    // Setup address variable
    u32 address = 0;
    address |= 0x80000000; // bit 31: enable = 1
    // bits 30-24: reserved, leave them as 0
    u8 bus = 0; // 8 bits
    u8 device = 0; // 8 bits
    u8 function = 0; // 3 bits
    u8 offset = 0; // 8 bits
    address |= (bus << 16); // bits 23-16: bus
    address |= (device << 11); // bits 15-11: device
    function &= 0b111;
    address |= (function << 8); // bits 10-8: function
    address |= offset; // bits 7-0: offset

    // Set the PCI address to read
    outl(CONFIG_ADDRESS_PORT, address);

    // Read the value!
    u32 retval = inl(CONFIG_DATA_PORT);
    println("read:");
    u8 result[10];
    print("0x");
    println(itoah(retval, *result));
}
