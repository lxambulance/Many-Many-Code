#include <stdlib.h>
#include <cstdio>
#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

#ifdef DEBUG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

const int LOCOMOTIVE_CARDS_TOTAL_COUNT = 14;
const int SIMPLE_CARDS_TOTAL_COUNT = 12;
const int COLORS_COUNT = 8;
const char colors[COLORS_COUNT][50] = {"purple", "blue", "orange", "white", "green", "yellow", "black", "red"};
#define LOCOMOTIVE_COLOR COLORS_COUNT
#define IS_LOCOMOTIVE(color) ((color) == LOCOMOTIVE_COLOR)

int parseColor(const char * color_name, const char * locomotive_color_name) {
  if (!strcmp(color_name, locomotive_color_name)) {
    return LOCOMOTIVE_COLOR;
  }
  int i = 0;
  while (i < COLORS_COUNT && strcmp(color_name, colors[i])) {
    ++i;
  }
  if (i == COLORS_COUNT) {
    fprintf(stderr, "Unknown color '%s'\n", color_name);
    assert(0);
  }
  return i;
}

int parseRoadColor(const char * color_name) {
  return parseColor(color_name, "any");
}

int parseCardColor(const char * color_name) {
  return parseColor(color_name, "locomotive");
}

int readCardColor() {
  static char color[50];
  assert(scanf("%s", color) == 1);
  return parseCardColor(color);
}

class Deck {
public:
  class Card {
  private:
    Deck *deck;
    int number;
  public:
    Card(Deck *deck, int number)
      : deck(deck), number(number) {}

    Deck* getDeck() const {
      return deck;
    }

    int getColor() const {
      return deck->getCardColor(number);
    }

    bool wasViewedByPlayer(int player_num) const {
      return deck->cardWasViewedByPlayer(player_num, number);
    }

    void markAsViewedByPlayer(int player_num) const {
      return deck->markCardAsViewedByPlayer(player_num, number);
    }

    void markAsViewedPublic() const {
      return deck->markCardAsViewedPublic(number);
    }
  };

private:
  class DeckObserver {
  private:
    int count_not_viewed[COLORS_COUNT + 1];
    vector <bool> was_viewed;
  public:
    DeckObserver(const vector <int> & card_colors) : was_viewed(card_colors.size(), false) {
      memset(count_not_viewed, 0, sizeof(count_not_viewed));
      for (int color : card_colors) {
        count_not_viewed[color]++;
      }
    }

    void markCardAsViewed(int number, int color) {
      assert(0 <= number && number < int(was_viewed.size()));
      if (!was_viewed[number]) {
        was_viewed[number] = true;
        count_not_viewed[color]--;
        assert(count_not_viewed[color] >= 0);
      }
    }

    bool cardWasViewed(int number) const {
      assert(0 <= number && number < int(was_viewed.size()));
      return was_viewed[number];
    }

    int getCountNotViewed(int color) const {
      return count_not_viewed[color];
    }
  };

  int total_cards_count;
  vector <int> card_colors;
  int count_not_used[COLORS_COUNT + 1];
  vector <DeckObserver> observers;

public:
  Deck(int players_count, const vector <int> & card_colors_not_shuffled)
    : total_cards_count(card_colors_not_shuffled.size()),
      observers(players_count, DeckObserver(card_colors_not_shuffled)) {
    card_colors.reserve(card_colors_not_shuffled.size());
    memset(count_not_used, 0, sizeof(count_not_used));
    for (int color : card_colors_not_shuffled) {
      count_not_used[color]++;
    }
  }

  int getCardColor(int number) {
    assert(0 <= number && number < int(card_colors.size()));
    return card_colors[number];
  }

  bool isEmpty() const {
    return int(card_colors.size()) == total_cards_count;
  }

  Card takeTopCard() {
    assert(!isEmpty());
    int color = readCardColor();
    assert(count_not_used[color] > 0);
    count_not_used[color]--;
    int card_number = (int)card_colors.size();
    card_colors.push_back(color);
    return Card(this, card_number);
  }

