    lw    1,0,six
    lw    2,1,two
    addi  3,1,4
    beq   2,3,end
    addi  2,2,1
    j     loop
end       halt
six       .fill  6
two       .fill  2
six       .fill  8  #second use of label six