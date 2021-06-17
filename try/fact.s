	.file	"fact.c"
	.text
	.globl	factorial
	.type	factorial, @function
factorial:
	movl	$1, %edx
	movl	$0, %eax
.L2:
	cmpl	%edi, %eax
	jg	.L4
	imull	%eax, %edx
	addl	$1, %eax
	jmp	.L2
.L4:
	movl	%edx, %eax
	ret
	.size	factorial, .-factorial
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"factorial(%d) = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
	subq	$8, %rsp
	movl	$5, %edi
	call	factorial
	movl	%eax, %edx
	movl	$5, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$8, %rsp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 9.2.1 20191120 (Red Hat 9.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
