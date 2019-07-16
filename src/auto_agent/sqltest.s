	.file	"sqltest.c"
	.globl	pHostName
	.section	.rodata
.LC0:
	.string	"localhost"
	.data
	.align 8
	.type	pHostName, @object
	.size	pHostName, 8
pHostName:
	.quad	.LC0
	.globl	pUserName
	.section	.rodata
.LC1:
	.string	"root"
	.data
	.align 8
	.type	pUserName, @object
	.size	pUserName, 8
pUserName:
	.quad	.LC1
	.globl	pPassword
	.section	.rodata
.LC2:
	.string	"guagua"
	.data
	.align 8
	.type	pPassword, @object
	.size	pPassword, 8
pPassword:
	.quad	.LC2
	.globl	pDbName
	.section	.rodata
.LC3:
	.string	"automation"
	.data
	.align 8
	.type	pDbName, @object
	.size	pDbName, 8
pDbName:
	.quad	.LC3
	.globl	DbPort
	.section	.rodata
	.align 4
	.type	DbPort, @object
	.size	DbPort, 4
DbPort:
	.long	3306
.LC4:
	.string	"mysql_real_connect fail"
.LC5:
	.string	"select * from project"
.LC6:
	.string	"mysql_real_query fail"
.LC7:
	.string	"mysql_store_result fail"
.LC8:
	.string	"%s, %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$1352, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-1328(%rbp), %rax
	movq	%rax, %rdi
	call	mysql_init
	movl	$3306, %r8d
	movq	pDbName(%rip), %rdi
	movq	pPassword(%rip), %rcx
	movq	pUserName(%rip), %rdx
	movq	pHostName(%rip), %rsi
	leaq	-1328(%rbp), %rax
	movq	$0, 8(%rsp)
	movq	$0, (%rsp)
	movl	%r8d, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	mysql_real_connect
	testq	%rax, %rax
	jne	.L2
	movl	$.LC4, %edi
	call	puts
	movl	$0, %eax
	jmp	.L8
.L2:
	leaq	-1328(%rbp), %rax
	movl	$21, %edx
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	mysql_real_query
	testl	%eax, %eax
	je	.L4
	movl	$.LC6, %edi
	call	puts
	movl	$0, %eax
	jmp	.L8
.L4:
	leaq	-1328(%rbp), %rax
	movq	%rax, %rdi
	call	mysql_store_result
	movq	%rax, -1344(%rbp)
	cmpq	$0, -1344(%rbp)
	jne	.L5
	movl	$.LC7, %edi
	call	puts
	leaq	-1328(%rbp), %rax
	movq	%rax, %rdi
	call	mysql_error
	movq	%rax, %rdi
	call	puts
	jmp	.L6
.L5:
	jmp	.L6
.L7:
	movq	-1336(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdx
	movq	-1336(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
.L6:
	movq	-1344(%rbp), %rax
	movq	%rax, %rdi
	call	mysql_fetch_row
	movq	%rax, -1336(%rbp)
	cmpq	$0, -1336(%rbp)
	jne	.L7
	movq	-1344(%rbp), %rax
	movq	%rax, %rdi
	call	mysql_free_result
	leaq	-1328(%rbp), %rax
	movq	%rax, %rdi
	call	mysql_close
	movl	$0, %eax
.L8:
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L9
	call	__stack_chk_fail
.L9:
	addq	$1352, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
