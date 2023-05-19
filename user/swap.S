# Context swap
#
#   void swap(struct greg_t *old, struct greg_t *new);
# 
# Save current registers in old. Load from new.	
# Change Return Address


.globl swap
swap:

        sd ra, 0(a0)
        sd sp, 8(a0)
        sd a0, 16(a0)
        sd a1, 24(a0)
        sd a2, 32(a0)
        sd s0, 40(a0)
        sd s1, 48(a0)
        sd s2, 56(a0)
        sd s3, 64(a0)
        sd s4, 72(a0)
        sd s5, 80(a0)
        sd s6, 88(a0)
        sd s7, 96(a0)
        sd s8, 104(a0)
        sd s9, 112(a0)
        sd s10, 120(a0)
        sd s11, 128(a0)

       ld ra, 0(a1)
        ld sp, 8(a1)
        ld a0, 16(a1)
        ld a1, 24(a1)
        ld a2, 32(a1)
        ld s0, 40(a1)
        ld s1, 48(a1)
        ld s2, 56(a1)
        ld s3, 64(a1)
        ld s4, 72(a1)
        ld s5, 80(a1)
        ld s6, 88(a1)
        ld s7, 96(a1)
        ld s8, 104(a1)
        ld s9, 112(a1)
        ld s10, 120(a1)
        ld s11, 128(a1)

#       move a0, t0
#  