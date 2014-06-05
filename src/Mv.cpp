// Brittle C++ Library - Model-View Implementation

#include "BrittlePch.h"

#include <Brittle/Core/Async.h>
#include <Brittle/Mv/Model.h>


namespace Brittle
{

//
// [Contents]
//
//   Model
//

///////////////////////////////////////////////////////////////////////////////
//
// Model
//

Model::Model( std::string modelName )
    : m_machine( std::move( modelName ), Async::RenderExecutor() )
{
}


Model::~Model()
{
}


void Model::LinkEventTarget( AnyEventTarget& target )
{
    m_dispatcher.LinkTarget( target );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
