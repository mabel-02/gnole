#ifndef __HEMISPHERE_HH__
#define __HEMISPHERE_HH__
#include "Observables.hh"

class Hemisphere : public Observable
{
public:
    /// constructor
    Hemisphere(double p, int nbin = 100, double maxlnkt = lnktmax, double maxt = EVOLCUT)
        : Observable(p, nbin, maxlnkt, maxt) {}

    /// description
    virtual std::string description() const
    {
        return "Hemisphere observable";
    }

    /// return true if emission is in the hemisphere
    virtual bool in_region(const Momentum &emsn, const Momentum *thrust_axis) const;

    /// return delta rap
    virtual double parameter() const { return 0.0; }

private:
    double delta_rap_;
};

#endif // __HEMISPHERE_HH__