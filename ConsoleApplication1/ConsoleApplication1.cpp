#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <fstream>

using namespace std;
vector <char> templateStrand;
vector <char> mRna;
vector <string> protein;

void findTemplateStrand(string codingStrand) {

	int numberOfBases = codingStrand.length();
	//goes through coding strand and turns it into the template strand
	for (int i = 0; i < numberOfBases; i++)
	{
		switch (codingStrand[i])
		{
		case 'a': templateStrand.push_back('t');
			break;
		case 't': templateStrand.push_back('a');
			break;
		case 'g': templateStrand.push_back('c');
			break;
		case 'c': templateStrand.push_back('g');
			break;

		}

	}

	

}


void findMRna(string templateStrand) {

	int numberOfBases = templateStrand.length();

	//goes through template strand and turns it into mRNA
	for (int i = 0; i < numberOfBases; i++)
	{
		switch (templateStrand[i])
		{
		case 'a': mRna.push_back('u');
			break;
		case 't': mRna.push_back('a');
			break;
		case 'g': mRna.push_back('c');
			break;
		case 'c': mRna.push_back('g');
			break;

		}




	}
}

void findProtein( string mRnaStrand) {

	int numberOfBases = mRnaStrand.length();
	string codon;
	for (int i = 0; i < numberOfBases; i++) {
	
		codon = { mRnaStrand[i], mRnaStrand[i + 1], mRnaStrand[i + 2] };

			if (codon == "uuu" || codon == "uuc") {
			
				
				protein.push_back("Phe ");
			
			}

			else if (codon == "uua" || codon == "uug" || codon == "cuu" || codon == "cuc" || codon == "cua" || codon == "cug") {


				protein.push_back("Leu ");

			}

			else if (codon == "aug") {


				protein.push_back("Met |start codon| ");

			}

			else if (codon == "guu" || codon == "guc" || codon == "gua" || codon == "gug") {


				protein.push_back("Val ");

			}

			else if (codon == "ucu" || codon == "ucc" || codon == "uca" || codon == "ucg" || codon == "agu" || codon == "agc") {


				protein.push_back("Ser ");

			}

			else if (codon == "ccu" || codon == "ccc" || codon == "cca" || codon == "ccg") {


				protein.push_back("Pro ");

			}

			else if (codon == "acu" || codon == "acc" || codon == "aca" || codon == "acg") {


				protein.push_back("Thr ");

			}

			else if (codon == "gcu" || codon == "gcc" || codon == "gca" || codon == "gcg") {


				protein.push_back("Ala ");

			}

			else if (codon == "uau" || codon == "uac") {


				protein.push_back("Tyr ");

			}

			else if (codon == "cua" || codon == "cac") {


				protein.push_back("His ");

			}

			else if (codon == "caa" || codon == "cag") {


				protein.push_back("Gln ");

			}

			else if (codon == "aau" || codon == "aac") {


				protein.push_back("Asn ");

			}

			else if (codon == "aaa" || codon == "aag") {


				protein.push_back("Lys ");

			}

			else if (codon == "gau" || codon == "gac") {


				protein.push_back("Asp ");

			}

			else if (codon == "gaa" || codon == "gag") {


				protein.push_back("Glu ");

			}

			else if (codon == "ugu" || codon == "ugc") {


			protein.push_back("Cys ");

			}

			else if (codon == "ugg") {


			protein.push_back("Trp ");

			}

			else if (codon == "cgu" || codon == "cgc" || codon == "cga" || codon == "cgg" || codon == "aga" || codon == "agg") {


			protein.push_back("Arg ");

			}

			else if (codon == "ggu" || codon == "ggc" || codon == "gga" || codon == "ggg") {


			protein.push_back("Gly ");

			}

			else if (codon == "auu" || codon == "auc" || codon == "aua") {


			protein.push_back("Ile ");

			}

			else if (codon == "uaa" || codon == "uag" || codon == "uga") {


			protein.push_back("|STOP CODON| ");

			}
	
	
	
			i = i + 3;
	
	}

	


}


int main() {

//	int numberOfThreads = thread::hardware_concurrency();
	fstream dnaFile;
	dnaFile.open("dna.txt");
	string dnaStrand;
	string dnaStrand2;
	while (getline(dnaFile, dnaStrand)) {
		
		
		dnaStrand2 = dnaStrand2 + dnaStrand;
		
	}
	dnaFile.close();
	findTemplateStrand(dnaStrand2);
	
	string stringTemplateStrand(templateStrand.begin(), templateStrand.end());
	findMRna(stringTemplateStrand);

	string stringMRna(mRna.begin(), mRna.end());
	
	findProtein(stringMRna);
	
	


	fstream dnaOutput("dnaOut.txt");

	dnaOutput << "The template strand is: ";
	for (auto i = templateStrand.begin(); i != templateStrand.end(); i++) {
	
		dnaOutput << *i << "";
	}

	dnaOutput << "\n  \n";
	

	dnaOutput << "The mRna strand is: ";
	for (auto i = mRna.begin(); i != mRna.end(); i++) {

		dnaOutput << *i << "";
	}


	dnaOutput << "\n  \n";

	dnaOutput << "The protein strand is: ";
	for (auto i = protein.begin(); i != protein.end(); i++) {

		dnaOutput << *i << "";
	}


}