#ifndef ATTACH_H
#include "Attach.h"
#endif

dispersion::dispersion()
{
	// Default Constructor
	params_defined = false;

	core = nullptr; substrate = nullptr; cladding = nullptr; 
}

dispersion::dispersion(sweep &swp_obj, material *Ncore, material *Nsub, material *Nclad)
{
	set_params(swp_obj, Ncore, Nsub, Nclad);
}

dispersion::~dispersion()
{
	// Deconstructor

	params_defined = false; 

	wl_vals.clear(); neff_vals.clear();	ng_vals.clear();
}

void dispersion::set_params(sweep &swp_obj, material *Ncore, material *Nsub, material *Nclad)
{
	// Assign the values to the object parameters
	try {
		bool c1 = swp_obj.defined();
		bool c4 = Ncore != nullptr ? true : false; 
		bool c5 = Nsub != nullptr ? true : false; 
		bool c6 = Nclad != nullptr ? true : false; 
		bool c10 = c1 && c4 && c5 && c6; 

		if (c10) {

			wavelength.set_vals(swp_obj); // assign the values for the wavelength parameter space

			// assign the material objects
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
			if (!c1) reason += "swp_obj is not correct\n"; 
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

// Defintion of the wire eaveguide dispersion calculation
wire_dispersion::wire_dispersion()
{
	// Default constructor
}

void wire_dispersion::compute_dispersion_data(sweep &swp_obj, wg_dims &dim_obj, material *Ncore, material *Nsub, material *Nclad)
{
	// Compute the dispersion data based on the defined inputs

	try {
		if (dim_obj.params_set()) {
			// Compute dispersion curves here
			
			set_params(swp_obj, Ncore, Nsub, Nclad);


		}
		else {
			std::string reason;
			reason = "Error: void wire_dispersion::compute_dispersion_data()\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}

// Definition of the rib waveguide dispersion calculation

rib_dispersion::rib_dispersion()
{
	
}

void rib_dispersion::compute_dispersion_data(sweep &swp_obj, wg_dims &dim_obj, material *Ncore, material *Nsub, material *Nclad)
{
	// Compute the dispersion data based on the defined inputs

	try {
		if (params_defined) {
			// Compute dispersion curves here

		}
		else {
			std::string reason;
			reason = "Error: void rib_dispersion::compute_dispersion_data()\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}