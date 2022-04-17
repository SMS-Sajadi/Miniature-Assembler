        lw   1,0,two #undeclared label
        lw   2,1,ten
        add  3,1,2
        addi 3,3,-10
loop    beq  3,0,end
        slti 4,3,0
        addi 3,3,1
        j    loop
end     halt
ten     .fill  10