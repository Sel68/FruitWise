#include <iostream>
using namespace std;

#include <fstream>



double shelfLife(string fruit, double score, double temp, double humidity, string fruits[], double parameters[3][4] ){
    
    int i;
    for(i=0; i<3; i++){
        if(fruit == fruits[i])
            break;
    }
    double life;
    life = parameters[i][0] * score / (parameters[0][1] +parameters[0][2] * temp + parameters[0][3] * humidity);
    return life;
}

int main(){

    ifstream fruitText;
    fruitText.open("E:\\CP\\CS101 Project\\Code\\fruit_output.txt");

    if(!fruitText)
        cout<<"Unable to open file " << "fruit_output.txt"<<endl;
    else{
        
        string fruit;
        getline(fruitText, fruit);
        fruitText.close();

        double score;
        cout<<"Please enter the health score of your fruit. (0-5, floating point allowed)\n";
        cin>>score;

        string fruits[] = {"orange", "apple", "banana"};
        double temp = 22.0;
        double hum = 46.0;
        double parameters[3][4]= {{6, 1, 0.05, 0.01}, {8, 1, 0.04, 0.008},
            {4, 1, 0.07, 0.015}};

        double life = shelfLife(fruit, score, temp, hum, fruits, parameters);
        cout<<life<<endl;
    }

    return 0;
}