#ifndef __FDLRASTER_H
#define __FDLRASTER_H

#define MNSL00  0x00
#define MNSL10  0x02
#define SL      0x03
#define MNSR00  0x04
#define MNSR10  0x06
#define SR      0x07
#define MNCL00  0x08
#define MNCL10  0x0A
#define MNCL11  0x0B
#define MNCR00  0x0C
#define MNCR10  0x0E
#define MNCR11  0x0F
#define WWSL00  0x10
#define WWSL10  0x12
#define WWSR00  0x14
#define WWSR10  0x16
#define WWCL00  0x18
#define WWCL10  0x1A
#define WWCL11  0x1B
#define WWCR00  0x1C
#define WWCR10  0x1E
#define WWCR11  0x1F
#define XW0ADD  0x20
#define XW1ADD  0x21
#define XW2ADD  0x22
#define XW3ADD  0x23
#define XW4ADD  0x24
#define XW5ADD  0x25
#define XW6ADD  0x26
#define XW7ADD  0x27
#define XW0SUB  0x28
#define XW1SUB  0x29
#define XW2SUB  0x2A
#define XW3SUB  0x2B
#define XW4SUB  0x2C
#define XW5SUB  0x2D
#define XW6SUB  0x2E
#define XW7SUB  0x2F
#define LOAD    0x30
#define XLOAD   0x31
#define MOVX    0x32
#define MOVY    0x33
#define MNSTOR  0x34
#define WWSTOR  0x35
#define SWFX    0x36
#define SWFY    0x37
#define YW0ADD  0x40
#define YW1ADD  0x41
#define YW2ADD  0x42
#define YW3ADD  0x43
#define YW4ADD  0x44
#define YW5ADD  0x45
#define YW6ADD  0x46
#define YW7ADD  0x47
#define YW0SUB  0x48
#define YW1SUB  0x49
#define YW2SUB  0x4A
#define YW3SUB  0x4B
#define YW4SUB  0x4C
#define YW5SUB  0x4D
#define YW6SUB  0x4E
#define YW7SUB  0x4F
#define XV0ADD  0x50
#define XV1ADD  0x51
#define XV2ADD  0x52
#define XV3ADD  0x53
#define XV4ADD  0x54
#define XV5ADD  0x55
#define XV6ADD  0x56
#define XV7ADD  0x57
#define XV0SUB  0x58
#define XV1SUB  0x59
#define XV2SUB  0x5A
#define XV3SUB  0x5B
#define XV4SUB  0x5C
#define XV5SUB  0x5D
#define XV6SUB  0x5E
#define XV7SUB  0x5F
#define YV0ADD  0x60
#define YV1ADD  0x61
#define YV2ADD  0x62
#define YV3ADD  0x63
#define YV4ADD  0x64
#define YV5ADD  0x65
#define YV6ADD  0x66
#define YV7ADD  0x67
#define YV0SUB  0x68
#define YV1SUB  0x69
#define YV2SUB  0x6A
#define YV3SUB  0x6B
#define YV4SUB  0x6C
#define YV5SUB  0x6D
#define YV6SUB  0x6E
#define YV7SUB  0x6F
#define ENDSUB  0x70
#define ENDSTR  0x71
#define ENDCHR  0x7F

#define MNSL00b ( 0x00 + 0x80 )
#define MNSL10b ( 0x02 + 0x80 )
#define MNSR00b ( 0x04 + 0x80 )
#define MNSR10b ( 0x06 + 0x80 )
#define MNCL00b ( 0x08 + 0x80 )
#define MNCL10b ( 0x0A + 0x80 )
#define MNCL11b ( 0x0B + 0x80 )
#define MNCR00b ( 0x0C + 0x80 )
#define MNCR10b ( 0x0E + 0x80 )
#define MNCR11b ( 0x0F + 0x80 )
#define WWSL00b ( 0x10 + 0x80 )
#define WWSL10b ( 0x12 + 0x80 )
#define WWSR00b ( 0x14 + 0x80 )
#define WWSR10b ( 0x16 + 0x80 )
#define WWCL00b ( 0x18 + 0x80 )
#define WWCL10b ( 0x1A + 0x80 )
#define WWCL11b ( 0x1B + 0x80 )
#define WWCR00b ( 0x1C + 0x80 )
#define WWCR10b ( 0x1E + 0x80 )
#define WWCR11b ( 0x1F + 0x80 )
#define MNSTORb ( 0x34 + 0x80 )
#define WWSTORb ( 0x35 + 0x80 )

