
//
// MiRader
// Rx Initialization
// 

//Step1 Reserved
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x00
0x00
0x00
0x03

//Step2 Temperature sensor to ATEST
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x00
0x02
0x04
0x06

//Step3 Configure Channel 1
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x20
0x00
0x14
0x99

//Step4 Configure Channel 2 
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x40
0x00
0x14
0x99

//Step5 Configure Channel 3 
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x60
0x00
0x14
0x99

//Step6  Configure Channel 4
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x80
0x00
0x14
0x99

//Step7 Configure LO
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0xA0
0x00
0x00
0x19

//Step8 Power up
#start
0x02
0x31 // Rx Init
0    // Data Number H
4    // Data Number L
0x80
0x00
0x7C
0xA0

