#include <iostream>
#include <iomanip>
#include <list>
#include <cmath>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct inputTrade
{
	double timeStamp;
	string symbol;
	int quantity;
	int price;
};

struct outputTrade
{
	string symbol;
	double maxTimeGap;
	int volume;
	int weightedAveragePrice;
	int maxPrice;
};

int main()
{
	deque<inputTrade> inputTrades;
	deque<outputTrade> outputTrades;
	ifstream inputFile("C:\\Users\\username\\Desktop\\input.csv");
	string sym;
	string time;
	string quant;
	string price;
	int totalSymbols;
	int totalPrice;
	double initialTime;
	int initialAverage;
	int initialQuantity;

	while (!inputFile.eof())
	{
		while (getline(inputFile, time, ','))
		{
			inputTrade t;

			if (!inputFile.eof())
			{
				t.timeStamp = stod(time);
			}

			if (!inputFile.eof())
			{
				getline(inputFile, sym, ',');
				t.symbol = sym;
			}

			if (!inputFile.eof())
			{
				getline(inputFile, quant, ',');
				t.quantity = stoi(quant);
			}

			if (!inputFile.eof())
			{
				getline(inputFile, price);
				t.price = stoi(price);
			}

			inputTrades.push_back(t);
		}
	}

	for (int i = 0; i < inputTrades.size(); i++)
	{
		outputTrade t;
		totalPrice = 0;
		totalSymbols = 0;
		t.symbol = inputTrades.at(i).symbol;
		initialTime = inputTrades.at(i).timeStamp;
		t.maxPrice = inputTrades.at(i).price;
		t.maxTimeGap = 0;
		t.volume = 0;
		initialAverage = inputTrades.at(i).quantity * inputTrades.at(i).price;
		initialQuantity = inputTrades.at(i).quantity;
		for (int j = i+1; j < inputTrades.size(); j++)
		{
			if (inputTrades.at(j).symbol == t.symbol)
			{
				t.volume += inputTrades.at(j).quantity;
				if (inputTrades.at(j).price > t.maxPrice)
					t.maxPrice = inputTrades.at(j).price;
				if ((inputTrades.at(j).timeStamp - initialTime) > t.maxTimeGap)
					t.maxTimeGap = inputTrades.at(j).timeStamp - initialTime;
				totalPrice += inputTrades.at(j).quantity * inputTrades.at(j).price;
				totalSymbols += inputTrades.at(j).quantity;
				t.weightedAveragePrice = (initialAverage + totalPrice) / (initialQuantity + totalSymbols);
				inputTrades.erase(inputTrades.begin() + j);
				j--;
			}
		}
		outputTrades.push_back(t);
	}

	ofstream output("C:\\Users\\username\\Desktop\\output.csv");
	while (!outputTrades.empty())
	{
		output << outputTrades.front().symbol << "," << outputTrades.front().maxTimeGap << "," << outputTrades.front().volume << "," << outputTrades.front().weightedAveragePrice << "," << outputTrades.front().maxPrice << endl;
		outputTrades.pop_front();
	}
	output.close();

	cout << "Program ran successfully" << endl;
	system("pause");
}