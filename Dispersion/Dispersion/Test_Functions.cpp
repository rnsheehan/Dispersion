#ifndef ATTACH_H
#include "Attach.h"
#endif

void testing::slab_wg_neff_calc()
{
	// Run a three layer slab waveguide neff calculation and check the results
	// R. Sheehan 2 - 5 - 2018

	double W = 1.5; 
	double WL = 1.55; 
	double Nc = 3.38; 
	double Ns = 3.17; 
	double Ncl = 1.0; 

	slab_tl_neff sl_obj; 

	sl_obj.set_params(W, WL, Nc, Ns, Ncl); 

	sl_obj.neff_search(TE); 

	std::cout << "Complete\n"; 
}

void testing::fl_slab_wg_neff_calc()
{
	// Compute the effective index in a four layer slab waveguide
	// R. Sheehan 5 - 10 - 2018

	double W, Wr, WL, Nc, Ns, Nr, Ncl; 

	// Case B: Field Oscillating in Core Only
	// For there to be a solution one has to have ncl < nm < nc, where nm = Max(nr,ns)
	//W = 0.5; Wr = 0.5; WL = 1.55; // n_{TM} = 3.274464
	//W = 0.5; Wr = 1.0; WL = 1.55; // n_{TM} = 3.27562
	//W = 0.6; Wr = 0.4; WL = 1.55; // n_{TM} = 3.29152
	W = 0.6; Wr = 0.9; WL = 1.55; // n_{TM} = 3.293
	Ns = 3.17; Nc = 3.38; Nr = 3.17; Ncl = 1.0;

	slab_fl_neff_B fl_obj;

	fl_obj.set_params(W, Wr, WL, Nc, Ns, Ncl, Nr); 

	fl_obj.neff_search(TE); 
}

void testing::fl_slab_wg_mode_calc()
{
	// Compute the mode profile in a four layer slab waveguide
	// R. Sheehan 20 - 2 - 2019

	double W, Wr, WL, Nc, Ns, Nr, Ncl;

	// Case B: Field Oscillating in Core Only
	// For there to be a solution one has to have ncl < nm < nc, where nm = Max(nr,ns)
	W = 0.5; Wr = 0.5; WL = 1.55; // n_{TM} = 3.274464
	//W = 0.5; Wr = 1.0; WL = 1.55; // n_{TM} = 3.27562
	//W = 0.6; Wr = 0.4; WL = 1.55; // n_{TM} = 3.29152
	//W = 0.6; Wr = 0.9; WL = 1.55; // n_{TM} = 3.293
	Ns = 3.17; Nc = 3.38; Nr = 3.17; Ncl = 1.0;
}

void testing::eim_rect_wg()
{
	// Approximate the effective index of a rectangular waveguide using EIM
	// R. Sheehan 20 - 2 - 2019

	// Confirmed from online simulator that method is accurate to within 1e-3
	// Seems to be more accurate when computing TE modes (starting from TM)
	// R. Sheehan 20 - 2 - 2019

	bool polarisation = TE; 
	double WL, W, H, nc, ncl; 

	WL = 1.55; 
	W = 2; H = 1; 
	nc = 3.38; ncl = 3.17; 

	wg_dims dim; 

	dim.set_rect_wire(W, H); 

	ri_vals ri; 

	ri.set_rect(nc, ncl, WL); 

	Rectangular wguide; 

	//wguide.set_params(polarisation, W, H, nc, ncl, WL);

	wguide.set_params(polarisation, dim, ri); 

	wguide.reduce_wg(); 

	wguide.get_index(true); 
}

