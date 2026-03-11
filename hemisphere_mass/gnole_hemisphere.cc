// example program to run non global evolution
// usage:
//   ./gnole [-out output.dat] [-nev 1e6] [-drap 1.0] [-seed 0] [-order 0] [-xmur 1.0] [-xQ 1.0] [-p -1] [-nbins 100]
//
// the program will create a file containing the dS/dlnET histogram.

#include "Shower.hh"
#include "Observables.hh"
#include "Parameters.hh"
#include "CmdLine.hh"
#include <string>
#include <sstream>
#include "Hemisphere.hh"
#include "Momentum.hh"
using namespace std;


int main(int argc, char **argv)
{
    CmdLine cmdline(argc, argv);

    ostringstream header;
    header << "# " + cmdline.command_line() + "\n# file created on: " + cmdline.time_stamp() + '\n';

    // run parameters
    int seed = cmdline.value("-seed", 0);
    header << "# seed = " << seed << endl;
    int order = cmdline.value("-order", 0);
    header << "# order = " << order << endl;
    double dy = cmdline.value("-drap", 1.0).help("full rapidity width of the slice (centered on y=0)");
    header << "# dy = " << dy << endl;
    double dyl = cmdline.value("-drapl", 0.5);
    header << "# dyl = " << dyl << endl;
    double dyr = cmdline.value("-drapr", 0.5);
    header << "# dyl = " << dyr << endl;
    double nev = cmdline.value("-nev", 1e6).help("number of events to run");
    header << "# nev_requested = " << nev << endl;
    double xmur = cmdline.value("-xmur", 1.0);
    header << "# xmur = " << xmur << endl;
    double xQ = cmdline.value("-xQ", 1.0);
    header << "# xQ = " << xQ << endl;

    // set shower IR cutoff (besides the Landau pole)
    double cutoff = cmdline.value("-lnktmax", 20);
    header << "# lnktmax = " << cutoff << endl;
    set_lnktmax(cutoff);

    // set collinear cutoff
    double etamax = cmdline.value("-etamax", 5);
    header << "# etamax = " << etamax << endl;
    set_rapmax(etamax);

    // set strong coupling
    double alphas = cmdline.value("-as", 0.118).help("Value of the coupling at mu=rts").argname("alphas(rts)");
    header << "# alphas(rts) = " << as << endl;
    set_alphas_at_Q(alphas);

    // decide whether to expand NLL corrections
    bool nll_expanded = cmdline.present("-expand-nll");
    set_nll_expanded(nll_expanded);
    //decide wether to use Dasgupta Salam variant or standart gnole
    bool DS = cmdline.present("-DS");

    // check whether the observable should be computed in SL approximation
    // only appears in the calculation of ET2, has no influence on dSdt
    bool sl_observable = cmdline.present("-sl-obs");
    set_sl_observable(sl_observable);

    // observable
    double p = cmdline.value("-p", -1.0);
    header << "# p = " << p << endl;

    int nbins = cmdline.value("-nbins", 100);
    header << "# nbins = " << nbins << endl;
    double obsmax = cmdline.value("-obsmax", cutoff);
    header << "# obsmax = " << obsmax << endl;

    Slice slice(dy, p, nbins, obsmax);
    Hemisphere2 hemisphere(dy, p, nbins, obsmax);
    asymSlice aslice(dyl, dyr, p, nbins, obsmax);
    // output
    string filename = cmdline.value<string>("-out", "output.dat");

    #ifdef NNET
        string fn_evl_nn = cmdline.value<string>("-evol", "");
        Shower shower(hemisphere, xmur, xQ, fn_evl_nn, order, header.str(), seed);
    #else
        Shower shower(aslice, xmur, xQ, order, DS, header.str(), seed);
    #endif
    // this makes sure there are no unused options
    // left and also triggers the code needed to produce
    // the output for -h
    cmdline.assert_all_options_used();
/*
    double lnkt = 1;
    double eta;
    std::cin >> eta;

    double phi = 0.6 * M_PI;

    double exp_eta = std::exp(eta);
    double alpha = std::exp(-lnkt) * exp_eta;
    double beta = std::exp(-lnkt) / exp_eta;
    double gluon_px = std::exp(-lnkt) * sin(phi);
    double gluon_py = std::exp(-lnkt) * cos(phi);
    double gluon_pz = 0.5 * (alpha - beta);
    double gluon_E = 0.5 * (alpha + beta);

    double theta = 2 * atan(exp(-eta));
    double px = sin(theta) * cos(phi);
    double py = sin(theta) * sin(phi);
    double pz = cos(theta);

    double e = sqrt(px * px + py * py + pz * pz);

    Momentum vec(px, py, pz, e);
    Momentum vecGnole(gluon_px, gluon_py, gluon_pz, gluon_E);
    Momentum thrust_axis(0, 0, -1, 1);
    std::cout << vec.rap() << std::endl;
    std::cout << vecGnole.rap() << std::endl;*/
    shower.run(nev, filename);
}