    Graph ${1:g}(${2:n});
    for (int i = 0; i < $2; i++) {
        int2(tmpx, tmpy);
        ${3: };
       ${4: }tmpx--; tmpy--;
        addEdge($1, tmpx, tmpy$3);
    }
    ${0:#:TARGET}
