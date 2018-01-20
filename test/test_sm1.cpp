/*
 * Copyright (C) 2007 Woody.Lee All rights reserved.
 */
#include <cstdlib>
#include "c++/statemachine.h"

// Event definition should be public
enum {
    E_DEV_NOTIFY
};

class USBDevice
{
public:
    // State definition should be private.
    enum {
        S_INSERTED,
        S_UNPLUGGED
    };

    USBDevice() {}
    virtual ~USBDevice() {}

    void mountLocalFS(void)
    {
        printf("do mount!\n");
    }

    void umountLocalFS(void)
    {
        printf("do unmount!\n");
    }
};

int main(int argc, char** argv)
{
    StateMachine<5> sm("USBDevice", USBDevice::S_UNPLUGGED);
    USBDevice usb_dev;

    // define transitions by adding from_state, to_state and trigger event.
    // callback function and client object needs to be provided.
    sm.addTransit(USBDevice::S_UNPLUGGED, E_DEV_NOTIFY, USBDevice::S_INSERTED, &usb_dev, &USBDevice::umountLocalFS);
    sm.addTransit(USBDevice::S_INSERTED,  E_DEV_NOTIFY, USBDevice::S_UNPLUGGED, &usb_dev, &USBDevice::mountLocalFS);

    // The following format is also allowed, which has no callback functions.
    // This kind of transition only maintains the change of state machine's internal state.
    //```
    // sm.addTransit(USBDevice::S_INSERTED, E_DEV_NOTIFY, USBDevice::S_UNPLUGGED);
    //```

    printf("Initial state:%d\n", sm.getState());

    sm.updateState(E_DEV_NOTIFY);
    printf("Current state:%d\n", sm.getState());

    sm.updateState(E_DEV_NOTIFY);
    printf("Current state:%d\n", sm.getState());

    sm.updateState(E_DEV_NOTIFY);
    printf("Current state:%d\n", sm.getState());

    return 0;
}

