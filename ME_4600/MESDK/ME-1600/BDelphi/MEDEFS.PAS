{File Name 'medefs.pas'
Defines for Meilhaus 32-bit ME-1600 board drivers}

unit medefs;


interface


{Maximum number of ME1600 Boards}
        const ME_MAX_DEVICES  = 32;

{ME1600 Device IDs}
        const ME1600_PCI_DEV_ID =      $1600;




{board identifier }
        const BOARD_00 =  0;
        const BOARD_01 =  1;
        const BOARD_02 =  2;
        const BOARD_03 =  3;
        const BOARD_04 =  4;
        const BOARD_05 =  5;
        const BOARD_06 =  6;
        const BOARD_07 =  7;
        const BOARD_08 =  8;
        const BOARD_09 =  9;
        const BOARD_10 = 10;
        const BOARD_11 = 11;
        const BOARD_12 = 12;
        const BOARD_13 = 13;
        const BOARD_14 = 14;
        const BOARD_15 = 15;
        const BOARD_16 = 16;
        const BOARD_17 = 17;
        const BOARD_18 = 18;
        const BOARD_19 = 19;
        const BOARD_20 = 20;
        const BOARD_21 = 21;
        const BOARD_22 = 22;
        const BOARD_23 = 23;
        const BOARD_24 = 24;
        const BOARD_25 = 25;
        const BOARD_26 = 26;
        const BOARD_27 = 27;
        const BOARD_28 = 28;
        const BOARD_29 = 29;
        const BOARD_30 = 30;
        const BOARD_31 = 31;


{channel identifier}
        const AO_CHAN_00 =  0;
        const AO_CHAN_01 =  1;
        const AO_CHAN_02 =  2;
        const AO_CHAN_03 =  3;
        const AO_CHAN_04 =  4;
        const AO_CHAN_05 =  5;
        const AO_CHAN_06 =  6;
        const AO_CHAN_07 =  7;
        const AO_CHAN_08 =  8;
        const AO_CHAN_09 =  9;
        const AO_CHAN_10 = 10;
        const AO_CHAN_11 = 11;
        const AO_CHAN_12 = 12;
        const AO_CHAN_13 = 13;
        const AO_CHAN_14 = 14;
        const AO_CHAN_15 = 15;


{channel group identifier}
        const AO_GROUP_A = 0;
        const AO_GROUP_B = 1;
        const AO_GROUP_C = 2;
        const AO_GROUP_D = 3;

{scheint verkehrt zu sein}

{output modes}
        const AO_BUFFERED    =  0;
        const AO_TRANSPARENT =  1;


{output ranges}
        const AO_UNIPOLAR = 0;       {   0V ..  10V}
        const AO_BIPOLAR  = 1;       { -10V .. +10V}


{current flow identifier}
        const AO_CURRENT_OFF = 0;
        const AO_CURRENT_ON  = 1;


{current mode identifier}
        const AO_RANGE_0_20  = 0;
        const AO_RANGE_4_20  = 1;




implementation

end.

