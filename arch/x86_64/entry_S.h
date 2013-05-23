/* This file is actually the entry point and is a disguised assembly code
 * fragment
 */

#ifndef __ENTRY_S_H
#define __ENTRY_S_H

#define ELF_MACHINE_NAME "x86_64"


/* Ha! Here is where everything starts, the actual entry point is _dl_start */
#define RTLD_ENTRY asm("\n\
	.text\n\
	.align 16\n\
.globl	_start\n\
.globl	_dl_start_user\n\
_start:\n\
	movq %rsp, %rdi\n\
	call _dl_start\n\
_dl_start_user:\n\
	# save the user entry point address in %r12\n\
	movq %rax, %r12\n\
	# Check if program was run from command line\n\
	movl _dl_skip_args(%rip), %eax\n\
	# Get argc\n\
	pop %rdx\n\
	# Adjust stack pointer to skip _dl_skip_args words\n\
	leaq (%rsp,%rax,8), %rsp\n\
	# Subtract _dl_skip_args from argc\n\
	subl %eax, %edx\n\
	# Push argc back on the stack\n\
	pushq %rdx\n\
	# Call _dl_init(struct link_map *main_map, int argc,\n\
	#               char **argv, char **env)\n\
	# where argc -> rsi\n\
	movq %rdx, %rsi\n\
	# Align stack for _dl_init_internal\n\
	andq $-16, %rsp\n\
	# _dl_loaded -> rdi\n\
	movq _rtld_local(%rip), %rdi\n\
	# env -> rcx\n\
	leaq 16(%r13,%rdx,8), %rcx\n\
	# argv -> rdx\n\
	leaq 8(%r13), %rdx\n\
	# Clear %rbp to mark outermost frame for constructors\n\
	xorl %ebp, %ebp\n\
	# Run initializers\n\
	call _dl_init_internal@PLT\n\
	# Pass finalizer function to the user in %rdx as per ELF ABI\n\
	leaq _dl_fini(%rip), %rdx \n\
	# Make sure %rsp points to argc \n\
	movq %r13, %rsp\n\
	# Jump to the user's entry point\n\
	jmp *%r12\n\
.previous\n\
");



#endif // __ENTRY_S_H




