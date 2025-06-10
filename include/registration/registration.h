#ifndef REGISTRATION_H
#define REGISTRATION_H

#include"registration_base.h"
#include"participant.h"
#include"prompt.h"
#include"date.h"

#include<string>
#include<memory>
#include<unordered_map>
#include<type_traits>

/* Abstract class for registration to an event
 * It will be needed to add different behaviors accordingly to
 * the type of registration - it's required to have hybrid events support, so online and
 * in person registration must be handled differently */
template<typename ParticipantType>
class Registration : public RegistrationBase {
    /* asserts inheritage for the template */
    static_assert(std::is_base_of<Participant, ParticipantType>::value, "<ParticipantType> of Registration must be derived from Participant class");
protected:
    /* user input when there aren't available participants */
    Registration (int id) : RegistrationBase(id) {};

    /* user input based constructor when there are available participants*/
    Registration (int id, const std::unordered_map<int, std::shared_ptr<ParticipantType>>& availableParticipants) : RegistrationBase(id, Prompt::forType<ParticipantType>::getSelectableFromInput("Select the registered participant:", availableParticipants)) {};

    /* default constructor */
    Registration (int id, const std::string& date, const std::shared_ptr<ParticipantType>& participant) : RegistrationBase(id, date, participant) {};
public:
    void printSelf() const override;
private:
    // std::shared_ptr<ParticipantType> participant;
};

#endif
