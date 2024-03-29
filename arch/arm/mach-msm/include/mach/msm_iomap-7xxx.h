/* arch/arm/mach-msm/include/mach/msm_iomap-7xxx.h
 *
 * Copyright (C) 2007 Google, Inc.
 * Author: Brian Swetland <swetland@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *
 * The MSM peripherals are spread all over across 768MB of physical
 * space, which makes just having a simple IO_ADDRESS macro to slide
 * them into the right virtual location rough.  Instead, we will
 * provide a master phys->virt mapping for peripherals here.
 *
 */

#ifndef __ASM_ARCH_MSM_IOMAP_7XXX_H
#define __ASM_ARCH_MSM_IOMAP_7XXX_H

#define MSM_VIC_BASE          IOMEM(0xF8000000)
#define MSM_VIC_PHYS          0xC0000000
#define MSM_VIC_SIZE          SZ_4K

#define MSM_CSR_BASE          IOMEM(0xF8001000)
#define MSM_CSR_PHYS          0xC0100000
#define MSM_CSR_SIZE          SZ_4K

#define MSM_GPT_PHYS          MSM_CSR_PHYS
#define MSM_GPT_BASE          MSM_CSR_BASE
#define MSM_GPT_SIZE          SZ_4K

#define MSM_DMOV_BASE         IOMEM(0xF8002000)
#define MSM_DMOV_PHYS         0xA9700000
#define MSM_DMOV_SIZE         SZ_4K

#define MSM_GPIO1_BASE        IOMEM(0xF8003000)
#define MSM_GPIO1_PHYS        0xA9200000
#define MSM_GPIO1_SIZE        SZ_4K

#define MSM_GPIO2_BASE        IOMEM(0xF8004000)
#define MSM_GPIO2_PHYS        0xA9300000
#define MSM_GPIO2_SIZE        SZ_4K

#define MSM_GPIO2E_BASE       IOMEM(0xF8010000)
#define MSM_GPIO2E_PHYS       0xA9100000
#define MSM_GPIO2E_SIZE       SZ_4K

#define MSM_CLK_CTL_BASE      IOMEM(0xF8005000)
#define MSM_CLK_CTL_PHYS      0xA8600000
#define MSM_CLK_CTL_SIZE      SZ_4K

#define MSM_CLK_CTL_SH2_BASE  IOMEM(0xF8006000)
#define MSM_CLK_CTL_SH2_PHYS  0xABA01000
#define MSM_CLK_CTL_SH2_SIZE  SZ_4K

#define MSM_SHARED_RAM_BASE   IOMEM(0xF8100000)
#if defined(CONFIG_ARCH_MSM7227)
#define MSM_SHARED_RAM_PHYS   0x00100000
#elif defined(CONFIG_ARCH_MSM7225)
#define MSM_SHARED_RAM_PHYS   0x07F00000
#else
#define MSM_SHARED_RAM_PHYS   0x01F00000
#endif
#define MSM_SHARED_RAM_SIZE   SZ_1M

#define MSM_UART1_PHYS        0xA9A00000
#define MSM_UART1_SIZE        SZ_4K

#define MSM_UART2_PHYS        0xA9B00000
#define MSM_UART2_SIZE        SZ_4K

#define MSM_UART3_PHYS        0xA9C00000
#define MSM_UART3_SIZE        SZ_4K

#ifdef CONFIG_MSM_DEBUG_UART
#define MSM_DEBUG_UART_BASE   0xF9000000
#if CONFIG_MSM_DEBUG_UART == 1
#define MSM_DEBUG_UART_PHYS   MSM_UART1_PHYS
#elif CONFIG_MSM_DEBUG_UART == 2
#define MSM_DEBUG_UART_PHYS   MSM_UART2_PHYS
#elif CONFIG_MSM_DEBUG_UART == 3
#define MSM_DEBUG_UART_PHYS   MSM_UART3_PHYS
#endif
#define MSM_DEBUG_UART_SIZE   SZ_4K
#endif

#define MSM_SDC1_PHYS         0xA0400000
#define MSM_SDC1_SIZE         SZ_4K
#define MSM_SDC2_BASE         IOMEM(0xF800C000)
#define MSM_SDC2_PHYS         0xA0500000
#define MSM_SDC2_SIZE         SZ_4K
#define MSM_SDC3_PHYS         0xA0600000
#define MSM_SDC3_SIZE         SZ_4K
#define MSM_SDC4_PHYS         0xA0700000
#define MSM_SDC4_SIZE         SZ_4K

#define MSM_I2C_PHYS          0xA9900000
#define MSM_I2C_SIZE          SZ_4K

#define MSM_HSUSB_PHYS        0xA0800000
#define MSM_HSUSB_SIZE        SZ_4K

#define MSM_PMDH_PHYS         0xAA600000
#define MSM_PMDH_SIZE         SZ_4K

#define MSM_EMDH_PHYS         0xAA700000
#define MSM_EMDH_SIZE         SZ_4K

#define MSM_MDP_BASE		  IOMEM(0xF9200000)
#define MSM_MDP_PHYS          0xAA200000
#define MSM_MDP_SIZE          SZ_1M

#define MSM_MDC_BASE	      IOMEM(0xF8200000)
#define MSM_MDC_PHYS	      0xAA500000
#define MSM_MDC_SIZE	      SZ_1M

#define MSM_AD5_BASE          IOMEM(0xF8300000)
#define MSM_AD5_PHYS          0xAC000000
#define MSM_AD5_SIZE          (SZ_1M*13)

#define MSM_VFE_PHYS          0xA0F00000
#define MSM_VFE_SIZE          SZ_1M

#define MSM_UART1DM_PHYS      0xA0200000
#define MSM_UART2DM_PHYS      0xA0300000

#if defined(CONFIG_ARCH_MSM7225)
#define MSM_SSBI_BASE         IOMEM(0xF800A000)
#define MSM_SSBI_PHYS         0xA8100000
#define MSM_SSBI_SIZE         SZ_4K

#define MSM_TSSC_BASE         IOMEM(0xF800B000)
#define MSM_TSSC_PHYS         0xAA300000
#define MSM_TSSC_SIZE         SZ_4K
#endif

#if defined(CONFIG_CACHE_L2X0)
#define MSM_L2CC_BASE         IOMEM(0xF8008000)
#define MSM_L2CC_PHYS         0xC0400000
#define MSM_L2CC_SIZE         SZ_4K
#endif

#if defined(CONFIG_ARCH_MSM7227)
#define MSM_TGPIO1_BASE         IOMEM(0xF8009000)
#define MSM_TGPIO1_PHYS         0xA9000000
#define MSM_TGPIO1_SIZE         SZ_4K
#endif

#if defined(CONFIG_ARCH_MSM7227)
#define MSM_GPU_REG_PHYS      0xA0000000
#define MSM_GPU_REG_SIZE      0x00020000
#endif

#endif
