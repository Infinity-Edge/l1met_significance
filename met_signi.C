#define met_signi_cxx
#include "met_signi.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "JER_finder.h"

void met_signi::Loop(TString dir = "sigs_110X", TString tProcess = "VBF")
{
   if (fChain == 0) return;
	TH1F* hPFmet = new TH1F("hPFmet", "PF MET;PF E^{miss}_{T} [GeV];Events", 100, 0, 400);
	TH1F* hPUmet = new TH1F("hPUmet", "Puppi MET;Puppi E^{miss}_{T} [GeV];Events", 100, 0, 400);

	TH1F* hPFjs = new TH1F("hPFjs", "PF JER;Jet Resolution;Events", 100, 0, 1.);
	TH1F* hPUjs = new TH1F("hPUjs", "PUPPI JER;Jet Resolution;Events", 100, 0, 1.);

	TH1F* hPFj = new TH1F("hPFj", "PF JER * PF Jet pT;JER*Jet p_{T} [GeV];Events", 100, 0,200);
	TH1F* hPUj = new TH1F("hPUj", "Puppi JER * Puppi Jet pT;JER*Jet p_{T};Events", 100, 0, 200);

	TH1F* hGEsig = new TH1F("hGEsig", "GE MET Significance;Significance;Events", 100, 0, 20);
	TH1F* hPFsig = new TH1F("hPFsig", "PF MET Significance;Significance;Events", 100, 0, 20);
	TH1F* hPUsig = new TH1F("hPUsig", "Puppi MET Significance;Significance;Events", 100, 0, 20);

	TH2F* hPFmetsig = new TH2F("hPFmetsig", "PF MET v.s. significance;E^{miss}_{T} [GeV];significance", 100, 0, 400, 100, 0, 15);
	TH2F* hPUmetsig = new TH2F("hPUmetsig", "PUPPI MET v.s. significance;E^{miss}_{T} [GeV];significance", 100, 0, 400, 100, 0, 15);

	double pt_range[20] = {20,25,30,35,40,45,50,55,60,70,80,90,100,120,140,160,200,250,320,400};

    const int N = 3;

	TString prox = tProcess;


	Long64_t nentries = fChain->GetEntriesFast();

	// Significance file
    TFile *fsig = new TFile("./"+dir+"/"+prox+"/MET_sig_ntuple_"+prox+".root", "RECREATE");
    TTree *tsig = new TTree("Events", " MET significance");

    Float_t bPF_sig;
    Float_t bPU_sig;

    Float_t bGe_met;
    Float_t bPF_met;
    Float_t bPU_met;

	tsig->Branch("L1PFMet_sig", &bPF_sig);
	tsig->Branch("L1PuppiMet_sig", &bPU_sig);

	tsig->Branch("genMet_pt", &bGe_met);
	tsig->Branch("L1PFMet_pt", &bPF_met);
	tsig->Branch("L1PuppiMet_pt", &bPU_met);

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		// Number of reco jets
		const int Npfj = nL1PFJets;		const int Npuj = nL1PuppiJets;
		
		// JER for each jet
		double pfjresols[Npfj];		double pujresols[Npuj];


		// PF MET significance Calcualtion
		int count_pfj = 0;
		for (int i = 0 ; i < nL1PFJets ; i++)
		{
			double pf = L1PFJets_pt[i];
			if (pf > 20.) {
			double pf_res = PF_JER(pf, tProcess);
			pfjresols[i] = pf*pf_res;
			hPFj->Fill(pfjresols[i]);
			hPFjs->Fill(pf_res);
			count_pfj++;
			}
		}

		// PUPPI MET significance Calculation
    	int count_puj = 0;
    	for (int i = 0 ; i < nL1PuppiJets ; i++)
    	{
    		double pu = L1PuppiJets_pt[i];
    		if (pu > 20.) {
    		double pu_res = TTbar_PUPPI_JER(pu);
			pujresols[i] = pu*pu_res;
			hPUj->Fill(pujresols[i]);
			hPUjs->Fill(pu_res);
			count_puj++;
			}
		}

		double sPFJR = sq_JR(pfjresols, count_pfj);
		double sPUJR = sq_JR(pujresols, count_puj);

		double geMET = genMet_pt;
		double pfMET = L1PFMet_pt;
		double puMET = L1PuppiMet_pt;


		hPFmet->Fill(pfMET);	hPFsig->Fill(pfMET/sPFJR);	hPFmetsig->Fill(pfMET, pfMET/sPFJR);
		hPUmet->Fill(puMET);	hPUsig->Fill(puMET/sPUJR);	hPUmetsig->Fill(puMET, puMET/sPUJR);


		// If demoninator is 0, the significance can not be defined!
		if (sPFJR == 0.) {
			bPF_sig  = 0.;
		} else {
			bPF_sig  = pfMET/sPFJR;
		}

		if (sPUJR == 0.) {
			bPU_sig  = 0.;
		} else {
			bPU_sig  = puMET/sPUJR;
		}
		
		bGe_met = geMET;
		bPF_met = pfMET;
		bPU_met = puMET;

    	tsig->Fill();
	}

    tsig->Write();    fsig->Close();

	TFile *fout = new TFile("./"+dir+"/"+prox+"/sig_plots_"+prox+".root", "RECREATE");

	hPFmet->Write();
	hPUmet->Write();

	hPFjs->Write();	hPFj->Write();	hPFsig->Write();	hPFmetsig->Write();
	hPUjs->Write(); hPUj->Write();	hPUsig->Write();	hPUmetsig->Write();
	
	hGEsig->Write();

	fout->Close();

	gStyle->SetOptStat(0000);
	TCanvas *c0 = new TCanvas("c0", "", 500, 500);

	hPUmetsig->Draw("colz");
	hPUmetsig->SetTitle("");
	hPUmetsig->GetXaxis()->SetTitle("PUPPI E_{T}^{miss} [GeV]");
	hPUmetsig->GetYaxis()->SetTitle("PUPPI E_{T}^{miss} significance");
	hPUmetsig->GetXaxis()->SetTitleSize(0.05);
	hPUmetsig->GetYaxis()->SetTitleSize(0.05);
	hPUmetsig->GetXaxis()->SetTitleOffset(0.8);
	hPUmetsig->GetYaxis()->SetTitleOffset(0.9);

	c0->Print("./"+dir+"/"+prox+"/PUmetsig_2D_"+prox+".pdf");
}

