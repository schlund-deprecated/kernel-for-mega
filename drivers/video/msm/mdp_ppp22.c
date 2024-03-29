/* drivers/video/msm/mdp_ppp22.c
 *
 * Copyright (C) 2007 QUALCOMM Incorporated
 * Copyright (C) 2007 Google Incorporated
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/msm_mdp.h>

#include "mdp_hw.h"
#include "mdp_ppp.h"

struct mdp_table_entry {
	uint32_t reg;
	uint32_t val;
};

enum {
	MDP_DOWNSCALE_PT2TOPT4,
	MDP_DOWNSCALE_PT4TOPT6,
	MDP_DOWNSCALE_PT6TOPT8,
	MDP_DOWNSCALE_PT8TO1,
	MDP_DOWNSCALE_MAX,

	/* not technically in the downscale table list */
	MDP_DOWNSCALE_BLUR,
};

static int downscale_x_table;
static int downscale_y_table;

static struct mdp_table_entry mdp_upscale_table[] = {
	{ 0x5fffc, 0x0 },
	{ 0x50200, 0x7fc00000 },
	{ 0x5fffc, 0xff80000d },
	{ 0x50204, 0x7ec003f9 },
	{ 0x5fffc, 0xfec0001c },
	{ 0x50208, 0x7d4003f3 },
	{ 0x5fffc, 0xfe40002b },
	{ 0x5020c, 0x7b8003ed },
	{ 0x5fffc, 0xfd80003c },
	{ 0x50210, 0x794003e8 },
	{ 0x5fffc, 0xfcc0004d },
	{ 0x50214, 0x76c003e4 },
	{ 0x5fffc, 0xfc40005f },
	{ 0x50218, 0x73c003e0 },
	{ 0x5fffc, 0xfb800071 },
	{ 0x5021c, 0x708003de },
	{ 0x5fffc, 0xfac00085 },
	{ 0x50220, 0x6d0003db },
	{ 0x5fffc, 0xfa000098 },
	{ 0x50224, 0x698003d9 },
	{ 0x5fffc, 0xf98000ac },
	{ 0x50228, 0x654003d8 },
	{ 0x5fffc, 0xf8c000c1 },
	{ 0x5022c, 0x610003d7 },
	{ 0x5fffc, 0xf84000d5 },
	{ 0x50230, 0x5c8003d7 },
	{ 0x5fffc, 0xf7c000e9 },
	{ 0x50234, 0x580003d7 },
	{ 0x5fffc, 0xf74000fd },
	{ 0x50238, 0x534003d8 },
	{ 0x5fffc, 0xf6c00112 },
	{ 0x5023c, 0x4e8003d8 },
	{ 0x5fffc, 0xf6800126 },
	{ 0x50240, 0x494003da },
	{ 0x5fffc, 0xf600013a },
	{ 0x50244, 0x448003db },
	{ 0x5fffc, 0xf600014d },
	{ 0x50248, 0x3f4003dd },
	{ 0x5fffc, 0xf5c00160 },
	{ 0x5024c, 0x3a4003df },
	{ 0x5fffc, 0xf5c00172 },
	{ 0x50250, 0x354003e1 },
	{ 0x5fffc, 0xf5c00184 },
	{ 0x50254, 0x304003e3 },
	{ 0x5fffc, 0xf6000195 },
	{ 0x50258, 0x2b0003e6 },
	{ 0x5fffc, 0xf64001a6 },
	{ 0x5025c, 0x260003e8 },
	{ 0x5fffc, 0xf6c001b4 },
	{ 0x50260, 0x214003eb },
	{ 0x5fffc, 0xf78001c2 },
	{ 0x50264, 0x1c4003ee },
	{ 0x5fffc, 0xf80001cf },
	{ 0x50268, 0x17c003f1 },
	{ 0x5fffc, 0xf90001db },
	{ 0x5026c, 0x134003f3 },
	{ 0x5fffc, 0xfa0001e5 },
	{ 0x50270, 0xf0003f6 },
	{ 0x5fffc, 0xfb4001ee },
	{ 0x50274, 0xac003f9 },
	{ 0x5fffc, 0xfcc001f5 },
	{ 0x50278, 0x70003fb },
	{ 0x5fffc, 0xfe4001fb },
	{ 0x5027c, 0x34003fe },
};

static struct mdp_table_entry mdp_downscale_x_table_PT2TOPT4[] = {
	{ 0x5fffc, 0x740008c },
	{ 0x50280, 0x33800088 },
	{ 0x5fffc, 0x800008e },
	{ 0x50284, 0x33400084 },
	{ 0x5fffc, 0x8400092 },
	{ 0x50288, 0x33000080 },
	{ 0x5fffc, 0x9000094 },
	{ 0x5028c, 0x3300007b },
	{ 0x5fffc, 0x9c00098 },
	{ 0x50290, 0x32400077 },
	{ 0x5fffc, 0xa40009b },
	{ 0x50294, 0x32000073 },
	{ 0x5fffc, 0xb00009d },
	{ 0x50298,  0x31c0006f },
	{ 0x5fffc,  0xbc000a0 },
	{ 0x5029c,  0x3140006b },
	{ 0x5fffc,  0xc8000a2 },
	{ 0x502a0,  0x31000067 },
	{ 0x5fffc,  0xd8000a5 },
	{ 0x502a4,  0x30800062 },
	{ 0x5fffc,  0xe4000a8 },
	{ 0x502a8,  0x2fc0005f },
	{ 0x5fffc,  0xec000aa },
	{ 0x502ac,  0x2fc0005b },
	{ 0x5fffc,  0xf8000ad },
	{ 0x502b0,  0x2f400057 },
	{ 0x5fffc,  0x108000b0 },
	{ 0x502b4,  0x2e400054 },
	{ 0x5fffc,  0x114000b2 },
	{ 0x502b8,  0x2e000050 },
	{ 0x5fffc,  0x124000b4 },
	{ 0x502bc,  0x2d80004c },
	{ 0x5fffc,  0x130000b6 },
	{ 0x502c0,  0x2d000049 },
	{ 0x5fffc,  0x140000b8 },
	{ 0x502c4,  0x2c800045 },
	{ 0x5fffc,  0x150000b9 },
	{ 0x502c8,  0x2c000042 },
	{ 0x5fffc,  0x15c000bd },
	{ 0x502cc,  0x2b40003e },
	{ 0x5fffc,  0x16c000bf },
	{ 0x502d0,  0x2a80003b },
	{ 0x5fffc,  0x17c000bf },
	{ 0x502d4,  0x2a000039 },
	{ 0x5fffc,  0x188000c2 },
	{ 0x502d8,  0x29400036 },
	{ 0x5fffc,  0x19c000c4 },
	{ 0x502dc,  0x28800032 },
	{ 0x5fffc,  0x1ac000c5 },
	{ 0x502e0,  0x2800002f },
	{ 0x5fffc,  0x1bc000c7 },
	{ 0x502e4,  0x2740002c },
	{ 0x5fffc,  0x1cc000c8 },
	{ 0x502e8,  0x26c00029 },
	{ 0x5fffc,  0x1dc000c9 },
	{ 0x502ec,  0x26000027 },
	{ 0x5fffc,  0x1ec000cc },
	{ 0x502f0,  0x25000024 },
	{ 0x5fffc,  0x200000cc },
	{ 0x502f4,  0x24800021 },
	{ 0x5fffc,  0x210000cd },
	{ 0x502f8,  0x23800020 },
	{ 0x5fffc,  0x220000ce },
	{ 0x502fc,  0x2300001d },
};

