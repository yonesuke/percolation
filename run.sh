n_iter=1000
folder="data"
for L in {32,64,128,256}; do
    ./run 0 $L $n_iter > ${folder}/theta$L.txt
    ./run 1 $L $n_iter > ${folder}/chi$L.txt
    ./run 2 $L $n_iter > ${folder}/chif$L.txt
done