  void markCardAsViewedByPlayer(int player_num, int number) {
    assert(0 <= player_num && player_num < int(observers.size()));
    observers[player_num].markCardAsViewed(number, getCardColor(number));
  }

  void markCardAsViewedPublic(int number) {
    int color = getCardColor(number);
    for (DeckObserver & observer : observers) {
      observer.markCardAsViewed(number, color);
    }
  }

  bool cardWasViewedByPlayer(int player_num, int number) {
    assert(0 <= player_num && player_num < int(observers.size()));
    return observers[player_num].cardWasViewed(number);
  }

  int getCountNotViewedByPlayer(int player_num, int color) {
    assert(0 <= player_num && player_num < int(observers.size()));
    return observers[player_num].getCountNotViewed(color);
  }
};

class Player {
private:
  vector <Deck::Card> hand_cards;

public:

  void putCardInHand(const Deck::Card & card) {
    hand_cards.push_back(card);
  }

  void playCards(const vector <int> & numbers, vector <Deck::Card> & cards) {
    assert(0 <= numbers[0]);
    for (int i = 1; i < int(numbers.size()); ++i) {
      assert(numbers[i - 1] < numbers[i]);
    }
    assert(numbers.back() < int(hand_cards.size()));
    cards.clear();
    cards.reserve(numbers.size());
    vector <Deck::Card> new_hand_cards;
    new_hand_cards.reserve(hand_cards.size() - numbers.size());
    int i = 0, j = 0;
    for (const Deck::Card & card : hand_cards) {
      if (j < int(numbers.size()) && i == numbers[j]) {
        cards.push_back(card);
        ++j;
      } else {
        new_hand_cards.push_back(card);
      }
      ++i;
    }
    hand_cards.swap(new_hand_cards);
  }

  int getKnownCardsCountFor(int player_num, int color) {
    int cards_count = 0;
    for (const Deck::Card & card : hand_cards) {
      if (card.wasViewedByPlayer(player_num) && card.getColor() == color) {
        cards_count++;
      }
    }
    return cards_count;
  }

  void getUnknownCardsCountFor(int player_num, map <Deck*, int> & unknown_cards_count) {
    unknown_cards_count.clear();
    for (const Deck::Card & card : hand_cards) {
      if (!card.wasViewedByPlayer(player_num)) {
        unknown_cards_count[card.getDeck()]++;
      }
    }
  }

  void debugPrint() {
    for (const Deck::Card & card : hand_cards) {
      dbg("%d ", card.getColor());
    }
    dbg("\n");
  }
};

class Game {
private:
  static const int FACE_UP_CARDS_COUNT = 5;

  int cur_player_number;
  int cur_drawn_cards;
  vector < shared_ptr <Deck> > decks;
  vector <Player> players;
  vector <Deck::Card> face_up_cards;
  vector <int> trash_colors;

public:
  Game(int cnt_players)
    : cur_player_number(0),
      cur_drawn_cards(0),
      players(cnt_players) {
    for (int i = 0; i < LOCOMOTIVE_CARDS_TOTAL_COUNT; ++i) {
      trash_colors.push_back(LOCOMOTIVE_COLOR);
    }
    for (int i = 0; i < COLORS_COUNT; ++i) {
      for (int j = 0; j < SIMPLE_CARDS_TOTAL_COUNT; ++j) {
        trash_colors.push_back(i);
      }
    }
    shuffleTrash();

    for (int i = 0; i < FACE_UP_CARDS_COUNT; ++i) {
      face_up_cards.push_back(takeTopCard());
      face_up_cards.back().markAsViewedPublic();
    }
    rebuildFaceUpCardsIfNeed();
  }

  void drawBlind() {
    dbg("%d: draw blind\n", cur_player_number);
    Deck::Card card = takeTopCard();
    players[cur_player_number].putCardInHand(card);
    card.markAsViewedByPlayer(cur_player_number);
    cur_drawn_cards++;
    if (cur_drawn_cards == 2) {
      cur_drawn_cards = 0;
      moveToNextPlayer();
    }
  }

