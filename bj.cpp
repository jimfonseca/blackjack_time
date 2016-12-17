#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include <unistd.h>
using namespace std;


int main()
{

  srand (time(NULL));
  
  int init_dollars = 300;
  int dollars_per_hand = 10;
  int player_dollars = init_dollars;

//http://wizardofodds.com/ask-the-wizard/blackjack/probability/
//According to my blackjack appendix 4, the probability of an overall win in blackjack is 42.22%, a tie is 8.48%, and a loss is 49.10%. 
  float house_odds = 0.49;
  float tie_odds = 0.08;

  int number_of_hands = 0;
  float number_of_hands_running_average = 0;
  int worst_number_of_hands = 100000;
  int best_number_of_hands = 0;
  int games = 0;
  double myrand;
  int max_dollars = init_dollars; 
  int max_hand = 0; 
  
  float max_hand_average = 0; 
  
  int output_level = 1;

  while (true)
  {
    games++;  
	while (player_dollars >= dollars_per_hand)
	{
	  //keep em coming
	  number_of_hands++;
	  myrand = ((double) rand() / (RAND_MAX));
      if (output_level == 0)
      { 
        sleep(1);
        cout << number_of_hands << ":\t" << std::fixed << std::setprecision( 4 ) << std::setfill( '0' ) << myrand << "\t"; 
	  }
	  if (myrand < house_odds)
	  {
		//house wins
		player_dollars = player_dollars - dollars_per_hand;  
        if (output_level == 0)
        { 
     	  cout << " lose\t" << player_dollars << "  " << max_dollars << endl;
     	}
	  }
	  else if (myrand > (house_odds+tie_odds))
	  {
		//winnah!
		player_dollars = player_dollars + dollars_per_hand;
        if (output_level == 0)
        { 
          cout << " win\t" << player_dollars << "  " << max_dollars << endl;
        }
        if (player_dollars > max_dollars)
        {
          max_dollars = player_dollars;
          max_hand = number_of_hands;
        }
	  }
	  else
	  {
		//tie
        if (output_level == 0)
        { 
  	      cout << " tie\t" << player_dollars << "  " << max_dollars << endl;
  	    }
	  }      
	}
    //busted

	number_of_hands_running_average = (number_of_hands_running_average*(games-1) + number_of_hands)/games;

	max_hand_average = (max_hand_average*(games-1) + max_hand)/games;


    if (number_of_hands < worst_number_of_hands)
    {
      worst_number_of_hands = number_of_hands;
    }
    
    if (number_of_hands > best_number_of_hands)
    {
      best_number_of_hands = number_of_hands;
    }
    
    if (output_level <=1)
    { 
      cout << "Game" << games << "\t" << max_hand << "\t" << max_hand_average << "\tBusted! after\t" << number_of_hands << " hands\t" << "Running Avg:\t" << number_of_hands_running_average << "\tBest\t" << best_number_of_hands << "\tWorst\t" << worst_number_of_hands << "\tmaxD\t" << max_dollars << endl;
    }
	number_of_hands = 0;
    player_dollars = init_dollars;
    max_dollars = init_dollars;
    max_hand = 0; 

//  sleep (0);    
  } 

  
}

