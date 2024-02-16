#include "przedmiot.h"

przedmiot::przedmiot()
{
    symbol = 'I';
}



string typToString(przedmiotTyp typ) {
    switch (typ) {
        case HELM: return "HELM";
        case PANCERZ: return "PANCERZ";
        case SPODNIE: return "SPODNIE";
        case BRON: return "BRON";
        case PIERSCIEN: return "PIERSCIEN";
        case PAS: return "PAS";
        case BUTY: return "BUTY";
        case REKAWICE: return "REKAWICE";
        case AMULET: return "AMULET";
        case MIKSTURA_UZDROWIENIA: return "MIKSTURA UZDRAWIAJACA";
        default: return "NIEZNANY";
    }
}
