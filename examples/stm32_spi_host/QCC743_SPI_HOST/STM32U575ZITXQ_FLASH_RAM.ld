/*
******************************************************************************
**
**  File        : LinkerScript.ld (debug in RAM dedicated)
**
**  Author      : STM32CubeIDE
**
**  Abstract    : Linker script for STM32U575xx Device from STM32U5 series
**                      784Kbytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** Copyright (c) 2023 STMicroelectronics.
** All rights reserved.
**
** This software is licensed under terms that can be found in the LICENSE file
** in the root directory of this software component.
** If no LICENSE file comes with this software, it is provided AS-IS.
**
*****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);	/* end of "RAM" Ram type memory */

_Min_Heap_Size = 0x200;	/* required amount of heap  */
_Min_Stack_Size = 0x400;	/* required amount of stack */

/* Memories definition */
MEMORY
{
  RAM	(xrw)	: ORIGIN = 0x20000000,	LENGTH = 768K
  SRAM4	(xrw)	: ORIGIN = 0x28000000,	LENGTH = 16K
  FLASH	(rx)	: ORIGIN = 0x08000000,	LENGTH = 2048K
}

/* Sections */
SECTIONS
{
  .isr_vector :
  {
	_sisr_vector = .;
    KEEP(*(.isr_vector)) /* Startup code */
	KEEP(*(.text.Reset_Handler))
	KEEP(*(.text.SystemInit))
	KEEP(*loader*.o*(.text .text.*))
	_eisr_vector = .;
  } > FLASH

  __isr_vector_load_addr_start = LOADADDR(.isr_vector);
  __isr_vector_load_addr_end = __isr_vector_load_addr_start + SIZEOF(.isr_vector);
  
  /* The program code and other data into "RAM" Ram type memory */
  .text :
  {
	_stext = .;		/* define a global symbols at start of code */
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    KEEP (*(.init))
    KEEP (*(.fini))

    _etext = .;        /* define a global symbols at end of code */
  } > RAM AT > FLASH
  __text_load_addr_start = LOADADDR(.text);
  __text_load_addr_end = __text_load_addr_start + SIZEOF(.text);

  /* Constant data into "RAM" Ram type memory */
  .rodata :
  {
	_srodata = .;
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
	_erodata = .;
  } > RAM AT > FLASH

  __rodata_load_addr_start = LOADADDR(.rodata);
  __rodata_load_addr_end = __rodata_load_addr_start + SIZEOF(.rodata);
  
  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >RAM

  .ARM :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >RAM

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >RAM

  .init_array :
  {
    PROVIDE (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE (__init_array_end = .);
  } > RAM AT > FLASH
  __init_array_load_addr_start = LOADADDR(.init_array);
  __init_array_load_addr_end = __init_array_load_addr_start + SIZEOF(.init_array);

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >RAM

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM" Ram type memory */
  .data :
  {
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    _edata = .;        /* define a global symbol at data end */
  } > RAM AT > FLASH

  /* Uninitialized data section into "RAM" Ram type memory */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } > RAM

  /* User_heap_stack section, used to check that there is enough "RAM" Ram type memory left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } > RAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
