package com.brittle.core;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class BrittleActivity extends Cocos2dxActivity
{
	public Cocos2dxGLSurfaceView onCreateView()
	{
		Cocos2dxGLSurfaceView view = new Cocos2dxGLSurfaceView( this );
		view.setEGLConfigChooser( 8, 8, 8, 8, 16, 0 );
		return view;
	}
}
