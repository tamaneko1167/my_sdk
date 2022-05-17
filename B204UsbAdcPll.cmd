
//
// MiRader
// ADC PLL Set
// 

//Step1 PLL output : Internal master clock
#start
0x02
0x32 // ADC PLL Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x00 // Register Number L
0x00
0x00

//Step2 M=125
#start
0x02
0x32 // ADC PLL Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x01 // Register Number L
0x00
0x7D

//Step3 N=38
#start
0x02
0x32 // ADC PLL Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x02 // Register Number L
0x00
0x26

//Step4 R=2AX=1AFractional ModeAPLL_EN
#start
0x02
0x32 // ADC PLL Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x03 // Register Number L
0x10
0x13

//Step5 Read only 0x0001 confirms PLL_LOCK
#start
0x02
0x32 // ADC PLL Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x05 // Register Number L
0x00
0x00

