#ifndef __HEMISPHERE_HH__
#define __HEMISPHERE_HH__
#include "Observables.hh"

class Slice2 : public Observable
{
public:
    /// constructor
    Slice2(double delta_rap, double p, int nbin = 100, double maxlnkt = lnktmax, double maxt = EVOLCUT)
        : Observable(p, nbin, maxlnkt, maxt), delta_rap_(delta_rap) {}

    /// description
    virtual std::string description() const
    {
        return "Slice with delta rap = " + std::to_string(delta_rap_);
    }

    /// return true if emission is in the slice
    virtual bool in_region(const Momentum &emsn, const Momentum *thrust_axis) const
    {
        if (std::abs(emsn.rap(thrust_axis)) < delta_rap_ / 2.0){
            return true;
        };
        return false;
    }

    /// return delta rap
    virtual double parameter() const { return delta_rap_; }

private:
    double delta_rap_;
};


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
    virtual double parameter() const { return delta_rap_; }

private:
    double delta_rap_;
};

#endif // __HEMISPHERE_HH__