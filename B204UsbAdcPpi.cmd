
//
// MiRader
// ADC Ppi Set
// 

//Step1 0x0040 0x0001 Master Enable
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x40 // Register Number L
0x00
0x01

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x40 // Register Number L


//Step2 0x0042 0x03cd Power Enable
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x42 // Register Number L
0x03
0xCD

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x42 // Register Number L

//Step3 0x0000 PLL output : Internal master clock
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x00 // Register Number L
0x00
0x02
//0x00


// Register Read 0x0000
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x00 // Register Number L


//Step4 0x0001  M=125
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x01 // Register Number L
0x00
0x7D

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x01 // Register Number L


//Step5 0x0002  N=38
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x02 // Register Number L
0x00
0x26

// Register Read 0x0002
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x02 // Register Number L

 
//Step6 0x0003  R=2AX=1AFractional ModeAPLL_EN
// 50MHz * 1/R * (X +N/M) = 115.2MHz
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x03 // Register Number L
0x10
0x03 
//0x13

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x03 // Register Number L


//Step7 0x0005  Read only 0x0001 confirms PLL_LOCK
//#start
//0x02
//0x32 // ADC Ppi Set
//0    // Data Number H
//4    // Data Number L
//0x00 // Register Number H
//0x05 // Register Number L
//0x00
//0x00

// Register Read 0x0005
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x05 // Register Number L


//Step8 0x0102  ADC_ROUTING1_4
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x02 // Register Number L
//0x00 // ADC disabled
//0x00 // ADC disabled
//0x11 // Normal
//0x11 // Normal
0x22 // Normal(Bypass EQ)
0x22 // Normal(Bypass EQ)
//0x33 // Bypass(LNA PGA EQ)
//0x33 // Bypass(LNA PGA EQ)
//0x55 // TEST
//0x55 // TEST

// 000 ADC Disabled.
// 001 LNA PGA EQ Path.
// 010 LNA PGA Path (Bypass EQ).
// 011 Bypass LNA, PGA, and EQ.
// 100 Swap Channels.
// 101 Use Test Pin.

// Register Read 0x0102
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0x02 // Register Number L




//Step9 0x0041 ADC_ENABLE
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x41 // Register Number L
0x00
0xFF // 4ch
//0xCC // 2ch ????
//0x33 // 2ch   ch1, ch2

// Register Read 
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x41 // Register Number L



//Step10 0x0086 RM_CRC_ENABLE
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x00 // Register Number H
0x86 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x00 // Register Number H
0x86 // Register Number L


//Step11 0x0100 LNA_GAIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x00 // Register Number L
0x00
//0x00 // x2   6dB
//0x55 // x4  12dB
//0xaa // x8  18dB
0xff // x16 24dB

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0x00 // Register Number L


//Step12 0x0101  PGA_GAIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x01 // Register Number L
0x00
//0x00 // 1.4dB
//0x55 // 2.8dB
//0xaa // 5.6dB
0xff // 11.2dB

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0x01 // Register Number L



//Step13 0x0140 DECIM_RATE: Sampling Rate=1.2MSps.
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x40 // Register Number L
0x00
//0x03 // 1/48  1.2MSps
0x02 //   1/32  1.8MSps
//0x00 // 

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0x40 // Register Number L


//Step14 0x0141 HIGH_PASS
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0x41 // Register Number L
0x00
0x18
//0x58

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0x41 // Register Number L


//Step15 0x01c1 PARALLEL_MODE
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0xC1 // Register Number L
0x00
0x04

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0xC1 // Register Number L



//Step16 0x01c2 OUTPUT_MODE
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x01 // Register Number H
0xC2 // Register Number L
0x00
0x01

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x01 // Register Number H
0xC2 // Register Number L


//Step17 0x0280 SPI_CLK_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x80 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x80 // Register Number L


//Step18 0x0281 MISO_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x81 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x81 // Register Number L


//Step19 0x0282 SS_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x82 // Register Number L
0x00
0x04

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x82 // Register Number L


//Step20 0x0283 MOSI_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x83 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x83 // Register Number L


//Step21 0x0284 ADDR15_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x84 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x84 // Register Number L


//Step22 0x0285 FAULT_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x85 // Register Number L
0x00
0x04

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x85 // Register Number L


//Step23 0x0286 FS_ADC_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x86 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x86 // Register Number L


//Step24 0x0287 CS_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x87 // Register Number L
0x00
0x04

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x87 // Register Number L


//Step25 0x0288 SCLK_ADC_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x88 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x88 // Register Number L


//Step26 ADC_DOUT0_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x89 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x89 // Register Number L


//Step27 ADC_DOUT1_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8A // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x8A // Register Number L


//Step28 ADC_DOUT2_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8B // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x8B // Register Number L


//Step29 ADC_DOUT3_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8C // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x8C // Register Number L


//Step30 ADC_DOUT4_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8D // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x8D // Register Number L


//Step31 ADC_DOUT5_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x8E // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x8E // Register Number L


//Step32 0x0291 DATA_READY_PIN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x91 // Register Number L
0x00
0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x91 // Register Number L


//Step33 0x0292 XTAL_CTRL
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x02 // Register Number H
0x92 // Register Number L
0x00
0x00
//0x01

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x02 // Register Number H
0x92 // Register Number L





//Step34 0x0301 ADC_SETTING1
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number L
0x01 // Register Number L

//0x00 // EQ54kHz      Register Number H
//0x01 // EQ45kHz      Register Number H
//0x02 // EQ37kHz      Register Number H
0x03 // EQ32kHz      Register Number H

//0x02 // new2 Peak Detect Off Improve off
0x06 //new Peak Detect On Improve off
//0x04 //  Peak Detect On Improve on




// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x03 // Register Number H
0x01 // Register Number L


//Step35 0x0308 ADC_SETTING2
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x08 // Register Number L
0x00
0x13 // new
//0x00

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x03 // Register Number H
0x08 // Register Number L


//Step36 0x030a ADC_SETTING3
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x0A // Register Number L
0x00
0x00 // new
//0x09

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x03 // Register Number H
0x0A // Register Number L


//Step37 0x030e DEJITTER_WINDOW
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0x03 // Register Number H
0x0E // Register Number L
0x00
0x00 // new
//0x03

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0x03 // Register Number H
0x0E // Register Number L


//Step38 CRC_EN
#start
0x02
0x32 // ADC Ppi Set
0    // Data Number H
4    // Data Number L
0xFD // Register Number H
0x00 // Register Number L
0x00
//0x00 // 0:CRC enable
0x01 // 1:CRC disable

// Register Read
#start
0x02
0x33 // ADC Ppi Set
0    // Data Number H
2    // Data Number L
0xFD // Register Number H
0x00 // Register Number L


