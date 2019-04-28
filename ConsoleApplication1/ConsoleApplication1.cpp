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
mutex mutex_;
//temporary string for template strand that is use to combine all themplate strands from the threads
string finalTemplateStrand[3];

//vector<condition_variable> t;
//vector <char> templateStrand;
vector <char> mRna;
vector <string> protein;


//this will run at the same time as the findMRna function
string findTemplateStrand(string codingStrand, int iteration, int numberOfBases, int whichThread) {

	//this is only used within the thread function, as a stepping stone to the global variable
	vector <char> threadedTemplateStrand;
	
	
	//goes through coding strand and turns it into the template strand
	for (; iteration < numberOfBases; iteration++)
	{
		switch (codingStrand[iteration])
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

	//lock the global variable
	mutex_.lock();
	//puts in the part of the template strand, in the place according to which thread is submitting it
	finalTemplateStrand[whichThread] = threadedTempStrand;
	//unlock the variable
	mutex_.unlock();

	return threadedTempStrand;
}






int main() {

	int fff = thread::hardware_concurrency();
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
		codingStrandsFromThreads.push_back(async(findTemplateStrand, dnaStrand2, startingPos, maxBase, i));
	
	
	}

	fstream dnaOutput("dnaOut.txt");
	
	for (int i = 0; i < numberOfThreads; i++)
	{
		dnaOutput << codingStrandsFromThreads[i].get();

	}
	
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	
	cout << duration.count();

	cout << fff;

	
	


	



}