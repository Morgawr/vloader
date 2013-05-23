/* This file is actually the entry point and is a disguised assembly code
 * fragment
 */

#ifndef __ENTRY_S_H
#define __ENTRY_S_H

#define ELF_MACHINE_NAME "i386"

/* Ha! Here is where everything starts, the actual entry point is _dl_start */
#define RTLD_ENTRY asm("\n\
	.text \n\
	.align  16\n\
0:	movl (%esp), %ebx\n\
	ret\n\
	.align 16\n\
.globl	_start\n\
.globl	_dl_start_user\n\
_start:\n\
	# _dl_start gets the parameters in %eax\n\
	movl %esp, %eax \n\
	# With this we enter into the actual entry point of the loader\n\
	call _dl_start\n\
_dl_start_user:\n\
	# Save entry point address in %edi\n\
	movl %eax, %edi\n\
	# Point %ebx to the GOT\n\
	call 0b	\n\
	addl $_GLOBAL_OFFSET_TABLE, %ebx\n\
	# Check if the program was called from command line (should be)\n\
	movl _dl_skip_args@GOTOFF(%ebx), %eax\n\
	# Retrieve argc\n\
	popl %edx\n\
	# Adjust the stack pointer to skip _dl_skip_args words\n\
	leal (%esp,%eax,4), %esp\n\
	# Subtract _dl_skip_args from argc\n\
	subl %eax, %edx\n\
	# Push argc back on the stack\n\
	push %edx\n\
	# Load the parameters again\n\
	movl _rtld_local@GOTOFF(%ebx), %eax\n\
	leal 8(%esp,%edx,4), %esi\n\
	leal 4(%esp), %ecx\n\
	movl %esp, %ebp\n\
	# Make sure _dl_init is run with 16 bytes aligned stack\n\
	andl $-16, %esp\n\
	pushl %eax\n\
	pushl %eax\n\
	pushl %ebp\n\
	pushl %esi\n\
	# Clear %ebp so that even constructors have terminated backchain.\n\
	xorl %ebp, %ebp\n\
	# Call the function to run the initializers\n\
	call _dl_init_internal@PLT\n\
	# Pass the finalizer function to the user in %edx as per ELF ABI\n\
	leal _dl_fini@GOTOFF(%ebx), %edx\n\
	# Restore %esp _start expects\n\
	movl (%esp), %esp\n\
	# Jump to the user's entry point\n\
	jmp *%edi\n\
.previous\n\");

#endif // __ENTRY_S_H
