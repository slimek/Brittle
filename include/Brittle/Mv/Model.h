// Brittle C++ Library - Model-View - Model Header

#ifndef __BRITTLE_MV_MODEL_H
#define __BRITTLE_MV_MODEL_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Statechart/StateMachine.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Model
//

class Model
{
public:

    explicit Model( std::string modelName );
    virtual ~Model();

    void LinkEventTarget( AnyEventTarget& target );


protected:

    AnyEventDispatcher m_dispatcher;

    Statechart::StateMachine m_machine;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif //  __BRITTLE_MV_MODEL_H