static struct mdp_table_entry mdp_downscale_x_table_PT4TOPT6[] = {
	{ 0x5fffc,  0x740008c },
	{ 0x50280,  0x33800088 },
	{ 0x5fffc,  0x800008e },
	{ 0x50284,  0x33400084 },
	{ 0x5fffc,  0x8400092 },
	{ 0x50288,  0x33000080 },
	{ 0x5fffc,  0x9000094 },
	{ 0x5028c,  0x3300007b },
	{ 0x5fffc,  0x9c00098 },
	{ 0x50290,  0x32400077 },
	{ 0x5fffc,  0xa40009b },
	{ 0x50294,  0x32000073 },
	{ 0x5fffc,  0xb00009d },
	{ 0x50298,  0x31c0006f },
	{ 0x5fffc,  0xbc000a0 },
	{ 0x5029c,  0x3140006b },
	{ 0x5fffc,  0xc8000a2 },
	{ 0x502a0,  0x31000067 },
	{ 0x5fffc,  0xd8000a5 },
	{ 0x502a4,  0x30800062 },
	{ 0x5fffc,  0xe4000a8 },
	{ 0x502a8,  0x2fc0005f },
	{ 0x5fffc,  0xec000aa },
	{ 0x502ac,  0x2fc0005b },
	{ 0x5fffc,  0xf8000ad },
	{ 0x502b0,  0x2f400057 },
	{ 0x5fffc,  0x108000b0 },
	{ 0x502b4,  0x2e400054 },
	{ 0x5fffc,  0x114000b2 },
	{ 0x502b8,  0x2e000050 },
	{ 0x5fffc,  0x124000b4 },
	{ 0x502bc,  0x2d80004c },
	{ 0x5fffc,  0x130000b6 },
	{ 0x502c0,  0x2d000049 },
	{ 0x5fffc,  0x140000b8 },
	{ 0x502c4,  0x2c800045 },
	{ 0x5fffc,  0x150000b9 },
	{ 0x502c8,  0x2c000042 },
	{ 0x5fffc,  0x15c000bd },
	{ 0x502cc,  0x2b40003e },
	{ 0x5fffc,  0x16c000bf },
	{ 0x502d0,  0x2a80003b },
	{ 0x5fffc,  0x17c000bf },
	{ 0x502d4,  0x2a000039 },
	{ 0x5fffc,  0x188000c2 },
	{ 0x502d8,  0x29400036 },
	{ 0x5fffc,  0x19c000c4 },
	{ 0x502dc,  0x28800032 },
	{ 0x5fffc,  0x1ac000c5 },
	{ 0x502e0,  0x2800002f },
	{ 0x5fffc,  0x1bc000c7 },
	{ 0x502e4,  0x2740002c },
	{ 0x5fffc,  0x1cc000c8 },
	{ 0x502e8,  0x26c00029 },
	{ 0x5fffc,  0x1dc000c9 },
	{ 0x502ec,  0x26000027 },
	{ 0x5fffc,  0x1ec000cc },
	{ 0x502f0,  0x25000024 },
	{ 0x5fffc,  0x200000cc },
	{ 0x502f4,  0x24800021 },
	{ 0x5fffc,  0x210000cd },
	{ 0x502f8,  0x23800020 },
	{ 0x5fffc,  0x220000ce },
	{ 0x502fc,  0x2300001d },
};

