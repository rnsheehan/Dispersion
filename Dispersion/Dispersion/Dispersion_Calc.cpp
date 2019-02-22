#ifndef ATTACH_H
#include "Attach.h"
#endif

dispersion::dispersion()
{
	// Default Constructor
	wl_low = wl_high = wl_delta = 0.0; 

	core = nullptr; substrate = nullptr; cladding = nullptr; 
}

dispersion::dispersion(double wl_start, double wl_finish, double wl_step, material *Ncore, material *Nsub, material *Nclad)
{
	set_params(wl_start, wl_finish, wl_step, Ncore, Nsub, Nclad);
}

void dispersion::set_params(double wl_start, double wl_finish, double wl_step, material *Ncore, material *Nsub, material *Nclad)
{
	// Assign the values to the object parameters
	try {
		bool c1 = wl_start > 0.0 ? true : false; 
		bool c2 = wl_finish > wl_start ? true : false; 
		bool c3 = wl_step < wl_finish - wl_start ? true : false; 
		bool c4 = Ncore != nullptr ? true : false; 
		bool c5 = Nsub != nullptr ? true : false; 
		bool c6 = Nclad != nullptr ? true : false; 
		bool c10 = c1 && c2 && c3 && c4 && c5 && c6; 

		if (c10) {}
		else {
			std::string reason; 
			reason = "Error: void dispersion::set_params(double wl_start, double wl_finish, double wl_step, material *Ncore, material *Nsub, material *Nclad)\n"; 
			if (!c1) reason += "wl_start: " + template_funcs::toString(wl_start, 2) + " is not correct\n"; 
			if (!c2) reason += "wl_finish: " + template_funcs::toString(wl_finish, 2) + " is not correct\n";
			if (!c3) reason += "wl_step: " + template_funcs::toString(wl_step, 2) + " is not correct\n";
			if (!c4) reason += "Ncore has not been correctly assigned"; 
			if (!c5) reason += "Nsub has not been correctly assigned"; 
			if (!c6) reason += "Nclad has not been correctly assigned"; 
			throw std::invalid_argument(reason); 
		}

	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}