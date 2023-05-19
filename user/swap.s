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
        sd a0, 16(t0)
        sd a1, 24(t0)
        sd a2, 32(t0)
        sd a3, 40(t0)
        sd a4, 48(t0)
        sd a5, 56(t0)
        sd a6, 64(t0)
        sd a7, 72(t0)
        sd s0, 80(t0)
        sd s1, 88(t0)
        sd s2, 96(t0)
        sd s3, 104(t0)
        sd s4, 112(t0)
        sd s5, 120(t0)
        sd s6, 128(t0)
        sd s7, 136(t0)
        sd s8, 144(t0)
        sd s9, 152(t0)
        sd s10, 160(t0)
        sd s11, 168(t0)

        ld ra, 0(t1)
        ld sp, 8(t1)
        ld a0, 16(t1)
        ld a1, 24(t1)
        ld a2, 32(t1)
        ld a3, 40(t1)
        ld a4, 48(t1)
        ld a5, 56(t1)
        ld a6, 64(t1)
        ld a7, 72(t1)
        ld s0, 80(t1)
        ld s1, 88(t1)
        ld s2, 96(t1)
        ld s3, 104(t1)
        ld s4, 112(t1)
        ld s5, 120(t1)
        ld s6, 128(t1)
        ld s7, 136(t1)
        ld s8, 144(t1)
        ld s9, 152(t1)
        ld s10, 160(t1)
        ld s11, 168(t1)
        
        ret

	