static struct mdp_table_entry mdp_downscale_x_table_PT6TOPT8[] = {
	{ 0x5fffc,  0xfe000070 },
	{ 0x50280,  0x4bc00068 },
	{ 0x5fffc,  0xfe000078 },
	{ 0x50284,  0x4bc00060 },
	{ 0x5fffc,  0xfe000080 },
	{ 0x50288,  0x4b800059 },
	{ 0x5fffc,  0xfe000089 },
	{ 0x5028c,  0x4b000052 },
	{ 0x5fffc,  0xfe400091 },
	{ 0x50290,  0x4a80004b },
	{ 0x5fffc,  0xfe40009a },
	{ 0x50294,  0x4a000044 },
	{ 0x5fffc,  0xfe8000a3 },
	{ 0x50298,  0x4940003d },
	{ 0x5fffc,  0xfec000ac },
	{ 0x5029c,  0x48400037 },
	{ 0x5fffc,  0xff0000b4 },
	{ 0x502a0,  0x47800031 },
	{ 0x5fffc,  0xff8000bd },
	{ 0x502a4,  0x4640002b },
	{ 0x5fffc,  0xc5 },
	{ 0x502a8,  0x45000026 },
	{ 0x5fffc,  0x8000ce },
	{ 0x502ac,  0x43800021 },
	{ 0x5fffc,  0x10000d6 },
	{ 0x502b0,  0x4240001c },
	{ 0x5fffc,  0x18000df },
	{ 0x502b4,  0x40800018 },
	{ 0x5fffc,  0x24000e6 },
	{ 0x502b8,  0x3f000014 },
	{ 0x5fffc,  0x30000ee },
	{ 0x502bc,  0x3d400010 },
	{ 0x5fffc,  0x40000f5 },
	{ 0x502c0,  0x3b80000c },
	{ 0x5fffc,  0x50000fc },
	{ 0x502c4,  0x39800009 },
	{ 0x5fffc,  0x6000102 },
	{ 0x502c8,  0x37c00006 },
	{ 0x5fffc,  0x7000109 },
	{ 0x502cc,  0x35800004 },
	{ 0x5fffc,  0x840010e },
	{ 0x502d0,  0x33800002 },
	{ 0x5fffc,  0x9800114 },
	{ 0x502d4,  0x31400000 },
	{ 0x5fffc,  0xac00119 },
	{ 0x502d8,  0x2f4003fe },
	{ 0x5fffc,  0xc40011e },
	{ 0x502dc,  0x2d0003fc },
	{ 0x5fffc,  0xdc00121 },
	{ 0x502e0,  0x2b0003fb },
	{ 0x5fffc,  0xf400125 },
	{ 0x502e4,  0x28c003fa },
	{ 0x5fffc,  0x11000128 },
	{ 0x502e8,  0x268003f9 },
	{ 0x5fffc,  0x12c0012a },
	{ 0x502ec,  0x244003f9 },
	{ 0x5fffc,  0x1480012c },
	{ 0x502f0,  0x224003f8 },
	{ 0x5fffc,  0x1640012e },
	{ 0x502f4,  0x200003f8 },
	{ 0x5fffc,  0x1800012f },
	{ 0x502f8,  0x1e0003f8 },
	{ 0x5fffc,  0x1a00012f },
	{ 0x502fc,  0x1c0003f8 },
};

static struct mdp_table_entry mdp_downscale_x_table_PT8TO1[] = {
	{ 0x5fffc,  0x0 },
	{ 0x50280,  0x7fc00000 },
	{ 0x5fffc,  0xff80000d },
	{ 0x50284,  0x7ec003f9 },
	{ 0x5fffc,  0xfec0001c },
	{ 0x50288,  0x7d4003f3 },
	{ 0x5fffc,  0xfe40002b },
	{ 0x5028c,  0x7b8003ed },
	{ 0x5fffc,  0xfd80003c },
	{ 0x50290,  0x794003e8 },
	{ 0x5fffc,  0xfcc0004d },
	{ 0x50294,  0x76c003e4 },
	{ 0x5fffc,  0xfc40005f },
	{ 0x50298,  0x73c003e0 },
	{ 0x5fffc,  0xfb800071 },
	{ 0x5029c,  0x708003de },
	{ 0x5fffc,  0xfac00085 },
	{ 0x502a0,  0x6d0003db },
	{ 0x5fffc,  0xfa000098 },
	{ 0x502a4,  0x698003d9 },
	{ 0x5fffc,  0xf98000ac },
	{ 0x502a8,  0x654003d8 },
	{ 0x5fffc,  0xf8c000c1 },
	{ 0x502ac,  0x610003d7 },
	{ 0x5fffc,  0xf84000d5 },
	{ 0x502b0,  0x5c8003d7 },
	{ 0x5fffc,  0xf7c000e9 },
	{ 0x502b4,  0x580003d7 },
	{ 0x5fffc,  0xf74000fd },
	{ 0x502b8,  0x534003d8 },
	{ 0x5fffc,  0xf6c00112 },
	{ 0x502bc,  0x4e8003d8 },
	{ 0x5fffc,  0xf6800126 },
	{ 0x502c0,  0x494003da },
	{ 0x5fffc,  0xf600013a },
	{ 0x502c4,  0x448003db },
	{ 0x5fffc,  0xf600014d },
	{ 0x502c8,  0x3f4003dd },
	{ 0x5fffc,  0xf5c00160 },
	{ 0x502cc,  0x3a4003df },
	{ 0x5fffc,  0xf5c00172 },
	{ 0x502d0,  0x354003e1 },
	{ 0x5fffc,  0xf5c00184 },
	{ 0x502d4,  0x304003e3 },
	{ 0x5fffc,  0xf6000195 },
	{ 0x502d8,  0x2b0003e6 },
	{ 0x5fffc,  0xf64001a6 },
	{ 0x502dc,  0x260003e8 },
	{ 0x5fffc,  0xf6c001b4 },
	{ 0x502e0,  0x214003eb },
	{ 0x5fffc,  0xf78001c2 },
	{ 0x502e4,  0x1c4003ee },
	{ 0x5fffc,  0xf80001cf },
	{ 0x502e8,  0x17c003f1 },
	{ 0x5fffc,  0xf90001db },
	{ 0x502ec,  0x134003f3 },
	{ 0x5fffc,  0xfa0001e5 },
	{ 0x502f0,  0xf0003f6 },
	{ 0x5fffc,  0xfb4001ee },
	{ 0x502f4,  0xac003f9 },
	{ 0x5fffc,  0xfcc001f5 },
	{ 0x502f8,  0x70003fb },
	{ 0x5fffc,  0xfe4001fb },
	{ 0x502fc,  0x34003fe },
};

struct mdp_table_entry *mdp_downscale_x_table[MDP_DOWNSCALE_MAX] = {
	[MDP_DOWNSCALE_PT2TOPT4] = mdp_downscale_x_table_PT2TOPT4,
	[MDP_DOWNSCALE_PT4TOPT6] = mdp_downscale_x_table_PT4TOPT6,
	[MDP_DOWNSCALE_PT6TOPT8] = mdp_downscale_x_table_PT6TOPT8,
	[MDP_DOWNSCALE_PT8TO1]  = mdp_downscale_x_table_PT8TO1,
};

