#ifndef __SUGAR_H
#define __SUGAR_H

/* Some syntactic sugar for the uglies of GNU extensions and the C language */
#define attribute_hidden __attribute__((visibility ("hidden")))
#define attribute_relro __attribute__((section (".data.rel.ro")))
#define forced_inline __attribute__((always_inline))
#define __used __attribute__((__used__))

#endif //__SUGAR_H
