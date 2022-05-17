
//
// MiRader
// System Setting
// 

#start
0x02
0x09 // System Setting
0x00
0x19
0x00
0x00
0x00
0x00
0x00
0x02 // <- 2:X1,TX2�A0:TX1�Œ�A1:TX2�Œ�
0x00
0x00
0x00
0x00
50 // <- AD�f�[�^��荞�ݒx��(ADC����ADC_DATA_READY��H�ɂȂ�����A4�|�C���g�ڂ���f�[�^�擾)
//100 // <- AD�f�[�^��荞�ݒx��(ADC����ADC_DATA_READY��H�ɂȂ�����A4�|�C���g�ڂ���f�[�^�擾)
4     //�v���f�[�^��
0x00
0x00
0x00 // <- PRI����(�ݒ�l x 100us)
//0x14 // <- 0x14 x 100us = 2ms  0x28 4ms
0     // <- 10 x 100us = 1ms 
0
0
100    // AD����
0x00   // master:0 slave:1
0x00   // Power Down Enable:1 Disable:0
0x00
0x00
0x00
0 // <- TX1,TX2���쎞�ATX1�̃f�[�^���擾�ォ��TX IC��TX2 ON��ݒ�J�n�܂ł̎���(100ms�P��) 0x10 x 100ns = ��1.6us (��1)
//70 // <- TX1,TX2���쎞�ATX1�̃f�[�^���擾�ォ��TX IC��TX2 ON��ݒ�J�n�܂ł̎���(100ms�P��) 0x10 x 100ns = ��1.6us (��1)
//0x4E



//(��1)
//  PLL��TX_DATA���o�͂���̂́ATX IC�ɐݒ�J�n�ォ��10us��Ȃ̂ŁA��L�ݒ�ł͖�11.6us��ɂȂ�܂��B


