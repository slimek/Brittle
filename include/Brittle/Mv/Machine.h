// Brittle C++ Library - Model-View - Machine Header

#ifndef __BRITTLE_MV_MACHINE_H
#define __BRITTLE_MV_MACHINE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Mv/Model.h>
#include <Caramel/Statechart/StateMachine.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Machine
// - A model class with a state-machine.
//

class Machine : public Model
{
public:

    explicit Machine( const std::string& machineName );

protected:    

    Statechart::StateMachine m_machine;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_MV_MACHINE_H
