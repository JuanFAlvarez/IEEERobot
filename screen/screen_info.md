
**Amazon link:**

https://www.amazon.com/Raspberry-Capacitive-Touch-Screen-Monitor/dp/B07QKSSQ66/ref=sr_1_16?dchild=1&keywords=raspberry+pi+lcd+screen+7+inch&qid=1595031241&sr=8-16%E2%80%8B

__Specifications:__

LCD Size: 7.0 inch (Diagonal)

Driver Element: Free Drive for HDMI host

High Resolution: 1024 x 3(RGB) x 600

Dot pitch: 0.0642(W) X 0.1790(H)mm

Active Area: 154.08(w)X 85.92(H)

Module Size: 164.9(w)X124.0(H)x5.7(D)mm

Blacklight: Highlighted LED lamp backlighting

TFT Power(pin Name: 3.3V): The power of the screen is 2.8-3.3V; not use 5V, all the Pin's voltage on the module

Can not be more than 3.3V.


**Setup Directions:**
Setting "config" file
For Raspberry System: After burning official system(not only RASPBIAN system, other system like ubuntu, Kali is also same), please keep the TF card connecting your computer and open TF card root, find file named “config” Open the “config” file and copy the following code in the end of the file, then save.

max_usb_current=1

hdmi_force_hotplug=1

config_hdmi_boost=10

hdmi_group=2

hdmi_mode=87

hdmi_cvt 1024 600 60 6 0 0 0

After setting the code, Raspberry Pi USB can output 1A current. The default is 500mA, if the current is not enough, the screen current supply is insufficient, after the setting is completed, the resolution of the screen can reach 1024*600 pixel
