// Brittle C++ Library - Layout Implementation

#include "BrittlePch.h"

#include <Brittle/Layout/Stretch.h>
#include <Brittle/Utils/Geometry.h>


namespace Brittle
{

//
// [Contents]
//
//   StretchCharm
//

///////////////////////////////////////////////////////////////////////////////
//
// Stretch Charm
//

StretchCharm::StretchCharm( Node* target )
    : m_target( target )
{
    CARAMEL_ASSERT( target );
    CARAMEL_ASSERT( target->getParent() );
}


StretchCharm::~StretchCharm()
{
    this->Apply();
}


void StretchCharm::Apply()
{
    if ( m_applied ) { return; }
    m_applied = true;

    const auto parent = m_target->getParent();
    const auto parentSize = parent->getContentSize();
    auto targetSize = m_target->getContentSize();
    
    const Float scalingX = parentSize.width / targetSize.width;
    const Float scalingY = parentSize.height / targetSize.height;

    /// Stretch ///

    switch ( m_stretchMethod )
    {
    case STRETCH_UNDEF: // default
    case STRETCH_FILL:
    {
        m_target->setScale( std::max( scalingX, scalingY ));
        break;
    }

    case STRETCH_FIT:
    {
        m_target->setScale( std::min( scalingX, scalingY ));
        break;
    }
    
    default:
        CARAMEL_THROW( "Unknown stretch method: %d", m_stretchMethod );
    }

    /// Align ///

    const auto center = GetCenter( parent->getContentSize() );
    m_target->setPosition( center );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
