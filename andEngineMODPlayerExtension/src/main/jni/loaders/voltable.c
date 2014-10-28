#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "load.h"

/*
from Tom Hargreaves <hex@freezone.co.uk>
date Sat, Jan 16, 2010 at 9:38 PM

the volume table for volume commands and the VIDC lookup table for
sample conversion are (should be) one and the same. A full-precision
version of the table is as follows:

0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46
48 52 56 60 64 68 72 76 80 84 88 92 96 100 104 108
112 120 128 136 144 152 160 168 176 184 192 200 208 216 224 232
240 256 272 288 304 320 336 352 368 384 400 416 432 448 464 480
496 528 560 592 624 656 688 720 752 784 816 848 880 912 944 976
1008 1072 1136 1200 1264 1328 1392 1456 1520 1584 1648 1712 1776 1840 1904 1968
2032 2160 2288 2416 2544 2672 2800 2928 3056 3184 3312 3440 3568 3696 3824 3952 */


/* Claudio's note: this is a curve approximation using linear segments,
 * so I'll perform linear interpolation to have all 256 values
 */

int arch_vol_table[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x08,
	0x09, 0x09, 0x09, 0x09, 0x0a, 0x0a, 0x0a, 0x0a,
	0x0b, 0x0b, 0x0b, 0x0b, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0d, 0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0e, 0x0e,
	0x0f, 0x0f, 0x10, 0x10, 0x11, 0x11, 0x12, 0x12,
	0x13, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 0x16,
	0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a,
	0x1b, 0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e,
	0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e,
	0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
	0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e,
	0x40, 0x41, 0x43, 0x45, 0x47, 0x49, 0x4b, 0x4d,
	0x4f, 0x51, 0x53, 0x55, 0x57, 0x59, 0x5b, 0x5d,
	0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e,
	0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,
	0x81, 0x83, 0x87, 0x8b, 0x8f, 0x93, 0x97, 0x9b,
	0xa0, 0xa4, 0xa8, 0xac, 0xb0, 0xb4, 0xb8, 0xbc,
	0xc1, 0xc5, 0xc9, 0xcd, 0xd1, 0xd5, 0xd9, 0xdd,
	0xe2, 0xe6, 0xea, 0xee, 0xf2, 0xf6, 0xfa, 0xff,
	0xff
};

#if 0
int arch_vol_table[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09,
	0x09, 0x09, 0x09, 0x09, 0x0a, 0x0a, 0x0a, 0x0a,
	0x0b, 0x0b, 0x0b, 0x0b, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f,
	0x0f, 0x10, 0x10, 0x10, 0x11, 0x11, 0x12, 0x12,
	0x12, 0x13, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16,
	0x16, 0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a,
	0x1a, 0x1b, 0x1c, 0x1c, 0x1d, 0x1e, 0x1e, 0x1f,
	0x20, 0x20, 0x21, 0x22, 0x23, 0x23, 0x24, 0x25,
	0x26, 0x27, 0x28, 0x28, 0x29, 0x2a, 0x2b, 0x2c,
	0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x33, 0x34, 0x35,
	0x36, 0x37, 0x38, 0x3a, 0x3b, 0x3c, 0x3e, 0x3f,
	0x40, 0x42, 0x43, 0x45, 0x46, 0x48, 0x49, 0x4b,
	0x4d, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a,
	0x5b, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6b,
	0x6d, 0x6f, 0x72, 0x74, 0x77, 0x7a, 0x7c, 0x7f,
	0x82, 0x85, 0x88, 0x8b, 0x8e, 0x91, 0x94, 0x97,
	0x9b, 0x9e, 0xa1, 0xa5, 0xa9, 0xac, 0xb0, 0xb4,
	0xb8, 0xbc, 0xc0, 0xc4, 0xc9, 0xcd, 0xd2, 0xd6,
	0xdb, 0xe0, 0xe5, 0xea, 0xef, 0xf4, 0xfa, 0xff,
	0xff
};
#endif

