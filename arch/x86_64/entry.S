/* This is taken from the glibc rtld entry point,
 * it's the equivalent of RTLD_START
 */

	.text
	.align 16
	
.globl	_start
.globl	_dl_start_user

_start:
	movq %rsp, %rdi
	call _dl_start

_dl_start_user:
	// save the user entry point address in %r12
	movq %rax, %r12
	// Check if program was run from command line
	movl _dl_skip_args(%rip), %eax
	// Get argc
	pop %rdx
	// Adjust stack pointer to skip _dl_skip_args words
	leaq (%rsp,%rax,8), %rsp
	// Subtract _dl_skip_args from argc
	subl %eax, %edx
	// Push argc back on the stack
	pushq %rdx
	// Call _dl_init(struct link_map *main_map, int argc,
	//               char **argv, char **env)
	// where argc -> rsi
	movq %rdx, %rsi
	// Align stack for _dl_init_internal
	andq $-16, %rsp
	// _dl_loaded -> rdi
	movq _rtld_local(%rip), %rdi
	// env -> rcx
	leaq 16(%r13,%rdx,8), %rcx
	// argv -> rdx
	leaq 8(%r13), %rdx
	// Clear %rbp to mark outermost frame for constructors
	xorl %ebp, %ebp
	// Run initializers
	call _dl_init_internal@PLT
	// Pass finalizer function to the user in %rdx as per ELF ABI
	leaq _dl_fini(%rip), %rdx 
	// Make sure %rsp points to argc 
	movq %r13, %rsp
	// Jump to the user's entry point
	jmp *%r12

.previous








