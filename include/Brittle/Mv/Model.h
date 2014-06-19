// Brittle C++ Library - Model-View - Model Header

#ifndef __BRITTLE_MV_MODEL_H
#define __BRITTLE_MV_MODEL_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Async/AnyEventDispatcher.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Model
//

class Model
{
public:

    virtual ~Model();

    void LinkEventTarget( AnyEventTarget& target );


protected:

    void Dispatch( const AnyEvent& event );

    void DispatchEvent( Int eventId );
    void DispatchEvent( Int eventId, const Any& value );
    void DispatchEvent( Int eventId, Any&& value );

    AnyEventDispatcher m_dispatcher;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif //  __BRITTLE_MV_MODEL_H
