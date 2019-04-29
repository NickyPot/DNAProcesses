//to do:
//change template to coding strand

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <future>
#include <mutex>
#include <chrono>

using namespace std::chrono;
using namespace std;
using std::thread;
//mutex for template strand
mutex mutex_protein;


vector <string> protein;




//this will run at the same time as the findMRna function
string findCodingStrand(string templateStrand, int iteration, int numberOfBases, int whichThread) {

	//this is only used within the thread function, as a stepping stone to the global variable
	vector <char> threadedTemplateStrand;
	
	
	//goes through coding strand and turns it into the template strand
	for (; iteration < numberOfBases; iteration++)
	{
		switch (templateStrand[iteration])
		{
		case 'a': threadedTemplateStrand.push_back('t');
			break;
		case 't': threadedTemplateStrand.push_back('a');
			break;
		case 'g': threadedTemplateStrand.push_back('c');
			break;
		case 'c': threadedTemplateStrand.push_back('g');
			break;

		}
		

	}
	
	//turns the vector char template strand into a string, in order to put it in the global string array for the template strand
	string threadedTempStrand(threadedTemplateStrand.begin(), threadedTemplateStrand.end());

	

	return threadedTempStrand;
}




string findMRna(string templateStrand, int iteration, int numberOfBases) {

	vector <char> threadedMRna;
	

	//goes through template strand and turns it into mRNA
	for ( ; iteration < numberOfBases; iteration++)
	{
		switch (templateStrand[iteration])
		{
		case 'a': threadedMRna.push_back('u');
			break;
		case 't': threadedMRna.push_back('a');
			break;
		case 'g': threadedMRna.push_back('c');
			break;
		case 'c': threadedMRna.push_back('g');
			break;

		}
			   		 
	}

	string threadedMRnaInString(threadedMRna.begin(), threadedMRna.end());
	return threadedMRnaInString;
}






int main() {

	//int fff = thread::hardware_concurrency();
	fstream dnaFile;
	dnaFile.open("dna.txt");
	string dnaStrand;
	string dnaStrand2;
	while (getline(dnaFile, dnaStrand)) {
		
		
		dnaStrand2 = dnaStrand2 + dnaStrand;
		
	}


	
	//allows for easy performance evaluation
	int numberOfThreads;
	cout << "what is the number of threads? ";
	cin >> numberOfThreads;
	dnaFile.close();
	auto start = high_resolution_clock::now();
	int maxBase = 0;
	int codingBases = dnaStrand2.length();
	int basesJump = codingBases / numberOfThreads;
	
	//async object that gets the coding strands from the threads
	vector <future<string>> codingStrandsFromThreads;
	
	for (int i = 0; i < numberOfThreads; i++) {
	
		maxBase = maxBase + basesJump;
		int startingPos = basesJump * i;
		codingStrandsFromThreads.push_back(async(findMRna, dnaStrand2, startingPos, maxBase));
	
	
	}

	fstream dnaOutput("dnaOut.txt");
	
	for (int i = 0; i < numberOfThreads; i++)
	{
		dnaOutput << codingStrandsFromThreads[i].get();

	}
	
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	
	cout << duration.count();

	//cout << fff;

	
	


	



}