#!/bin/bash

# make cmd.cpp
echo -n "    " > cmd.txt
for filename in $( ls . | grep .cpp$ ); do
    echo -n "${filename%.cpp} " >> cmd.txt
done
echo "" >> cmd.txt
mv cmd.txt cmd.cpp

# make cpp.snip
rm cpp.snip
for filename in $( ls . | grep .cpp$ ); do
    echo "snippet       ${filename%.cpp}" >> cpp.snip
    echo "#{{{" >> cpp.snip
    #echo "options       head" >> cpp.snip
    cat ${filename} >> cpp.snip
    echo -e "#}}}\n" >> cpp.snip
done

mv cpp.snip $HOME/.vim/snippets
