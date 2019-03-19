
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;


int orientare(pair<int, int> p, pair<int, int> q, pair<int, int> r)
{
    /**
    0 : cele 3 puncte sunt coliniare
    1 : viraj la dreapta
    2 : viraj la stanga
    */
	int val = (q.second - p.second) * (r.first - q.first)
		- (q.first - p.first) * (r.second - q.second);
	if (val == 0)
	{
		return 0;
	}
	return (val > 0) ? 1 : 2;
}


int main()
{
    ifstream f("date.in");
	int n;    // n = nr de puncte
	int k = 0; // k = Numarul de puncte sterse in construirea frontierei superioare
    int k2=0; // k2 = Numarul de puncte sterse in construirea frontierei inferioare
	int t=0;
	int ii=2;
	// iterator pentru a forma acoperirirea inferioara
	int j = 0;
	// j : what is j
	// GRAFICA
	int careLinie = 0;
	int careLinie2 = 0;

	f >> n;
	int fs_i = n-3;

    // GRAFICA
    float shiftare = 0.5 * 5;
    float asteapta;

	int x, y;
	vector<pair<int, int> > a;
	// a : vector de puncte
	// citire din fisier
	for (int i = 0; i < n; i++)
	{
		f >> x >> y;
		a.push_back(make_pair(x, y));
	}
	f.close();


    vector<pair<int, int> > fi;   /// ACOPERIREA INFERIOARA
	fi.push_back(a[0]);
	fi.push_back(a[1]);
    // acoparirea inferioara cuprinde cele mai "din stanga" puncte

	vector<pair<int, int> > fs;   /// ACOPERIREA SUPERIOARA
	fs.push_back(a[n-1]);
	fs.push_back(a[n-2]);
	// acoperiarea superioara cuprinde cele mai "din dreapta" puncte


/*
    sf::Vertex linii[n][2];
    sf::Vertex linii2[n][2];

    sf::Vertex line[]{
        sf::Vertex(sf::Vector2f(fi[0].first*5  + 400, 300-  5*fi[0].second)),
        sf::Vertex(sf::Vector2f(fi[1].first*5  + 400, 300 - 5*fi[1].second))
    };
    linii[careLinie][0] = line[0];
    linii[careLinie++][1] = line[1];

    sf::Vertex line2[]{
        sf::Vertex(sf::Vector2f(fs[0].first*5  + 400, 300-  5*fs[0].second)),
        sf::Vertex(sf::Vector2f(fs[1].first*5  + 400, 300 - 5*fs[1].second))
    };
    linii2[careLinie2][0] = line2[0];
    linii2[careLinie2++][1] = line2[1];


    cout << "Alege cate secunde sa astepti intre pasi (0.1 - 2) : ";
    cin >> asteapta;
    ShowWindow( GetConsoleWindow(), SW_HIDE );

    sf::RenderWindow app2(sf::VideoMode(800, 600), "SFML window");
*/
    // citirea punctelor in versiunea grafica
    while (j <= 2*n)
    {
        // Process events
 /*       sf::Event event;
        while (app2.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app2.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    ShowWindow( GetConsoleWindow(), SW_RESTORE );

                    cout << "EXIT!";
                    app2.close();
                    cin.get();
                    return 0;
                }
            }
        }

        // Clear screen
        app2.clear();

        for(int i=0; i<n; i++){
            sf::CircleShape cerc3(3);
            cerc3.setPosition(a[i].first*5 + 400-shiftare, 300 - a[i].second*5-shiftare);
            app2.draw(cerc3);
        }
*/
    /// CONSTRUIM FRONTIERA SUPERIOARA
	if(ii<n)
    {
	    if(j<n)
	    {
            fi.push_back(a[ii]);
            // adaugam nodul curent in frontiera inferioara
           /*  sf::Vertex line[]{
                    sf::Vertex(sf::Vector2f(fi[ii - k - 1].first*5 + 400-shiftare, 300 - shiftare -5*fi[ii - k - 1].second)),
                    sf::Vertex(sf::Vector2f(fi[ii - k].first*5 + 400-shiftare, 300 - shiftare -5* fi[ii - k].second))
                };
                linii[careLinie][0] = line[0];
                linii[careLinie++][1] = line[1];
*/
            while (fi.size() > 2)
                /// facem verificare pt un singur punct a[ii]
            {
                int x = orientare(fi[ii - 2 - k], fi[ii - k - 1], fi[ii - k]);

                if (x != 2)
                {
                    // daca nu avem viraj la stanga stergem nodul anterior pana avem viraj bun
                    careLinie -=2;
 /*                   sf::Vertex line[]{
                        sf::Vertex(sf::Vector2f(fi[ii - 2 - k].first*5 + 400-shiftare, 300 - shiftare -5* fi[ii - 2 - k].second)),
                        sf::Vertex(sf::Vector2f(fi[ii - k].first*5 + 400-shiftare, 300 - shiftare -5* fi[ii - k].second))

                };
                    linii[careLinie][0] = line[0];
                    linii[careLinie++][1] = line[1];
*/
                    fi[ii - k - 1] = fi[ii - k];
                    ///stergem pe fi[1] si il inlocuin cu a[ii]
                    fi.pop_back();
                    k++;
                }
                else
                    // conditie de stop
                    // avem viraj stanga
                    break;
            }
	    }
	}// ii < n

	// Trecem la urmatorul punct
    ii++;
    /// CONSTRUIM FRONTIERA INFERIOARA
    if(ii>=n) // am terminat frontiera inferioara si acum o facem pe cea superioara
    {
        if(fs_i >= 0) /// fs_i = n-3 ( ultimele 2 puncte au fost adaugate deja in hull superior)
        {
            fs.push_back(a[fs_i]);

           /* sf::Vertex line[]
                {
                    sf::Vertex(sf::Vector2f(fs[t+1-k2].first*5 + 400-shiftare, 300 - shiftare -5*fs[t+1-k2].second)),
                    sf::Vertex(sf::Vector2f(fs[t+2-k2].first*5 + 400-shiftare, 300 - shiftare -5* fs[t+2-k2].second))
                };
            linii2[careLinie2][0] = line[0];
            linii2[careLinie2++][1] = line[1];*/
            // Valori initiale
            // t = 0
            // k2 = 0
            while (fs.size() > 2)
            {
                int x = orientare(fs[t-k2], fs[t+1-k2], fs[t+2-k2]);
                if (x != 2)
                {
                    /*careLinie2 -=2;
                    sf::Vertex line[]
                        {
                            sf::Vertex(sf::Vector2f(fs[t-k2].first*5 + 400-shiftare, 300 - shiftare -5* fs[t-k2].second)),
                            sf::Vertex(sf::Vector2f(fs[t+2-k2].first*5 + 400-shiftare, 300 - shiftare -5* fs[t+2-k2].second))
                        };
                    linii2[careLinie2][0] = line[0];
                    linii2[careLinie2++][1] = line[1];
*/
                    fs[t+1-k2] = fs[t+2-k2];
                    fs.pop_back();
                    k2++;
                }
                else
                    break;
            }
            t++;
        }// if fs_i >= 0
        fs_i--;
    }// if ii <=n

       /* for(int o = 0; o < careLinie; o++){
            linii[o][0].color = sf::Color::Red;
            linii[o][1].color = sf::Color::Red;
            app2.draw(linii[o], 2, sf::Lines);
        }
        if(ii>=n)
        for(int o = 0; o < careLinie2; o++){
            linii2[o][0].color = sf::Color::Red;
            linii2[o][1].color = sf::Color::Red;
            app2.draw(linii2[o], 2, sf::Lines);
        }

        for(int i=0; i<fi.size(); i++){
            sf::CircleShape cerc2(4);
            cerc2.setFillColor(sf::Color(0, 255, 0));
            cerc2.setPosition(fi[i].first*5 + 400-shiftare, 300 - shiftare -5* fi[i].second);
            app2.draw(cerc2);
        }

        if(ii>=n)
        for(int i=0; i<fs.size(); i++){
            sf::CircleShape cerc2(4);
            cerc2.setFillColor(sf::Color(0, 255, 0));
            cerc2.setPosition(fs[i].first*5 + 400-shiftare, 300 - shiftare -5* fs[i].second);
            app2.draw(cerc2);
        }
*/
        j++;
        // Update the window
/*        app2.display();
        //system("pause");

        sf::Clock clock;
        clock.restart();
        while(clock.getElapsedTime().asSeconds() < asteapta){}

         //if(j == nrcerc+1){
         if(fs[fs.size()-1] == a[0]){
            clock.restart();

            while(clock.getElapsedTime().asSeconds() < 5.0f){}

            app2.close();
         }
    } // While app2 is open

    ShowWindow( GetConsoleWindow(), SW_RESTORE ); */
    }
    for ( pair < int , int > i : fi)
        cout << i.first << " " << i.second << "\n";
    cout << "sup \n";
    for (pair < int, int> i : fs)
        cout << i.first << " "<< i.second << "\n";
    return 0;
}

