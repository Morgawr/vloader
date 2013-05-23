#include "include/config.h"
#include <stdio.h>
#include <elf.h>
#include <link.h>

#include <sugar.h>

/* Datas */

int _dl_argc attribute_relro attribute_hidden;
unsigned int _dl_skip_args attribute_relro attribute_hidden;
char **_dl_argv attribute_relro = NULL;


/* Prototypes */

static ElfW(Addr) _dl_start(void *arg);
static ElfW(Addr) _dl_start_final(void *arg);

/* machine dependent entry point */
#include <entry_S.h>
RTLD_ENTRY
/* end of machine dependent entry point */



/* Actual C entry point of the rtld */
static ElfW(Addr) __used _dl_start(void *arg)
{
	return 0; //stub
}

static inline ElfW(Addr) forced_inline _dl_start_final(void *arg)
{
	return 0; //stub
}


