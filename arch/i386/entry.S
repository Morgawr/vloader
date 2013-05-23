/* This is taken from the glibc rtld entry point,
 * it's the equivalent of RTLD_START
 */

	.text 
	.align  16

0:	movl (%esp), %ebx
	ret

	.align 16

.globl	_start
.globl	_dl_start_user

_start:
	// _dl_start gets the parameters in %eax
	movl %esp, %eax 
	// With this we enter into the actual entry point of the loader
	call _dl_start

_dl_start_user:
	// Save entry point address in %edi
	movl %eax, %edi
	// Point %ebx to the GOT
	call 0b	
	addl $_GLOBAL_OFFSET_TABLE, %ebx
	// Check if the program was called from command line (should be)
	movl _dl_skip_args@GOTOFF(%ebx), %eax
	// Retrieve argc
	popl %edx
	// Adjust the stack pointer to skip _dl_skip_args words
	leal (%esp,%eax,4), %esp
	// Subtract _dl_skip_args from argc
	subl %eax, %edx
	// Push argc back on the stack
	push %edx

	// Load the parameters again
	movl _rtld_local@GOTOFF(%ebx), %eax
	leal 8(%esp,%edx,4), %esi
	leal 4(%esp), %ecx
	movl %esp, %ebp
	// Make sure _dl_init is run with 16 bytes aligned stack
	andl $-16, %esp
	pushl %eax
	pushl %eax
	pushl %ebp
	pushl %esi
	// Clear %ebp so that even constructors have terminated backchain.
	xorl %ebp, %ebp
	// Call the function to run the initializers
	call _dl_init_internal@PLT
	// Pass the finalizer function to the user in %edx as per ELF ABI
	leal _dl_fini@GOTOFF(%ebx), %edx
	// Restore %esp _start expects
	movl (%esp), %esp
	// Jump to the user's entry point
	jmp *%edi

.previous




