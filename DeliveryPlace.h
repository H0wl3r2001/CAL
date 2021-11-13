#pragma once
#include "Time.h"

/**
 * @brief A delivery place for bread
 *
 */
class DeliveryPlace
{
protected:
    /**
     * @brief Name of the delivery place.
     */
    std::string name;

private:
    /**
     * @brief delivery time (ideal)
     */
    Time deliveryTime;
    /**
     * @brief lower limit of the time window available for delivery
     */
    Time minimumTime;
    /**
     * @brief upper limit of the time window available for delivery.
     */
    Time maximumTime;
    /**
     * @brief Quantity of bread to be delivered
     */
    unsigned int breadQuantity;
    /**
     * @brief Max Precedence in delivery time (in minutes)
     */
    unsigned int maxPrecedence;
    /**
     * @brief Max delay in delivery time (in minutes)
     */
    unsigned int maxDelay;

public:
    /**
     * @brief Construct a new Delivery Place object.
     *
     * @param deliveryTime ideal time of the delivery.
     * @param name Name of the delivery place.
     * @param breadQuantity quantity of bread for the delivery
     * @param maxPrecedence Max delivery precedence (to calculate minimum delivery time)
     * @param maxDelay Max delivery delay (to calculate maximum delivery time)
     */
    DeliveryPlace(const Time &deliveryTime, const std::string &name, const unsigned int &breadQuantity, const unsigned int &maxPrecendence, const unsigned int &maxDelay);
    /**
     * @brief Construct a new Delivery Place object
     *
     * @param deliveryTime ideal time of the delivery.
     * @param name Name of the delivery place.
     * @param breadQuantity quantity of bread for the delivery
     *
     * @note maxPrecendence will be set to 10 and maxDelay to 30 as default values
     */
    DeliveryPlace(const Time &deliveryTime, const std::string &name, const unsigned int &breadQuantity);
    /**
     * @brief Construct a new Delivery Place object.
     *
     * @param deliveryTime ideal time of the delivery.
     * @param name Name of the delivery place.
     *
     * @note maxPrecendence will be set to 10 and maxDelay to 30 as default values
     */
    DeliveryPlace(const Time &deliveryTime, const std::string &name);
    /**
     * @brief Construct a new Delivery Place object (DUMMY)
     */
    DeliveryPlace();
    /**
     * @brief Get the Name object.
     *
     * @return std::string name of the delivery place.
     */
    std::string getName() const;
    /**
     * @brief Get the Name And Time Window object
     *
     * @return std::string name with the time window separated by a \\n
     */
    std::string getNameAndTimeWindow() const;
    /**
     * @brief Get the ideal delivery time.
     *
     * @return Time returns the ideal time of this delivery.
     */
    Time getIdealTime() const;
    /**
     * @brief Get the minimum delivery time.
     *
     * @return Time returns the lower limit of the time window available for delivery
     */
    Time getMinTime() const;
    /**
     * @brief Get the maximum delivery time.
     *
     * @return Time returns the upper limit of the time window available for delivery
     */
    Time getMaxTime() const;

    /**
     * @brief Find out if @p t is on time
     *
     * @param t time
     * @return true if it is lower than the maximum time
     * @return false otherwise
     */
    bool inTime(const Time &t) const;

    /**
     * @brief Get the Bread Quatity object
     *
     * @return const unsigned int bread quantity
     */
    unsigned int getBreadQuatity() const;

    /**
     * @brief Sends to an output stream the information of a Delivery Place object
     *
     * @param os output stream
     * @param dp delivery place object
     * @return std::ostream& return the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const DeliveryPlace &dp);
};
