for i in {1..10}; do commandNameHere; done


echo "bitonic Normal"
gcc -o bitonic.out bitonicSort.c 
./bitonic.out

echo "bitonic OMP"
export OMP_NUM_THREADS=4
gcc -o ompBitonic.out ompBitonicSort.c -fopenmp 
./ompBitonic.out

echo "merge Normal"
gcc -o merge.out mergeSort.c
./merge.out

echo "merge MPI"
mpicc mpiMergeSort.c -o mpiMerge.out
mpirun -np 4 mpiMerge.out 1024
