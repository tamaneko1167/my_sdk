


//
// MiRader
// ADC Ppi Set
// 

//Step1
#start
0x02//
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0xFD // Register Number H
0x00 // Register Number L
0x00
0x01

//Step2
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x42 // Register Number L
0x03
0xCD


//Step3 PLL output : Internal master clock
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x00 // Register Number L
0x00
0x00

//Step4 M=125
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x01 // Register Number L
0x00
0x7D

//Step5 N=38
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x02 // Register Number L
0x00
0x26

//Step6 R=2AX=1AFractional ModeAPLL_EN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x03 // Register Number L
0x10
0x13

//Step7 Read only 0x0001 confirms PLL_LOCK
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x05 // Register Number L
0x00
0x00

//Step8 ADC_ROUTING1_4
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x02 // Register Number L
0x22
0x22

//Step9 ADC_ENABLE
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x41 // Register Number L
0x00
0xFF

//Step10 RM_CRC_ENABLE
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x86 // Register Number L
0x00
0x00

//Step11 LNA_GAIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x00 // Register Number L
0x00
0x00

//Step12 PGA_GAIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x01 // Register Number L
0x00
0x00

//Step13 DECIM_RATE: Sampling Rate=1.2MSps.
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x40 // Register Number L
0x00
0x03

//Step14 HIGH_PASS
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x41 // Register Number L
0x00
0x18

//Step15 PARALLEL_MODE
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0xC1 // Register Number L
0x00
0x04

//Step16 OUTPUT_MODE
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0xC2 // Register Number L
0x00
0x01

//Step17 SPI_CLK_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x80 // Register Number L
0x00
0x00

//Step18 MISO_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x81 // Register Number L
0x00
0x00

//Step19 SS_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x82 // Register Number L
0x00
0x04

//Step20 MOSI_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x83 // Register Number L
0x00
0x00

//Step21 ADDR15_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x84 // Register Number L
0x00
0x00

//Step22 FAULT_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x85 // Register Number L
0x00
0x04

//Step23 FS_ADC_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x86 // Register Number L
0x00
0x00

//Step24 CS_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x87 // Register Number L
0x00
0x04

//Step25 SCLK_ADC_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x88 // Register Number L
0x00
0x00

//Step26 ADC_DOUT0_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x89 // Register Number L
0x00
0x00

//Step27 ADC_DOUT1_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8A // Register Number L
0x00
0x00

//Step28 ADC_DOUT2_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8B // Register Number L
0x00
0x00

//Step29 ADC_DOUT3_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8C // Register Number L
0x00
0x00

//Step30 ADC_DOUT4_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8D // Register Number L
0x00
0x00

//Step31 ADC_DOUT5_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8E // Register Number L
0x00
0x00

//Step32 DATA_READY_PIN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x91 // Register Number L
0x00
0x00

//Step33 XTAL_CTRL
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x92 // Register Number L
0x00
0x01

//Step34 ADC_SETTING1
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x01 // Register Number L
0x03
0x04

//Step35 ADC_SETTING2
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x08 // Register Number L
0x00
0x00

//Step36 ADC_SETTING3
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x0A // Register Number L
0x00
0x09

//Step37 DEJITTER_WINDOW
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x0E // Register Number L
0x00
0x03

//Step38 CRC_EN
//#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0xFD // Register Number H
0x00 // Register Number L
0x00
//0x00 // 0:CRC enable
0x01 // 1:CRC disable


//
// MiRader
// ADC Register Read
// 

//Step0
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0xFD // Register Number H
0x00 // Register Number L

//Step1
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x83 // Register Number L

//Step2
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x84 // Register Number L

//Step3
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x85 // Register Number L

//Step4
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x86 // Register Number L

//Step5
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x87 // Register Number L

//Step6
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x88 // Register Number L

//Step7
#start
0x02
0x33 // ADC Register Read
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x89 // Register Number L
