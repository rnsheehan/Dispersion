#ifndef ATTACH_H
#include "Attach.h"
#endif

dispersion::dispersion()
{
	// Default Constructor
	params_defined = false;

	wl_N = 0; 

	wl_low = wl_high = wl_delta = 0.0; 

	core = nullptr; substrate = nullptr; cladding = nullptr; 
}

dispersion::dispersion(double wl_start, double wl_finish, double wl_step, material *Ncore, material *Nsub, material *Nclad)
{
	set_params(wl_start, wl_finish, wl_step, Ncore, Nsub, Nclad);
}

dispersion::~dispersion()
{
	// Deconstructor

	params_defined = false; 

	wl_vals.clear(); neff_vals.clear();	ng_vals.clear();
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

		if (c10) {
			wl_low = wl_start; 
			wl_high = wl_finish; 
			wl_delta = wl_step; 

			wl_N = static_cast<int>(1.0 + ( (wl_high - wl_low) / wl_delta) ); 

			core = Ncore; 
			substrate = Nsub; 
			cladding = Nclad; 

			wl_vals.clear(); 
			neff_vals.clear(); 
			ng_vals.clear(); 

			params_defined = true; 
		}
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

void dispersion::compute_dispersion_data()
{
	// Compute the dispersion data based on the defined inputs

	try {
		if (params_defined) {
			// Compute dispersion curves here
			
		}
		else {
			std::string reason;
			reason = "Error: void dispersion::compute_dispersion_data()\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}