#ifndef __PCI_H
#define __PCI_H

#include "../common/types.h"

struct PCI_Device {
    u16 vendor_id;
    u16 device_id;
    u8 base_class;
    u8 sub_class;
    u8 prog_interface;
    u16 command;
    u16 status;
};

struct PCI_Device get_pci_device(u8 bus, u8 slot, u8 function);
void lspci();
void idetest();

#endif