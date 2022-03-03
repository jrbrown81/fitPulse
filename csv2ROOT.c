//
//  csv2ROOT.c
//
//
//  Created by Jamie Brown on 19/08/2019.
// Modifed 25/2/22
/*
 Open root
 Load this macro using:
 .L csv2ROOT.c
 then run it on your file using:
 csv2ROOT("filename")
 the filename should include the .CSV extension

Note: that the header information needs to be stripped out of the .CSV file first
*/

#include <stdio.h>

void csv2ROOT(TString inFile){

	TString outFile=inFile;
	outFile.ReplaceAll(".CSV",".root");

	TFile* file=new TFile(outFile,"recreate");
	TTree* tree=new TTree("tree","");
	Long64_t nLines=tree->ReadFile(inFile,"junk:x:y");
	tree->Write();
	file->Close();

	return;
}

void help(){
 cout <<"Open root \n";
 cout<< "Load this macro using:\n";
 cout <<".L csv2ROOT.c\n";
 cout <<"then run it on your file using:\n";
 cout <<"csv2ROOT(\"filename\")\n";
 cout <<"the filename should include the .CSV extension\n\n";
 cout <<"Note: that the header information needs to be stripped out of the .CSV file first.\n"<< endl;

}
