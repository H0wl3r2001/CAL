#include "Place.h"

Place::Place()
{
    this->name = std::to_string(id_place);
    id_place++;
}