void testing::eim_wire_wg()
{
	// Approximate the effective index of a wire waveguide using EIM
	// R. Sheehan 20 - 2 - 2019

	// Confirmed from online simulator that method is accurate to within 1e-3
	// Seems to be more accurate when computing TE modes (starting from TM)
	// When dealing with wire waveguides the TE mode (starting from TM) approximates 
	// the TM mode of the online simulator and vice versa
	// There must be a relationship between accuracy of EIM and index contrast
	// R. Sheehan 20 - 2 - 2019

	bool polarisation = TE;
	double WL, W, H, nc, ns, ncl;

	WL = 1.55;
	//W = 1; H = 0.5;
	//nc = 2.45; ns = 1.45; ncl = 1.0;
	// Si Wire has one TE mode with neff = 2.124
	// EIM starting with TE gives neff = 2.332 when ni is averaged over ns and ncl
	// EIM starting with TE gives neff = 2.294 when ni is ncl
	// EIM starting with TM gives neff = 1.625 when ni is averaged over ns and ncl
	// EIM starting with TM gives neff = 1.594 when ni is ncl
	/*W = 0.45; H = 0.22; 
	nc = 3.45; ns = 1.45; ncl = 1.0;*/

	WL = 1.55; 
	W = 1.0; H = 0.3;
	nc = 2.00704; ns = 1.44428; ncl = 1.0;

	wg_dims dim;

	dim.set_rect_wire(W, H);

	ri_vals ri;

	ri.set_rib_wire(nc, ns, ncl, WL);

	Wire wguide;

	//wguide.set_params(polarisation, W, H, nc, ns, ncl, WL);

	wguide.set_params(TE, dim, ri); 

	wguide.reduce_wg();

	wguide.get_index(true);

	wguide.set_params(TM, dim, ri);

	wguide.reduce_wg();

	wguide.get_index(true);
}

void testing::eim_rib_wg()
{
	// Estimate the effective index of a rib waveguide
	// R. Sheehan 21 - 2 - 2019

	bool polarisation = TM; 

	double W, E, T, ncore, nsub, nclad, WL; 

	//W = 1.5; E = 0.3; T = 0.45; WL = 1.55; // neff = 3.265 for TM -> TE, neff = 3.269 for TE calc online
	//ncore = 3.38; nsub = 3.17; nclad = 1.0; // neff = 3.281 for TE -> TM, neff = 3.257 for TM calc online

	W = 2.0; E = 0.5; T = 0.5; WL = 1.55; // neff = 3.265 for TM -> TE, neff = 3.269 for TE calc online
	ncore = 3.38; nsub = 3.17; nclad = 1.0; // neff = 3.281 for TE -> TM, neff = 3.257 for TM calc online

	wg_dims dim;

	dim.set_rib(W, E, T);

	ri_vals ri;

	ri.set_rib_wire(ncore, nsub, nclad, WL);

	Rib wguide; 

	//wguide.set_params(polarisation, W, E, T, ncore, nsub, nclad, WL); 
	wguide.set_params(polarisation, dim, ri); 

	wguide.reduce_wg(); 

	wguide.get_index(true); 
}

void testing::eim_ridge_wg()
{
	// Estimate the effective index of a ridge waveguide
	// R. Sheehan 21 - 2 - 2019

	bool polarisation = TM;

	double W, E, T, D, ncore, nsub, nrib, nclad, WL;

	W = 2.0; D = 0.6; E = 0.5; T = 0.4; WL = 1.55; // neff = 3.292 for TM -> TE, neff = 3.295 for TE calc online
	ncore = 3.38; nsub = nrib = 3.17; nclad = 1.0; 

	wg_dims dim;

	dim.set_ridge(W, E, T, D);

	ri_vals ri;

	ri.set_ridge(ncore, nsub, nrib, nclad, WL);

	Shallow_Ridge wguide;

	wguide.set_params(polarisation, dim, ri);

	wguide.reduce_wg();

	wguide.get_index(true);
}

void testing::eim_arb_wg()
{
	// Perform an EIM calculation using the EIM base class
	// R. Sheehan 28 - 2 - 2019

	bool polarisation = TM;

	double W, E, T, ncore, nsub, nclad, WL;

	W = 1.5; E = 0.3; T = 0.45; WL = 1.55; // neff = 3.265 for TM -> TE, neff = 3.269 for TE calc online
	ncore = 3.38; nsub = 3.17; nclad = 1.0; // neff = 3.281 for TE -> TM, neff = 3.257 for TM calc online

	//W = 2.0; E = 0.5; T = 0.5; WL = 1.55; // neff = 3.265 for TM -> TE, neff = 3.269 for TE calc online
	//ncore = 3.38; nsub = 3.17; nclad = 1.0; // neff = 3.281 for TE -> TM, neff = 3.257 for TM calc online

	wg_dims dim;

	dim.set_rib(W, E, T);

	ri_vals ri;

	ri.set_rib_wire(ncore, nsub, nclad, WL);

	Rib wguide; 

	EIM *compute = &wguide; 

	compute->set_params(polarisation, dim, ri); 

	compute->reduce_wg(); 

	compute->get_index(true); 
}

