    Graph ${1:g}(${2:n});
    for (int i = 0; i < ${3:n}; i++) {
        int2(tmpx, tmpy);
        ${4: };
       ${5: }tmpx--; tmpy--;
        addEdge($1, tmpx, tmpy$4);
    }
    ${0:#:TARGET}
