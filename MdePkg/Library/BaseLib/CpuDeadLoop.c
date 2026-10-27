/** @file
  Base Library CPU Functions for all architectures.

  Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Base.h>
#include <Library/BaseLib.h>

/**
  Executes an infinite loop.

  Forces the CPU to execute an infinite loop. A debugger may be used to skip
  past the loop and the code that follows the loop must execute properly. This
  implies that the infinite loop must not cause the code that follow it to be
  optimized away.

**/
VOID
EFIAPI
CpuDeadLoop (
  VOID
  )
{
  volatile UINTN  Index;

  for (Index = 0; Index == 0;) {
    *(volatile UINT32 *)(UINTN)0x0B017010 = 0xFFFFFFFF;
    *(volatile UINT32 *)(UINTN)0x0B017014 = 0xFFFFFFFF;
    *(volatile UINT32 *)(UINTN)0x0B017008 = 0; // WDT0_EN = 0 (DISABLE)
    *(volatile UINT32 *)(UINTN)0x0B017004 = 1; // WDT0_RST = 1 (PET)
    *(volatile UINT32 *)(UINTN)0x0B017000 = 1;
    CpuPause ();
  }
}
