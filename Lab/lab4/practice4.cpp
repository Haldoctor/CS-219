#include <iostream>
using namespace std;
enum Day{Monday = 1, Tuesday , Wednesday , Thursday , Friday , Saturday , Sunday};
enum Weather{SUNNY = 0, RAINY, CLOUDY, SNOWNY};

int main(int argc, char* argv[]){
  cout <<"input the Day value: Monday(1), Tuesday(2), Wednesday(3), Thursday(4),Friday(5), Saturday(6), Sunday(7)\n" << endl;
  int day = 0;
  int wea = 0;
  cin >> day;
cout<<"This is";
cout << day << endl;
cout<<"input the Weather value: SUNNY(0), RAINY(1), CLOUDY(2), SNOWNY(3)\n" << endl;
cin >> wea;

cout<<"The weather is: ";
cout << wea << endl;
if(wea < 2) cout<<"can Travel\n";
else cout<<"not suitable for travelling\n"; 
return 0;}