  void drawFaceUp(int num) {
    dbg("%d: draw face up %d\n", cur_player_number, num);
    assert(0 <= num && num < FACE_UP_CARDS_COUNT);
    Deck::Card drawn_card = face_up_cards[num];
    if (IS_LOCOMOTIVE(drawn_card.getColor())) {
      assert(cur_drawn_cards == 0);
      cur_drawn_cards = 1;
    }
    players[cur_player_number].putCardInHand(drawn_card);
    face_up_cards[num] = takeTopCard();
    face_up_cards[num].markAsViewedPublic();
    rebuildFaceUpCardsIfNeed();
    cur_drawn_cards++;
    if (cur_drawn_cards == 2) {
      cur_drawn_cards = 0;
      moveToNextPlayer();
    }
  }

  void claimRoute(int need_color, int need_locomotives, const vector <int> & played_card_numbers) {
    dbg("%d: claim route (color %d length %d locomotives %d)\n", cur_player_number, need_color, int(played_card_numbers.size()), need_locomotives);
    assert(cur_drawn_cards == 0);
    vector <Deck::Card> played_cards;
    players[cur_player_number].playCards(played_card_numbers, played_cards);
    int locomotives_count = 0;
    int color = LOCOMOTIVE_COLOR;
    for (const Deck::Card & card : played_cards) {
      if (IS_LOCOMOTIVE(card.getColor())) {
        locomotives_count++;
      } else {
        if (IS_LOCOMOTIVE(color)) {
          color = card.getColor();
        } else {
          assert(color == card.getColor());
        }
      }
      card.markAsViewedPublic();
      trash_colors.push_back(card.getColor());
    }
    dbg("color = %d, need_color = %d\n", color, need_color);
    assert(locomotives_count >= need_locomotives);
    assert(IS_LOCOMOTIVE(color) || IS_LOCOMOTIVE(need_color) || need_color == color);
    moveToNextPlayer();
  }

  bool guessClaimRoute(int player_num, int color, int length, int need_locomotives) {
    if (IS_LOCOMOTIVE(color)) {
      for (int i = 0; i < COLORS_COUNT; ++i) {
        if (guessClaimRoute(player_num, i, length, need_locomotives)) {
          return true;
        }
      }
      return false;
    }

    dbg("%d: guess claim route (player_num %d color %d length %d locomotives %d)\n", cur_player_number, player_num, color, length, need_locomotives);
    assert(0 <= player_num && player_num < int(players.size()));

    Player & player = players[player_num];
    int color_cards = player.getKnownCardsCountFor(cur_player_number, color);
    int locomotive_cards = player.getKnownCardsCountFor(cur_player_number, LOCOMOTIVE_COLOR);

    players[0].debugPrint();
    players[1].debugPrint();

    //dbg("locomotive_cards %d color_cards %d\n", locomotive_cards, color_cards);
    
    map <Deck*, int> unknown_cards_count;
    player.getUnknownCardsCountFor(cur_player_number, unknown_cards_count);
    for (const pair <Deck*, int> & kvp : unknown_cards_count) {
      Deck *cur_deck = kvp.first;
      int cur_count = kvp.second;
      int max_locomotive_cards = cur_deck->getCountNotViewedByPlayer(cur_player_number, LOCOMOTIVE_COLOR);
      int max_color_cards = cur_deck->getCountNotViewedByPlayer(cur_player_number, color);

      int x = min(cur_count, max_locomotive_cards);
      cur_count -= x;
      locomotive_cards += x;

      x = min(cur_count, max_color_cards);
      cur_count -= x;
      color_cards += x;
    }

    dbg("locomotive_cards %d color_cards %d\n", locomotive_cards, color_cards);
    return locomotive_cards >= need_locomotives && locomotive_cards + color_cards >= length;
  }

private:
  Deck::Card takeTopCard() {
    assert(!decks.empty());
    Deck::Card card = decks.back()->takeTopCard();
    //dbg("Taken %d(%s)\n", card.getColor(), colors[card.getColor()]);
    if (decks.back()->isEmpty()) {
      shuffleTrash();
    }
    return card;
  }