static struct mdp_table_entry mdp_downscale_y_table_PT2TOPT4[] = {
	{ 0x5fffc,  0x740008c },
	{ 0x50300,  0x33800088 },
	{ 0x5fffc,  0x800008e },
	{ 0x50304,  0x33400084 },
	{ 0x5fffc,  0x8400092 },
	{ 0x50308,  0x33000080 },
	{ 0x5fffc,  0x9000094 },
	{ 0x5030c,  0x3300007b },
	{ 0x5fffc,  0x9c00098 },
	{ 0x50310,  0x32400077 },
	{ 0x5fffc,  0xa40009b },
	{ 0x50314,  0x32000073 },
	{ 0x5fffc,  0xb00009d },
	{ 0x50318,  0x31c0006f },
	{ 0x5fffc,  0xbc000a0 },
	{ 0x5031c,  0x3140006b },
	{ 0x5fffc,  0xc8000a2 },
	{ 0x50320,  0x31000067 },
	{ 0x5fffc,  0xd8000a5 },
	{ 0x50324,  0x30800062 },
	{ 0x5fffc,  0xe4000a8 },
	{ 0x50328,  0x2fc0005f },
	{ 0x5fffc,  0xec000aa },
	{ 0x5032c,  0x2fc0005b },
	{ 0x5fffc,  0xf8000ad },
	{ 0x50330,  0x2f400057 },
	{ 0x5fffc,  0x108000b0 },
	{ 0x50334,  0x2e400054 },
	{ 0x5fffc,  0x114000b2 },
	{ 0x50338,  0x2e000050 },
	{ 0x5fffc,  0x124000b4 },
	{ 0x5033c,  0x2d80004c },
	{ 0x5fffc,  0x130000b6 },
	{ 0x50340,  0x2d000049 },
	{ 0x5fffc,  0x140000b8 },
	{ 0x50344,  0x2c800045 },
	{ 0x5fffc,  0x150000b9 },
	{ 0x50348,  0x2c000042 },
	{ 0x5fffc,  0x15c000bd },
	{ 0x5034c,  0x2b40003e },
	{ 0x5fffc,  0x16c000bf },
	{ 0x50350,  0x2a80003b },
	{ 0x5fffc,  0x17c000bf },
	{ 0x50354,  0x2a000039 },
	{ 0x5fffc,  0x188000c2 },
	{ 0x50358,  0x29400036 },
	{ 0x5fffc,  0x19c000c4 },
	{ 0x5035c,  0x28800032 },
	{ 0x5fffc,  0x1ac000c5 },
	{ 0x50360,  0x2800002f },
	{ 0x5fffc,  0x1bc000c7 },
	{ 0x50364,  0x2740002c },
	{ 0x5fffc,  0x1cc000c8 },
	{ 0x50368,  0x26c00029 },
	{ 0x5fffc,  0x1dc000c9 },
	{ 0x5036c,  0x26000027 },
	{ 0x5fffc,  0x1ec000cc },
	{ 0x50370,  0x25000024 },
	{ 0x5fffc,  0x200000cc },
	{ 0x50374,  0x24800021 },
	{ 0x5fffc,  0x210000cd },
	{ 0x50378,  0x23800020 },
	{ 0x5fffc,  0x220000ce },
	{ 0x5037c,  0x2300001d },
};

static struct mdp_table_entry mdp_downscale_y_table_PT4TOPT6[] = {
	{ 0x5fffc,  0x740008c },
	{ 0x50300,  0x33800088 },
	{ 0x5fffc,  0x800008e },
	{ 0x50304,  0x33400084 },
	{ 0x5fffc,  0x8400092 },
	{ 0x50308,  0x33000080 },
	{ 0x5fffc,  0x9000094 },
	{ 0x5030c,  0x3300007b },
	{ 0x5fffc,  0x9c00098 },
	{ 0x50310,  0x32400077 },
	{ 0x5fffc,  0xa40009b },
	{ 0x50314,  0x32000073 },
	{ 0x5fffc,  0xb00009d },
	{ 0x50318,  0x31c0006f },
	{ 0x5fffc,  0xbc000a0 },
	{ 0x5031c,  0x3140006b },
	{ 0x5fffc,  0xc8000a2 },
	{ 0x50320,  0x31000067 },
	{ 0x5fffc,  0xd8000a5 },
	{ 0x50324,  0x30800062 },
	{ 0x5fffc,  0xe4000a8 },
	{ 0x50328,  0x2fc0005f },
	{ 0x5fffc,  0xec000aa },
	{ 0x5032c,  0x2fc0005b },
	{ 0x5fffc,  0xf8000ad },
	{ 0x50330,  0x2f400057 },
	{ 0x5fffc,  0x108000b0 },
	{ 0x50334,  0x2e400054 },
	{ 0x5fffc,  0x114000b2 },
	{ 0x50338,  0x2e000050 },
	{ 0x5fffc,  0x124000b4 },
	{ 0x5033c,  0x2d80004c },
	{ 0x5fffc,  0x130000b6 },
	{ 0x50340,  0x2d000049 },
	{ 0x5fffc,  0x140000b8 },
	{ 0x50344,  0x2c800045 },
	{ 0x5fffc,  0x150000b9 },
	{ 0x50348,  0x2c000042 },
	{ 0x5fffc,  0x15c000bd },
	{ 0x5034c,  0x2b40003e },
	{ 0x5fffc,  0x16c000bf },
	{ 0x50350,  0x2a80003b },
	{ 0x5fffc,  0x17c000bf },
	{ 0x50354,  0x2a000039 },
	{ 0x5fffc,  0x188000c2 },
	{ 0x50358,  0x29400036 },
	{ 0x5fffc,  0x19c000c4 },
	{ 0x5035c,  0x28800032 },
	{ 0x5fffc,  0x1ac000c5 },
	{ 0x50360,  0x2800002f },
	{ 0x5fffc,  0x1bc000c7 },
	{ 0x50364,  0x2740002c },
	{ 0x5fffc,  0x1cc000c8 },
	{ 0x50368,  0x26c00029 },
	{ 0x5fffc,  0x1dc000c9 },
	{ 0x5036c,  0x26000027 },
	{ 0x5fffc,  0x1ec000cc },
	{ 0x50370,  0x25000024 },
	{ 0x5fffc,  0x200000cc },
	{ 0x50374,  0x24800021 },
	{ 0x5fffc,  0x210000cd },
	{ 0x50378,  0x23800020 },
	{ 0x5fffc,  0x220000ce },
	{ 0x5037c,  0x2300001d },
};

