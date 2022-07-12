#include <string>
#include <stack>
#include <deque>
#include <iostream>
#include <sstream>

//#define GTEST
typedef std::vector< std::deque< int > > State;
class Game
{
public:
    Game(std::deque< int > &hand)
        : hand_(hand)
    {
        init();
    };

public:
    void init();
    bool record();
    bool check(std::deque< int > &);
    int place(int &pos);
    std::string game_result();

private:
    std::deque< int > hand_;
    std::deque< int > pile_[7];
    std::map< State, bool > hand_record;
};

void Game::init()
{
    for (int i = 0; i < 7; i++)
        pile_[i].push_back(hand_.front()), hand_.pop_front();
    record();
}

bool Game::record()
{
    State tmp;
    tmp.push_back(hand_);
    for (int i = 0; i < 7; i++)
        tmp.push_back(pile_[i]);
    if (hand_record[tmp])
        return false;
    hand_record[tmp] = true;
    return true;
}

bool Game::check(std::deque< int > &q)
{
    if (q.size() < 3)
        return false;
    int first = q.front(), last = q.back();
    q.pop_front(), q.pop_back();
    if (first + q.front() + last == 10 || first + q.front() + last == 20 || first + q.front() + last == 30) {
        hand_.push_back(first);
        hand_.push_back(q.front());
        hand_.push_back(last);
        q.pop_front();
        return true;
    }
    if (first + q.back() + last == 10 || first + q.back() + last == 20 || first + q.back() + last == 30) {
        hand_.push_back(first);
        hand_.push_back(q.back());
        hand_.push_back(last);
        q.pop_back();
        return true;
    }
    q.push_front(first);
    first = q.back();
    q.pop_back();

    if (first + q.back() + last == 10 || first + q.back() + last == 20 || first + q.back() + last == 30) {
        hand_.push_back(q.back());
        hand_.push_back(first);
        hand_.push_back(last);
        q.pop_back();
        return true;
    }
    q.push_back(first), q.push_back(last);
    return false;
}

int Game::place(int &pos)
{
    while (pile_[pos].empty())
        pos = (pos + 1) % 7;
    pile_[pos].push_back(hand_.front()), hand_.pop_front();

    if (!record())
        return -1;

    while (check(pile_[pos]))
        ;

    if (hand_.empty())
        return 0;

    return 1;
}

std::string Game::game_result()
{
    std::string result;
    int times = 7, pos = 0;
    while (1) {

        if (hand_.size() == 52) {
            result = "Win : ";
            break;
        }
        int c = place(pos);

        if (c == -1) {
            result = "Draw: ";
            break;
        } else if (!c) {
            times++;
            result = "Loss: ";
            break;
        }
        ++times, pos = (pos + 1) % 7;
    }
    result += std::to_string(times);

    result += "\n";
    return result;
}

void uva246(std::istream &is, std::ostream &os)
{
    int number;
    while ((is >> number) && number) {
        std::deque< int > hand;
        hand.push_back(number);

        for (int i = 0; i < 51; i++) {
            is >> number;
            hand.push_back(number);
        }

        Game game(hand);
        os << game.game_result();

        hand.clear();
    }
}

int main(int argc, char **argv)
{

#ifdef GTEST
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    uva246(std::cin, std::cout);
#endif
    return 0;
}