void testing::eim_calc_with_materials(double WL)
{
	// Test the EIM calculation with the material object
	// R. Sheehan 1 - 3 - 2019

	bool polarisation = TM;

	double W, E, T, ncore, nsub, nclad, asfrac;

	W = 1.5; E = 0.3; T = 0.45; // neff = 3.265 for TM -> TE, neff = 3.269 for TE calc online
	ncore = 3.38; nsub = 3.17; nclad = 1.0; // neff = 3.281 for TE -> TM, neff = 3.257 for TM calc online

	W = 0.3; 

	Air cladding;
	//InP substrate; 
	//InGaAsP core; 
	SiO2 substrate; 
	SiN core; 

	cladding.set_wavelength(WL); substrate.set_wavelength(WL); core.set_wavelength(WL); 

	asfrac = 0.6; 
	ncore = core.refractive_index(); 
	nsub = substrate.refractive_index(); 
	nclad = cladding.refractive_index(); 

	std::cout << "Refractive Index Values\n";
	std::cout << "ncore: " << ncore << "\n"; 
	std::cout << "nsub: " << nsub << "\n";
	std::cout << "nclad: " << nclad << "\n\n";

	wg_dims dim;

	dim.set_rib(W, E, T);

	ri_vals ri;

	ri.set_rib_wire(ncore, nsub, nclad, WL);

	Rib wguide;

	EIM *compute = &wguide;

	compute->set_params(polarisation, dim, ri);

	compute->reduce_wg();

	compute->get_index(true);
}

void testing::copy_constructor_test()
{
	// What's the best way to implement a copy constructor?
	// Can you use the this operator to assign all the values?
	// Or do you have to assign each element individually

	wg_dims Dims;

	Dims.set_ridge(1.5, 0.5, 0.3, 0.45); 

	wg_dims alt_dims(Dims); 

	std::cout << "\n";
}

void testing::disp_curve_wire()
{
	// Compute the dispersion curve for a wire waveguide object
	// R. Sheehan 7 - 3 - 2019

	bool pol = TE; 

	int n_pts; 
	double start, stop, W, H; 

	sweep WL; 
	wg_dims wire_dims; 

	Air ri_air; 
	SiN ri_si; 
	SiO2 ri_sio2; 

	n_pts = 50; start = 1.5; stop = 1.6; 
	WL.set_vals(n_pts, start, stop); 

	W = 1.0; H = 0.3;    

	wire_dims.set_rect_wire(W, H); 

	wire_dispersion disp_calc; 

	std::string filename; 

	std::string pol_str = pol == TE ? "_TE" : "_TM"; 

	filename = "Wire_WG_Dispersion_W_" + template_funcs::toString(W, 2) + "_H_" + template_funcs::toString(H, 2) + pol_str + dottxt;

	disp_calc.compute_dispersion_data(pol, WL, wire_dims, &ri_si, &ri_sio2, &ri_air, filename); 
}

void testing::disp_curve_rib()
{
	// Compute the dispersion curve for a rib waveguide object
	// R. Sheehan 8 - 3 - 2019

	bool pol = TM;

	int n_pts;
	double start, stop, W, E, T;

	sweep WL;
	wg_dims rib_dims;

	Air ri_air;
	Si ri_si;
	SiO2 ri_sio2;

	n_pts = 50; start = 1.4; stop = 1.6;
	WL.set_vals(n_pts, start, stop);

	W = 1; E = 0.5; T = 0.3; 
	rib_dims.set_rib(W, E, T); 

	rib_dispersion disp_calc;

	std::string filename = "Rib_WG_Dispersion.txt"; 

	disp_calc.compute_dispersion_data(pol, WL, rib_dims, &ri_si, &ri_sio2, &ri_air, filename);
}

void testing::material_RI_curve_test()
{
	// Compute the material RI curves at multiple WL
	// R. Sheehan 15 - 4 - 2019

	int n_pts;
	double start, stop, lambda; 

	sweep WL;

	Air ri_air;
	Si ri_si;
	SiO2 ri_sio2;
	SiN ri_sin; 

	n_pts = 50; start = 1.5; stop = 1.6;
	WL.set_vals(n_pts, start, stop);

	std::ofstream write("RI_Values.txt", std::ios_base::out, std::ios_base::trunc);

	for (int i = 0; i < WL.get_Nsteps(); i++) {
		lambda = WL.get_val(i);
		ri_sin.set_wavelength(lambda);
		ri_si.set_wavelength(lambda); 
		ri_sio2.set_wavelength(lambda);

		write << std::setprecision(10) << lambda << " , " << ri_si.refractive_index() << " , " << ri_sio2.refractive_index() << " , " << ri_sin.refractive_index() << "\n";
	}
}