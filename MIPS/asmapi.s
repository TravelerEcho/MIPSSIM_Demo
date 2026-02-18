#Copyright 2025 TravelerEcho
.text
.section .text.krnlapi

.global krnl_irq_enable
.type krnl_irq_enable,@function

krnl_irq_enable:
    MFC0 $t0,$12
    li $t1,1
    or $t0,$t0,$t1
    MTC0 $t0,$12
    jr $ra

.global krnl_irq_disable
.type krnl_irq_disable,@function

krnl_irq_disable:
    MFC0 $t0,$12
    li $t1,0xFFFE
    and $t0,$t0,$t1
    MTC0 $t0,$12
    jr $ra
