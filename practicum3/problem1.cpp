#include <iostream>
#include <vector>

using namespace std;


class City {
    public:
        City();
        City(string name);

        bool AddAddress(double lotValue, string lotAddress);
        double ComputeAverage();
        int CountAddresses(double min_value);
        int CountSameAddress(string lotAddress);


    private:
        string cityName;
        vector<double> landValues;
        vector<string> addresses;

};