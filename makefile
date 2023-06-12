all:
	g++ -g -std=c++14 main.cpp Elec_Mag.cpp Elec_Mag_Block.cpp Experiment.cpp Tensor.cpp Vect.cpp Vect_3d.cpp Vect_3ddir.cpp MagnetProb.cpp -o main

%.exe:
	g++ -g -std=c++14 $*.cpp Elec_Mag.cpp Elec_Mag_Block.cpp Tensor.cpp Vect.cpp Vect_3d.cpp Vect_3ddir.cpp MagnetProb.cpp -o $*
	./$*.exe
	del $*.exe