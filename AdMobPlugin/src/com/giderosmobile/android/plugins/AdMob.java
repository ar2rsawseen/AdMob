package com.giderosmobile.android.plugins;

import java.lang.ref.WeakReference;
import java.util.Hashtable;

import android.app.Activity;
import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

import com.google.ads.*;
import com.google.ads.AdRequest.ErrorCode;

public class AdMob implements AdListener {
	
	//reference to main activity
	private static WeakReference<Activity> sActivity;
	//reference to layout
	private static RelativeLayout layout;
	//layout parameters
	private static RelativeLayout.LayoutParams params;
	//AdMob adview
	private static AdView adView;
	private static InterstitialAd interstitial;
	//current type of AdMob banner
	private static AdSize currentType;
	//all AdMob banner types
	private static Hashtable<String, AdSize> adTypes;
	//admob alignment
	private static Hashtable<String, Integer> alignHor;
	private static Hashtable<String, Integer> alignVer;
	private static String curHorAlignment = "center";
	private static String curVerAlignment = "top";
	//reference to instance
	private static AdMob self;
	
	//on create event from Gideros
	//receives reference to current activity
	public static void onCreate(Activity activity)
	{
		self = new AdMob();
		//reference to activity
		sActivity =  new WeakReference<Activity>(activity);
		
		//create ad types
		adTypes = new Hashtable<String, AdSize>();
		adTypes.put("banner", AdSize.BANNER);
		adTypes.put("iab_banner", AdSize.IAB_BANNER);
		adTypes.put("iab_leaderboard", AdSize.IAB_LEADERBOARD);
		adTypes.put("iab_mrect", AdSize.IAB_MRECT);
		adTypes.put("iab_skyscaper", AdSize.IAB_WIDE_SKYSCRAPER);
		adTypes.put("smart_banner", AdSize.SMART_BANNER);
		
		alignVer = new Hashtable<String, Integer>();
		alignVer.put("top", Gravity.TOP);
		alignVer.put("bottom", Gravity.BOTTOM);
		alignVer.put("center", Gravity.CENTER_VERTICAL);
		
		alignHor = new Hashtable<String, Integer>();
		alignHor.put("left", Gravity.LEFT);
		alignHor.put("right", Gravity.RIGHT);
		alignHor.put("center", Gravity.CENTER_HORIZONTAL);
		
		//create layout
		layout = new RelativeLayout(sActivity.get());
	
		//set parameters
		params = new RelativeLayout.LayoutParams(
			  RelativeLayout.LayoutParams.WRAP_CONTENT,
			  RelativeLayout.LayoutParams.WRAP_CONTENT);
		
		layout.setHorizontalGravity(alignHor.get(curHorAlignment));
		layout.setVerticalGravity(alignVer.get(curVerAlignment));
		//reference to main layout
		FrameLayout mainlayout = (FrameLayout)sActivity.get().getWindow().getDecorView();
		
		//add ad layout to main layout
		mainlayout.addView(layout);
	}
	
	//on destroy event
	public static void onDestroy()
	{	
		removeAd();
	}
	
	//load an Ad
	public static void loadAd(final String admobID, final String adType)
	{
		//get current ad type
		currentType = adTypes.get(adType);
		try
		{
			sActivity.get().runOnUiThread(new Runnable() {
			
				@Override
				public void run() {
					//if there is an existing ad view
					//destroy it
					if(adView != null)
					{
						layout.removeView(adView);
						adView.destroy();
					}
					
					if(adType.equals("interstitial"))
					{
						interstitial = new InterstitialAd(sActivity.get(), admobID);
						
						AdRequest adRequest = new AdRequest();
						//adRequest.addTestDevice("545D828B0002576098659942B35646D7");
						interstitial.loadAd(adRequest);
						interstitial.setAdListener(self);
					}
					else
					{
						// Create the adView with your publisher ID and type
						adView = new AdView(sActivity.get(), currentType, admobID);
						layout.addView(adView, params);
						adView.loadAd(new AdRequest());
					}
				}
			});
		
		}
		catch(Exception ex)	{}
	}
	
	//remove ad
	public static void removeAd()
	{
		try
		{
			sActivity.get().runOnUiThread(new Runnable() {
				
				@Override
				public void run() {
					if(adView != null)
					{
						layout.removeView(adView);
						adView.destroy();
					}
				}
			});
		}
		catch(Exception ex){}
	}
	
	//set alignment of ad (both horizontal and vertical)
	public static void setAlignment(final String hor, final String ver)
	{
		curHorAlignment = hor;
		curVerAlignment = ver;
		try
		{
			sActivity.get().runOnUiThread(new Runnable() {
			
				@Override
				public void run() {
					layout.setHorizontalGravity(alignHor.get(curHorAlignment));
					layout.setVerticalGravity(alignVer.get(curVerAlignment));
				}
			});
		}
		catch(Exception ex)	{}
	}
	
	//set horizontal alignment of ad
	public static void setHorizontalAlignment(final String hor)
	{
		setAlignment(hor, getVerticalAlignment());
	}
	
	//set vertical alignment of ad
	public static void setVerticalAlignment(final String ver)
	{
		setAlignment(getHorizontalAlignment(), ver);
	}
	
	//get horizontal alignment of ad
	public static String getHorizontalAlignment(){
		return curHorAlignment;
	}
	
	//get horizontal alignment of ad
	public static String getVerticalAlignment(){
		return curVerAlignment;
	}
		
		
	//get vertical alignment of ad
	
	//set visibility of ad
	public static void setVisible(final boolean visible)
	{
		try
		{
			sActivity.get().runOnUiThread(new Runnable() {
				
				@Override
				public void run() {
					if(adView != null)
					{		
						if(visible){
							adView.setVisibility( View.VISIBLE );
						}
						else
						{
							adView.setVisibility( View.GONE );
						}
					}
				}
			});
		}
		catch(Exception ex)	{}
	}
	
	public void onReceiveAd(Ad ad) {
		if (ad == interstitial) {
			interstitial.show();
		}
	}

	@Override
	public void onDismissScreen(Ad arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onFailedToReceiveAd(Ad arg0, ErrorCode arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onLeaveApplication(Ad arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onPresentScreen(Ad arg0) {
		// TODO Auto-generated method stub
		
	}
	
}
