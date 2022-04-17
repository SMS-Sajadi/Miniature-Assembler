addr     .fill  45
nouse    .fill  12756
    add  2,1,0
    sw   2,0,addr
    slti 3,2,-3 #testing neg imm
    addi 4,0,1
loop    beq  3,4,done
    addi 3,3,-1
    j    loop
done     halt