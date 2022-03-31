.text
.global trap_vectors
.type trap_vectors, @function
.balign 256

.equ ARCH_BIT,      4

trap_vectors:
    j   undefined_handler   /* user software interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* supervisor software interrupt */
.balign ARCH_BIT     
    j   undefined_handler   /* reserved */
.balign ARCH_BIT
    j   undefined_handler   /* machine software interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* user timer interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* supervisor timer interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* reserved */
.balign ARCH_BIT
    j   timer_handler       /* machine timer interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* user external interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* supervisor external interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* reserved */
.balign ARCH_BIT
    j   undefined_handler   /* machine external interrupt */
.balign ARCH_BIT
    j   undefined_handler   /* reserved */
.balign ARCH_BIT
    j   undefined_handler   /* reserved */
.balign ARCH_BIT
    j   undefined_handler   /* reserved */
.balign ARCH_BIT
    j   undefined_handler   /* reserved */
    .size   trap_vectors, .-trap_vectors


undefined_handler:
    mret

