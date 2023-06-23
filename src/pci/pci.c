#include "../common/types.h"

#define CONFIG_ADDRESS_PORT 0xCF8
#define CONFIG_DATA_PORT 0xCFC

u32 read_pci_port(u8 bus, u8 device, u8 function, u8 offset) {
    u32 address = 0;
    
    // Clear out any bits not within range
    function &= 0b111; // 3 bits
    
    // Set the bits
    address |= 0x80000000; // bit 31: enable = 1
    // bits 30-24: reserved, leave them as 0
    address |= (bus << 16); // bits 23-16: bus
    address |= (device << 11); // bits 15-11: device
    address |= (function << 8); // bits 10-8: function
    address |= offset; // bits 7-0: offset

    // Set the address to read
    outl(CONFIG_ADDRESS_PORT, address);

    // Read data from PCI
    return inl(CONFIG_DATA_PORT);
}

void lspci() {
    u8 string_rep[10];
    for (u8 i = 0; i < 255; i++) {
        for (u8 j = 0; j < 255; j++) {
            for (u8 k = 0; k < 8; k++) {
                u32 pci_data = read_pci_port(i, j, k, 0);
                u16 vendor_id = pci_data & 0xffff;
                u16 device_id = (pci_data >> 16) & 0xffff;
                pci_data = read_pci_port(i, j, k, 0x09);
                u8 base_class = (pci_data >> 16) & 0xff;
                u8 sub_class = (pci_data >> 8) & 0xff;
                u8 progInterface = pci_data & 0xff;
                if (vendor_id == 0xFFFF) {
                    continue;
                }
                print("Bus ");
                print(itoa(i, string_rep));
                print(" Device ");
                print(itoa(j, string_rep));
                print(" Function ");
                print(itoa(k, string_rep));
                print(": Vendor=");
                print(itoah(vendor_id, *string_rep));
                print(" Device=");
                print(itoah(device_id, *string_rep));
                print(" Class=");
                print(itoah(base_class, *string_rep));
                print(" SubClass=");
                print(itoah(sub_class, *string_rep));
                print(" ProgIf=");
                println(itoah(progInterface, *string_rep));
            }
        }
    }
}
