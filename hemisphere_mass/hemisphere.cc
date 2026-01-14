#include "Hemisphere.hh"

/// return true if emission is in the hemisphere
bool Hemisphere::in_region(const Momentum & emsn, const Momentum* thrust_axis) const {
        if (emsn.rap(thrust_axis) > 0){return true;}
        return false;
    }