static struct mdp_table_entry mdp_downscale_y_table_PT6TOPT8[] = {
	{ 0x5fffc,  0xfe000070 },
	{ 0x50300,  0x4bc00068 },
	{ 0x5fffc,  0xfe000078 },
	{ 0x50304,  0x4bc00060 },
	{ 0x5fffc,  0xfe000080 },
	{ 0x50308,  0x4b800059 },
	{ 0x5fffc,  0xfe000089 },
	{ 0x5030c,  0x4b000052 },
	{ 0x5fffc,  0xfe400091 },
	{ 0x50310,  0x4a80004b },
	{ 0x5fffc,  0xfe40009a },
	{ 0x50314,  0x4a000044 },
	{ 0x5fffc,  0xfe8000a3 },
	{ 0x50318,  0x4940003d },
	{ 0x5fffc,  0xfec000ac },
	{ 0x5031c,  0x48400037 },
	{ 0x5fffc,  0xff0000b4 },
	{ 0x50320,  0x47800031 },
	{ 0x5fffc,  0xff8000bd },
	{ 0x50324,  0x4640002b },
	{ 0x5fffc,  0xc5 },
	{ 0x50328,  0x45000026 },
	{ 0x5fffc,  0x8000ce },
	{ 0x5032c,  0x43800021 },
	{ 0x5fffc,  0x10000d6 },
	{ 0x50330,  0x4240001c },
	{ 0x5fffc,  0x18000df },
	{ 0x50334,  0x40800018 },
	{ 0x5fffc,  0x24000e6 },
	{ 0x50338,  0x3f000014 },
	{ 0x5fffc,  0x30000ee },
	{ 0x5033c,  0x3d400010 },
	{ 0x5fffc,  0x40000f5 },
	{ 0x50340,  0x3b80000c },
	{ 0x5fffc,  0x50000fc },
	{ 0x50344,  0x39800009 },
	{ 0x5fffc,  0x6000102 },
	{ 0x50348,  0x37c00006 },
	{ 0x5fffc,  0x7000109 },
	{ 0x5034c,  0x35800004 },
	{ 0x5fffc,  0x840010e },
	{ 0x50350,  0x33800002 },
	{ 0x5fffc,  0x9800114 },
	{ 0x50354,  0x31400000 },
	{ 0x5fffc,  0xac00119 },
	{ 0x50358,  0x2f4003fe },
	{ 0x5fffc,  0xc40011e },
	{ 0x5035c,  0x2d0003fc },
	{ 0x5fffc,  0xdc00121 },
	{ 0x50360,  0x2b0003fb },
	{ 0x5fffc,  0xf400125 },
	{ 0x50364,  0x28c003fa },
	{ 0x5fffc,  0x11000128 },
	{ 0x50368,  0x268003f9 },
	{ 0x5fffc,  0x12c0012a },
	{ 0x5036c,  0x244003f9 },
	{ 0x5fffc,  0x1480012c },
	{ 0x50370,  0x224003f8 },
	{ 0x5fffc,  0x1640012e },
	{ 0x50374,  0x200003f8 },
	{ 0x5fffc,  0x1800012f },
	{ 0x50378,  0x1e0003f8 },
	{ 0x5fffc,  0x1a00012f },
	{ 0x5037c,  0x1c0003f8 },
};

static struct mdp_table_entry mdp_downscale_y_table_PT8TO1[] = {
	{ 0x5fffc,  0x0 },
	{ 0x50300,  0x7fc00000 },
	{ 0x5fffc,  0xff80000d },
	{ 0x50304,  0x7ec003f9 },
	{ 0x5fffc,  0xfec0001c },
	{ 0x50308,  0x7d4003f3 },
	{ 0x5fffc,  0xfe40002b },
	{ 0x5030c,  0x7b8003ed },
	{ 0x5fffc,  0xfd80003c },
	{ 0x50310,  0x794003e8 },
	{ 0x5fffc,  0xfcc0004d },
	{ 0x50314,  0x76c003e4 },
	{ 0x5fffc,  0xfc40005f },
	{ 0x50318,  0x73c003e0 },
	{ 0x5fffc,  0xfb800071 },
	{ 0x5031c,  0x708003de },
	{ 0x5fffc,  0xfac00085 },
	{ 0x50320,  0x6d0003db },
	{ 0x5fffc,  0xfa000098 },
	{ 0x50324,  0x698003d9 },
	{ 0x5fffc,  0xf98000ac },
	{ 0x50328,  0x654003d8 },
	{ 0x5fffc,  0xf8c000c1 },
	{ 0x5032c,  0x610003d7 },
	{ 0x5fffc,  0xf84000d5 },
	{ 0x50330,  0x5c8003d7 },
	{ 0x5fffc,  0xf7c000e9 },
	{ 0x50334,  0x580003d7 },
	{ 0x5fffc,  0xf74000fd },
	{ 0x50338,  0x534003d8 },
	{ 0x5fffc,  0xf6c00112 },
	{ 0x5033c,  0x4e8003d8 },
	{ 0x5fffc,  0xf6800126 },
	{ 0x50340,  0x494003da },
	{ 0x5fffc,  0xf600013a },
	{ 0x50344,  0x448003db },
	{ 0x5fffc,  0xf600014d },
	{ 0x50348,  0x3f4003dd },
	{ 0x5fffc,  0xf5c00160 },
	{ 0x5034c,  0x3a4003df },
	{ 0x5fffc,  0xf5c00172 },
	{ 0x50350,  0x354003e1 },
	{ 0x5fffc,  0xf5c00184 },
	{ 0x50354,  0x304003e3 },
	{ 0x5fffc,  0xf6000195 },
	{ 0x50358,  0x2b0003e6 },
	{ 0x5fffc,  0xf64001a6 },
	{ 0x5035c,  0x260003e8 },
	{ 0x5fffc,  0xf6c001b4 },
	{ 0x50360,  0x214003eb },
	{ 0x5fffc,  0xf78001c2 },
	{ 0x50364,  0x1c4003ee },
	{ 0x5fffc,  0xf80001cf },
	{ 0x50368,  0x17c003f1 },
	{ 0x5fffc,  0xf90001db },
	{ 0x5036c,  0x134003f3 },
	{ 0x5fffc,  0xfa0001e5 },
	{ 0x50370,  0xf0003f6 },
	{ 0x5fffc,  0xfb4001ee },
	{ 0x50374,  0xac003f9 },
	{ 0x5fffc,  0xfcc001f5 },
	{ 0x50378,  0x70003fb },
	{ 0x5fffc,  0xfe4001fb },
	{ 0x5037c,  0x34003fe },
};

