	.file	"a.c"
	.text
	.globl	tgt
	.data
	.align 32
	.type	tgt, @object
	.size	tgt, 38
tgt:
	.string	"Lorem ipsum sit consecutar dolor amet"
	.section	.rodata
	.align 8
.LC0:
	.string	"01233456789abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.; "
	.align 8
.LC1:
	.string	"Error: Failed to allocate population\n"
.LC2:
	.string	"%8d:%s%8d"
.LC4:
	.string	"%8d:%s%8d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movl	%edi, -132(%rbp)
	movq	%rsi, -144(%rbp)
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movl	$0, -112(%rbp)
	leaq	tgt(%rip), %rdi
	call	strlen@PLT
	movq	%rax, -48(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -40(%rbp)
	movq	$0, -32(%rbp)
	movl	$-1, -92(%rbp)
	movl	$-1, -88(%rbp)
	movl	$-1, -84(%rbp)
	movq	$32, -72(%rbp)
	movq	-72(%rbp), %rax
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -64(%rbp)
	cmpq	$0, -64(%rbp)
	jne	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$37, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rdi
	call	fwrite@PLT
	movl	$1, %eax
	jmp	.L3
.L2:
	movq	$0, -56(%rbp)
	jmp	.L4
.L5:
	movq	-56(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	genstr
	movq	%rax, (%rbx)
	addq	$1, -56(%rbp)
.L4:
	movq	-56(%rbp), %rax
	cmpq	-72(%rbp), %rax
	jb	.L5
	movq	-72(%rbp), %rsi
	movq	-64(%rbp), %rax
	leaq	cmpstr(%rip), %rcx
	movl	$8, %edx
	movq	%rax, %rdi
	call	qsort@PLT
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	leaq	tgt(%rip), %rsi
	movq	%rax, %rdi
	call	fitness
	movl	%eax, %ecx
	movq	-64(%rbp), %rax
	movq	(%rax), %rdx
	movl	-112(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$13, %edi
	call	putchar@PLT
	movb	$0, -113(%rbp)
	movl	$0, -108(%rbp)
	jmp	.L6
.L16:
	movq	-72(%rbp), %rsi
	movq	-64(%rbp), %rax
	leaq	cmpstr(%rip), %rcx
	movl	$8, %edx
	movq	%rax, %rdi
	call	qsort@PLT
	movq	-72(%rbp), %rax
	testq	%rax, %rax
	js	.L7
	cvtsi2sdq	%rax, %xmm0
	jmp	.L8
.L7:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L8:
	movsd	.LC3(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -80(%rbp)
	movl	-80(%rbp), %eax
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -64(%rbp)
	cmpq	$0, -64(%rbp)
	je	.L19
	movl	$0, -104(%rbp)
	jmp	.L11
.L12:
	movl	-80(%rbp), %eax
	movl	%eax, %esi
	movl	$0, %edi
	call	genrnd
	cltq
	movq	-72(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rbx
	movl	-80(%rbp), %eax
	movl	%eax, %esi
	movl	$0, %edi
	call	genrnd
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	tgt(%rip), %rdx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	mate
	movq	%rax, -24(%rbp)
	movl	-104(%rbp), %eax
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rax, (%rdx)
	addl	$1, -104(%rbp)
.L11:
	movl	-104(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jl	.L12
	movl	-80(%rbp), %eax
	cltq
	addq	%rax, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	-64(%rbp), %rax
	leaq	cmpstr(%rip), %rcx
	movl	$8, %edx
	movq	%rax, %rdi
	call	qsort@PLT
	movl	$0, -100(%rbp)
	jmp	.L13
.L14:
	movl	-100(%rbp), %eax
	cltq
	movq	-72(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	addl	$1, -100(%rbp)
.L13:
	movl	-100(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jl	.L14
	movl	-80(%rbp), %eax
	cltq
	movq	-72(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -64(%rbp)
	cmpq	$0, -64(%rbp)
	je	.L20
	movl	-80(%rbp), %eax
	cltq
	subq	%rax, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	-64(%rbp), %rax
	leaq	cmpstr(%rip), %rcx
	movl	$8, %edx
	movq	%rax, %rdi
	call	qsort@PLT
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	leaq	tgt(%rip), %rsi
	movq	%rax, %rdi
	call	fitness
	movl	%eax, -76(%rbp)
	cmpl	$0, -76(%rbp)
	sete	%al
	movb	%al, -113(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rdx
	movl	-76(%rbp), %ecx
	movl	-112(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -112(%rbp)
	addl	$1, -108(%rbp)
.L6:
	cmpl	$4095, -108(%rbp)
	jg	.L10
	movzbl	-113(%rbp), %eax
	xorl	$1, %eax
	testb	%al, %al
	jne	.L16
	jmp	.L10
.L19:
	nop
	jmp	.L10
.L20:
	nop
.L10:
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, -96(%rbp)
	jmp	.L17
.L18:
	movl	-96(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	addl	$1, -96(%rbp)
.L17:
	movl	-96(%rbp), %eax
	cltq
	cmpq	%rax, -72(%rbp)
	ja	.L18
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
.L3:
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC5:
	.string	"Error:genstr: failed to allocate buffer\n"
	.align 8
.LC6:
	.string	"Error:genstr: invalid parameters\n"
	.text
	.globl	genstr
	.type	genstr, @function
genstr:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	$0, -24(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L22
	cmpq	$0, -48(%rbp)
	je	.L22
	movq	-48(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L23
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -8(%rbp)
	movq	$0, -16(%rbp)
	jmp	.L24
.L25:
	call	rand@PLT
	cltq
	movl	$0, %edx
	divq	-8(%rbp)
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addq	$1, -16(%rbp)
.L24:
	movq	-16(%rbp), %rax
	cmpq	-48(%rbp), %rax
	jb	.L25
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	jmp	.L27
.L23:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$40, %edx
	movl	$1, %esi
	leaq	.LC5(%rip), %rdi
	call	fwrite@PLT
	jmp	.L27
.L22:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$33, %edx
	movl	$1, %esi
	leaq	.LC6(%rip), %rdi
	call	fwrite@PLT
.L27:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	genstr, .-genstr
	.section	.rodata
	.align 8
.LC7:
	.string	"Error:fitness: invalid parameters\n"
	.text
	.globl	fitness
	.type	fitness, @function
fitness:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$-1, -28(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L30
	cmpq	$0, -48(%rbp)
	je	.L30
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -8(%rbp)
	movl	$0, -28(%rbp)
	movq	$0, -24(%rbp)
	jmp	.L31
.L33:
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movq	-48(%rbp), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	setne	%al
	movzbl	%al, %eax
	addl	%eax, -28(%rbp)
	addq	$1, -24(%rbp)
.L31:
	movq	-24(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jnb	.L36
	movq	-24(%rbp), %rax
	cmpq	-8(%rbp), %rax
	jb	.L33
	jmp	.L36
.L30:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$34, %edx
	movl	$1, %esi
	leaq	.LC7(%rip), %rdi
	call	fwrite@PLT
	jmp	.L34
.L36:
	nop
.L34:
	movl	-28(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	fitness, .-fitness
	.section	.rodata
.LC8:
	.string	"Error:mate: unequal lengths\n"
	.align 8
.LC9:
	.string	"Error:mate: invalid parameters\n"
	.text
	.globl	mate
	.type	mate, @function
mate:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	movq	$0, -56(%rbp)
	cmpq	$0, -72(%rbp)
	je	.L38
	cmpq	$0, -80(%rbp)
	je	.L38
	cmpq	$0, -88(%rbp)
	je	.L38
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rbx
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpq	%rax, %rbx
	jne	.L39
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -40(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -32(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -56(%rbp)
	movq	$0, -48(%rbp)
	jmp	.L40
.L44:
	movl	$100, %esi
	movl	$0, %edi
	call	genrnd
	movl	%eax, -60(%rbp)
	cmpl	$44, -60(%rbp)
	jg	.L41
	movq	-72(%rbp), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movq	-56(%rbp), %rcx
	movq	-48(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	jmp	.L42
.L41:
	cmpl	$89, -60(%rbp)
	jg	.L43
	movq	-80(%rbp), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movq	-56(%rbp), %rcx
	movq	-48(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	jmp	.L42
.L43:
	cmpl	$99, -60(%rbp)
	jg	.L42
	call	rand@PLT
	cltq
	movl	$0, %edx
	divq	-24(%rbp)
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movq	-56(%rbp), %rcx
	movq	-48(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
.L42:
	addq	$1, -48(%rbp)
.L40:
	movq	-48(%rbp), %rax
	cmpq	-40(%rbp), %rax
	jb	.L44
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	jmp	.L46
.L39:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$28, %edx
	movl	$1, %esi
	leaq	.LC8(%rip), %rdi
	call	fwrite@PLT
	jmp	.L46
.L38:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$31, %edx
	movl	$1, %esi
	leaq	.LC9(%rip), %rdi
	call	fwrite@PLT
.L46:
	movq	-56(%rbp), %rax
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	mate, .-mate
	.globl	genrnd
	.type	genrnd, @function
genrnd:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	call	rand@PLT
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %ecx
	movl	%edx, %eax
	cltd
	idivl	%ecx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	genrnd, .-genrnd
	.globl	cmpstr
	.type	cmpstr, @function
cmpstr:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	leaq	tgt(%rip), %rsi
	movq	%rax, %rdi
	call	fitness
	movl	%eax, -24(%rbp)
	movq	-8(%rbp), %rax
	leaq	tgt(%rip), %rsi
	movq	%rax, %rdi
	call	fitness
	movl	%eax, -20(%rbp)
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	setg	%al
	movb	%al, -25(%rbp)
	movl	-24(%rbp), %eax
	subl	-20(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	cmpstr, .-cmpstr
	.section	.rodata
	.align 8
.LC3:
	.long	0
	.long	1071644672
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
