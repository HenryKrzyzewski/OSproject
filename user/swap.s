# Context swap
#
#   void swap(struct greg_t *old, struct greg_t *new);
# 
# Save current registers in old. Load from new.	
# Change Return Address


.globl swap
swap:

#       THIS NEEDS FIXED
#       need to change registers

        move a0, t0
        move a1, t1

        sd ra, 0(t0)
        sd sp, 8(t0)
        sd s0, 16(t0)
        sd s1, 24(t0)
        sd s2, 32(t0)
        sd s3, 40(t0)
        sd s4, 48(t0)
        sd s5, 56(t0)
        sd s6, 64(t0)
        sd s7, 72(t0)
        sd s8, 80(t0)
        sd s9, 88(t0)
        sd s10, 96(t0)
        sd s11, 104(t0)

        ld ra, 0(t1)
        ld sp, 8(t1)
        ld s0, 16(t1)
        ld s1, 24(t1)
        ld s2, 32(t1)
        ld s3, 40(t1)
        ld s4, 48(t1)
        ld s5, 56(t1)
        ld s6, 64(t1)
        ld s7, 72(t1)
        ld s8, 80(t1)
        ld s9, 88(t1)
        ld s10, 96(t1)
        ld s11, 104(t1)
        
        ret

	
