//
// MiRader
// VCO ReCalibration Setting (+2dBm)
// 

//Step1 EnableCounters.Tx1 off,Tx2 off,LO on.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x81
0x9F
0xE5
0x20

//Step2 
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x2A
0x20
0xB9
0x29

//Step3 Set Tx amplitude levelÅi+2dBmÅj
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0xFF
0xF7
0xE3
0xC1

//Step4 VCO frequency calibration (800 É s).
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x81
0x9F
0xE7
0x20
#wait 0.001

//Step5 Tx1 on, Tx2 off, and LO on.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x81
0x9F
0xE5
0x60

//Step6 Tx1 amplitude calibration (400 É s)
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x81
0x9F
0xED
0x60
#wait 0.001

//Step7 Tx1 off, Tx2 on, and LO on.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x81
0x9F
0xE5
0xA0

//Step8 Tx2 amplitude calibration (400 É s).
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

//Step9 
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x28
0x00
0xB9
0x29

//Step10 Disabled the R and N counters.
#start
0x02
0x30 // VCO CAL
0    // Data Number H
4    // Data Number L
0x81
0x9F
0x25
0xA0

