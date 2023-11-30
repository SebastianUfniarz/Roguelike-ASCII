#include <algorithm>
#include <iostream>
#include <vector>

class Item {
public:
    char symbol;
    std::string name;
    int x;
    int y;

    Item(char sym, const std::string& name_, int x_, int y_) : symbol(sym), name(name_), x(x_), y(y_) {}
};

class Field {
public:
    char symbol;
    int x;
    int y;
    std::vector<Item> items;

    Field(char sym, int x_, int y_) : symbol(sym), x(x_), y(y_) {}

    virtual ~Field() {}

    virtual void display() const {
        if (!items.empty()) {
            std::cout << items.back().symbol;
        } else {
            std::cout << symbol;
        }
    }

    virtual bool isPassable() const {
        return true;
    }
};

class CharacterStats {
public:
    int health;
    int strength;
    int dexterity;
    int intelligence;
    int wisdom;
    int mana;
    int proficiency;
    int armor;

    int evasionCount;  // Licznik uników
    int criticalStrikeCount;  // Licznik ciosów krytycznych

       CharacterStats(int health_, int strength_, int dexterity_, int intelligence_,
                      int wisdom_, int mana_, int proficiency_, int armor_)
           : health(health_), strength(strength_), dexterity(dexterity_),
             intelligence(intelligence_), wisdom(wisdom_), mana(mana_),
             proficiency(proficiency_), armor(armor_), evasionCount(0), criticalStrikeCount(0) {}
};
CharacterStats generateRandomStatsForEnemy(const std::string& enemyName) {
    int health = 0, strength = 0, dexterity = 0, intelligence = 0, wisdom= 0, mana = 0, proficiency = 0, armor=0;

    if (enemyName == "Rat") {
            health = rand() % 21 + 30;
            strength = 5;
            dexterity = rand() % 11 + 10;
            intelligence = 5;
            wisdom = 5;
            mana = 100;
            proficiency = rand() % 6 + 5;
            armor = 0;
        }
        else if (enemyName == "Goblin") {
            health = rand() % 31 + 30;
            strength = rand() % 6 + 5;
            dexterity = rand() % 16 + 15;
            intelligence = 5;
            wisdom = rand() % 6 + 5;
            mana = 100;
            proficiency = rand() % 11 + 10;
            armor = 5;
        }
        else if (enemyName == "Ogre") {
            health = rand() % 41 + 80;
            strength = rand() % 21 + 10;
            dexterity = 5;
            intelligence = 5;
            wisdom = 5;
            mana = 100;
            proficiency = rand() % 16 + 15;
            armor = 5;
        }
        else if (enemyName == "hero") {
            health = rand() % 31 + 40;
            strength = rand() % 11 + 10;
            dexterity = rand() % 11 + 10;
            intelligence = rand() % 6 + 5;
            wisdom = rand() % 6 + 5;
            mana = 100;
            proficiency = rand() % 21 + 20;
            armor = 10;
        }

    return CharacterStats(health, strength, dexterity, intelligence, wisdom, mana, proficiency, armor);
}
class Character : public Field {
public:
    bool is_Item;
    std::string name;
    CharacterStats stats;

    Character(char sym, int x_, int y_, bool item, const std::string& name_, const CharacterStats& stats_)
        : Field(sym, x_, y_), is_Item(item), name(name_), stats(stats_) {}

    virtual void display() const override {
        std::cout << symbol;
    }

    virtual bool isPassable() const override {
        return false;
    }

    void receiveDamage(int damage) {
        stats.health -= damage;
        if (stats.health < 0) {
            stats.health = 0;
        }
    }

    float calculateDamageReduction(const Character& enemy) const {
            const float armorHardness = 50.0;
            return enemy.stats.armor / (enemy.stats.armor + armorHardness);
        }

    void heal(int healingPoints) {
        stats.health += healingPoints;
        if (stats.health > 100) {
            stats.health = 100;
        }
    }

    int getHealth() const {
        return stats.health;
    }

    bool isAlive() const {
        return stats.health > 0;
    }

    bool evadeAttack() {

        int maxEvasionChance = 50;
        int baseEvasionChance = 2;
        int evasionChance = std::min(stats.dexterity, maxEvasionChance);

        if (stats.dexterity > 5) {
            int additionalChance = (stats.dexterity - 5) * baseEvasionChance;
            evasionChance += additionalChance;
        }

        int randomValue = rand() % 100 + 1;

        return randomValue <= evasionChance;
    }

