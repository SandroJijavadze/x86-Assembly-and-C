Date: 05/03/2017    dd/mm/yyyy</br>
<b>Generates pseudo random numbers using XORshift.</b></br>
The taps used are: 32 30 26 and 26 (taps are bit numbers that get XOR ed).</br>
https://upload.wikimedia.org/wikipedia/commons/2/28/LFSR-F16.svg    <b>This picture shows 16 bit implementation, but code uses 32 bit unsigned long.</b></br>
</br>
<b>Function for generation is implemented in both, C and X86 Assembly, you can cally any of then..</b>

These taps have maximum pseudorandom sequence of 4294967296 bits long or 4294967296/32 = 134217728 pseudorandom 32 bit numbers in total.</br>



