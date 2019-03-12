#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif
#include <windows.h>

using namespace std;


int orientare(pair<int, int> p, pair<int, int> q, pair<int, int> r)
{
	int val = (q.second - p.second) * (r.first - q.first)
		- (q.first - p.first) * (r.second - q.second);
	if (val == 0)
	{
		return 0;
	}
	return (val > 0) ? 2 : 1; // 2 left
}

bool cmp(pair<int, int> p, pair<int, int> q){
    if(p.first < q.first)
        return 1;
    else if(p.first == q.first)
        return p.second < q.second;
    else
        return 0;
}

int main()
{
    ifstream f("date.in");
	int n=0;
	int k = 0, k2=0;
	int t=0;
	int ii=2;
	int j = 0;
	int careLinie = 0;
	int careLinie2 = 0;

	//f >> n;


    float shiftare = 0.5 * 5;
    float asteapta;

	int x, y;
	vector<pair<int, int> > a;
	/*for (int i = 0; i < n; i++)
	{
		f >> x >> y;
		a.push_back(make_pair(x, y));
	}*/
	f.close();

	cout << "Please choose the points! (Press ENTER to continue)";
    cin.get();

    sf::RenderWindow app(sf::VideoMode(800, 600), "Press ESCAPE/ENTER to continue");

    ShowWindow( GetConsoleWindow(), SW_HIDE );

    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
                {
                    ShowWindow( GetConsoleWindow(), SW_RESTORE );

                    cout << "Now that we chose the points/Acum ca am ales punctele: \n";
                    app.close();
                }

            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    a.push_back(make_pair(event.mouseButton.x, event.mouseButton.y));
                    n++;
                }
            }

        }

        // Clear screen
        app.clear();


        for(int i=0; i<n; i++){
            sf::CircleShape cerc3(3);
            cerc3.setPosition(a[i].first , a[i].second);
            app.draw(cerc3);
        }

        app.display();
    }

    sort(a.begin(), a.end(), cmp);
//    for(int i=0; i<n; i++)
//        cout << a[i].first << " " << a[i].second << endl;

    int fs_i = n-3;
    vector<pair<int, int> > fi;   /// ACOPERIREA INFERIOARA
	fi.push_back(a[0]);
	fi.push_back(a[1]);

	vector<pair<int, int> > fs;   /// ACOPERIREA SUPERIOARA
	fs.push_back(a[n-1]);
	fs.push_back(a[n-2]);



    sf::Vertex linii[n][2];
    sf::Vertex linii2[n][2];

    sf::Vertex line[]{
        sf::Vertex(sf::Vector2f(fi[0].first, fi[0].second)),
        sf::Vertex(sf::Vector2f(fi[1].first, fi[1].second))
    };
    linii[careLinie][0] = line[0];
    linii[careLinie++][1] = line[1];

    sf::Vertex line2[]{
        sf::Vertex(sf::Vector2f(fs[0].first, fs[0].second)),
        sf::Vertex(sf::Vector2f(fs[1].first, fs[1].second))
    };
    linii2[careLinie2][0] = line2[0];
    linii2[careLinie2++][1] = line2[1];


    cout << "Choose seconds between steps/Alege cate secunde sa astepti intre pasi: ";
    cin >> asteapta;

    ShowWindow( GetConsoleWindow(), SW_HIDE );




    sf::RenderWindow app2(sf::VideoMode(800, 600), "Press ESCAPE to Exit!");

    while (app2.isOpen())
    {
        // Process events
        sf::Event event;
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
            cerc3.setPosition(a[i].first, a[i].second);
            app2.draw(cerc3);
        }


	if(ii<n){
	    if(j<n){
            fi.push_back(a[ii]);

             sf::Vertex line[]{
                    sf::Vertex(sf::Vector2f(fi[ii - k - 1].first, fi[ii - k - 1].second)),
                    sf::Vertex(sf::Vector2f(fi[ii - k].first, fi[ii - k].second))
                };
                linii[careLinie][0] = line[0];
                linii[careLinie++][1] = line[1];

            while (fi.size() > 2)
            {
                int x = orientare(fi[ii - 2 - k], fi[ii - k - 1], fi[ii - k]);

                if (x != 2)
                {
                    careLinie -=2;
                    sf::Vertex line[]{
                        sf::Vertex(sf::Vector2f(fi[ii - 2 - k].first, fi[ii - 2 - k].second)),
                        sf::Vertex(sf::Vector2f(fi[ii - k].first, fi[ii - k].second))
                    };
                    linii[careLinie][0] = line[0];
                    linii[careLinie++][1] = line[1];

                    fi[ii - k - 1] = fi[ii - k];

                    fi.pop_back();
                    k++;
                }
                else
                    break;
            }
	    }
	}

    ii++;

        if(ii>=n){
            if(fs_i >= 0){
                fs.push_back(a[fs_i]);
                    sf::Vertex line[]{
                        sf::Vertex(sf::Vector2f(fs[t+1-k2].first, fs[t+1-k2].second)),
                        sf::Vertex(sf::Vector2f(fs[t+2-k2].first, fs[t+2-k2].second))
                    };
                    linii2[careLinie2][0] = line[0];
                    linii2[careLinie2++][1] = line[1];

                while (fs.size() > 2)
                {
                    int x = orientare(fs[t-k2], fs[t+1-k2], fs[t+2-k2]);
                    if (x != 2)
                    {
                        careLinie2 -=2;
                        sf::Vertex line[]{
                            sf::Vertex(sf::Vector2f(fs[t-k2].first, fs[t-k2].second)),
                            sf::Vertex(sf::Vector2f(fs[t+2-k2].first, fs[t+2-k2].second))
                        };
                        linii2[careLinie2][0] = line[0];
                        linii2[careLinie2++][1] = line[1];

                        fs[t+1-k2] = fs[t+2-k2];
                        fs.pop_back();
                        k2++;
                    }
                    else
                        break;
                }
                t++;
            }
            fs_i--;
        }

        for(int o = 0; o < careLinie; o++){
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
            cerc2.setPosition(fi[i].first, fi[i].second);
            app2.draw(cerc2);
        }

        if(ii>=n)
        for(int i=0; i<fs.size(); i++){
            sf::CircleShape cerc2(4);
            cerc2.setFillColor(sf::Color(0, 255, 0));
            cerc2.setPosition(fs[i].first, fs[i].second);
            app2.draw(cerc2);
        }

        j++;
        // Update the window
        app2.display();
        //system("pause");

        if(fs[fs.size()-1] != a[0]){
            sf::Clock clock;
            clock.restart();
            while(clock.getElapsedTime().asSeconds() < asteapta){}
        }
         //if(j == nrcerc+1){
         /*if(fs[fs.size()-1] == a[0]){
            clock.restart();

            while(clock.getElapsedTime().asSeconds() < 5.0f){}
           // wait = true;
            app2.close();
         }*/
    }

    ShowWindow( GetConsoleWindow(), SW_RESTORE );
    return EXIT_SUCCESS;
}