  void moveToNextPlayer() {
    cur_player_number = (cur_player_number + 1) % int(players.size());
  }

  void rebuildFaceUpCardsIfNeed() {
    while (1) {
      int count_face_up_locomotives = 0;
      for (const Deck::Card & card : face_up_cards) {
        if (IS_LOCOMOTIVE(card.getColor())) {
          ++count_face_up_locomotives;
        }
      }
      if (count_face_up_locomotives < 3) {
        break;
      }
      dbg("%d locomotives faced up!\n", count_face_up_locomotives);
      for (const Deck::Card & card : face_up_cards) {
        trash_colors.push_back(card.getColor());
      }
      for (int i = 0; i < FACE_UP_CARDS_COUNT; ++i) {
        face_up_cards[i] = takeTopCard();
        face_up_cards[i].markAsViewedPublic();
      }
    }
  }

  void shuffleTrash() {
    dbg("deck is empty: shuffle trash\n");
    decks.push_back(make_shared<Deck>(int(players.size()), trash_colors));
    trash_colors.clear();
  }
};

inline void skipToken(const char * expected_token) {
  static char token[50];
  assert(scanf("%s", token) == 1);
  if (strcmp(token, expected_token)) {
    fprintf(stderr, "Exptected token '%s', found '%s'\n", expected_token, token);
    assert(0);
  }
}

int main() {
#ifndef NOFILES
  freopen("ttr.in", "r", stdin);
  freopen("ttr.out", "w", stdout);
#endif

  int n;
  assert(scanf("%d%*d", &n) == 1);
  static char token[50];
  assert(scanf("%s", token) == 1 && !strcmp(token, "open"));
  Game game(n);
  int line = 2, guessed = 0;
  while (scanf("%s", token) == 1) {
    if (!strcmp(token, "take")) {
      assert(scanf("%s", token) == 1);
      if (!strcmp(token, "blind")) {
        game.drawBlind();
      } else if ('1' <= token[0] && token[0] <= '5' && token[1] == '\0') {
        game.drawFaceUp(token[0] - '1');
      } else {
        fprintf(stderr, "Unknown drawing description '%s'\n", token);
        assert(0);
      }
    } else if (!strcmp(token, "build")) {
      assert(scanf("%s", token) == 1);
      int color;
      int length, need_locomotives;
      if (!strcmp(token, "ferry")) {
        color = LOCOMOTIVE_COLOR;
        assert(scanf("%d %d", &length, &need_locomotives) == 2);
        assert(1 <= need_locomotives && need_locomotives <= length);
      } else {
        color = parseRoadColor(token);
        assert(scanf("%d", &length) == 1);
        need_locomotives = 0;
      }
      vector <int> cards(length);
      for (int i = 0; i < length; ++i) {
        assert(scanf("%d", &cards[i]) == 1);
        --cards[i];
      }
      game.claimRoute(color, need_locomotives, cards);
    } else if (!strcmp(token, "?")) {
      int player;
      assert(scanf("%d", &player) == 1);
      --player;
      
      assert(scanf("%s", token) == 1);
      int color;
      int length, need_locomotives;
      if (!strcmp(token, "ferry")) {
        color = LOCOMOTIVE_COLOR;
        assert(scanf("%d %d", &length, &need_locomotives) == 2);
        assert(1 <= need_locomotives && need_locomotives <= length);
      } else {
        color = parseRoadColor(token);
        assert(scanf("%d", &length) == 1);
        need_locomotives = 0;
      }
      printf("%s\n", game.guessClaimRoute(player, color, length, need_locomotives) ? "Maybe" : "No");
      ++guessed;
    } else {
      fprintf(stderr, "Unknown command '%s'\n", token);
      assert(0);
    }
    ++line;
  }

  return 0;
}
