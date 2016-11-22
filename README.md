# genom-2
Project in genomics no 2

compile : g++ src/*.cpp -std=c++11 -o x.x
lauch : ./x.x

you have to add to your genom-2 file the DBP_PPM.mat and promoters.fasta files (from moodle)

cd build

cmake ../

make

./Main


The test have been natively deactivated in the Cmakefile, just call make test if you want to build your tests!

Tadaa!
Don't hesitate to contact me if you want to add your test files to cMake, I'll help make sure that all prerogatives are filled. (Taron)
