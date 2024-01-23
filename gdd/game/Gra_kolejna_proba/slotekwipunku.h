#include "przedmiot.h"
class SlotEkwipunku {
public:
    SlotEkwipunku(przedmiotTyp miejsce, przedmiot& item) : miejsce(miejsce), item(item) {}

    przedmiotTyp miejsce;
    przedmiot& item;
};
