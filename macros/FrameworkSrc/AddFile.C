
bool Framework::AddFile(){
  char buf[120];
  if(fgets(buf,120,flist)==NULL) return false;
  buf[strlen(buf)-1]=0;
  string infile = buf;
  tf->Close();
  tf = new TFile(infile.data(),"read");
  if(tf->IsZombie())                 {
    cout<<"ZOMBIE:    " <<infile.data()<<endl; 
    string remove = "rm "+infile;
    system(remove.data());
    return true;
  }
  hntrk->Add((TH1D *) tf->Get("vnanalyzer/Ntrk"));
  for(int i = 0; i<nrange; i++) {
    TH2F * ptspec;
    TH2F * ptspecCnt;
    TH1D * ntrk;
    TH2F * qA[11];
    TH2F * qB[11];
    TH2F * wnA[11];
    TH2F * wnB[11];
    TH1D * qBA[11];
    TH1D * qCA[11];
    TH1D * qCB[11];
    TH1D * qBAcnt[11];
    TH1D * qCAcnt[11];
    TH1D * qCBcnt[11];
    ptspec = (TH2F *) tf->Get(Form("vnanalyzer/Spectra/%d_%d/ptspec",r[i].minNtrk,r[i].maxNtrk));
    ptspecCnt = (TH2F *) tf->Get(Form("vnanalyzer/Spectra/%d_%d/ptspecCnt",r[i].minNtrk,r[i].maxNtrk));
    qA[0] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qA",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qB[0] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qB",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    wnA[0] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/wnA",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    wnB[0] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/wnB",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qBA[0] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qBA",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qCA[0] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qCA",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qCB[0] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qCB",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qBAcnt[0] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qBAcnt",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qCAcnt[0] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qCAcnt",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    qCBcnt[0] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/qCBcnt",r[i].minNtrk,r[i].maxNtrk,r[i].order));
    for(int isub = 1; isub<=10; isub++) {
      qA[isub] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qA_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qB[isub] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qB_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      wnA[isub] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/wnA_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      wnB[isub] = (TH2F *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/wnB_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qBA[isub] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qBA_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qCA[isub] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qCA_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qCB[isub] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qCB_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qBAcnt[isub] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qBAcnt_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qCAcnt[isub] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qCAcnt_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
      qCBcnt[isub] = (TH1D *) tf->Get(Form("vnanalyzer/Harmonics/%d_%d/N%d/SubEvents/qCBcnt_%d",r[i].minNtrk,r[i].maxNtrk,r[i].order,isub));
    }
    //////////////////
    for(int j = r[i].minEtaBin[0]; j<= r[i].maxEtaBin[0]; j++) {
      for(int k = r[i].minPtBin; k<=r[i].maxPtBin; k++) {
	r[i].qn[0]+=qA[0]->GetBinContent(k,j);
	r[i].qne[0]+=pow(qA[0]->GetBinError(k,j),2);
	r[i].wnA[0] += wnA[0]->GetBinContent(k,j);
	r[i].qAB[0] += qBA[0]->GetBinContent(1);
	r[i].qAC[0] += qCA[0]->GetBinContent(1);
	r[i].qBC[0] += qCB[0]->GetBinContent(1);
	r[i].wAB[0] += qBAcnt[0]->GetBinContent(1);
	r[i].wAC[0] += qCAcnt[0]->GetBinContent(1);
	r[i].wBC[0] += qCBcnt[0]->GetBinContent(1);

	r[i].pt[0] += ptspec->GetBinContent(k,j);
	r[i].ptcnt[0] += ptspecCnt->GetBinContent(k,j);
	
	for(int m = 1; m<11; m++) {  
	  r[i].qnSub[0][m-1]+=qA[m]->GetBinContent(k,j);
	  r[i].wnASub[0][m-1] += wnA[m]->GetBinContent(k,j);
	}
      }
    }
    //////////////////
    for(int j = r[i].minEtaBin[1]; j<= r[i].maxEtaBin[1]; j++) {
      for(int k = r[i].minPtBin; k<=r[i].maxPtBin; k++) {
	r[i].qn[1]+=qB[0]->GetBinContent(k,j);
	r[i].qne[1]+=pow(qB[0]->GetBinError(k,j),2);
	r[i].wnA[1] += wnB[0]->GetBinContent(k,j);
	r[i].qAB[1] += qBA[0]->GetBinContent(1);
	r[i].qAC[1] += qCB[0]->GetBinContent(1);
	r[i].qBC[1] += qCA[0]->GetBinContent(1);
	r[i].wAB[1] += qBAcnt[0]->GetBinContent(1);
	r[i].wAC[1] += qCBcnt[0]->GetBinContent(1);
	r[i].wBC[1] += qCAcnt[0]->GetBinContent(1);

	r[i].pt[1] += ptspec->GetBinContent(k,j);
	r[i].ptcnt[1] += ptspecCnt->GetBinContent(k,j);
	
	for(int m = 1; m<11; m++) {  
	  r[i].qnSub[1][m-1]+=qB[m]->GetBinContent(k,j);
	  r[i].wnASub[1][m-1] += wnB[m]->GetBinContent(k,j);
	}
      }
    }
  }
  return true;
}