struct mdp_table_entry *mdp_downscale_y_table[MDP_DOWNSCALE_MAX] = {
	[MDP_DOWNSCALE_PT2TOPT4] = mdp_downscale_y_table_PT2TOPT4,
	[MDP_DOWNSCALE_PT4TOPT6] = mdp_downscale_y_table_PT4TOPT6,
	[MDP_DOWNSCALE_PT6TOPT8] = mdp_downscale_y_table_PT6TOPT8,
	[MDP_DOWNSCALE_PT8TO1]  = mdp_downscale_y_table_PT8TO1,
};

struct mdp_table_entry mdp_gaussian_blur_table[] = {
	/* max variance */
	{ 0x5fffc, 0x20000080 },
	{ 0x50280, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50284, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50288, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5028c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50290, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50294, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50298, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5029c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502a0, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502a4, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502a8, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502ac, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502b0, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502b4, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502b8, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502bc, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502c0, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502c4, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502c8, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502cc, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502d0, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502d4, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502d8, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502dc, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502e0, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502e4, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502e8, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502ec, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502f0, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502f4, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502f8, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x502fc, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50300, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50304, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50308, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5030c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50310, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50314, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50318, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5031c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50320, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50324, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50328, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5032c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50330, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50334, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50338, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5033c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50340, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50344, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50348, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5034c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50350, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50354, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50358, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5035c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50360, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50364, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50368, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5036c, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50370, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50374, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x50378, 0x20000080 },
	{ 0x5fffc, 0x20000080 },
	{ 0x5037c, 0x20000080 },
};

static void load_table(const struct mdp_info *mdp,
		       struct mdp_table_entry *table, int len)
{
	int i;
	for (i = 0; i < len; i++)
		mdp_writel(mdp, table[i].val, table[i].reg);
}

enum {
	IMG_LEFT,
	IMG_RIGHT,
	IMG_TOP,
	IMG_BOTTOM,
};

static void get_edge_info(uint32_t src, uint32_t src_coord, uint32_t dst,
			  uint32_t *interp1, uint32_t *interp2,
			  uint32_t *repeat1, uint32_t *repeat2) {
	if (src > 3 * dst) {
		*interp1 = 0;
		*interp2 = src - 1;
		*repeat1 = 0;
		*repeat2 = 0;
	} else if (src == 3 * dst) {
		*interp1 = 0;
		*interp2 = src;
		*repeat1 = 0;
		*repeat2 = 1;
	} else if (src > dst && src < 3 * dst) {
		*interp1 = -1;
		*interp2 = src;
		*repeat1 = 1;
		*repeat2 = 1;
	} else if (src == dst) {
		*interp1 = -1;
		*interp2 = src + 1;
		*repeat1 = 1;
		*repeat2 = 2;
	} else {
		*interp1 = -2;
		*interp2 = src + 1;
		*repeat1 = 2;
		*repeat2 = 2;
	}
	*interp1 += src_coord;
	*interp2 += src_coord;
}

