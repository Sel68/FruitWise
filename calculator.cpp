#include <iostream>
using namespace std;

#include <fstream>

string fruits[] = {"orange", "apple", "banana"}; //string array of fruits
const int fruitCount=3;

const double temp = 22.0; // Dec high, low = 19,0, 8.1 (Topi)
const double hum = 46.0; // Dec Avg (Topi)
double parameters[3][4]= {{6, 1, 0.05, 0.01}, {8, 1, 0.04, 0.008},
        {4, 1, 0.07, 0.015}}; //2-D array  of parameters for each fruit


double shelfLife(string fruit, double score){    
    int i;
    for(i=0; i<fruitCount; i++){
        if(fruit == fruits[i])
            break;
    }
    double life;
    life = parameters[i][0] * score / (parameters[i][1] +parameters[i][2] * temp + parameters[i][3] * hum);
    return life;
}

int main(){

    ifstream fruitText;
    fruitText.open("E:\\CP\\CS101 Project\\Code\\fruit_output.txt"); 
    //file saved as fruit_output.txt

    if(!fruitText)
        cout<<"Unable to open file " << "fruit_output.txt"<<endl;
    else{
        
        string fruit;
        getline(fruitText, fruit);
        fruitText.close();

        double score;
        cout<<"Please enter the health score of your fruit. (0-5, floating point allowed)\n";
        cin>>score;

        
        

        double life = shelfLife(fruit, score);
        cout<<life<<endl;
    }

    return 0;
}