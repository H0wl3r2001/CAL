#pragma once
#include "DeliveryPlace.h"

static unsigned int id_place = 0;

/**
 * @brief Dummy place
 *
 */
class Place : public DeliveryPlace
{
public:
    /**
     * @brief Construct a new Place object
     */
    Place();
};
