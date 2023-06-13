
//
// MiRader
// VCO Calibration Setting
// 

//Step1 Master Reset.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x02
0x00
0x00
0x07

//Step2 Counter Rset.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x00
0x00
0x00
0x2B

//Step3 Counter Enabled.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x00
0x00
0x00
0x0B

//Step4 
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x1D
0x32
0xA6
0x4A

//Step5 
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x2A
0x20
0xB9
0x29

//Step6 Frequency Calibration Divider Clock to 100kHz.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x40
0x00
0x3E
0x88

//Step7 Power-Up the device and LO (10 É s).
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0xE5
0x20
#wait 0.001

//Step8 R counter clock to 50 MHz,Calibration clock
//      to 100 kHz. Reference Doubler Enabled.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x01
0x1F
//0x4C
0x40
0x27

//Step9 LSB FRAC = 0. 
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x00
0x00
0x00
0x06

//Step10 INT = 241. MSB FRAC = 2048.( 24.15GHz)
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x01
0xE3
0x00
0x05

//Step11 ATEST pin to high impedance.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x00
0x20
0x00
0x04

//Step12 IO level to 3.3 V.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x01
0x89
0x08
0x03

//Step13 ADC clock to 1 MHz.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x00
0x02
0x06
0x42

//Step14 Set Tx amplitude levelÅiMaxÅj
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0xFF
0xF7
0xFF
0xE1

//Step15 VCO frequency calibration (800 É s).
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0xE7
0x20
#wait 0.001

//Step16 Tx1 on, Tx2 off, and LO on.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0xE5
0x60

//Step17 Tx1 amplitude calibration (400 É s)
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0xED
0x60
#wait 0.001

//Step18 Tx1 off, Tx2 on, and LO on.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0xE5
0xA0

//Step19 Tx2 amplitude calibration (400 É s).
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0xF5
0xA0
#wait 0.001

//Step20 
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x28
0x00
0xB9
0x29

//Step21 Disabled the R and N counters.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x80
0x9F
0x25
0xA0


