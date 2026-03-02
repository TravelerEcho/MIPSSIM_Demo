#Copyright 2026 TravelerEcho
.file	1 "except_asm.s"
.section .text.except_tlbrefill
.globl  except_handler_tlbrefill_link
.set	nomips16
.set	nomicromips
.ent    except_handler_tlbrefill_link
.type   except_handler_tlbrefill_link, @function
except_handler_tlbrefill_link:
.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
.mask	0x40000000,-4
.fmask	0x00000000,0
    nop
.size   except_handler_tlbrefill_link,.-except_handler_tlbrefill_link
.end    except_handler_tlbrefill_link

.section .text.except_others
.globl  except_handler_others_link
.set	nomips16
.set	nomicromips
.ent    except_handler_others_link
.type   except_handler_others_link, @function
except_handler_others_link:
.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
.mask	0x40000000,-4
.fmask	0x00000000,0
    addiu   $sp, $sp, -128
    sw      $ra, 124($sp)
    sw      $v0, 116($sp)
    sw      $v1, 112($sp)
    sw      $a0, 108($sp)
    sw      $a1, 104($sp)
    sw      $a2, 100($sp)
    sw      $a3, 96($sp)
    sw      $t0, 92($sp)
    sw      $t1, 88($sp)
    sw      $t2, 84($sp)
    sw      $t3, 80($sp)
    sw      $t4, 76($sp)
    sw      $t5, 72($sp)
    sw      $t6, 68($sp)
    sw      $t7, 64($sp)
    sw      $s0, 60($sp)
    sw      $s1, 56($sp)
    sw      $s2, 52($sp)
    sw      $s3, 48($sp)
    sw      $s4, 44($sp)
    sw      $s5, 40($sp)
    sw      $s6, 36($sp)
    sw      $s7, 32($sp)
    sw      $t8, 28($sp)
    sw      $t9, 24($sp)
    mfc0    $a0, $12
    mfc0    $a1, $13
    mfc0    $a2, $14
    jal     except_handler_others
    #Resume
    lw      $ra, 124($sp)
    lw      $v0, 116($sp)
    lw      $v1, 112($sp)
    lw      $a0, 108($sp)
    lw      $a1, 104($sp)
    lw      $a2, 100($sp)
    lw      $a3, 96($sp)
    lw      $t0, 92($sp)
    lw      $t1, 88($sp)
    lw      $t2, 84($sp)
    lw      $t3, 80($sp)
    lw      $t4, 76($sp)
    lw      $t5, 72($sp)
    lw      $t6, 68($sp)
    lw      $t7, 64($sp)
    lw      $s0, 60($sp)
    lw      $s1, 56($sp)
    lw      $s2, 52($sp)
    lw      $s3, 48($sp)
    lw      $s4, 44($sp)
    lw      $s5, 40($sp)
    lw      $s6, 36($sp)
    lw      $s7, 32($sp)
    lw      $t8, 28($sp)
    lw      $t9, 24($sp)
    addiu   $sp, $sp, 128
    ERET
.size   except_handler_others_link,.-except_handler_others_link
.end    except_handler_others_link
