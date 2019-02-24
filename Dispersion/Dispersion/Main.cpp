#ifndef ATTACH_H
#include "Attach.h"
#endif

// This is an implementation of a code used to compute the dispersion curves of 2D waveguides
// The EIM is used to approximate the waveguide neff as a function of wavelength
// Testing will focus on the Wire WG and the Rib WG structures
// Output from this code should be neff and ngroup versus wavelength wrt waveguide materials and dimensions
// R. Sheehan 22 - 2 - 2019

int main(int argc, char *argv[])
{
	//testing::slab_wg_mode_calc(); 

	//testing::eim_rect_wg(); 

	//testing::eim_wire_wg(); 

	//testing::eim_rib_wg();

	testing::copy_constructor_test(); 

	std::cout<<"Press enter to close console\n";
	std::cin.get(); 

	return 0; 
}