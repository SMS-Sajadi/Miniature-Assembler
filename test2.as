    add  1,2,3
    addi 2,0,32677
    sub  2,2,1
    lw   23,4,12 #testing register error
    slt  12,7,3
    j    done
done      halt
first    .fill 45
sec      .fill 212
last     .fill -67