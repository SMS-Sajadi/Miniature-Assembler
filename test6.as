        lw      1,0,four
        addi    1,1,4
        lw      2,0,max
        nand    4,1,2
        slt     3,2,1
        addi    5,0,1
        beq     3,5,end
        addi    1,4,-32769 #more than 16bit needed
end     halt
four    .fill   4
two     .fill   2
max     .fill   2147483647 #32bit is needed