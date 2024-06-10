#include <iostream>
#include <memory>

struct Player
{
//   std::shared_ptr<Player> companion;

    std::weak_ptr<Player> companion; // убираем утечку памяти с shared_ptr
    ~Player() { std::cout << "~Player\n"; }
};

int main()
{
    std::shared_ptr<Player> jasmine = std::make_shared<Player>();
    std::shared_ptr<Player> albert  = std::make_shared<Player>();

    jasmine->companion = albert; // (1)
    albert->companion  = jasmine; // (2)

    std::cout << jasmine.use_count() << std::endl;
    return 0;
}