#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

// Namespace containing functions used to check that calculations are being done correctly
// R. Sheehan 2 - 5 - 2018

namespace testing {
	
	void slab_wg_neff_calc(); 

	void fl_slab_wg_neff_calc(); 

	void fl_slab_wg_mode_calc(); 

	void eim_rect_wg(); 

	void eim_wire_wg();

	void eim_rib_wg();

	void eim_ridge_wg(); 

	void eim_arb_wg(); 

	void eim_calc_with_materials(double WL);

	void disp_curve_wire(); 

	void disp_curve_rib();

	void copy_constructor_test(); 

	void material_RI_curve_test(); 
}

#endif
