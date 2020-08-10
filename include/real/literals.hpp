#include <real/real.hpp>

namespace boost{
	namespace real{
		namespace literals{
			/**
			 * Mass of electrong (in atomic mass unit) : 0.000548579909070 atomic mass unit
			 * Reference: 
			 * Mohr, P.J.; Newell, D.B.; Taylor, B.N. 
			 * CODATA recommended values of the fundamental physical constants
			 * 2014.Rev. Mod. Phys.2016,88, 03500
			 **/

			template<typename T>
			const real<T> mass_of_electron = real<T>("0.000548579909067");

			/**
			 * Mass of proton (in atomic mass unit) : 1.007276466583 atomic mass unit
			 * Reference:
			 * F. Heiße, F. Köhler-Langes, S. Rau, J. Hou, S. Junck, A. Kracke, A. Mooser, W. Quint, S. Ulmer, G. Werth, K. Blaum, S. Sturm.
			 * High-Precision Measurement of the Proton’s Atomic Mass. 
			 * Physical Review Letters, 2017; 119 (3) 
			 * DOI: 10.1103/PhysRevLett.119.033001
			 **/

			template<typename T>
			const real<T> mass_of_proton = real<T>("1.007276466583");

			/**
			 * Mass of deuteron (in atomic mass unit) : 2.01355321280 atomic mass unit
			 * Wang, M.; Audi, G.; Kondev, F.G.; Huang, W.J.; Naimi, S.; Xu, X. 
			 * The AME2016 atomic mass evaluation (II)Tables, graphs and references.Chin. 
			 * Phys. C2017,41, 030003
			 **/

			template<typename T>
			const real<T> mass_of_deuteron = real<T>("2.01355321280");

			
			/**
			 * Mass of neutron (in atomic mass unit) : 1.00866491580 atomic mass unit
			 * Wang, M.; Audi, G.; Kondev, F.G.; Huang, W.J.; Naimi, S.; Xu, X. 
			 * The AME2016 atomic mass evaluation (II)Tables, graphs and references.Chin. 
			 * Phys. C2017,41, 030003
			 **/

			template<typename T>
			const real<T> mass_of_neutron = real<T>("1.00866491580");

			/**
			 * Speed of Light (in metres per second) : 299792458 m/s
			 * Source : https://en.wikipedia.org/wiki/Speed_of_light
			 **/

			template<typename T>
			const real<T> speed_of_light = real<T>("299792458", TYPE::INTEGER);

			/**
			 * Planck's Constant : 6.62607015 × 10^−34 J s (Joule Second)
			 * Reference:
			 * Jianwei Huang, Dingsong Wu, Yongqing Cai, Yu Xu, Cong Li, Qiang Gao, Lin Zhao, Guodong Liu, Zuyan Xu, and X. J. Zhou
			 * High precision determination of the Planck constant by modern photoemission spectroscopy 
			 * Review of Scientific Instruments 91, 045116 (2020); https://doi.org/10.1063/1.5129140
			 **/

			template<typename T>
			const real<T> planck_constant = real<T>("6.62607015e-34");



		}
	}
}