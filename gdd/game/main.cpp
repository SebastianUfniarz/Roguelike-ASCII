#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <iomanip>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 20;
bool display_Stats = false;

class Stats {
public:
    int health;
    int attack;
    int strength;
    int dexterity;
    int defense;
    int intelligence;
    int willpower;
    int charisma;

    Stats() : health(100), attack(10), strength(10), dexterity(10), defense(10), intelligence(10), willpower(10), charisma(10) {}
};

class Characters {
public:
    char symbol;
    int x;
    int y;
    bool is_Item;
    std::string name;
    Stats stats;

    bool operator==(const Characters& other) const {
        return (x == other.x) && (y == other.y);
    }

    Characters() : symbol(' '), x(0), y(0), is_Item(false), name("Hero") {}

    Characters(char sym, int x_, int y_, bool item, const std::string& name_)
        : symbol(sym), x(x_), y(y_), is_Item(item), name(name_) {}

};

std::map<std::string, char> symbols = {
    {"Gremlin", 'G'},
    {"Ogre", 'O'},
    {"Shield", 's'},
    {"Potion", 'p'},
    };

void display_Options() {
    std::cout << "Movement options:" << std::endl;
    std::cout << "WSAD - move UP, DOWN, LEFT, RIGHT" << std::endl;
    std::cout << "i - Add item (Enter position (x,y) and item name), r - Remove item" << std::endl;
    std::cout << "n - Add enemy (Enter position (x,y) and enemy name), u - Remove enemy, q - Quit" << std::endl;
    std::cout << "c - Add walls (type in how many)" << std::endl;
    std::cout << "l - Display statistics" << std::endl;
}

void display_Character_Stats_Table(const Characters& character) {
    std::cout << "+--------------------------+" << std::endl;
    std::cout << "| Character Statistics     |" << std::endl;
    std::cout << "+--------------------------+" << std::endl;
    std::cout << "Name: " << character.name << std::endl;
    std::cout << "Symbol: " << character.symbol << std::endl;
    std::cout << "Position: (" << character.x << "," << character.y << ")" << std::endl;
    std::cout << "Stats:" << std::endl;
    std::cout << "  - Health (HP): " << character.stats.health << std::endl;
    std::cout << "  - Attack: " << character.stats.attack << std::endl;
    std::cout << "  - Strength: " << character.stats.strength << std::endl;
    std::cout << "  - Dexterity: " << character.stats.dexterity << std::endl;
    std::cout << "  - Defense: " << character.stats.defense << std::endl;
    std::cout << "  - Intelligence: " << character.stats.intelligence << std::endl;
    std::cout << "  - Willpower: " << character.stats.willpower << std::endl;
    std::cout << "  - Charisma: " << character.stats.charisma << std::endl;
    std::cout << "+--------------------------+" << std::endl;
}

void clear_Screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void generate_Map(char map[HEIGHT][WIDTH], Characters& hero, std::vector<Characters>& enemies, std::vector<Characters>& items) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            map[y][x] = '.';
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        map[y][0] = '|';
        map[y][WIDTH - 1] = '|';
    }
    for (int x = 0; x < WIDTH; x++) {
        map[0][x] = '-';
        map[HEIGHT - 1][x] = '-';
    }

    hero.symbol = '@';
    hero.x = rand() % (WIDTH - 2) + 1;
    hero.y = rand() % (HEIGHT - 2) + 1;
    map[hero.y][hero.x] = hero.symbol;

    const std::string Enemies_Names[] = {"Gremlin", "Ogre"};
    for (const std::string& name : Enemies_Names) {
        Characters enemy;
        enemy.symbol = toupper(name[0]);
        enemy.name = name;
        enemy.stats.health = rand() % 100 + 50;
        do {
            enemy.x = rand() % (WIDTH - 2) + 1;
            enemy.y = rand() % (HEIGHT - 2) + 1;
        } while (map[enemy.y][enemy.x] != '.');
        enemies.push_back(enemy);
        map[enemy.y][enemy.x] = enemy.symbol;
    }

    const std::string Items_Names[] = {"Shield", "Potion"};
    for (const std::string& name : Items_Names) {
        Characters item;
        item.symbol = tolower(name[0]);
        item.name = name;
        item.stats.health = rand() % 50 + 10;
        do {
            item.x = rand() % (WIDTH - 2) + 1;
            item.y = rand() % (HEIGHT - 2) + 1;
        } while (map[item.y][item.x] != '.');
        item.is_Item = true;
        items.push_back(item);
        map[item.y][item.x] = item.symbol;
    }
}

void toggle_Stats_Display() {
    display_Stats = !display_Stats;
}

