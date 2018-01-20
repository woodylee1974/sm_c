Simple State Machine (C++) Version 1.0.00

Copyright (C) 2017 Woody.Lee All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
The name of the Woody Lee may not be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

---

# Introduction
This state machine is a compact table-driven state machine on C++. In general, a state machine contains a set of states, a set of possible input events and the actions should be performed when an event is recevied on a specified state. A state is changed to another state by performing specified actions when a specified event is received. State diagram or state table is used to describe state transitions, and the later is more formally, and easier to be implemented correspondingly. Although simply state machine can be implemented by nested switch/case or if/else, considering the requirement of re-usability or maintainable, table-driven state machine pattern is recommended to use for more complex cases.

Where we should use state machine:

* simple parser, lexers, ... or any filter-pattern stuffs
* UI logic, which represents enable, disable, checked, unchecked and so on.
* device control, typical sample is like the control of recorder, player, or something like that

When you find you have to do with a group of complex rule and conditions, you should consider to use state machine pattern. A simple example is like:

* A device has 2 states, plugged, unplugged
* This device driver only sends an event named "DEV_NOTIFY" to tell a change happen. Thus, a state machine is required to trace the state of device. When "DEV_NOTIFY" is received on the state - "INSERTED", we need to unmount local file system and change the state from "INSERTED" to "UNPLUGGED". Otherwise, when "DEV_NOTIFY" is received on the state - "UNPLUGGED", we need to mount local file system and change from "UNPLUGGED" to "INSERTED". The difference between you use state machine and not use it is whether "rule" and "mechanism" is separated.

Also, we may describe the rule by a state transition table, as the following

|  	| unplugged 	| plugged 	|
|------------	|--------------------------	|----------------------------	|
| DEV_NOTIFY 	| mount local storage 	| umount local storage 	|

To implement this, we have a class, named USBDevice, which is responsible for implementing the "mechanism" of USB device, such as:
`mountLocalFS()` or `umountLocalFS()`.

Then, we defined the rule by a state machine as the following:
```
    USBDevice usb_dev;
    StateMachine<5> sm("USBDevice", USBDevice::S_UNPLUGGED);

    sm.addTransit(USBDevice::S_UNPLUGGED, E_DEV_NOTIFY, USBDevice::S_INSERTED, &usb_dev, &USBDevice::umountLocalFS);
    sm.addTransit(USBDevice::S_INSERTED,  E_DEV_NOTIFY, USBDevice::S_UNPLUGGED, &usb_dev, &USBDevice::mountLocalFS);
```

When a `DEV_NOTIFY` really emitted, we simply call the following function to force state machine update the state:
```
    sm.updateState(E_DEV_NOTIFY);
```

Thus, you may see what the state change and the transition function does. You may check the state of a state machine:
```
    printf("current state:%d\n", sm.getState());
```

The transition functions has several various:
1. with full parameters.
for example:
```
void mountLocalFS(int old_state, int event, int new_state, void* param);
```

2. with one parameter.
for example:
```
void mountLocalFS(void* param);
```

3. without parameter.
for example:
```
void mountLocalFS(void);
```

Hence, correspondingly, there is 2 trigger:
1. Without data parameter.
for example:
```
sm.updateState(E_DEV_NOTIFY);
```

2. With data parameter.
for example:
```
sm.updateState(E_DEV_NOTIFY, data);
```

# Bug reports

Hope this small piece of code does your help, if it can make your code more simple, more maintainability, I shall feel happy. If you find any problems, or you have any improvement advice, please contact with me by the following e-mail address:

-- By woody(li.woodyli@gmail.com)



