cd build
make
./photon ../input.pho ../output.asm
cd ..
spim -file output.asm
