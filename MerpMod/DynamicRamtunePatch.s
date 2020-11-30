!!
!!  This program is free software: you can redistribute it and/or modify
!!  it under the terms of the GNU General Public License as published by
!!  the Free Software Foundation, either version 3 of the License, or
!!  (at your option) any later version.
!!
!!  This program is distributed in the hope that it will be useful,
!!  but WITHOUT ANY WARRANTY; without even the implied warranty of
!!  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!!  GNU General Public License for more details.

.section Pull2DFloatRamInjectStart,"ax"

!! TODO: verify function is the same across ECUs and can be blindly patched...
_Pull2DFloatPatch:
    fmov    fr4, fr0
    
    mov.l   Pull2DFloatDynRamHook, r2
    jsr     @r2
    mov     r0, r6 !! use r6 to store X index

    mova    @(0x20,pc), r0
    mov.l   @(r0,r3), r2 !! Previous subroutine stores table datatype into r3
    jsr     @r2
    mov     r6, r0 !! recall X index before jumping to datatype-specific subroutine

    tst     r3, r3
    bt/s    _exit
    fmov    fr2, fr1

    add     #0xC, r4
    fmov.s  @r4+, fr0
    fmov.s  @r4, fr1
    fmac    fr0, fr2, fr1

_exit:
    lds.l   @r15+, pr
    rts
    fmov    fr1, fr0

Pull2DFloatDynRamHook:
    .long _Pull2DFloatDynRamHook !!this must line up exactly before the address at the injection end
