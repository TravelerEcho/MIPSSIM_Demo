#Copyright 2025 TravelerEcho
.text
.section .text.loader


.global __start
.type __start, @function

__start:
    li $sp,0x80FFFFF0
    li $a0,0xA0000000
    li $a1,0xBFC00200
    li $a2,0xFE00
    jal memcpy
    nop
    la $t0, main
    jr $t0


memcpy:
    addiu	$sp,$sp,-24
    sw	$s8,20($sp)
    move	$s8,$sp
    sw	$a0,24($s8)
    sw	$a1,28($s8)
    sw	$a2,32($s8)
    lw	$v0,24($s8)
    sw	$v0,4($s8)
    lw	$v0,28($s8)
    sw	$v0,8($s8)
    sw	$zero,0($s8)
    b	$L2
    nop
$L1:
    lw	$v1,4($s8)
    lw  $v0,0($s8)
    addu	$v0,$v1,$v0
    lw	$a0,8($s8)
    lw	$v1,0($s8)
    addu	$v1,$a0,$v1
    lbu	$v1,0($v1)
    sb	$v1,0($v0)
    lw	$v0,0($s8)
    addiu	$v0,$v0,1
    sw	$v0,0($s8)
$L2:
    lw	$v1,0($s8)
    lw	$v0,32($s8)
    sltu	$v0,$v1,$v0
    bnez	$v0,$L1
    nop
    lw	$v0,24($s8)
    move	$sp,$s8
    lw	$s8,20($sp)
    addiu	$sp,$sp,24
    jr  $ra
    nop
