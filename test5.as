one     .fill   1
neg1    .fill   -1
neg2    .fill   -2
        lw      1,0,one
        lw      2,0,neg1
        sub     3,1,2
loop    beq     3,0,done
        subi    3,3,-1 #unknown instruction
        j       loop
done    halt