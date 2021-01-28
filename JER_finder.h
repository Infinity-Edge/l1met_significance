#include <stdio.h>
#include "TMath.h"

double sq_JR(double *res, int N)
{
	double raw = 0;

	for(int i = 0 ; i < N ; i++)
	{
		raw += res[i]*res[i];
	}

	return sqrt(raw);
}


double PUPPI_JER(double jet_pt, TString s)
{
	// TTbar JER
	if (s == "TTbar" || s == "Minbias") // +Minbias
	{
		if ( jet_pt > 0. && jet_pt <= 43.80) {

			double p0 = 0.248603;
			double p1 = 31.1636;
			double p2 = 22.0301;
			double x = jet_pt;
			
			return p0*exp(-0.5*pow((x-p1)/p2, 2));

		} else if (jet_pt > 35.04 && jet_pt <= 328.5) {

			double p0 = 6.41;
			double p1 = 0.0766;
			double p2 = 0.00082;
			double x = jet_pt;

			return p0/x+p1*exp(p2*x);

		} else {

			double p0 = 0.118;

			return p0;
		}

	}

	// VBF JER
	if (s == "VBF")
	{
		if ( jet_pt > 0. && jet_pt <= 56.94) {

			double p0 = 0.258359;
			double p1 = 41.0433;
			double p2 = 24.3014;
			double x = jet_pt;
			
			return p0*exp(-0.5*pow((x-p1)/p2, 2));

		} else if (jet_pt > 43.80 && jet_pt <= 328.5) {

			double p0 = 8.;
			double p1 = 0.067;
			double p2 = 0.00169;
			double x = jet_pt;

			return p0/x+p1*exp(p2*x);

		} else {

			double p0 = -0.00057;
			double p1 = 0.3;
			double x = jet_pt;

			return p0*x+p1;
		}

	}

	// DY JER
	if (s == "DY")
	{
		if ( jet_pt > 0. && jet_pt <= 43.8) {

			double p0 = -0.242;
			double p1 = -0.0445;
			double x = jet_pt;
			
			return exp(p0+p1*x);

		} else if (jet_pt > 43.80 && jet_pt <= 153.3) {

			double p0 = 0.79;
			double p1 = 113.;
			double p2 = 60.;
			double x = jet_pt;

			return p0*TMath::Landau(x, p1, p2);

		} else if (jet_pt > 153.30 && jet_pt <= 179.58) {

			double p0 = 0.125;
			return p0;

		} else if (jet_pt > 179.58 && jet_pt <= 227.76) {

			double p0 = -0.000469;
			double p1 = 0.209;
			double x = jet_pt;

			return p0*x+p1;

		} else {

			double p0 = 24.;
			double p1 = -3.;
			double p2 = 18.;
			double x = jet_pt;

			return log(x/p0+p1)/p2;
		}

	}
	
	return 0.;
}


double PF_JER(double jet_pt, TString s)
{

	// TTbar JER
	if (s == "TTbar" || s == "Minbias") // +Minbias
	{

		double p0 = 10.17;
		double p1 = 0.048;
		double p2 = 0.00123;
		double x = jet_pt;

		return p0/x+p1*exp(p2*x);
	}

	// VBF JER
	if (s == "VBF")
	{

		double p0 = 11.358;
		double p1 = 0.092;
		double p2 = -0.000663;
		double x = jet_pt;

		return p0/x+p1*exp(p2*x);
	}

	// DY JER
	if (s == "DY") 
	{

		double p0 = 11;
		double p1 = 0.03;
		double p2 = 0.0035;
		double x = jet_pt;

		return p0/x+p1*exp(p2*x);
	}

	return 0;
}

// Calculated on 110X env
double TTbar_PUPPI_JER(double jet_pt)
{
		if (jet_pt > 0. && jet_pt <= 315.) {

			double p0 = 6.41;
			double p1 = 0.0766;
			double p2 = 0.00082;
			double x = jet_pt;

			return p0/x+p1*exp(p2*x);

		} else {

			double p0 = 0.1195;

			return p0;
		}

	
	return 0.262;
}

