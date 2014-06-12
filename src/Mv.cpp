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
