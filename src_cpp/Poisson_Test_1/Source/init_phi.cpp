#include "myfunc.H"
#include "mykernel.H"

#include <AMReX_BCRec.H>
#include <AMReX_BCUtil.H>

using namespace amrex;

void actual_init_phi(amrex::Real> const& rh, amrex::Real> const& phi_e, amrex::Real> const&phi_i  amrex::Geometry const& geom)
{
    GpuArray<Real, AMREX_SPACEDIM> dx = geom.CellSizeArray();
    GpuArray<Real, AMREX_SPACEDIM> prob_lo = geom.ProbLoArray();

    for (MFIter mfi(rhs); mfi.isValid(); ++mfi)
    {
	    const Box& bx = mfi.vaidbox();
	    Array4<Real> const rh = rhs.array(mfi);
	    Array4<Real> const phi_e = phi_exact.array(mfi);
	    Arrat4<Real> const phi_i = phi_initial.array(mfi);
	    amrex::ParallelFor(bx, [=] AMREX_GPU_DEVICE(int i, int j)
			    {
			       actual_init_poisson(i, j, rh, phi_e, phi_i, dx, prob_lo);
			    });
      }













///////////////////////////////////////////

    //***for (MFIter mfi(phi_new); mfi.isValid(); ++mfi)
    //{
    //    const Box& vbx = mfi.validbox();
    //    auto const& phiNew = phi_new.array(mfi);
    //    amrex::ParallelFor(vbx, [=] AMREX_GPU_DEVICE(int i, int j, int k)
    //            {
    //                init_phi(i, j, k, phiNew, dx, prob_lo);
    //            });
   // }
///////////////////////////////////////////
}
