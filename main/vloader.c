#include "include/config.h"
#include <stdio.h>
#include <elf.h>
#include <link.h>

/* machine dependent entry point */
#include <entry_S.h>
RTLD_ENTRY
/* end of machine dependent entry point */

/* Actual C entry point of the rtld */
static ElfW(Addr) _dl_start(void *arg)
{
	return 0; //stub
}


