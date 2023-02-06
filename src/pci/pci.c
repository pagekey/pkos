#define CONFIG_ADDRESS_PORT 0xCF8
#define CONFIG_DATA_PORT 0xCFC

void lspci() {
    println("hello pci");
    // Setup address variable
    unsigned int address = 0;
    address |= 0x80000000; // bit 31: enable = 1
    // bits 30-24: reserved, leave them as 0
    unsigned char bus = 0; // 8 bits
    unsigned char device = 0; // 8 bits
    unsigned char function = 0; // 3 bits
    unsigned char offset = 0; // 8 bits
    address |= (bus << 23); // bits 23-16: bus
    address |= (device << 15); // bits 15-11: device
    function &= 0b111;
    address |= (function << 10); // bits 10-8: function
    address |= offset; // bits 7-0: offset

    // Set the PCI address to read
    ioport_out(CONFIG_ADDRESS_PORT, address);

    // Read the value!
    unsigned int retval = ioport_in(CONFIG_DATA_PORT); // this only reads 16 bits??
    println("read:");
    char result[10];
    print("0x");
    println(itoah(retval, *result));
}
