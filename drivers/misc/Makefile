#
# Makefile for misc devices that really don't fit anywhere else.
#

obj-$(CONFIG_IBM_ASM)		+= ibmasm/
obj-$(CONFIG_HDPU_FEATURES)	+= hdpuftrs/
obj-$(CONFIG_ATMEL_PWM)		+= atmel_pwm.o
obj-$(CONFIG_ATMEL_SSC)		+= atmel-ssc.o
obj-$(CONFIG_ATMEL_TCLIB)	+= atmel_tclib.o
obj-$(CONFIG_ICS932S401)	+= ics932s401.o
obj-$(CONFIG_LKDTM)		+= lkdtm.o
obj-$(CONFIG_TIFM_CORE)       	+= tifm_core.o
obj-$(CONFIG_TIFM_7XX1)       	+= tifm_7xx1.o
obj-$(CONFIG_PHANTOM)		+= phantom.o
ifeq ($(CONFIG_ARCH_MSM7227),y)
        obj-$(CONFIG_ANDROID_PMEM)      += pmem_7x27.o
else
        ifeq ($(CONFIG_ARCH_MSM7X30),y)
                obj-$(CONFIG_ANDROID_PMEM)      += pmem_qcom.o
        else
			ifeq ($(CONFIG_ARCH_MSM7225),y)
				obj-$(CONFIG_ANDROID_PMEM)      += pmem_7x27.o
			else
				obj-$(CONFIG_ANDROID_PMEM)      += pmem.o
			endif
        endif
endif
obj-$(CONFIG_SGI_IOC4)		+= ioc4.o
obj-$(CONFIG_ENCLOSURE_SERVICES) += enclosure.o
obj-$(CONFIG_KERNEL_DEBUGGER_CORE)	+= kernel_debugger.o
obj-$(CONFIG_KGDB_TESTS)	+= kgdbts.o
obj-$(CONFIG_SGI_XP)		+= sgi-xp/
obj-$(CONFIG_SGI_GRU)		+= sgi-gru/
obj-$(CONFIG_HP_ILO)		+= hpilo.o
obj-$(CONFIG_ISL29003)		+= isl29003.o
obj-$(CONFIG_EP93XX_PWM)	+= ep93xx_pwm.o
obj-$(CONFIG_UID_STAT)		+= uid_stat.o
obj-$(CONFIG_C2PORT)		+= c2port/
obj-y				+= eeprom/
obj-$(CONFIG_VIDC)		+= vidc/
obj-y				+= cb710/
obj-$(CONFIG_WL127X_RFKILL)	+= wl127x-rfkill.o
obj-$(CONFIG_APANIC)		+= apanic.o
obj-$(CONFIG_SENSORS_BMA150_SPI)+= bma150_spi.o
obj-$(CONFIG_PMIC8058_PWM) += pmic8058-pwm.o
ifeq ($(CONFIG_MSM_SSBI),y)
else
obj-$(CONFIG_PMIC8058_NFC) += pmic8058-nfc.o
endif
