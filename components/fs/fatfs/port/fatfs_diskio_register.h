#ifndef FATFS_DISKIO_REGISTER_H
#define FATFS_DISKIO_REGISTER_H

#if defined(CONFIG_FATFS_SDH_SDCARD)

void fatfs_sdh_driver_register(void);

#elif defined(CONFIG_FATFS_USBH)

void fatfs_usbh_driver_register(void);

#endif

#endif