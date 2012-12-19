package com.giderosmobile.android;

import com.yourdomain.yourapp.R;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.FrameLayout;

import com.giderosmobile.android.player.*;

public class AdMobActivity extends Activity implements OnTouchListener
{
	static
	{
		System.loadLibrary("gideros");
		System.loadLibrary("luasocket");
		System.loadLibrary("lfs");
		//System.loadLibrary("ggooglebilling");
		System.loadLibrary("admob");
	}

	static private String[] externalClasses = {
		//"com.giderosmobile.android.plugins.googlebilling.GGoogleBilling",
		"com.giderosmobile.android.plugins.AdMob"
	};
	
	private GLSurfaceView mGLView;

	private boolean mToBeResumed = false;
	private boolean mLostFocus = false;
		
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
				
        mGLView = new GiderosGLSurfaceView(this);
		//setContentView(mGLView);
        
        setContentView(R.layout.main);
        FrameLayout layout = (FrameLayout)findViewById(R.id.layout_main);
        layout.addView(mGLView);
		mGLView.setOnTouchListener(this);
		
		WeakActivityHolder.set(this);

		GiderosApplication.onCreate(externalClasses);
	}

	int[] id = new int[256];
	int[] x = new int[256];
	int[] y = new int[256];

	@Override
	public void onStart()
	{
		super.onStart();
		GiderosApplication.getInstance().onStart();
	}

	@Override
	public void onRestart()
	{
		super.onRestart();
		GiderosApplication.getInstance().onRestart();
	}

	@Override
	public void onStop()
	{
		GiderosApplication.getInstance().onStop();
		super.onStop();
	}

	@Override
	public void onDestroy()
	{
		GiderosApplication.onDestroy();
		super.onDestroy();
	}

	@Override
	protected void onPause()
	{
		mLostFocus = true;
		
		GiderosApplication.getInstance().onPause();
		mGLView.onPause();
		
		super.onPause();
	}

	@Override
	protected void onResume()
	{
		super.onResume();

		mToBeResumed = mLostFocus;
		if (!mLostFocus)
		{
			mGLView.onResume();
			GiderosApplication.getInstance().onResume();
		}
	}
	
	@Override
	public void onLowMemory()
	{
		super.onLowMemory();
		GiderosApplication.getInstance().onLowMemory();
	}
	 
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);
		GiderosApplication.getInstance().onActivityResult(requestCode, resultCode, data);
	}
	
	@Override
	public void onWindowFocusChanged(boolean hasFocus)
	{
		super.onWindowFocusChanged(hasFocus);
		
		mLostFocus = !hasFocus;
		if (mToBeResumed && hasFocus)
		{
			mToBeResumed = false;
			GiderosApplication.getInstance().onResume();
			mGLView.onResume();
		}
	}
	
	public boolean onTouch(View v, MotionEvent event)
	{
		int size = event.getPointerCount();
		for (int i = 0; i < size; i++)
		{
			id[i] = event.getPointerId(i);
			x[i] = (int) event.getX(i);
			y[i] = (int) event.getY(i);
		}

		int actionMasked = event.getActionMasked();
		boolean isPointer = (actionMasked == MotionEvent.ACTION_POINTER_DOWN || actionMasked == MotionEvent.ACTION_POINTER_UP);
		int actionIndex = isPointer ? event.getActionIndex() : 0;
				
		if (actionMasked == MotionEvent.ACTION_DOWN || actionMasked == MotionEvent.ACTION_POINTER_DOWN)
		{
			GiderosApplication.getInstance().onTouchesBegin(size, id, x, y, actionIndex);
		} else if (actionMasked == MotionEvent.ACTION_MOVE)
		{
			GiderosApplication.getInstance().onTouchesMove(size, id, x, y);
		} else if (actionMasked == MotionEvent.ACTION_UP || actionMasked == MotionEvent.ACTION_POINTER_UP)
		{
			GiderosApplication.getInstance().onTouchesEnd(size, id, x, y, actionIndex);
		} else if (actionMasked == MotionEvent.ACTION_CANCEL)
		{
			GiderosApplication.getInstance().onTouchesCancel(size, id, x, y);
		}

		return true;
	}

	@Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
		if (GiderosApplication.getInstance().onKeyDown(keyCode, event) == true)
			return true;
		
		return super.onKeyDown(keyCode, event);
    }

	
	@Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
		if (GiderosApplication.getInstance().onKeyUp(keyCode, event) == true)
			return true;
		
		return super.onKeyUp(keyCode, event);
    }
}

class GiderosGLSurfaceView extends GLSurfaceView
{
	public GiderosGLSurfaceView(Context context)
	{
		super(context);
		mRenderer = new GiderosRenderer();
		setRenderer(mRenderer);
	}

	GiderosRenderer mRenderer;
}

class GiderosRenderer implements GLSurfaceView.Renderer
{
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		GiderosApplication.getInstance().onSurfaceCreated();
	}

	public void onSurfaceChanged(GL10 gl, int w, int h)
	{
		GiderosApplication.getInstance().onSurfaceChanged(w, h);
	}

	public void onDrawFrame(GL10 gl)
	{
		GiderosApplication.getInstance().onDrawFrame();
	}
}
