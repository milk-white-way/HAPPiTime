#ifndef AMREX_POISSON_H_
#define AMREX_POISSON_H_
#include <AMReX_Config.H>

#if (AMREX_SPACEDIM == 2)
namespace amrex {
#endif

AMREX_GPU_DEVICE AMREX_FORCE_INLINE
void compute_flux_x (int i, int j,
                     amrex::Array4<amrex::Real> const& fluxx,
                     amrex::Array4<amrex::Real const> const& phi, amrex::Real dxinv,
                     int lo, int hi, int dom_lo, int dom_hi, int bc_lo, int bc_hi)
{
    if (lo == dom_lo &&
        (bc_lo == BCType::foextrap ||
         bc_lo == BCType::ext_dir))
    {
        if(i == lo)
        {
            fluxx(i,j,0) = (phi(i,j,0)-phi(i-1,j,0)) * dxinv / 0.5;
        }
        else
        {
            fluxx(i,j,0) = (phi(i,j,0)-phi(i-1,j,0)) * dxinv;
        }
    }
    else if (hi == dom_hi &&
             (bc_hi == BCType::foextrap ||
              bc_hi == BCType::ext_dir))
    {
        if(i == hi+1)
        {
            fluxx(i,j,0) = (phi(i,j,0)-phi(i-1,j,0)) * dxinv / 0.5;
        }
        else
        {
            fluxx(i,j,0) = (phi(i,j,0)-phi(i-1,j,0)) * dxinv;
        }
    }
    else
    {
        fluxx(i,j,0) = (phi(i,j,0)-phi(i-1,j,0)) * dxinv;
    }
}

AMREX_GPU_DEVICE AMREX_FORCE_INLINE
void compute_flux_y (int i, int j,
                     amrex::Array4<amrex::Real> const& fluxy,
                     amrex::Array4<amrex::Real const> const& phi, amrex::Real dyinv,
                     int lo, int hi, int dom_lo, int dom_hi, int bc_lo, int bc_hi)
if (lo == dom_lo &&
        (bc_lo == BCType::foextrap ||
         bc_lo == BCType::ext_dir))
    {
        if(j == lo)
        {
            fluxy(i,j,0) = (phi(i,j,0)-phi(i,j-1,0)) * dyinv / 0.5;
        }
        else
        {
            fluxy(i,j,0) = (phi(i,j,0)-phi(i,j-1,0)) * dyinv;
        }
    }
    else if (hi == dom_hi &&
             (bc_hi == BCType::foextrap ||
              bc_hi == BCType::ext_dir))
    {
        if(j == hi+1)
        {
            fluxy(i,j,0) = (phi(i,j,0)-phi(i,j-1,0)) * dyinv / 0.5;
        }
        else
        {
            fluxy(i,j,0) = (phi(i,j,0)-phi(i,j-1,0)) * dyinv;
        }
    }
    else
    {
        fluxy(i,j,0) = (phi(i,j,0)-phi(i,j-1,0)) * dyinv;
    }
}
|
AMREX_GPU_DEVICE AMREX_FORCE_INLINE
void update_phi (int i, int j,
                 amrex::Array4<amrex::Real const> const& phi,
                 amrex::Array4<amrex::Real      > const& rhs,
                 AMREX_D_DECL(amrex::Array4<amrex::Real const> const& fluxx,
                              amrex::Array4<amrex::Real const> const& fluxy,
                              amrex::Array4<amrex::Real const> const& fluxz),
                 amrex::Real dt,
                 AMREX_D_DECL(amrex::Real dxinv,
                              amrex::Real dyinv,
                              amrex::Real dzinv))
{
    rhs(i,j,0) = dxinv * (fluxx(i+1,j  ,0 ) - fluxx(i,j,0))
                  + dyinv * (fluxy(i  ,j+1,0  ) - fluxy(i,j,0))

}
                                     