#define LMCL11b 0x78
#define LMCR11b 0x79
#define LWCL11b 0x7A
#define LWCR11b 0x7B
#define XMCL11b 0x7C
#define XMCR11b 0x7D
#define XWCL11b 0x7E
#define XWCR11b 0x7F

#define XV0A    ( 0x50 + 0x80 )
#define XV1A    ( 0x51 + 0x80 )
#define XV2A    ( 0x52 + 0x80 )
#define XV3A    ( 0x53 + 0x80 )
#define XV4A    ( 0x54 + 0x80 )
#define XV5A    ( 0x55 + 0x80 )
#define XV6A    ( 0x56 + 0x80 )
#define XV7A    ( 0x57 + 0x80 )
#define XV0S    ( 0x58 + 0x80 )
#define XV1S    ( 0x59 + 0x80 )
#define XV2S    ( 0x5A + 0x80 )
#define XV3S    ( 0x5B + 0x80 )
#define XV4S    ( 0x5C + 0x80 )
#define XV5S    ( 0x5D + 0x80 )
#define XV6S    ( 0x5E + 0x80 )
#define XV7S    ( 0x5F + 0x80 )
#define YV0A    ( 0x60 + 0x80 )
#define YV1A    ( 0x61 + 0x80 )
#define YV2A    ( 0x62 + 0x80 )
#define YV3A    ( 0x63 + 0x80 )
#define YV4A    ( 0x64 + 0x80 )
#define YV5A    ( 0x65 + 0x80 )
#define YV6A    ( 0x66 + 0x80 )
#define YV7A    ( 0x67 + 0x80 )
#define YV0S    ( 0x68 + 0x80 )
#define YV1S    ( 0x69 + 0x80 )
#define YV2S    ( 0x6A + 0x80 )
#define YV3S    ( 0x6B + 0x80 )
#define YV4S    ( 0x6C + 0x80 )
#define YV5S    ( 0x6D + 0x80 )
#define YV6S    ( 0x6E + 0x80 )
#define YV7S    ( 0x6F + 0x80 )

#define XW0A    ( 0x20 + 0x80 )
#define XW1A    ( 0x21 + 0x80 )
#define XW2A    ( 0x22 + 0x80 )
#define XW3A    ( 0x23 + 0x80 )
#define XW4A    ( 0x24 + 0x80 )
#define XW5A    ( 0x25 + 0x80 )
#define XW6A    ( 0x26 + 0x80 )
#define XW7A    ( 0x27 + 0x80 )
#define XW0S    ( 0x28 + 0x80 )
#define XW1S    ( 0x29 + 0x80 )
#define XW2S    ( 0x2A + 0x80 )
#define XW3S    ( 0x2B + 0x80 )
#define XW4S    ( 0x2C + 0x80 )
#define XW5S    ( 0x2D + 0x80 )
#define XW6S    ( 0x2E + 0x80 )
#define XW7S    ( 0x2F + 0x80 )
#define YW0A    ( 0x40 + 0x80 )
#define YW1A    ( 0x41 + 0x80 )
#define YW2A    ( 0x42 + 0x80 )
#define YW3A    ( 0x43 + 0x80 )
#define YW4A    ( 0x44 + 0x80 )
#define YW5A    ( 0x45 + 0x80 )
#define YW6A    ( 0x46 + 0x80 )
#define YW7A    ( 0x47 + 0x80 )
#define YW0S    ( 0x48 + 0x80 )
#define YW1S    ( 0x49 + 0x80 )
#define YW2S    ( 0x4A + 0x80 )
#define YW3S    ( 0x4B + 0x80 )
#define YW4S    ( 0x4C + 0x80 )
#define YW5S    ( 0x4D + 0x80 )
#define YW6S    ( 0x4E + 0x80 )
#define YW7S    ( 0x4F + 0x80 )

#define ENDSUBb 0xF0


#endif