int mdp_ppp_cfg_edge_cond(struct mdp_blit_req *req, struct ppp_regs *regs)
{
	int32_t luma_interp[4];
	int32_t luma_repeat[4];
	int32_t chroma_interp[4];
	int32_t chroma_bound[4];
	int32_t chroma_repeat[4];
	uint32_t dst_w, dst_h;

	memset(&luma_interp, 0, sizeof(int32_t) * 4);
	memset(&luma_repeat, 0, sizeof(int32_t) * 4);
	memset(&chroma_interp, 0, sizeof(int32_t) * 4);
	memset(&chroma_bound, 0, sizeof(int32_t) * 4);
	memset(&chroma_repeat, 0, sizeof(int32_t) * 4);
	regs->edge = 0;

	if (req->flags & MDP_ROT_90) {
		dst_w = req->dst_rect.h;
		dst_h = req->dst_rect.w;
	} else {
		dst_w = req->dst_rect.w;
		dst_h = req->dst_rect.h;
	}

	if (regs->op & (PPP_OP_SCALE_Y_ON | PPP_OP_SCALE_X_ON)) {
		get_edge_info(req->src_rect.h, req->src_rect.y, dst_h,
			      &luma_interp[IMG_TOP], &luma_interp[IMG_BOTTOM],
			      &luma_repeat[IMG_TOP], &luma_repeat[IMG_BOTTOM]);
		get_edge_info(req->src_rect.w, req->src_rect.x, dst_w,
			      &luma_interp[IMG_LEFT], &luma_interp[IMG_RIGHT],
			      &luma_repeat[IMG_LEFT], &luma_repeat[IMG_RIGHT]);
	} else {
		luma_interp[IMG_LEFT] = req->src_rect.x;
		luma_interp[IMG_RIGHT] = req->src_rect.x + req->src_rect.w - 1;
		luma_interp[IMG_TOP] = req->src_rect.y;
		luma_interp[IMG_BOTTOM] = req->src_rect.y + req->src_rect.h - 1;
		luma_repeat[IMG_LEFT] = 0;
		luma_repeat[IMG_TOP] = 0;
		luma_repeat[IMG_RIGHT] = 0;
		luma_repeat[IMG_BOTTOM] = 0;
	}

	chroma_interp[IMG_LEFT] = luma_interp[IMG_LEFT];
	chroma_interp[IMG_RIGHT] = luma_interp[IMG_RIGHT];
	chroma_interp[IMG_TOP] = luma_interp[IMG_TOP];
	chroma_interp[IMG_BOTTOM] = luma_interp[IMG_BOTTOM];

	chroma_bound[IMG_LEFT] = req->src_rect.x;
	chroma_bound[IMG_RIGHT] = req->src_rect.x + req->src_rect.w - 1;
	chroma_bound[IMG_TOP] = req->src_rect.y;
	chroma_bound[IMG_BOTTOM] = req->src_rect.y + req->src_rect.h - 1;

	if (IS_YCRCB(req->src.format)) {
		chroma_interp[IMG_LEFT] = chroma_interp[IMG_LEFT] >> 1;
		chroma_interp[IMG_RIGHT] = (chroma_interp[IMG_RIGHT] + 1) >> 1;

		chroma_bound[IMG_LEFT] = chroma_bound[IMG_LEFT] >> 1;
		chroma_bound[IMG_RIGHT] = chroma_bound[IMG_RIGHT] >> 1;
	}

	if (req->src.format == MDP_Y_CBCR_H2V2 ||
	    req->src.format == MDP_Y_CRCB_H2V2) {
		chroma_interp[IMG_TOP] = (chroma_interp[IMG_TOP] - 1) >> 1;
		chroma_interp[IMG_BOTTOM] = (chroma_interp[IMG_BOTTOM] + 1)
					    >> 1;
		chroma_bound[IMG_TOP] = (chroma_bound[IMG_TOP] + 1) >> 1;
		chroma_bound[IMG_BOTTOM] = chroma_bound[IMG_BOTTOM] >> 1;
	}

	chroma_repeat[IMG_LEFT] = chroma_bound[IMG_LEFT] -
				  chroma_interp[IMG_LEFT];
	chroma_repeat[IMG_RIGHT] = chroma_interp[IMG_RIGHT] -
				  chroma_bound[IMG_RIGHT];
	chroma_repeat[IMG_TOP] = chroma_bound[IMG_TOP] -
				  chroma_interp[IMG_TOP];
	chroma_repeat[IMG_BOTTOM] = chroma_interp[IMG_BOTTOM] -
				  chroma_bound[IMG_BOTTOM];

	if (chroma_repeat[IMG_LEFT] < 0 || chroma_repeat[IMG_LEFT] > 3 ||
	    chroma_repeat[IMG_RIGHT] < 0 || chroma_repeat[IMG_RIGHT] > 3 ||
	    chroma_repeat[IMG_TOP] < 0 || chroma_repeat[IMG_TOP] > 3 ||
	    chroma_repeat[IMG_BOTTOM] < 0 || chroma_repeat[IMG_BOTTOM] > 3 ||
	    luma_repeat[IMG_LEFT] < 0 || luma_repeat[IMG_LEFT] > 3 ||
	    luma_repeat[IMG_RIGHT] < 0 || luma_repeat[IMG_RIGHT] > 3 ||
	    luma_repeat[IMG_TOP] < 0 || luma_repeat[IMG_TOP] > 3 ||
	    luma_repeat[IMG_BOTTOM] < 0 || luma_repeat[IMG_BOTTOM] > 3)
		return -1;

	regs->edge |= (chroma_repeat[IMG_LEFT] & 3) << MDP_LEFT_CHROMA;
	regs->edge |= (chroma_repeat[IMG_RIGHT] & 3) << MDP_RIGHT_CHROMA;
	regs->edge |= (chroma_repeat[IMG_TOP] & 3) << MDP_TOP_CHROMA;
	regs->edge |= (chroma_repeat[IMG_BOTTOM] & 3) << MDP_BOTTOM_CHROMA;
	regs->edge |= (luma_repeat[IMG_LEFT] & 3) << MDP_LEFT_LUMA;
	regs->edge |= (luma_repeat[IMG_RIGHT] & 3) << MDP_RIGHT_LUMA;
	regs->edge |= (luma_repeat[IMG_TOP] & 3) << MDP_TOP_LUMA;
	regs->edge |= (luma_repeat[IMG_BOTTOM] & 3) << MDP_BOTTOM_LUMA;
	return 0;
}

#define ONE_HALF	(1LL << 32)
#define ONE		(1LL << 33)
#define TWO		(2LL << 33)
#define THREE		(3LL << 33)
#define FRAC_MASK (ONE - 1)
#define INT_MASK (~FRAC_MASK)

static int scale_params(uint32_t dim_in, uint32_t dim_out, uint32_t origin,
			uint32_t *phase_init, uint32_t *phase_step)
{
	/* to improve precicsion calculations are done in U31.33 and converted
	 * to U3.29 at the end */
	int64_t k1, k2, k3, k4, tmp;
	uint64_t n, d, os, os_p, od, od_p, oreq;
	unsigned rpa = 0;
	int64_t ip64, delta;

	if (dim_out % 3 == 0)
		rpa = !(dim_in % (dim_out / 3));

	n = ((uint64_t)dim_out) << 34;
	d = dim_in;
	if (!d)
		return -1;
	do_div(n, d);
	k3 = (n + 1) >> 1;
	if ((k3 >> 4) < (1LL << 27) || (k3 >> 4) > (1LL << 31))
		return -1;

	n = ((uint64_t)dim_in) << 34;
	d = (uint64_t)dim_out;
	if (!d)
		return -1;
	do_div(n, d);
	k1 = (n + 1) >> 1;
	k2 = (k1 - ONE) >> 1;

	*phase_init = (int)(k2 >> 4);
	k4 = (k3 - ONE) >> 1;

	if (rpa) {
		os = ((uint64_t)origin << 33) - ONE_HALF;
		tmp = (dim_out * os) + ONE_HALF;
		if (!dim_in)
			return -1;
		do_div(tmp, dim_in);
		od = tmp - ONE_HALF;
	} else {
		os = ((uint64_t)origin << 1) - 1;
		od = (((k3 * os) >> 1) + k4);
	}

	od_p = od & INT_MASK;
	if (od_p != od)
		od_p += ONE;

	if (rpa) {
		tmp = (dim_in * od_p) + ONE_HALF;
		if (!dim_in)
			return -1;
		do_div(tmp, dim_in);
		os_p = tmp - ONE_HALF;
	} else {
		os_p = ((k1 * (od_p >> 33)) + k2);
	}

	oreq = (os_p & INT_MASK) - ONE;

	ip64 = os_p - oreq;
	delta = ((int64_t)(origin) << 33) - oreq;
	ip64 -= delta;
	/* limit to valid range before the left shift */
	delta = (ip64 & (1LL << 63)) ? 4 : -4;
	delta <<= 33;
	while (abs((int)(ip64 >> 33)) > 4)
		ip64 += delta;
	*phase_init = (int)(ip64 >> 4);
	*phase_step = (uint32_t)(k1 >> 4);
	return 0;
}

