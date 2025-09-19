
./throughput_simd_fma.x:     file format elf64-x86-64


Disassembly of section .init:

0000000000400468 <_init>:
  400468:	f3 0f 1e fa          	endbr64 
  40046c:	48 83 ec 08          	sub    $0x8,%rsp
  400470:	48 8b 05 79 0b 20 00 	mov    0x200b79(%rip),%rax        # 600ff0 <__gmon_start__@Base>
  400477:	48 85 c0             	test   %rax,%rax
  40047a:	74 02                	je     40047e <_init+0x16>
  40047c:	ff d0                	callq  *%rax
  40047e:	48 83 c4 08          	add    $0x8,%rsp
  400482:	c3                   	retq   

Disassembly of section .plt:

0000000000400490 <.plt>:
  400490:	ff 35 72 0b 20 00    	pushq  0x200b72(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400496:	ff 25 74 0b 20 00    	jmpq   *0x200b74(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40049c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004004a0 <printf@plt>:
  4004a0:	ff 25 72 0b 20 00    	jmpq   *0x200b72(%rip)        # 601018 <printf@GLIBC_2.2.5>
  4004a6:	68 00 00 00 00       	pushq  $0x0
  4004ab:	e9 e0 ff ff ff       	jmpq   400490 <.plt>

Disassembly of section .text:

00000000004004b0 <main>:
  4004b0:	53                   	push   %rbx
  4004b1:	bf 64 00 00 00       	mov    $0x64,%edi
  4004b6:	31 db                	xor    %ebx,%ebx
  4004b8:	48 83 ec 10          	sub    $0x10,%rsp
  4004bc:	0f 1f 40 00          	nopl   0x0(%rax)
  4004c0:	0f 31                	rdtsc  
  4004c2:	89 d1                	mov    %edx,%ecx
  4004c4:	89 c6                	mov    %eax,%esi
  4004c6:	0f 31                	rdtsc  
  4004c8:	48 c1 e2 20          	shl    $0x20,%rdx
  4004cc:	89 c0                	mov    %eax,%eax
  4004ce:	48 c1 e1 20          	shl    $0x20,%rcx
  4004d2:	48 09 c2             	or     %rax,%rdx
  4004d5:	48 09 f1             	or     %rsi,%rcx
  4004d8:	48 29 ca             	sub    %rcx,%rdx
  4004db:	48 01 d3             	add    %rdx,%rbx
  4004de:	83 ef 01             	sub    $0x1,%edi
  4004e1:	75 dd                	jne    4004c0 <main+0x10>
  4004e3:	31 c0                	xor    %eax,%eax
  4004e5:	48 89 de             	mov    %rbx,%rsi
  4004e8:	bf f8 06 40 00       	mov    $0x4006f8,%edi
  4004ed:	e8 ae ff ff ff       	callq  4004a0 <printf@plt>
  4004f2:	48 85 db             	test   %rbx,%rbx
  4004f5:	78 5b                	js     400552 <main+0xa2>
  4004f7:	c5 f1 57 c9          	vxorpd %xmm1,%xmm1,%xmm1
  4004fb:	c4 e1 f3 2a cb       	vcvtsi2sd %rbx,%xmm1,%xmm1
  400500:	c5 f3 59 0d 60 02 00 	vmulsd 0x260(%rip),%xmm1,%xmm1        # 400768 <__dso_handle+0x78>
  400507:	00 
  400508:	bf 28 07 40 00       	mov    $0x400728,%edi
  40050d:	b8 01 00 00 00       	mov    $0x1,%eax
  400512:	c5 f3 5e 0d 56 02 00 	vdivsd 0x256(%rip),%xmm1,%xmm1        # 400770 <__dso_handle+0x80>
  400519:	00 
  40051a:	c5 f9 28 c1          	vmovapd %xmm1,%xmm0
  40051e:	c5 fb 11 4c 24 08    	vmovsd %xmm1,0x8(%rsp)
  400524:	e8 77 ff ff ff       	callq  4004a0 <printf@plt>
  400529:	c5 fb 10 4c 24 08    	vmovsd 0x8(%rsp),%xmm1
  40052f:	bf 50 07 40 00       	mov    $0x400750,%edi
  400534:	c5 fb 10 05 3c 02 00 	vmovsd 0x23c(%rip),%xmm0        # 400778 <__dso_handle+0x88>
  40053b:	00 
  40053c:	b8 01 00 00 00       	mov    $0x1,%eax
  400541:	c5 fb 5e c1          	vdivsd %xmm1,%xmm0,%xmm0
  400545:	e8 56 ff ff ff       	callq  4004a0 <printf@plt>
  40054a:	48 83 c4 10          	add    $0x10,%rsp
  40054e:	31 c0                	xor    %eax,%eax
  400550:	5b                   	pop    %rbx
  400551:	c3                   	retq   
  400552:	48 89 d8             	mov    %rbx,%rax
  400555:	83 e3 01             	and    $0x1,%ebx
  400558:	c5 f1 57 c9          	vxorpd %xmm1,%xmm1,%xmm1
  40055c:	48 d1 e8             	shr    %rax
  40055f:	48 09 d8             	or     %rbx,%rax
  400562:	c4 e1 f3 2a c8       	vcvtsi2sd %rax,%xmm1,%xmm1
  400567:	c5 f3 58 c9          	vaddsd %xmm1,%xmm1,%xmm1
  40056b:	eb 93                	jmp    400500 <main+0x50>

000000000040056d <.annobin_elf_init.c.hot>:
  40056d:	0f 1f 00             	nopl   (%rax)

0000000000400570 <_start>:
  400570:	f3 0f 1e fa          	endbr64 
  400574:	31 ed                	xor    %ebp,%ebp
  400576:	49 89 d1             	mov    %rdx,%r9
  400579:	5e                   	pop    %rsi
  40057a:	48 89 e2             	mov    %rsp,%rdx
  40057d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400581:	50                   	push   %rax
  400582:	54                   	push   %rsp
  400583:	49 c7 c0 d0 06 40 00 	mov    $0x4006d0,%r8
  40058a:	48 c7 c1 60 06 40 00 	mov    $0x400660,%rcx
  400591:	48 c7 c7 b0 04 40 00 	mov    $0x4004b0,%rdi
  400598:	ff 15 4a 0a 20 00    	callq  *0x200a4a(%rip)        # 600fe8 <__libc_start_main@GLIBC_2.2.5>
  40059e:	f4                   	hlt    

000000000040059f <.annobin_init.c>:
  40059f:	90                   	nop

00000000004005a0 <_dl_relocate_static_pie>:
  4005a0:	f3 0f 1e fa          	endbr64 
  4005a4:	c3                   	retq   

00000000004005a5 <.annobin__dl_relocate_static_pie.end>:
  4005a5:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4005ac:	00 00 00 
  4005af:	90                   	nop

00000000004005b0 <deregister_tm_clones>:
  4005b0:	48 8d 3d 71 0a 20 00 	lea    0x200a71(%rip),%rdi        # 601028 <__TMC_END__>
  4005b7:	48 8d 05 6a 0a 20 00 	lea    0x200a6a(%rip),%rax        # 601028 <__TMC_END__>
  4005be:	48 39 f8             	cmp    %rdi,%rax
  4005c1:	74 15                	je     4005d8 <deregister_tm_clones+0x28>
  4005c3:	48 8b 05 16 0a 20 00 	mov    0x200a16(%rip),%rax        # 600fe0 <_ITM_deregisterTMCloneTable@Base>
  4005ca:	48 85 c0             	test   %rax,%rax
  4005cd:	74 09                	je     4005d8 <deregister_tm_clones+0x28>
  4005cf:	ff e0                	jmpq   *%rax
  4005d1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4005d8:	c3                   	retq   
  4005d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004005e0 <register_tm_clones>:
  4005e0:	48 8d 3d 41 0a 20 00 	lea    0x200a41(%rip),%rdi        # 601028 <__TMC_END__>
  4005e7:	48 8d 35 3a 0a 20 00 	lea    0x200a3a(%rip),%rsi        # 601028 <__TMC_END__>
  4005ee:	48 29 fe             	sub    %rdi,%rsi
  4005f1:	48 c1 fe 03          	sar    $0x3,%rsi
  4005f5:	48 89 f0             	mov    %rsi,%rax
  4005f8:	48 c1 e8 3f          	shr    $0x3f,%rax
  4005fc:	48 01 c6             	add    %rax,%rsi
  4005ff:	48 d1 fe             	sar    %rsi
  400602:	74 14                	je     400618 <register_tm_clones+0x38>
  400604:	48 8b 05 ed 09 20 00 	mov    0x2009ed(%rip),%rax        # 600ff8 <_ITM_registerTMCloneTable@Base>
  40060b:	48 85 c0             	test   %rax,%rax
  40060e:	74 08                	je     400618 <register_tm_clones+0x38>
  400610:	ff e0                	jmpq   *%rax
  400612:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400618:	c3                   	retq   
  400619:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400620 <__do_global_dtors_aux>:
  400620:	f3 0f 1e fa          	endbr64 
  400624:	80 3d f9 09 20 00 00 	cmpb   $0x0,0x2009f9(%rip)        # 601024 <_edata>
  40062b:	75 13                	jne    400640 <__do_global_dtors_aux+0x20>
  40062d:	55                   	push   %rbp
  40062e:	48 89 e5             	mov    %rsp,%rbp
  400631:	e8 7a ff ff ff       	callq  4005b0 <deregister_tm_clones>
  400636:	c6 05 e7 09 20 00 01 	movb   $0x1,0x2009e7(%rip)        # 601024 <_edata>
  40063d:	5d                   	pop    %rbp
  40063e:	c3                   	retq   
  40063f:	90                   	nop
  400640:	c3                   	retq   
  400641:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
  400648:	00 00 00 00 
  40064c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400650 <frame_dummy>:
  400650:	f3 0f 1e fa          	endbr64 
  400654:	eb 8a                	jmp    4005e0 <register_tm_clones>
  400656:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40065d:	00 00 00 

0000000000400660 <__libc_csu_init>:
  400660:	f3 0f 1e fa          	endbr64 
  400664:	41 57                	push   %r15
  400666:	49 89 d7             	mov    %rdx,%r15
  400669:	41 56                	push   %r14
  40066b:	49 89 f6             	mov    %rsi,%r14
  40066e:	41 55                	push   %r13
  400670:	41 89 fd             	mov    %edi,%r13d
  400673:	41 54                	push   %r12
  400675:	4c 8d 25 84 07 20 00 	lea    0x200784(%rip),%r12        # 600e00 <__frame_dummy_init_array_entry>
  40067c:	55                   	push   %rbp
  40067d:	48 8d 2d 84 07 20 00 	lea    0x200784(%rip),%rbp        # 600e08 <__init_array_end>
  400684:	53                   	push   %rbx
  400685:	4c 29 e5             	sub    %r12,%rbp
  400688:	48 83 ec 08          	sub    $0x8,%rsp
  40068c:	e8 d7 fd ff ff       	callq  400468 <_init>
  400691:	48 c1 fd 03          	sar    $0x3,%rbp
  400695:	74 1f                	je     4006b6 <__libc_csu_init+0x56>
  400697:	31 db                	xor    %ebx,%ebx
  400699:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4006a0:	4c 89 fa             	mov    %r15,%rdx
  4006a3:	4c 89 f6             	mov    %r14,%rsi
  4006a6:	44 89 ef             	mov    %r13d,%edi
  4006a9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006ad:	48 83 c3 01          	add    $0x1,%rbx
  4006b1:	48 39 dd             	cmp    %rbx,%rbp
  4006b4:	75 ea                	jne    4006a0 <__libc_csu_init+0x40>
  4006b6:	48 83 c4 08          	add    $0x8,%rsp
  4006ba:	5b                   	pop    %rbx
  4006bb:	5d                   	pop    %rbp
  4006bc:	41 5c                	pop    %r12
  4006be:	41 5d                	pop    %r13
  4006c0:	41 5e                	pop    %r14
  4006c2:	41 5f                	pop    %r15
  4006c4:	c3                   	retq   

00000000004006c5 <.annobin___libc_csu_fini.start>:
  4006c5:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
  4006cc:	00 00 00 00 

00000000004006d0 <__libc_csu_fini>:
  4006d0:	f3 0f 1e fa          	endbr64 
  4006d4:	c3                   	retq   

Disassembly of section .fini:

00000000004006d8 <_fini>:
  4006d8:	f3 0f 1e fa          	endbr64 
  4006dc:	48 83 ec 08          	sub    $0x8,%rsp
  4006e0:	48 83 c4 08          	add    $0x8,%rsp
  4006e4:	c3                   	retq   
