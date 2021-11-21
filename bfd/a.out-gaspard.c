#define N_HEADER_IN_TEXT(x) 0
#define BYTES_IN_WORD 4
/*#define ENTRY_CAN_BE_ZERO*/
/*#define N_SHARED_LIB(x) 0*/
#define TEXT_START_ADDR 4198560
#define TARGET_PAGE_SIZE 40
#define SEGMENT_SIZE TARGET_PAGE_SIZE
#define DEFAULT_ARCH bfd_arch_unknown

/* Do not "beautify" the CONCAT* macro args.  Traditional C will not   remove whitespace added here, and thus will fail to concatenate   the tokens.  */
#define MY(OP) CONCAT2 (gaspard_,OP)

#define TARGETNAME "a.out-gaspard"

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
#include "libaout.h"

#include "aout-target.h"
