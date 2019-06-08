#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream> //istringstream



using namespace std;

int main()
{

	char inputfilename[80] = { '\0' };
	ifstream inputfile;
	char outputfilename[80] = { '\0' };
	ofstream outputfile;
	int inputtries = 0; // tries counter when opening input file fails
	int outputtries = 0; // tries counter when  output file fails
	double numberoflines = 0;
	int blankline = 0; // blank line counter to terminate file early

	string stringvalues; // string to store getline data in ==> coinweight coindiameter coinbent coinmatch extradata
	double coinweight = 0;
	string coinw; // coin weight grabbed from file
	double coindiameter = 0;
	string coind; // coin diameter grabbed from file
	string coinbent;
	string coinmatch;
	string extradata;

	const double nickeldiameter = 21.0;
	const double dimediameter = 18.0;
	const double quarterdiameter = 23.7;
	const double looniediameter = 26.0;
	const double twoniediameter = 28.0;

	const double nickelweight = 3.95;
	const double dimeweight = 1.75;
	const double quarterweight = 4.40;
	const double loonieweight = 7.00;
	const double twonieweight = 7.30;

	// coin type per roll
	const int nickelproll = 40;
	const int dimeproll = 50;
	const int quarterproll = 40;
	const int loonieproll = 25;
	const int twonieproll = 25;

	// counter for current coins in coin wrappers
	int nickelwrapper = 0;
	int dimewrapper = 0;
	int quarterwrapper = 0;
	int looniewrapper = 0;
	int twoniewrapper = 0;
	//counter for total coin rolls filled
	int nickelroll = 0;
	int dimeroll = 0;
	int quarterroll = 0;
	int loonieroll = 0;
	int twonieroll = 0;

	bool ignoreline = false; // flag to ingore line
	bool othercoin = false; // flag to treat coin as othe coin

	// total coins processed
	int othercoinamount = 0;
	int totalcoinamount = 0;
	// total coin weight processed
	double othercoinweightsum = 0;
	double bentcoinweightsum = 0;
	// counter for bins filled
	int otherbin = 0;
	int bentbin = 0;
	// current weight of bin
	double othercontainer = 0;
	double bentcontainer = 0;
	const double othercontainermax = 200.0; // max 200g for other container
	const double bentcontainermax = 100.0; // max 100g for bent container

	cout << "Enter the name of the file containing the input data" << endl;
	do
	{
		cin >> inputfilename;
		inputfile.open(inputfilename);

		if (inputfile.fail())
		{

			cerr << "ERROR: File " << inputfilename << " could not be opened for input" << endl;
			inputtries++;
			if (inputtries == 3)
			{
				cerr << "ERROR: You exceeded maximum number of tries allowed while enter the input name " << endl;

				return 1;
			}
			cout << "Reenter the name of the file containing the input data" << endl;
		}
	} while (inputfile.fail()); // check if input file has open correctly

	cout << "Enter the name of the file containing the output data" << endl;
	do
	{
		cin >> outputfilename;
		outputfile.open(outputfilename);

		if (outputfile.fail())
		{

			cerr << "ERROR: File " << outputfilename << " could not be opened for output" << endl;
			outputtries++;
			if (outputtries == 3)
			{
				cerr << "ERROR: You exceeded maximum number of tries allowed while enter the output name " << endl;

				return 2;
			}
			cout << "Reenter the name of the file containing the output data" << endl;
		}
	} while (outputfile.fail()); // check if output file has opened correctly
	cout << fixed << setprecision(2);
	outputfile << fixed << setprecision(2); // making sure all numbers printed to outputfile has 2 decimal places
	inputfile >> numberoflines;
	// check number of lines taken an appropriate value
	if (inputfile.fail() && !inputfile.eof())
	{
		cerr << "ERROR: First piece of data in the file is not an integer" << endl;
		//return 3;
	}
	else if (inputfile.eof())
	{
		cerr << "ERROR: Input data file is empty" << endl;
		//return 4;
	}
	else if (!(numberoflines == int(numberoflines)))
	{
		cerr << "ERROR: First piece of data in the file is not an integer" << endl;
		cout << double(numberoflines) << endl;
		//return 5;
	}
	else if (numberoflines <= 0 || numberoflines > 5000)
	{
		cerr << "ERROR: The number of sensor readings is out of range " << endl;
		return 3;
	}
	else
	{
		cout << "number of lines is " << numberoflines << endl;
	}

	for (int linecounter = 1; linecounter < (numberoflines); linecounter++)
	{
		//setting everythign to zero
		stringvalues = ("");
		coinweight = 0;
		coindiameter = 0;
		coinw = ("");
		coind = ("");
		coinbent = ("");
		coinmatch = ("");
		extradata = ("");
		ignoreline = false;
		othercoin = false;
		blankline = 0;

		getline(inputfile, stringvalues);

		if (stringvalues.length() == 0)//ignores blank lines
		{
			outputfile << "";
			ignoreline = true;
			blankline++;
			if (blankline == 3)
			{
				cerr << "ERROR: No more data" << endl;
				cerr << "Simulation completed early before line " << linecounter - 2 << " of input" << endl;
			}
		}
		else
		{
			blankline--;
			istringstream iss(stringvalues);

			//iss >> coinweight >> coindiameter >> coinbent >> coinmatch >> extradata;
			iss >> coinw;
			//coinw = iss.peek(); // peek coin diameter
			if (!isdigit(coinw[0]))
			{
				cerr << "ERROR: weight sensor value read on line " << linecounter << " is not an integer" << endl;
				cerr << "Simulation terminated early: Please correct your data file " << endl;
				//return 0;
			}
			else
			{
				stringstream doubleconvert(coinw);
				doubleconvert >> coinweight;
			}

			iss >> coind;
			//coind = iss.peek(); // peek coin diameter
			if (!isdigit(coind[0])) //if (IsOnlyDigits(num))
			{
				cerr << "ERROR: Diameter sensor value read on line " << linecounter << " is not an integer" << endl;
				cerr << "Simulation terminated early: Please correct your data file " << endl;
				//return 0;
			}
			else
			{
				stringstream doubleconvert(coind);
				doubleconvert >> coindiameter;
			}



			iss >> coinbent;
			if ((coinbent.compare("bent") != 0) && (coinbent.compare("usable") != 0))
			{
				if ((coinbent.compare("") == 0) && (coinmatch.compare("") == 0))
				{
					cerr << "ERROR: Weight and diameter sensor measurements only" << endl;
				}
				else
				{
					cerr << "ERROR: Weight and diameter sensor measurements and bent string only" << endl;
					cerr << "Ignoring line " << linecounter << " of the input file " << endl;
					ignoreline = true;
				}
			}
			
			iss >> coinmatch;
			if ((coinmatch.compare("BothMatch") != 0) && (coinmatch.compare("OneMatch") != 0) && (coinmatch.compare("NoMatch") != 0))
			{
				cerr << "ERROR: image processing result at line " << linecounter << " is invalid" << endl;
				cerr << "Ignoring this line of data" << endl;
				ignoreline = true;
			}
			
			if (coinweight <= 0 || coinweight > 255)
			{
				cerr << "ERROR: Sensor reading out of range, ignoring line " << linecounter << " in the input file" << endl;
				ignoreline = true;
			}
			if (coindiameter <= 0 || coindiameter > 255)
			{
				cerr << "ERROR: Sensor reading out of range, ignoring line " << linecounter << " in the input file" << endl;
				ignoreline = true;
			}

			iss >> extradata;
			if (extradata.compare("") != 0)
			{
				cerr << "ERROR: Extra data at line " << linecounter << ".Ignoring extra data" << endl;
			}
			cout << coinweight << " " << coindiameter << " " << coinbent << " " << coinmatch << " " << extradata << " end" << endl;
			coinweight = ((coinweight * 500 / 255) * 2) / 100;
			coindiameter = ((coindiameter * 300 / 255) + 100) / 10;

			if (ignoreline == false)
			{
				if (coinbent.compare("bent") == 0) // check if coin is bent
				{
					bentcoinweightsum += coinweight;
					if ((bentcontainer + coinweight) < bentcontainermax)
					{
						bentcontainer += coinweight;
						outputfile << "The Coin Sorter has sent this coin to the bent coin container " << endl;
						outputfile << "The Coins in the bent coin container now weighs " << bentcontainer << " grams" << endl;
						cout << "The Coin Sorter has sent this coin to the bent coin container " << endl;
						cout << "The Coins in the bent coin container now weighs " << bentcontainer << " grams" << endl;
					}
					else //swap the coin container
					{
						bentcontainer = 0;
						bentcontainer += coinweight;
						bentbin++;
						outputfile << "The Coin Sorter has sent this coin to the bent coins container " << endl;
						outputfile << "This coin does not fit in the bent coins container " << endl;
						outputfile << "The bent coins container has been replaced " << endl;
						outputfile << "The Coins in the bent coins container now weighs " << bentcontainer << " grams" << endl;
						cout << "The Coin Sorter has sent this coin to the bent coins container " << endl;
						cout << "This coin does not fit in the bent coins container " << endl;
						cout << "The bent coins container has been replaced " << endl;
						cout << "The Coins in the bent coins container now weighs " << bentcontainer << " grams" << endl;
					}
				}

				else if (abs(coindiameter - nickeldiameter) < 0.8) // check if coin is a nickel else flag coin as an "othercoin"
				{
					if (abs(coinweight - nickelweight) < 0.35)
					{
						if (coinmatch.compare("BothMatch") == 0)
						{
							if (nickelwrapper < (nickelproll - 1))
							{
								nickelwrapper++;
								outputfile << "The Coin Sorter has sent one coin to the nickels wrapper " << endl;
								outputfile << "There are now " << nickelwrapper << " coins in the nickels wraper " << endl;
								cout << "The Coin Sorter has sent one coin to the nickels wrapper " << endl;
								cout << "There are now " << nickelwrapper << " coins in the nickels wraper " << endl;
							}
							else
							{
								nickelwrapper = 0;
								nickelwrapper++;
								nickelroll++;
								outputfile << "The Coin Sorter has sent one coin to the nickels wrapper " << endl;
								outputfile << "The nickels wrapper is now full " << endl;
								outputfile << "The nickels wrapper has now been replaced " << endl;
								cout << "The Coin Sorter has sent one coin to the nickels wrapper " << endl;
								cout << "The nickels wrapper is now full " << endl;
								cout << "The nickels wrapper has now been replaced " << endl;

							}
						}
						else
						{
							othercoin = true;
						}

					}
					else
					{
						othercoin = true;
					}

				}
				else if (abs(coindiameter - dimediameter) < 0.7) // check if coin is a dime else flag coin as an "othercoin"
				{
					if (abs(coinweight - dimeweight) < 0.45)
					{
						if (coinmatch.compare("BothMatch") == 0)
						{
							if (dimewrapper < (dimeproll - 1))
							{
								dimewrapper++;
								outputfile << "The Coin Sorter has sent one coin to the dime wrapper " << endl;
								outputfile << "There are now " << dimewrapper << " coins in the dime wraper " << endl;
								cout << "The Coin Sorter has sent one coin to the dime wrapper " << endl;
								cout << "There are now " << dimewrapper << " coins in the dime wraper " << endl;
							}
							else
							{
								dimewrapper = 0;
								dimewrapper++;
								dimeroll++;
								outputfile << "The Coin Sorter has sent one coin to the dimes wrapper " << endl;
								outputfile << "The dime wrapper is now full " << endl;
								outputfile << "The dime wrapper has now been replaced " << endl;
								cout << "The Coin Sorter has sent one coin to the dimes wrapper " << endl;
								cout << "The dime wrapper is now full " << endl;
								cout << "The dime wrapper has now been replaced " << endl;
							}
						}
						else
						{
							othercoin = true;
						}


					}
					else
					{
						othercoin = true;
					}

				}
				else if (abs(coindiameter - quarterdiameter) < 0.9) // check if coin is a quarter else flag coin as an "othercoin"
				{
					if (abs(coinweight - quarterweight) < 0.40)
					{
						if (coinmatch.compare("BothMatch") == 0)
						{
							if (quarterwrapper < (quarterproll - 1))
							{
								quarterwrapper++;
								outputfile << "The Coin Sorter has sent one coin to the quarter wrapper " << endl;
								outputfile << "There are now " << quarterwrapper << " coins in the quarter wraper" << endl;
								cout << "The Coin Sorter has sent one coin to the quarter wrapper " << endl;
								cout << "There are now " << quarterwrapper << " coins in the quarter wraper" << endl;
							}
							else
							{
								quarterwrapper = 0;
								quarterwrapper++;
								quarterroll++;
								outputfile << "The Coin Sorter has sent one coin to the quarters wrapper " << endl;
								outputfile << "The quarter wrapper is now full " << endl;
								outputfile << "The quarter wrapper has now been replaced " << endl;
								cout << "The Coin Sorter has sent one coin to the quarters wrapper " << endl;
								cout << "The quarter wrapper is now full " << endl;
								cout << "The quarter wrapper has now been replaced " << endl;
							}
						}
						else
						{
							othercoin = true;
						}


					}
					else
					{
						othercoin = true;
					}

				}
				else if (abs(coindiameter - looniediameter) < 1.0) // check if coin is a loonie else flag coin as an "othercoin"
				{
					if (abs(coinweight - loonieweight) < 0.50)
					{
						if (coinmatch.compare("BothMatch") == 0)
						{
							if (looniewrapper < (loonieproll - 1))
							{
								looniewrapper++;
								outputfile << "The Coin Sorter has sent one coin to the loonie wrapper " << endl;
								outputfile << "There are now " << looniewrapper << " coins in the loonie wraper " << endl;
								cout << "The Coin Sorter has sent one coin to the loonie wrapper " << endl;
								cout << "There are now " << looniewrapper << " coins in the loonie wraper " << endl;
							}
							else
							{
								looniewrapper = 0;
								looniewrapper++;
								loonieroll++;
								outputfile << "The Coin Sorter has sent one coin to the loonies wrapper " << endl;
								outputfile << "The loonie wrapper is now full " << endl;
								outputfile << "The loonie wrapper has now been replaced " << endl;
								cout << "The Coin Sorter has sent one coin to the loonies wrapper " << endl;
								cout << "The loonie wrapper is now full " << endl;
								cout << "The loonie wrapper has now been replaced " << endl;
							}
						}
						else
						{
							othercoin = true;
						}


					}
					else
					{
						othercoin = true;
					}

				}
				else if (abs(coindiameter - twoniediameter) < 1.1) // check if coin is a twonie else flag coin as an "othercoin"
				{
					if (abs(coinweight - twonieweight) < 0.55)
					{
						if (coinmatch.compare("BothMatch") == 0)
						{
							if (twoniewrapper < (twonieproll - 1))
							{
								twoniewrapper++;
								outputfile << "The Coin Sorter has sent one coin to the twonie wrapper " << endl;
								outputfile << "There are now " << twoniewrapper << " coins in the twonie wraper " << endl;
								cout << "The Coin Sorter has sent one coin to the twonie wrapper " << endl;
								cout << "There are now " << twoniewrapper << " coins in the twonie wraper " << endl;
							}
							else
							{
								twoniewrapper = 0;
								twoniewrapper++;
								twonieroll++;
								outputfile << "The Coin Sorter has sent one coin to the twonies wrapper " << endl;
								outputfile << "The twonie wrapper is now full " << endl;
								outputfile << "The twonie wrapper has now been replaced " << endl;
								cout << "The Coin Sorter has sent one coin to the twonies wrapper " << endl;
								cout << "The twonie wrapper is now full " << endl;
								cout << "The twonie wrapper has now been replaced " << endl;
							}
						}
						else
						{
							othercoin = true;
						}


					}
					else
					{
						othercoin = true;
					}

				}
				else // if coin cannont be identified flag coin as an "othercoin"
				{
					othercoin = true;
				}
				if (othercoin == true)
				{
					if ((othercontainer + coinweight) < othercontainermax)
					{
						othercoinamount++;
						othercontainer += coinweight;
						outputfile << "The Coin Sorter has sent this coin to the other coin container " << endl;
						outputfile << "The coins in the other coin container now weigh " << othercontainer << " grams" << endl;
						cout << "The Coin Sorter has sent this coin to the other coin container " << endl;
						cout << "The coins in the other coin container now weigh " << othercontainer << " grams" << endl;
					}
					else
					{
						othercoinamount = 0;
						othercoinamount++;
						othercontainer = 0;
						othercontainer += coinweight;
						otherbin++;
						outputfile << "The Coin Sorter has sent this coin to the other coin container " << endl;
						outputfile << "This coin does not fit in the other coin container " << endl;
						outputfile << "The other coins container has been replaced " << endl;
						outputfile << "The coins in the other coin container now weighs " << othercontainer << " grams" << endl;
						cout << "The Coin Sorter has sent this coin to the other coin container " << endl;
						cout << "This coin does not fit in the other coin container " << endl;
						cout << "The other coins container has been replaced " << endl;
						cout << "The coins in the other coin container now weighs " << othercontainer << " grams" << endl;
					}
					othercoinweightsum += coinweight;
					totalcoinamount++;
				}
			} // end of else
			if (ignoreline == true)//dont add to the line counter when ignoring line
			{
				linecounter--;
			}
		} // end of else loop (processing data loop)
    } // end of for loop
	
	outputfile << endl << endl << endl;
	outputfile << "SUMMARY" << endl;
	outputfile << "The Coin Sorter made " << nickelroll << " rolls of nickels." << endl;
	outputfile << "     There are " << nickelwrapper << " nickels in the partially full roll." << endl;
	outputfile << "The Coin Sorter made " << dimeroll << " rolls of dimes." << endl;
	outputfile << "     There are " << dimewrapper << " dimes in the partially full roll." << endl;
	outputfile << "The Coin Sorter made " << quarterroll << " rolls of quarters." << endl;
	outputfile << "     There are " << quarterwrapper << " quarters in the partially full roll." << endl;
	outputfile << "The Coin Sorter made " << loonieroll << " rolls of loonies." << endl;
	outputfile << "     There are " << looniewrapper << " loonies in the partially full roll." << endl;
	outputfile << "The Coin Sorter made " << twonieroll << " rolls of twonies." << endl;
	outputfile << "     There are " << twoniewrapper << " twonies in the partially full roll." << endl;

	outputfile << "The Coin Sorter processed " << totalcoinamount << " other coins." << endl;
	outputfile << "     The other coins completely filled " << otherbin << " containers" << endl;
	outputfile << "     There were " << othercoinamount << " other coins in the partially full container" << endl;
	outputfile << fixed << setprecision(3) << "     The total weight of the other coins was " << othercoinweightsum << " grams" << endl;
	outputfile << fixed << setprecision(4) << "The Coin Sorter processed " << bentcoinweightsum << " g of bent coins" << endl;

	cout << endl << endl << endl;
	cout << "SUMMARY" << endl;
	cout << "The Coin Sorter made " << nickelroll << " rolls of nickels." << endl;
	cout << "     There are " << nickelwrapper << " nickels in the partially full roll." << endl;
	cout << "The Coin Sorter made " << dimeroll << " rolls of dimes." << endl;
	cout << "     There are " << dimewrapper << " dimes in the partially full roll." << endl;
	cout << "The Coin Sorter made " << quarterroll << " rolls of quarters." << endl;
	cout << "     There are " << quarterwrapper << " quarters in the partially full roll." << endl;
	cout << "The Coin Sorter made " << loonieroll << " rolls of loonies." << endl;
	cout << "     There are " << looniewrapper << " loonies in the partially full roll." << endl;
	cout << "The Coin Sorter made " << twonieroll << " rolls of twonies." << endl;
	cout << "     There are " << twoniewrapper << " twonies in the partially full roll." << endl;

	cout << "The Coin Sorter processed " << totalcoinamount << " other coins." << endl;
	cout << "     The other coins completely filled " << otherbin << " containers" << endl;
	cout << "     There were " << othercoinamount << " other coins in the partially full container" << endl;
	cout << fixed << setprecision(3) << "     The total weight of the other coins was " << othercoinweightsum << " grams" << endl;
	cout << fixed << setprecision(4) << "The Coin Sorter processed " << bentcoinweightsum << " g of bent coins" << endl;

	system("PAUSE");
	return 0;

}