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

class Character : public Field {
public:
    bool is_Item;
    std::string name;

    Character(char sym, int x_, int y_, bool item, const std::string& name_)
        : Field(sym, x_, y_), is_Item(item), name(name_) {}

    virtual void display() const override {
        std::cout << symbol;
    }

    virtual bool isPassable() const override {
        return false;
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
    Map() : hero(nullptr) {
        fields.resize(HEIGHT, std::vector<Field*>(WIDTH, nullptr));
    }

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
        std::cout << "WSAD W-GORA, S-DOL, A-LEWO, D-PRAWO:" << std::endl;
        std::cout << "i - dodanie przedmiotu, u - usuniecie przemiotu" << std::endl;
        std::cout << "n - dodanie przeciwnika, x - usuniecie przeciwnika" << std::endl;
        std::cout << "z - dodanie scian, ile grup" << std::endl;

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                const Field* field = fields[y][x];
                field->display();
            }
            std::cout << std::endl;
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
                fields[y][x] = new Character(toupper(name[0]), x, y, false, name);
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

        addCharacter(new Character('@', 10, 5, false, "Hero"));
        addItem(15, 10, "Shield");
        addItem(15, 10, "Sword");
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
        if (hero) {
            switch (input) {
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

int main() {
    Map gameMap;

    gameMap.generateMap();

    while (true) {
        gameMap.mapClear();
        gameMap.display();
        gameMap.displayItemsAndEnemies();

        char input;
        std::cin >> input;
        gameMap.handleInput(input);
        gameMap.display();

    }

    return 0;
}
