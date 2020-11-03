all:
	g++ -g main.cpp Elec_Mag.cpp Elec_Mag_Block.cpp Experiment.cpp Tensor.cpp Vect.cpp Vect_3d.cpp Vect_3ddir.cpp MagnetProb.cpp -o main

%.exe:
	g++ -g $*.cpp Elec_Mag.cpp Elec_Mag_Block.cpp Tensor.cpp Vect.cpp Vect_3d.cpp Vect_3ddir.cpp MagnetProb.cpp -o $*
	./$*.exe
	rm -rf $*.exe