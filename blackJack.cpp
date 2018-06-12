#include <iostream>
#include <cstdlib>
#include <ctime>

enum CardRanks
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	MAX_RANK
};

enum CardSuit
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES,
	MAX_SUIT
};


struct Card
{
	CardRanks card_rank;
	CardSuit card_suit;
};

void printCard(const Card &card)
{
	switch(card.card_rank)
	{
		case TWO:
			std::cout << '2';
			break;
		case THREE:
			std::cout << '3';
			break;
		case FOUR:
			std::cout << '4';
			break;
		case FIVE:
			std::cout << '5';
			break;
		case SIX:
			std::cout << '6';
			break;
		case SEVEN:
			std::cout << '7';
			break;
		case EIGHT:
			std::cout << '8';
			break;
		case NINE:
			std::cout << '9';
			break;
		case TEN:
			std::cout << '1';
			break;
		case JACK:
			std::cout << 'J';
			break;
		case QUEEN:
			std::cout << 'Q';
			break;
		case KING:
			std::cout << 'K';
			break;
		case ACE:
			std::cout << 'A';
			break;
		}

	switch(card.card_suit)
	{
		case CLUBS:
			std::cout << "C ";
			break;
		case DIAMONDS:
			std::cout << "D ";
			break;
		case HEARTS:
			std::cout << "H ";
			break;
		case SPADES:
			std::cout << "S ";
			break;
	}
}

void printDeck(Card *card_deck, int length)
{
	for (int i =0; i<length; ++i)
	{
		printCard(card_deck[i]);
	}
}

void swapCard(Card &card1, Card &card2)
{
	CardRanks tempcr = card1.card_rank;
	CardSuit tempcs = card1.card_suit;
	card1.card_rank = card2.card_rank;
	card1.card_suit = card2.card_suit;
	card2.card_rank = tempcr;
	card2.card_suit = tempcs;
}

int generateRandomInt(int a, int b)
{
	double factor = static_cast<double> (rand() + 1)/ (static_cast<double>(RAND_MAX) + 1);
	int result = static_cast<int> (a + ((b - a + 1)*factor));
}

void shuffleDeck(Card *card_deck,int length)
{
	for (int i = 0; i< length; ++i)
	{
		int rand = generateRandomInt(0,51);
		swapCard(card_deck[i],card_deck[rand]);
	}
}

int getCardValue(const Card &card)
{
	switch(card.card_rank)
	{
		case TWO:
			return 2;
		case THREE:
			return 3;
		case FOUR:
			return 4;
		case FIVE:
			return 5;
		case SIX:
			return 6;
		case SEVEN:
			return 7;
		case EIGHT:
			return 8;
		case NINE:
			return 9;
		case TEN:
		case JACK:
		case QUEEN:
		case KING:
			return 10;
		case ACE:
			return 11;
	}
}

int playBlackjack(const Card *card_deck)
{
	int curr_deck_num(0);
	curr_deck_num++;
	int dealer_score(0);
	int player_score(0);
	std::cout << "Dealing now: " << '\n';
	std::cout << "Dealer card: " ;
	printCard(card_deck[curr_deck_num]);
	std::cout << '\n';
	dealer_score += getCardValue(card_deck[curr_deck_num]);
	std::cout << "Dealer score: " << dealer_score << '\n';
	curr_deck_num++;
	std::cout << "Your cards: ";
	printCard(card_deck[curr_deck_num]);
	player_score += getCardValue(card_deck[curr_deck_num]);
	curr_deck_num++;
	printCard(card_deck[curr_deck_num]);
	std::cout << '\n';
	player_score += getCardValue(card_deck[curr_deck_num]);
	curr_deck_num++;
	std::cout << "Your score: " << player_score << '\n';
	std::cout << "Let's start!!!" << '\n';
	bool isplay(true);
	while (isplay)
	{
		char call;
		std::cout << "Press 'H' for hit or 'S' for Stand ";
		std::cin >> call;
		if (call == 'S')
			isplay = false;
		else if(call == 'H')
		{
			std::cout << "Your card: ";
			printCard(card_deck[curr_deck_num]);
			std::cout << '\n';
			player_score += getCardValue(card_deck[curr_deck_num]);
			std::cout << "Your score: " << player_score << "\n";
			curr_deck_num++;
		}
		else
		{
			std::cout << "Please enter correct value" << '\n';
			continue;
		}
		if (player_score == 21)
			isplay = false;
		if (player_score > 21)
			return 2;
	}
	isplay = true;
	std::cout << "Dealer's turn" << '\n';
	while (isplay)
	{
		std::cout << "Dealer's card: ";
		printCard(card_deck[curr_deck_num]);
		std::cout << '\n';
		dealer_score += getCardValue(card_deck[curr_deck_num]);
		std::cout << "Dealer's score: " << dealer_score << '\n';
		curr_deck_num++;
		if (dealer_score >= 17)
			isplay = false;
		if (dealer_score > 21)
			return 1;
	}

	if (player_score >  dealer_score)
		return 1;
	else if (player_score < dealer_score)
		return 2;
	else
		return 3;
}

int main()
{
	Card card_deck[52];
	int card_num = 0;
	for (int i =0; i < MAX_RANK;++i)
	{
		for (int j =0; j < MAX_SUIT; ++j)
		{
			card_deck[card_num].card_rank = static_cast<CardRanks> (i);
			card_deck[card_num].card_suit = static_cast<CardSuit> (j);
			card_num++;
		}
	}
	std::srand(static_cast<unsigned int> (time(0)));
	std::cout << "Original Deck: " << '\n';
	printDeck(card_deck,52);
	std::cout << '\n';
	//std::cout << "Shuffled deck: " << '\n';
	//shuffleDeck(card_deck,52);
	//printDeck(card_deck,52);
	std::cout << "Deck is shuffled" ;
	std::cout << '\n';
	int game_result = playBlackjack(card_deck);
	if (game_result == 1)
		std::cout << "You win! Lets party " << '\n';
	else if (game_result == 2)
		std::cout << "You lose!!" << '\n';
	else
		std::cout << "Game drawn" << '\n';

	return 0;
}
