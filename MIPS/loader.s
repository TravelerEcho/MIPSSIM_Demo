#Copyright 2026 TravelerEcho
.text
.globl __start
.type __start, @function
__start:
    .align 0
    b $L0
    .ascii "   "
    .half 512
    .byte 1
    .half 1
    .byte 2
    .half 224
    .half 2880
    .byte 0xf0
    .half 9
    .half 18
    .half 2
    .word 0
    .word 2880
    .byte 0
    .byte 0
    .byte 0x29
    .word 0xffffffff
    .ascii "HELLO-OS   "
    .ascii "FAT12   "
    .space 8
    .align 4
$L0:
    li $sp,0x80FFFFF0
    li $a0,0xA0000000
    li $a1,0xBFC04200
    li $a2,0x0600
    jal memcpy              #load 0xbfc04200 0x0600 to 0x80000000 - 0x800005ff
    li $a0,0xA0000800
    li $a1,0xBFC00000
    li $a2,0x00168000
    jal memcpy              #load 0xbfc00000 0x00168000 to 0x80000800 - 0x801687ff
    li $t0, 0x80005000
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
    lw	$v0,24($s8)
    move	$sp,$s8
    lw	$s8,20($sp)
    addiu	$sp,$sp,24
    jr  $ra
.space 512 - (. - __start)
