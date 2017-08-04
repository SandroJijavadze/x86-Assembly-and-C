.global _lfsrasm

_lfsrasm:
push %ebp
mov %esp, %ebp

mov 8(%ebp), %eax
test %eax, %eax  # test
jnz labelone    # if not zero continue to label and use current seed
mov $1520828160, %eax # if zero, use 0x5AA5FF00 as seed

labelone:
mov %eax, %ebx # copy present value to ebx
mov %ebx, %edx # copy the same value to edx

shr $2, %ebx   # shift ebx right twice, therefore placing 30th bit in place of 32th.
xor %ebx, %edx # XOR  ebx and edx , therefore xoring 32th bit with 30th.
shr $4, %ebx   # shift right four times, aligning 26th bit of current SEED in the end.
xor %ebx, %edx # XOR ebx and edx, therefore xoring 26 th bit of current SEED with previous one.
shr $1, %ebx   # Shift right once, aligning 25th bit of in the end.
xor %ebx, %edx  # XOR therefore XOR ing bits 25 and 32.
and $1, %edx   # Clear all the bits except last one.
shr $1, %eax   # Shift the present value of seed, so that we can insert the bit.
shl $31, %edx  # Move calculated bit to end.
or %edx, %eax  # Set bit if corresponding bit is 1 in RAX

// NOTE the enumeration of the taps and bits are according to the wikipedia article that you linked.


mov %ebp, %esp
pop %ebp

ret
.end
