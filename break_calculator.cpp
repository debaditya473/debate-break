#include <bits/stdc++.h>
using namespace std;

void AP_Break(int teams, int rounds, int breaks)
{
    if (teams%2) teams += 1;
    
    float expected_points = 0;
    int epochs = 10000;
    //points[2] = {0, 1}

    for(int e = 0; e < epochs; e++)
    {
        vector<int> scores(teams, 0);
        for(int r = 0; r < rounds; r++)
        {
            for(int t = 0; t < teams; t+=2)
            {
                int c = floor(((double) rand() / (RAND_MAX)) + 0.5);
                scores[t] += c;
                scores[t+1] += 1-c; 
            }
            sort(scores.begin(), scores.end(), greater<int>());
        }
        expected_points += scores[breaks - 1];
    }
    //cout << expected_points;
    expected_points = float(expected_points)/float(epochs);


    int pos[2] = {int(expected_points), int(expected_points)+1};
    int *num_breaks = new int[2]();
    int *num_count = new int[2]();

    for(int e = 0; e < epochs; e++)
    {
        int *scores = new int[teams]();
        for(int r = 0; r < rounds; r++)
        {
            for(int t = 0; t < teams; t+=2)
            {
                int c = floor(((double) rand() / (RAND_MAX)) + 0.5);
                scores[t] += c;
                scores[t+1] += 1-c; 
            }
            sort(scores, scores + teams, greater<int>());
        }
        for(int i = 0; i < 2; i++){
            num_breaks[i] += count(scores, scores + breaks, pos[i]);
            num_count[i] += count(scores, scores + teams, pos[i]);
        }
    }

    cout << endl << "Expected points to break: " << expected_points << endl;
    
    for(int i = 0; i < 2; i++){
        cout << "Probability of breaking at " << pos[i] 
        << " = " << (float(num_breaks[i])/float(num_count[i]))*100
        << " %" << endl;
    }
    cout<<endl;
}

void BP_Break(int teams, int rounds, int breaks)
{
    if (teams%4) teams = (int(teams/4)+1)*4;
    
    float expected_points = 0;
    int epochs = 10000;
    int points[4] = {0, 1, 2, 3};

    for(int e = 0; e < epochs; e++)
    {
        vector<int> scores(teams, 0);
        for(int r = 0; r < rounds; r++)
        {
            for(int t = 0; t < teams; t+=4)
            {
                random_shuffle(points, points+4);
                for(int i = 0; i < 4; i ++){
                    scores[t+i] += points[i];
                }
            }
            sort(scores.begin(), scores.end(), greater<int>());
        }
        expected_points += scores[breaks - 1];
    }
    //cout << expected_points;
    expected_points = float(expected_points)/float(epochs);


    int pos[2] = {int(expected_points), int(expected_points)+1};
    int *num_breaks = new int[2]();
    int *num_count = new int[2]();

    for(int e = 0; e < epochs; e++)
    {
        int *scores = new int[teams]();
        for(int r = 0; r < rounds; r++)
        {
            for(int t = 0; t < teams; t+=4)
            {
                random_shuffle(points, points+4);
                for(int i = 0; i < 4; i ++){
                    scores[t+i] += points[i];
                }
            }
            sort(scores, scores + teams, greater<int>());
        }
        for(int i = 0; i < 2; i++){
            num_breaks[i] += count(scores, scores + breaks, pos[i]);
            num_count[i] += count(scores, scores + teams, pos[i]);
        }
    }

    cout << endl << "Expected points to break: " << expected_points << endl;
    
    for(int i = 0; i < 2; i++){
        cout << "Probability of breaking at " << pos[i] 
        << " = " << (float(num_breaks[i])/float(num_count[i]))*100
        << " %" << endl;
    }
    cout<<endl;
}

int main()
{
    int n, b, r, choice;
    cout << "AP (1) or BP (2): ";
    cin >> choice;
    cout << "Enter Number of Teams: ";
    cin >> n;
    cout << "Enter Number of Rounds: ";
    cin >> r;
    cout << "Enter Number of Breaks: ";
    cin >> b;

    switch (choice)
    {
    case 1:
        AP_Break(n, r, b);
        break;
    case 2:
        BP_Break(n, r, b);
        break;
    default:
        break;
    }

    return 0;
}