int mdp_ppp_cfg_scale(struct mdp_info *mdp, struct ppp_regs *regs,
		      struct mdp_rect *src_rect, struct mdp_rect *dst_rect,
		      uint32_t src_format, uint32_t dst_format)
{
	int downscale;
	uint32_t phase_init_x, phase_init_y, phase_step_x, phase_step_y;
	uint32_t scale_factor_x, scale_factor_y;

	if (scale_params(src_rect->w, dst_rect->w, 1, &phase_init_x,
			 &phase_step_x) ||
	    scale_params(src_rect->h, dst_rect->h, 1, &phase_init_y,
			 &phase_step_y))
		return -1;

	regs->phasex_init = phase_init_x;
	regs->phasey_init = phase_init_y;
	regs->phasex_step = phase_step_x;
	regs->phasey_step = phase_step_y;

	scale_factor_x = (dst_rect->w * 10) / src_rect->w;
	scale_factor_y = (dst_rect->h * 10) / src_rect->h;

	if (scale_factor_x > 8)
		downscale = MDP_DOWNSCALE_PT8TO1;
	else if (scale_factor_x > 6)
		downscale = MDP_DOWNSCALE_PT6TOPT8;
	else if (scale_factor_x > 4)
		downscale = MDP_DOWNSCALE_PT4TOPT6;
	else
		downscale = MDP_DOWNSCALE_PT2TOPT4;

	if (downscale != downscale_x_table) {
		load_table(mdp, mdp_downscale_x_table[downscale], 64);
		downscale_x_table = downscale;
	}

	if (scale_factor_y > 8)
		downscale = MDP_DOWNSCALE_PT8TO1;
	else if (scale_factor_y > 6)
		downscale = MDP_DOWNSCALE_PT6TOPT8;
	else if (scale_factor_y > 4)
		downscale = MDP_DOWNSCALE_PT4TOPT6;
	else
		downscale = MDP_DOWNSCALE_PT2TOPT4;

	if (downscale != downscale_y_table) {
		load_table(mdp, mdp_downscale_y_table[downscale], 64);
		downscale_y_table = downscale;
	}

	return 0;
}


int mdp_ppp_load_blur(struct mdp_info *mdp)
{
	if (!(downscale_x_table == MDP_DOWNSCALE_BLUR &&
              downscale_y_table == MDP_DOWNSCALE_BLUR)) {
		load_table(mdp, mdp_gaussian_blur_table, 128);
		downscale_x_table = MDP_DOWNSCALE_BLUR;
		downscale_y_table = MDP_DOWNSCALE_BLUR;
	}

	return 0;
}

#define MDP_SCALE_CFG_RETRY     3
void mdp_ppp_init_scale(struct mdp_info *mdp)
{
	int i, r;
	downscale_x_table = MDP_DOWNSCALE_MAX;
	downscale_y_table = MDP_DOWNSCALE_MAX;

#if 0
	load_table(mdp, mdp_upscale_table, ARRAY_SIZE(mdp_upscale_table));
#else
        for (i = 0; i < ARRAY_SIZE(mdp_upscale_table); i++) {
                mdp_writel(mdp, mdp_upscale_table[i].val,
                                mdp_upscale_table[i].reg);
                /* Workaround for MDP defect(couples of lines presented in
                 * ROI while scaling up image) based on QCT's suggestion
                 */
                for(r = 0 ; r < MDP_SCALE_CFG_RETRY ; r++) {
                        if (mdp_readl(mdp, mdp_upscale_table[i].reg) ==
                                        mdp_upscale_table[i].val)
                                break ;
                        pr_err("MDP: failed to config PPP up scale coefficients"
                                        " table: reg=0x%08X, val=0x%08X\n",
                                        mdp_upscale_table[i].reg,
                                        mdp_upscale_table[i].val);
                        mdp_writel(mdp, mdp_upscale_table[i].val,
                                        mdp_upscale_table[i].reg);
                }
                if (MDP_SCALE_CFG_RETRY == r) {
                        pr_err("MDP: PPP is defective and unrepairable!\n");
                        BUG();
                }
        }
#endif
}

int mdp_ppp_validate_blit(struct mdp_info *mdp, struct mdp_blit_req *req)
{
	/* WORKAROUND FOR HARDWARE BUG IN BG TILE FETCH */
	if (unlikely(req->src_rect.h == 0 ||
		     req->src_rect.w == 0)) {
		pr_info("mdp_ppp: src img of zero size!\n");
		return -EINVAL;
	}
	if (unlikely(req->dst_rect.h == 0 ||
		     req->dst_rect.w == 0))
		return -EINVAL;

	return 0;
}

int mdp_ppp_do_blit(struct mdp_info *mdp, struct mdp_blit_req *req,
		   struct file *src_file, unsigned long src_start,
		   unsigned long src_len, struct file *dst_file,
		   unsigned long dst_start, unsigned long dst_len)
{
	int ret;

	if (unlikely((req->transp_mask != MDP_TRANSP_NOP ||
		      req->alpha != MDP_ALPHA_NOP ||
		      HAS_ALPHA(req->src.format)) &&
		     (req->flags & MDP_ROT_90 &&
		      req->dst_rect.w <= 16 && req->dst_rect.h >= 16))) {
		int i;
		unsigned int tiles = req->dst_rect.h / 16;
		unsigned int remainder = req->dst_rect.h % 16;
		req->src_rect.w = 16*req->src_rect.w / req->dst_rect.h;
		req->dst_rect.h = 16;

		if (req->flags & MDP_ROT_270)
			return -EINVAL;

		for (i = 0; i < tiles; i++) {
			ret = mdp_ppp_blit_and_wait(mdp, req,
						src_file, src_start, src_len,
						dst_file, dst_start, dst_len);
			if (ret)
				goto end;
			req->dst_rect.y += 16;
			req->src_rect.x += req->src_rect.w;
		}
		if (!remainder)
			goto end;
		req->src_rect.w = remainder*req->src_rect.w / req->dst_rect.h;
		req->dst_rect.h = remainder;
	}

	ret = mdp_ppp_blit_and_wait(mdp, req,
				src_file, src_start, src_len,
				dst_file, dst_start, dst_len);
end:
	return ret;
}