    bool criticalStrike() {
        int baseCriticalChance = 5;
        int criticalChanceIncrease = 2;
        int criticalChance = std::min(stats.proficiency - 5, 50) + baseCriticalChance;
        if (stats.proficiency > 5) {
            int additionalChance = (stats.proficiency - 5) * criticalChanceIncrease;
            criticalChance += additionalChance;
        }
        int randomValue = rand() % 100 + 1;
        return randomValue <= criticalChance;
    }


    void attack(Character& target) {
        if (target.evadeAttack()) {
            ++stats.evasionCount;
            std::cout << target.name << " evaded the attack." << std::endl;
        }
        else if(target.criticalStrike()){
            ++stats.criticalStrikeCount;
            int baseMinDamage = 5;
            int damageRange = 2;

            int minDamage = baseMinDamage + (stats.strength - 5) * damageRange;
            int maxDamage = minDamage + stats.strength;

            int damage = rand() % (maxDamage - minDamage + 1) + minDamage;
            target.receiveDamage(damage*2);

            std::cout << name << " Landed critical strike on " << target.name << " for " << damage << " damage." << std::endl;
        }
        else {
            int baseMinDamage = 5;
            int damageRange = 2;

            int minDamage = baseMinDamage + (stats.strength - 5) * damageRange;
            int maxDamage = minDamage + stats.strength;
            float damageReduction = calculateDamageReduction(target);
            int damage = rand() % (maxDamage - minDamage + 1) + minDamage;
            int finalDamage = static_cast<int>(damage * (1.0 - damageReduction));
            target.receiveDamage(finalDamage);

            std::cout << name << " attacked " << target.name << " for " << damage << " damage." << std::endl;
        }
    }

};



class Wall : public Field {
public:
    Wall(int x_, int y_) : Field('#', x_, y_) {}

    virtual void display() const override {
        std::cout << symbol;
    }

    virtual bool isPassable() const override {
        return false;
    }
};

class Floor : public Field {
public:
    Floor(int x_, int y_) : Field('.', x_, y_) {}

    virtual void display() const override {
        std::cout << symbol;
    }
};