void print_Map(const char map[HEIGHT][WIDTH], const Characters& hero, const std::vector<Characters>& enemies, const std::vector<Characters>& items) {
    display_Options();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << map[y][x];
        }
        std::cout << std::endl;
    }

    std::cout << "Enemies: ";
    for (const Characters& enemy : enemies) {
        std::cout << enemy.name << "(" << enemy.x << "," << enemy.y << ") ";
    }
    std::cout << std::endl;

    std::cout << "Items: ";
    for (const Characters& item : items) {
        std::cout << item.name << "(" << item.x << "," << item.y << ") ";
    }
    std::cout << std::endl;

    if (display_Stats) {
        display_Character_Stats_Table(hero);
        for (const Characters& enemy : enemies) {
            display_Character_Stats_Table(enemy);
        }
    }
}

void move_Character(char map[HEIGHT][WIDTH], Characters& character, int newX, int newY) {
    if (map[newY][newX] == '.') {
        map[character.y][character.x] = '.';
        character.x = newX;
        character.y = newY;
        map[character.y][character.x] = character.symbol;
    }
}

void add_Item(char map[HEIGHT][WIDTH], std::vector<Characters>& items, int x, int y, const std::string& name) {
    for (const Characters& item : items) {
        if (item.x == x && item.y == y) {
            cout << "This place is already occupied by an item." << std::endl;
            return;
        }

        if (item.is_Item && item.name == name) {
            std::cout << "Found " << name << " at position (" << x << "," << y << ")." << std::endl;
            items.erase(std::remove(items.begin(), items.end(), item), items.end());
            break;
        }
    }
    Characters item;
    item.symbol = tolower(name[0]);
    item.x = x;
    item.y = y;
    item.is_Item = true;
    item.name = name;
    items.push_back(item);
    map[y][x] = item.symbol;
}

void remove_Item(char map[HEIGHT][WIDTH], std::vector<Characters>& items, int x, int y) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].x == x && items[i].y == y) {
            map[y][x] = '.';
            items.erase(items.begin() + i);
            break;
        }
    }
}

void add_Enemy(char map[HEIGHT][WIDTH], std::vector<Characters>& enemies, int x, int y, const std::string& name) {
    for (const Characters& enemy : enemies) {
        if (enemy.x == x && enemy.y == y) {
            std::cout << "This place is already occupied by an enemy." << std::endl;
            return;
        }

        if (!enemy.is_Item && enemy.name == name) {
            std::cout << "Found " << name << " at position (" << x << "," << y << ")." << std::endl;
            enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
            break;
        }
    }

    Characters enemy;
    enemy.symbol = toupper(name[0]);
    enemy.x = x;
    enemy.y = y;
    enemy.name = name;
    enemy.stats.health = rand() % 100 + 50;
    enemies.push_back(enemy);
    map[y][x] = enemy.symbol;
}

void remove_Enemy(char map[HEIGHT][WIDTH], std::vector<Characters>& enemies, int x, int y) {
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].x == x && enemies[i].y == y) {
            map[y][x] = '.';
            enemies.erase(enemies.begin() + i);
            break;
        }
    }
}

void add_Walls(char map[HEIGHT][WIDTH], int count){
    for(int i=0;i<count;i++){
        int x,y;
        do {
            x = rand() % (WIDTH-2)+1;
            y = rand() % (HEIGHT-2)+1;
        } while(map[x][y]!='.');
        map[x][y]='#';
    }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    srand(static_cast<unsigned int>(time(nullptr)));

    char map[HEIGHT][WIDTH];
    Characters hero;
    std::vector<Characters> enemies;
    std::vector<Characters> items;
    generate_Map(map, hero, enemies, items);

    while (true) {
        clear_Screen();
        print_Map(map, hero, enemies, items);

        char input;
        std::cin >> input;

        if (input == 'q' || input == 'Q') {
            std::cout << "Game over." << std::endl;
            break;
        }

        if (input == 'i') {
            int x, y;
            std::string name;
            std::cin >> x >> y >> name;
            add_Item(map, items, x, y, name);
        }
        else if (input == 'r') {
            int x, y;
            std::cin >> x >> y;
            remove_Item(map, items, x, y);
        }
        else if (input == 'n') {
            int x, y;
            std::string name;
            std::cin >> x >> y >> name;
            add_Enemy(map, enemies, x, y, name);
        }
        else if (input == 'u') {
            int x, y;
            std::cin >> x >> y;
            remove_Enemy(map, enemies, x, y);
        }

        else if (input == 'c') {
            int count;
            std::cin >> count;
            add_Walls(map, count);
        }
        else if (input == 'l') {
            display_Character_Stats_Table(hero);
            for (const Characters& enemy : enemies) {
                display_Character_Stats_Table(enemy);
            }
            toggle_Stats_Display();
        }

        int newX = hero.x;
        int newY = hero.y;

        if (input == 'w') {
            newY--;
        }
        else if (input == 's') {
            newY++;
        }
        else if (input == 'a') {
            newX--;
        }
        else if (input == 'd') {
            newX++;
        }

        move_Character(map, hero, newX, newY);

        for (Characters& enemy : enemies) {
            int moveX = rand() % 3 - 1;
            int moveY = rand() % 3 - 1;
            int newX = enemy.x + moveX;
            int newY = enemy.y + moveY;
            move_Character(map, enemy, newX, newY);
        }
    }

    return 0;
}
