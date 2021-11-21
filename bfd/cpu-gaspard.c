#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"


const bfd_arch_info_type bfd_gaspard_arch =


{
  64,               /* 16 bits in a word.  */
  64,               /* 32 bits in an address.  */
   8,               /*  8 bits in a byte.  */
  bfd_arch_gaspard,    /* enum bfd_architecture arch.  */
  bfd_mach_gaspard,    /* Machine value, used to distinguish between cr16 variants.  */
  "gaspard",           /* Architecture name (short version).  */
  "gaspard",           /* Architecture name (long version).  */
  1,                /* Section alignment power.  */
  1,             /* True if this is the default machine for the architecture.  */
  bfd_default_compatible, /* Function to call to determine if two different architectures are compatible.  */
  bfd_default_scan, /* Function to call to determine if a given string matches this architecture.  */
  NULL,             /* Pointer to the next gaspard machine architecture.  */
};
