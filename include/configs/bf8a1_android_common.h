/*
 * Copyright (C) 2013-2016 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _BF8A1_ANDROID_COMMON_H
#define _BF8A1__ANDROID_COMMON_H

#define CONFIG_CI_UDC
#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_DUALSPEED

#define CONFIG_USB_GADGET
#define CONFIG_CMD_USB_MASS_STORAGE
#define CONFIG_USB_GADGET_MASS_STORAGE
#define CONFIG_USBDOWNLOAD_GADGET
#define CONFIG_USB_GADGET_VBUS_DRAW	2

#define CONFIG_G_DNL_VENDOR_NUM		0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM	0x0d02
#define CONFIG_G_DNL_MANUFACTURER	"FSL"

#define CONFIG_CMD_FASTBOOT
#define CONFIG_CMD_READ
#define CONFIG_BCB_SUPPORT
#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_FASTBOOT_FLASH

#define CONFIG_FSL_FASTBOOT
#define CONFIG_ANDROID_RECOVERY

#if defined CONFIG_SYS_BOOT_NAND
#define CONFIG_FASTBOOT_STORAGE_NAND
#elif defined CONFIG_SYS_BOOT_SATA
#define CONFIG_FASTBOOT_STORAGE_SATA
#else
#define CONFIG_FASTBOOT_STORAGE_MMC
#endif

#define CONFIG_ANDROID_MAIN_MMC_BUS 2
#define CONFIG_ANDROID_BOOT_PARTITION_MMC 1
#define CONFIG_ANDROID_SYSTEM_PARTITION_MMC 5
#define CONFIG_ANDROID_RECOVERY_PARTITION_MMC 2
#define CONFIG_ANDROID_CACHE_PARTITION_MMC 6
#define CONFIG_ANDROID_DATA_PARTITION_MMC 4
#define CONFIG_ANDROID_MISC_PARTITION_MMC 8

#if defined(CONFIG_FASTBOOT_STORAGE_NAND)
#define ANDROID_FASTBOOT_NAND_PARTS "16m@64m(boot) 16m@80m(recovery) 810m@96m(android_root)ubifs"
#endif

#define CONFIG_CMD_BOOTA
#define CONFIG_SUPPORT_RAW_INITRD
#define CONFIG_SERIAL_TAG

#undef CONFIG_EXTRA_ENV_SETTINGS
#undef CONFIG_BOOTCOMMAND

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"script=boot.scr\0" \
	"image=zImage\0" \
	"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"fdt_addr=0x18000000\0" \
	"boot_fdt=try\0" \
	"ip_dyn=yes\0" \
	"console=" CONFIG_CONSOLE_DEV "\0" \
	"splashpos=m,m\0"	\
	"fdt_high=0xffffffff\0"	  \
	"initrd_high=0xffffffff\0" \
	"bootramdisk=uramdisk.img\0" \
	"initrdaddr=0x13000000\0" \
	"bootargs_base=console=ttymxc3,115200\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
	EMMC_ENV	 \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
	"root=${mmcroot}; ${bootargs_base}\0" \
	"loadbootscript=" \
	"fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
	"source\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadramdisk=fatload mmc ${mmcdev}:${mmcpart} ${initrdaddr} ${bootramdisk}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
	"run mmcargs; " \
	"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
	"	if run loadfdt; then " \
			"bootz ${loadaddr} - ${fdt_addr}; " \
		"else " \
			"if test ${boot_fdt} = try; then " \
			"bootz; " \
		"else " \
			"echo WARN: Cannot load the DT; " \
		"fi; " \
	"fi; " \
	"else " \
		"bootz; " \
	"fi;\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=fatload mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
	"env import -t -r $loadaddr $filesize\0" \
	"tn_boot_init=" \
		"if test ${bootmedia} = mmc; then " \
			"mmc dev ${mmcdev}; mmc rescan; " \
		"fi;" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi;" \
		"if run loadramdisk; then " \
			"setenv rootdevice ${ramdisk_dev}; " \
			"setenv mmcboot \'run mmcargs; bootz ${loadaddr} ${initrdaddr} ${fdt_addr}\'; " \
		"fi;" \
		"if run loadimage; then " \
			"run loadfdt; " \
			"run mmcboot; " \
		"else " \
			"if run loadimage; then " \
				"run mmcboot; " \
			"else " \
				"echo WARN: Cannot load kernel from boot media; " \
			"fi; " \
		"fi;\0" \

#define CONFIG_USB_FASTBOOT_BUF_ADDR   CONFIG_SYS_LOAD_ADDR
#ifdef CONFIG_FASTBOOT_STORAGE_NAND
#define CONFIG_USB_FASTBOOT_BUF_SIZE   0x25000000
#else
#define CONFIG_USB_FASTBOOT_BUF_SIZE   0x19000000
#endif
#endif /* MX6_SABRE_ANDROID_COMMON_H */
