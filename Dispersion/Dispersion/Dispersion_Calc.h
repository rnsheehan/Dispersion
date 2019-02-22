#ifndef DISPERSION_CALC_H
#define DISPERSION_CALC_H

// Declaration of the dispersion calculation object
// The aim is to compute the effective index and group index versus wavelength curves for a 
// given waveguide structure. Data is waveguide geometry and material dependent
// R. Sheehan 22 - 2 - 2019

// Update the EIM code to include virtual functions for reducing a wg and assigning parameters
// That way you can make EIM object part of the dispersion class as a pointer to an object derived from EIM
// It will make the coding much easier and obviate the need to have derived classes for the dispersion class
// R. Sheehan 22 - 2 - 2019

class dispersion {
public:
	dispersion(); 

	dispersion(double wl_start, double wl_finish, double wl_step, material *Ncore, material *Nsub, material *Nclad);

	~dispersion(); 

	void set_params(double wl_start, double wl_finish, double wl_step, material *Ncore, material *Nsub, material *Nclad);

	void compute_dispersion_data();

protected:
	bool params_defined; 

	int wl_N; // number of wl steps required for calculation

	double wl_low; // lower bound on wavelength range, units of um
	double wl_high; // upper bound on wavelength range, units of um 
	double wl_delta; // wavelength step-size, units of um

	material *core; // object for the core material
	material *substrate; // object for the substrate material
	material *cladding; // object for the cladding material

	std::vector<double> wl_vals; 
	std::vector<double> neff_vals; 
	std::vector<double> ng_vals; 
};

#endif
