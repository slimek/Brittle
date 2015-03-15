// Brittle C++ Library - Core Android Dependent Implementation

#include "BrittlePch.h"

#include <Brittle/Core/SimpleApp.h>
#include <Caramel/Android/JniBase.h>
#include <Caramel/Android/JniClass.h>
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Error/Alert.h>
#include <Caramel/Error/CatchException.h>


namespace Brittle
{

using namespace Caramel::Android;

//
// Contents
//
//   SimpleApp
//

///////////////////////////////////////////////////////////////////////////////
//
// Static Variables
//

static JniClass s_activity( "com/brittle/core/BrittleActivity" );

static const Char* LOG_TAG = "Brittle";


///////////////////////////////////////////////////////////////////////////////
//
// Simple Application
//

void SimpleApp::InitPlatform()
{
	auto logTracer = new Android::LogTraceAdapter( LOG_TAG );
	logTracer->BindBuiltinChannels( Trace::LEVEL_DEBUG );
	Trace::Listeners::AddManaged( logTracer );
}


} // namespace Brittle


///////////////////////////////////////////////////////////////////////////////
//
// Cocos2d-x 3 Export Functions
//

using namespace cocos2d;
using namespace Brittle;

static SimpleApp* s_app = nullptr;
static AppSettings s_settings;

void cocos_android_jni_on_load( JavaVM* vm )
{
	Caramel::Android::JniInitialize( vm, s_activity.Path() );
}


void cocos_android_app_init( JNIEnv* env, jobject thiz )
{
	NativeInit( s_app, s_settings );
}


void cocos_android_app_run()
{
	s_app->Launch( s_settings );
}


void cocos_android_app_render()
{
	auto xc = CatchException( [] { Director::getInstance()->mainLoop(); } );

	if ( xc )
	{
		CARAMEL_ALERT( xc.TracingMessage() );
	}
}


///////////////////////////////////////////////////////////////////////////////