class Map {
public:
    static const int WIDTH = 50;
    static const int HEIGHT = 20;

private:
    std::vector<std::vector<Field*>> fields;
    std::vector<Item> itemsList;
    std::vector<Character> enemiesList;
    Character* hero;

public:
    bool fightMode= false;
    Map() : hero(nullptr) {
        fields.resize(HEIGHT, std::vector<Field*>(WIDTH, nullptr));
    }
    void testCombat();
    ~Map() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                fields[y][x]->items.clear();
                delete fields[y][x];
            }
        }

    }

    void display() const {
            std::cout << "Options:" << std::endl;
            std::cout << "9 - Display map, 2 - Enter fight mode" << std::endl;

            if (!fightMode) {
                for (int y = 0; y < HEIGHT; y++) {
                    for (int x = 0; x < WIDTH; x++) {
                        const Field* field = fields[y][x];
                        field->display();
                    }
                    std::cout << std::endl;
                }
            }
        }

    void displayItemsAndEnemies() const {
        std::cout << "Przedmioty na mapie:" << std::endl;
        for (const auto& item : itemsList) {
            std::cout << "  " << item.name << " - (" << item.x << ", " << item.y << ")" << std::endl;
        }

        std::cout << "Przeciwnicy na mapie:" << std::endl;
        for (const auto& enemy : enemiesList) {
            std::cout << "  " << enemy.name << " - (" << enemy.x << ", " << enemy.y << ")" << std::endl;
        }
    }

    void mapClear() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void addCharacter(Character* character) {
        hero = character;
        fields[character->y][character->x] = character;
    }

    void addWall(int x, int y) {
        if (isValidPosition(x, y)) {
            delete fields[y][x];
            fields[y][x] = new Wall(x, y);
        } else {
            std::cout << "Nie można dodać ściany poza granicami mapy." << std::endl;
        }
    }

    void addFloor(int x, int y) {
        if (isValidPosition(x, y)) {
            delete fields[y][x];
            fields[y][x] = new Floor(x, y);
        } else {
            std::cout << "Nie można dodać podłogi poza granicami mapy." << std::endl;
        }
    }

    bool isPassable(int x, int y) const {
        return isValidPosition(x, y) && fields[y][x]->isPassable();
    }

    void addItem(int x, int y, const std::string& name) {
        if (isValidPosition(x, y)) {
            Field* field = fields[y][x];

            if (field && field->symbol == '.' && field->items.empty()) {
                Item newItem(tolower(name[0]), name, x, y);
                field->items.push_back(newItem);
                field->symbol = newItem.symbol;

                itemsList.push_back(newItem);
                std::cout << "Dodano przedmiot: " << newItem.name << " na pozycji (" << newItem.x << ", " << newItem.y << ")"
                          << std::endl;
            }
        } else {
            std::cout << "Nie można dodać przedmiotu poza granicami mapy." << std::endl;
        }
    }

    void addEnemy(int x, int y, const std::string& name) {
           if (isValidPosition(x, y)) {
               Field* field = fields[y][x];

               if (field && field->symbol == '.' && field->items.empty()) {
                   delete fields[y][x];
                   fields[y][x] = new Character(toupper(name[0]), x, y, false, name, generateRandomStatsForEnemy(name));
                   enemiesList.push_back(*static_cast<Character*>(fields[y][x]));

                   std::cout << "Dodano przeciwnika: " << name << " na pozycji (" << x << ", " << y << ")" << std::endl;
               }
           } else {
               std::cout << "Nie można dodać przeciwnika poza granicami mapy." << std::endl;
           }
       }


    void addRandomWalls(int numWalls) {
        srand(static_cast<unsigned>(time(nullptr)));

        for (int i = 0; i < numWalls; ++i) {
            int x, y;

            do {
                x = rand() % (WIDTH - 2) + 1;
                y = rand() % (HEIGHT - 2) + 1;
            } while (fields[y][x]->symbol == '#');

            int groupSize = rand() % 5 + 1;
            for (int j = 0; j < groupSize; ++j) {
                int offsetX = rand() % 3 - 1;
                int offsetY = rand() % 3 - 1;

                int newX = x + offsetX;
                int newY = y + offsetY;

                if (isValidPosition(newX, newY) && fields[newY][newX]->symbol != '#') {
                    addWall(newX, newY);
                }
            }
        }
    }

    void removeEnemy(int x, int y) {
        if (isValidPosition(x, y)) {
            Field* field = fields[y][x];

            auto it = std::remove_if(enemiesList.begin(), enemiesList.end(),
                                     [x, y](const Character& enemy) { return enemy.x == x && enemy.y == y; });

            if (it != enemiesList.end()) {
                enemiesList.erase(it, enemiesList.end());
                delete field;
                fields[y][x] = new Floor(x, y);
                std::cout << "Usunięto przeciwnika z pozycji (" << x << ", " << y << ")" << std::endl;
            } else {
                std::cout << "Na tej pozycji nie ma przeciwnika do usunięcia." << std::endl;
            }
        } else {
            std::cout << "Nie można usunąć przeciwnika poza granicami mapy." << std::endl;
        }
    }

    void removeItem(int x, int y) {
        if (isValidPosition(x, y)) {
            Field* field = fields[y][x];

            if (field && !field->items.empty()) {
                auto& items = field->items;
                items.pop_back();

                if (!items.empty()) {
                    field->symbol = items.back().symbol;
                }
                else {
                    field->symbol = '.';
                }

                auto it = std::remove_if(itemsList.begin(), itemsList.end(),[x, y](const Item& item) { return item.x == x && item.y == y; });

                if (it != itemsList.end()) {
                    itemsList.erase(it, itemsList.end());
                    std::cout << "Usunięto przedmiot z pozycji (" << x << ", " << y << ")" << std::endl;
                }
            } else {
                std::cout << "Na tej pozycji nie ma przedmiotu do usunięcia." << std::endl;
            }
        } else {
            std::cout << "Nie można usunąć przedmiotu poza granicami mapy." << std::endl;
        }
    }

    void generateMap() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                    addWall(x, y);
                } else {
                    addFloor(x, y);
                }
            }
        }

        // Przykładowe statystyki bohatera
              addCharacter(new Character('@', 10, 5, false, "Hero", CharacterStats(100, 15, 10,25,0, 5, 80, 10)));

              addItem(15, 10, "Shield");
              addItem(15, 10, "Sword");

              // Przykładowe statystyki przeciwnika
              addEnemy(20, 15, "Ogre");
    }

    void moveCharacter(int deltaX, int deltaY) {
        if (hero) {
            int newX = hero->x + deltaX;
            int newY = hero->y + deltaY;

            if (isValidPosition(newX, newY) && isPassable(newX, newY)) {
                if (fields[newY][newX]->isPassable()) {
                    fields[hero->y][hero->x] = new Floor(hero->x, hero->y);
                    hero->x = newX;
                    hero->y = newY;
                    fields[hero->y][hero->x] = hero;
                }
            }
        }
    }

    void handleInput(char input) {
        switch (input) {
            case '9':
                fightMode = false;
                break;
            case '2':
                fightMode = true;
                break;
            case 't': // Tryb testowania walki
                  testCombat();
                  break;
            case 'w':
                moveCharacter(0, -1);
                break;
            case 's':
                moveCharacter(0, 1);
                break;
            case 'a':
                moveCharacter(-1, 0);
                break;
            case 'd':
                moveCharacter(1, 0);
                break;
            case 'q':
                std::cout << "Game over." << std::endl;
                exit(0);
                break;
            case 'i': {
                std::cout << "Podaj nazwę przedmiotu: ";
                std::string itemName;
                std::cin >> itemName;
                std::cout << "Podaj współrzędne przedmiotu (x y): ";
                int itemX, itemY;
                std::cin >> itemX >> itemY;
                addItem(itemX, itemY, itemName);
                break;
            }
            case 'u': {
                std::cout << "Podaj współrzędne przedmiotu do usunięcia (x y): ";
                int itemX, itemY;
                std::cin >> itemX >> itemY;
                removeItem(itemX, itemY);
                break;
            }
            case 'n': {
                std::cout << "Podaj nazwę przeciwnika: ";
                std::string enemyName;
                std::cin >> enemyName;
                std::cout << "Podaj współrzędne przeciwnika (x y): ";
                int enemyX, enemyY;
                std::cin >> enemyX >> enemyY;
                addEnemy(enemyX, enemyY, enemyName);
                break;
            }
            case 'x': {
                std::cout << "Podaj współrzędne przeciwnika do usunięcia (x y): ";
                int enemyX, enemyY;
                std::cin >> enemyX >> enemyY;
                removeEnemy(enemyX, enemyY);
                break;
            }
            case 'z': {
                std::cout << "Podaj liczbę ścian do dodania: ";
                int numWalls;
                std::cin >> numWalls;
                addRandomWalls(numWalls);
                break;
            }
            default:
                break;
        }
    }

