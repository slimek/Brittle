// Brittle C++ Library - Model-View Implementation

#include "BrittlePch.h"

#include <Brittle/Core/Async.h>
#include <Brittle/Mv/Machine.h>
#include <Brittle/Mv/Model.h>


namespace Brittle
{

//
// [Contents]
//
//   Model
//   Machine
//

///////////////////////////////////////////////////////////////////////////////
//
// Model
//

Model::~Model()
{
}


void Model::LinkEventTarget( AnyEventTarget& target )
{
    m_dispatcher.LinkTarget( target );
}


void Model::Dispatch( const AnyEvent& event )
{
    m_dispatcher.Dispatch( event );
}


void Model::DispatchEvent( Int eventId )
{
    m_dispatcher.Dispatch( AnyEvent( eventId ));
}


void Model::DispatchEvent( Int eventId, const Any& value )
{
    m_dispatcher.Dispatch( AnyEvent( eventId, value ));
}


void Model::DispatchEvent( Int eventId, Any&& value )
{
    m_dispatcher.Dispatch( AnyEvent( eventId, std::move( value )));
}


///////////////////////////////////////////////////////////////////////////////
//
// Machine
//

Machine::Machine( const std::string& machineName )
    : m_machine( machineName, Async::RenderExecutor() )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
