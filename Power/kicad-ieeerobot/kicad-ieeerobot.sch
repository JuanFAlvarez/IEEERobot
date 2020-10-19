EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Raspberry_Pi_2_3 J?
U 1 1 5F8D2C01
P 1800 4600
F 0 "J?" H 1800 6081 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 1800 5990 50  0000 C CNN
F 2 "" H 1800 4600 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 1800 4600 50  0001 C CNN
	1    1800 4600
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A?
U 1 1 5F8D47DA
P 3650 4450
F 0 "A?" H 3650 3361 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 3650 3270 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 3650 4450 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3650 4450 50  0001 C CNN
	1    3650 4450
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:L298HN U?
U 1 1 5F8D57E6
P 7300 1750
F 0 "U?" H 7300 2631 50  0000 C CNN
F 1 "L298HN" H 7300 2540 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 7350 1100 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000240.pdf" H 7450 2000 50  0001 C CNN
	1    7300 1750
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_Servo M?
U 1 1 5F8E17A6
P 8700 4650
F 0 "M?" H 9032 4715 50  0000 L CNN
F 1 "Motor_Servo" H 9032 4624 50  0000 L CNN
F 2 "" H 8700 4460 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 8700 4460 50  0001 C CNN
	1    8700 4650
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_Servo M?
U 1 1 5F8E1F8E
P 8700 5350
F 0 "M?" H 9032 5415 50  0000 L CNN
F 1 "Motor_Servo" H 9032 5324 50  0000 L CNN
F 2 "" H 8700 5160 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 8700 5160 50  0001 C CNN
	1    8700 5350
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC_ALT M?
U 1 1 5F8E4226
P 9500 1350
F 0 "M?" H 9647 1346 50  0000 L CNN
F 1 "Motor_DC_ALT" H 9647 1255 50  0000 L CNN
F 2 "" H 9500 1260 50  0001 C CNN
F 3 "~" H 9500 1260 50  0001 C CNN
	1    9500 1350
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC_ALT M?
U 1 1 5F8E4832
P 9500 2050
F 0 "M?" H 9647 2046 50  0000 L CNN
F 1 "Motor_DC_ALT" H 9647 1955 50  0000 L CNN
F 2 "" H 9500 1960 50  0001 C CNN
F 3 "~" H 9500 1960 50  0001 C CNN
	1    9500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 2350 9250 2350
Wire Wire Line
	9250 2350 9250 1950
Wire Wire Line
	9250 1950 7900 1950
Wire Wire Line
	9500 1850 7900 1850
Wire Wire Line
	9500 1650 7900 1650
Wire Wire Line
	9500 1150 9250 1150
Wire Wire Line
	9250 1150 9250 1550
Wire Wire Line
	9250 1550 7900 1550
$EndSCHEMATC
