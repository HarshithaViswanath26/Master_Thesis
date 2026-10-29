mimose-fw/

├── app/

│   └── main.c

├── bsp/

│   ├── board\_pins.h           // pin map from schematic

│   ├── board.c/.h             // board init, creates bus + device instances

├── drivers/

│   ├── common/

│   │   ├── drv\_status.h       // shared return codes

│   │   └── i2c\_bus.h          // bus interface for all sensor drivers

│   ├── ads122c04/

│   │   ├── ads122c04.h        // public API

│   │   ├── ads122c04\_reg.h    // commands, registers, bit fields

│   │   └── ads122c04.c

│   ├── lsm6dsl/               // same 3 files

│   └── stts22h/               // same 3 files

├── hal/

│   ├── i2c.c/.h               // bare-metal I2C, per-flag timeouts

│   └── timebase.c/.h          // DWT

├── services/  middleware/  platform/  tests/  docs/