private:
    bool isValidPosition(int x, int y) const {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
    }

    bool isWallPlacementValid(int x, int y) const {
            if (isValidPosition(x, y) && fields[y][x]->isPassable()) {
                for (int i = y - 1; i <= y + 1; ++i) {
                    for (int j = x - 1; j <= x + 1; ++j) {
                        if (fields[i][j]->symbol == '#') {
                            return false;
                        }
                    }
                }
                if (fields[y][x]->symbol == '@' || fields[y][x]->symbol == 'O' || fields[y][x]->symbol == 'i') {
                    return false;
                }

                return true;
            }

            return false;
        }
};

void Map::testCombat() {
    std::cout << "Enter combat testing mode." << std::endl;

    // Wybór przeciwnika
    std::cout << "Choose an enemy:" << std::endl;
    std::cout << "1. Ogre" << std::endl;
    std::cout << "2. Goblin" << std::endl;
    std::cout << "3. Rat" << std::endl;
    // Dodaj inne przeciwniki

    int choice;
    std::cin >> choice;
    std::string enemyName;
    CharacterStats enemyStats = generateRandomStatsForEnemy(enemyName); ;


    switch (choice) {
           case 1:
               enemyName = "Ogre";
               enemyStats = generateRandomStatsForEnemy(enemyName);
               break;
           case 2:
               enemyName = "Goblin";
               enemyStats = generateRandomStatsForEnemy(enemyName);
               break;
           case 3:
               enemyName = "Rat";
               enemyStats = generateRandomStatsForEnemy(enemyName);
               break;

           default:
               std::cout << "Invalid choice. Exiting combat testing mode." << std::endl;
               return;
       }
    Character attacker('A', 5, 5, false, "Attacker", generateRandomStatsForEnemy("hero"));
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Attacker Stats:" << std::endl;
    std::cout << "  Health: " << attacker.stats.health << std::endl;
    std::cout << "  Strength: " << attacker.stats.strength << std::endl;
    std::cout << "  Dexterity: " << attacker.stats.dexterity << std::endl;
    std::cout << "  Intelligence: " << attacker.stats.intelligence << std::endl;
    std::cout << "  Wisdom: " << attacker.stats.wisdom << std::endl;
    std::cout << "  Mana: " << attacker.stats.mana << std::endl;
    std::cout << "  Proficiency: " << attacker.stats.proficiency << std::endl;
    std::cout << "  Armor: " << attacker.stats.armor << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Enemy Stats:" << std::endl;
    std::cout << "  Health: " << enemyStats.health << std::endl;
    std::cout << "  Strength: " << enemyStats.strength << std::endl;
    std::cout << "  Dexterity: " << enemyStats.dexterity << std::endl;
    std::cout << "  Intelligence: " << enemyStats.intelligence << std::endl;
    std::cout << "  Wisdom: " << enemyStats.wisdom << std::endl;
    std::cout << "  Mana: " << enemyStats.mana << std::endl;
    std::cout << "  Proficiency: " << enemyStats.proficiency << std::endl;
    std::cout << "  Armor: " << enemyStats.armor << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;


    Character enemy(enemyName[0], 7, 5, false, enemyName, enemyStats);

    int numTests;
    std::cout << "Enter the number of tests: ";
    std::cin >> numTests;

    int attackerWins = 0;
    int enemyWins = 0;
    int totalAttackerEvasion = 0;
    int totalAttackerCriticalStrike = 0;
    int totalEnemyEvasion = 0;
    int totalEnemyCriticalStrike = 0;

    for (int i = 0; i < numTests; ++i) {
        Character attacker('A', 5, 5, false, "Attacker", generateRandomStatsForEnemy("hero"));
        Character testEnemy(enemyName[0], 7, 5, false, enemyName, enemyStats);

        while (attacker.isAlive() && testEnemy.isAlive()) {
            attacker.attack(testEnemy);
            if (!testEnemy.isAlive()) {
                break;
            }
            testEnemy.attack(attacker);
            if (!attacker.isAlive()) {
                break;
            }
        }

        if (attacker.isAlive()) {
            std::cout <<"("<< attacker.name << "," << attacker.getHealth() << "," << testEnemy.name << ")" << std::endl;
            ++attackerWins;
        } else {
            std::cout <<"("<< testEnemy.name << "," << testEnemy.getHealth() << "," << attacker.name << ")" << std::endl;
            ++enemyWins;
        }
        totalAttackerEvasion += attacker.stats.evasionCount;
        totalAttackerCriticalStrike += attacker.stats.criticalStrikeCount;
        totalEnemyEvasion += testEnemy.stats.evasionCount;
        totalEnemyCriticalStrike += testEnemy.stats.criticalStrikeCount;
    }
    std::cout << std::endl;
    std::cout << "Results:" << std::endl;
    std::cout << "Attacker Wins: " << attackerWins << std::endl;
    std::cout << "Enemy Wins: " << enemyWins << std::endl;
    std::cout << "Attacker Evasion Count: " << totalAttackerEvasion << std::endl;
    std::cout << "Attacker Critical Strike Count: " << totalAttackerCriticalStrike << std::endl;
    std::cout << "Enemy Evasion Count: " << totalEnemyEvasion << std::endl;
    std::cout << "Enemy Critical Strike Count: " << totalEnemyCriticalStrike << std::endl;
    std::cout << std::endl;
}

int main() {
    Map gameMap;

    gameMap.generateMap();

    while (true) {
        gameMap.display();

        if (!gameMap.fightMode) {
            gameMap.displayItemsAndEnemies();
        }

        if (!gameMap.fightMode) {
            char input;
            std::cin >> input;
            gameMap.handleInput(input);
        } else {
            gameMap.testCombat();
        }
    }

    return 0;
}

