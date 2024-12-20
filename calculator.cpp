#include <iostream>
using namespace std;

#include <fstream>
#include <ctime>

string fruits[] = {"orange", "apple", "banana"}; // string array of fruits
const int fruitCount = 3;

double parameters[3][4] = {{6, 1, 0.05, 0.01}, {8, 1, 0.04, 0.008}, {4, 1, 0.07, 0.015}};
// 2-D array  of parameters for each fruit {orange, apple, banana} (in that order)

double shelfLife(string fruit, double score, double temp, double hum)
{
    int i;
    for (i = 0; i < fruitCount; i++)
    {
        if (fruit == fruits[i])
            break;
    }
    double life;
    life = parameters[i][0] * score / (parameters[i][1] + parameters[i][2] * temp + parameters[i][3] * hum);
    return life; //returns shelf life of fruit in days

}

//gives current time in "YYYY-MM-DD HH:MM:SS" format
string currentTime()
{
    time_t curr = time(0); // current time
    char buffer[80];
    struct tm timeComp; // structure to hold time broken into components
    timeComp = *localtime(&curr);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &timeComp);
    return string(buffer); //returns time as string
}

//calculates reminder time one hour before shelf life ends
string calculateReminder(double shelfLife)
{
    time_t current = time(0);
    struct tm reminder = *localtime(&current);

    int additionalHours = int((shelfLife * 24)) - 1; // reminder set for one hour before

    reminder.tm_hour += additionalHours;

    mktime(&reminder);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%A %d %B %I:%M %p", &reminder);

    return string(buffer); //returns reminder time as string
}

void userChoice(double &temp, double &hum)
{
    cout << "Please press Y to enter custom temperature and humidity values, or N to use preset Topi December averages.\n";
    char c;
    cin >> c;
    if (c == 'Y')
    {
        cout << "Please enter temperature: \n";
        cin >> temp;
        cout << "Please enter humidity percentage: \n";
        cin >> hum;
    }
    else if (c == 'N')
        cout << "Using preset values.\n";
    else
    {
        cout << "Incorrect keypress.\n";
        userChoice(temp, hum); //recursion 
    }
}

void values(double &score, double &temp, double &hum)
{
    cout << "Please enter the health score of your fruit. (0-5, floating point allowed)\n";
    cin >> score;
    while (score < 0 || score > 5)
    {
        cout << "Incorrect values. Please enter in the range [0, 5].\n";
        cin >> score;
    }

    temp = 22.0; // Dec high, low = 19,0, 8.1 (Topi)
    hum = 46.0;  // Dec Avg (Topi)

    userChoice(temp, hum);
}

void writeOutput(ofstream &shelfLifeOutput, string fruit, string reminder, double score, double life)
{
    if (shelfLifeOutput.is_open())
    {
        shelfLifeOutput << "Date: " << currentTime() << "\n";
        shelfLifeOutput << "Fruit: " << fruit << "\n";
        shelfLifeOutput << "Health Score: " << score << "\n";
        shelfLifeOutput << "Shelf Life (days): " << life << "\n";
        shelfLifeOutput << "Reminder: " << reminder << "\n\n";
        shelfLifeOutput.close();
        cout << "Shelf life: " << life << "\n";
        cout << "Reminder set for " << reminder << " to finish your " << fruit << "s :)" << endl;
    }
    else
        cout << "Unable to open shelf_life.txt" << endl;
}

bool canOpenFile(ifstream &file){

    if(file)
        return true; //returns true is file is open
    return false;
}

int main()
{

    ifstream fruitText;
    fruitText.open("E:\\CP\\CS101 Project\\Code\\fruit_output.txt");
    // file saved as fruit_output.txt
    
    bool flag = canOpenFile(fruitText); //varibale to store file state

    if (!flag)
        cout << "Unable to open file " << "fruit_output.txt" << endl;
    else
    {

        string fruit;
        getline(fruitText, fruit);
        fruitText.close();

        double score, temp, hum;
        values(score, temp, hum);

        double life = shelfLife(fruit, score, temp, hum);
        string reminder = calculateReminder(life);

        ofstream shelfLifeOutput("shelf_life.txt", ios::app);
        writeOutput(shelfLifeOutput, fruit, reminder, score, life);

        shelfLifeOutput.close();
    }

    return 0;
}