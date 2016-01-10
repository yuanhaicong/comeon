/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import org.cocos.Mahjong.R;
import org.cocos2dx.classes.AndroidNDKHelper;
import org.cocos2dx.classes.Util;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;

import com.tencent.connect.UserInfo;
import com.tencent.connect.common.Constants;
import com.tencent.tauth.IUiListener;
import com.tencent.tauth.Tencent;
import com.tencent.tauth.UiError;

public class AppActivity extends Cocos2dxActivity {
	public JSONObject usrInfo;
	public String CPPFunctionToBeCalled;
	public String mAppid;
	private UserInfo mInfo;
	public static Tencent mTencent;
	public static Context cont;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// 在主activity中，设置这个activity作为c++消息的接受者
		AndroidNDKHelper.SetNDKReciever(this);
		cont = this;
		usrInfo=new JSONObject();
		mAppid = "1101356704";
		mTencent = Tencent.createInstance(mAppid, this);
		// initViews();
	}

	static {
		System.loadLibrary("cocos2dcpp");
	}

	public  void initOpenidAndToken(JSONObject jsonObject) {
		try {
			String token = jsonObject.getString(Constants.PARAM_ACCESS_TOKEN);
			String expires = jsonObject.getString(Constants.PARAM_EXPIRES_IN);
			String openId = jsonObject.getString(Constants.PARAM_OPEN_ID);
			usrInfo.put("ident", openId) ;
			if (!TextUtils.isEmpty(token) && !TextUtils.isEmpty(expires)
					&& !TextUtils.isEmpty(openId)) {
				mTencent.setAccessToken(token, expires);
				mTencent.setOpenId(openId);
			}
		} catch (Exception e) {
		}
	}

	IUiListener loginListener = new BaseUiListener() {
		@Override
		protected void doComplete(JSONObject values) {
			// Log.d("SDKQQAgentPref", "AuthorSwitch_SDK:" +
			// SystemClock.elapsedRealtime());
			initOpenidAndToken(values);
			updateUserInfo();
		}
	};

	private class BaseUiListener implements IUiListener {

		@Override
		public void onComplete(Object response) {
			if (null == response) {
				Util.showResultDialog(AppActivity.this, "返回为空", "登录失败");
				return;
			}
			JSONObject jsonResponse = (JSONObject) response;
			if (null != jsonResponse && jsonResponse.length() == 0) {
				Util.showResultDialog(AppActivity.this, "返回为空", "登录失败");
				return;
			}
			// Util.showResultDialog(QQMainActivity.this, response.toString(),
			// "登录成功");
			// 有奖分享处理
			// handlePrizeShare();
			doComplete((JSONObject) response);
		}

		protected void doComplete(JSONObject values) {

		}

		@Override
		public void onError(UiError e) {
			Util.toastMessage(AppActivity.this, "onError: " + e.errorDetail);
			Util.dismissDialog();
		}

		@Override
		public void onCancel() {
			Util.toastMessage(AppActivity.this, "onCancel: ");
			Util.dismissDialog();
		}
	}

	private void initViews() {
		// mTencent = Tencent.createInstance(mAppid, this);
		// mUserInfo = (TextView) findViewById(R.id.user_nickname);
		// mUserLogo = (ImageView) findViewById(R.id.user_logo);

	}

	private void updateUserInfo() {
		if (mTencent != null && mTencent.isSessionValid()) {
			IUiListener listener = new IUiListener() {

				@Override
				public void onError(UiError e) {
					Util.toastMessage(AppActivity.this, "onError: "
							+ e.errorDetail);
					Util.dismissDialog();
				}

				@Override
				public void onComplete(final Object response) {
					Message msg = new Message();
					msg.obj = response;
					msg.what = 0;
					mHandler.sendMessage(msg);

					/*new Thread() {

						@Override
						public void run() {
							JSONObject result=(JSONObject) response;
							try {
								usrInfo.put("nickname", result.getString("nickname")) ;
								usrInfo.put("image_url", result.getString("figureurl_qq_2")) ;
							} catch (JSONException e) {
								// TODO Auto-generated catch block
								//e.printStackTrace();
								//usrInfo.put("nickname", "nickname") ;
							}
							AlertDialog.Builder builder = new AlertDialog.Builder(
									HelloCpp.this);
							builder.setMessage(usrInfo.toString()).setTitle("用户信息")
									.setNeutralButton("OK", null).show();
							AndroidNDKHelper.SendMessageWithParameters(
									CPPFunctionToBeCalled, usrInfo);
						}

					}.start();*/

				}

				@Override
				public void onCancel() {

				}
			};
			mInfo = new UserInfo(this, mTencent.getQQToken());
			// mInfo.getUserInfo(new
			// BaseUIListener(this,"get_simple_userinfo"));
			mInfo.getUserInfo(listener);

		}
	}

	Handler mHandler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			if (msg.what == 0) {
				//usrInfo = (JSONObject) msg.obj;
//				AlertDialog.Builder builder = new AlertDialog.Builder(
//						HelloCpp.this);
//				builder.setMessage(usrInfo.toString()).setTitle("用户信息")
//						.setNeutralButton("OK", null).show();
				/*
				 * AndroidNDKHelper.SendMessageWithParameters("SampleSelector",
				 * usrInfo);
				 */
				JSONObject result=(JSONObject) msg.obj;
				try {
					usrInfo.put("nickname", result.getString("nickname")) ;
					usrInfo.put("image_url", result.getString("figureurl_qq_2")) ;
					usrInfo.put("gender", result.getString("gender")) ;
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					//e.printStackTrace();
					//usrInfo.put("nickname", "nickname") ;
				}
				/*AlertDialog.Builder builder = new AlertDialog.Builder(
						HelloCpp.this);
				builder.setMessage(usrInfo.toString()).setTitle("用户信息")
						.setNeutralButton("OK", null).show();*/
				AndroidNDKHelper.SendMessageWithParameters(
						CPPFunctionToBeCalled, usrInfo);
			}
		}

	};

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// Log.d(TAG, "-->onActivityResult " + requestCode + " resultCode=" +
		// resultCode);
		if (requestCode == Constants.REQUEST_API) {
			if (resultCode == Constants.RESULT_LOGIN) {
				Tencent.handleResultData(data, loginListener);
				// Log.d(TAG, "-->onActivityResult handle logindata");
			}
		} else if (requestCode == Constants.REQUEST_APPBAR) { // app内应用吧登录
			if (resultCode == Constants.RESULT_LOGIN) {
				updateUserInfo();
				// updateLoginButton();
				Util.showResultDialog(AppActivity.this,
						data.getStringExtra(Constants.LOGIN_INFO), "登录成功");
			}
		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	// 实现这个被c++发送消息调用的方法
	// 确保这个方法的名字跟c++传递过来的字符串相同
	// 比如我们从c++中传递"SampleSelector"字符串，这就是为什么我们创建这个方法的原因了
	public void SampleSelector(JSONObject prms) {
		Log.v("SampleSelector", "传过来的参数是 : " + prms.toString());

		// String CPPFunctionToBeCalled = null;
		try {
			CPPFunctionToBeCalled = prms.getString("to_be_called");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (!mTencent.isSessionValid()) {
			mTencent.login(this, "all", loginListener);
		} else {
			mTencent.logout(this);
			mTencent.login(this, "all", loginListener);
			// updateUserInfo();
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			new AlertDialog.Builder(this)
					.setTitle(R.string.prompt)
					.setMessage(R.string.quit_desc)
					.setNegativeButton(R.string.cancel,
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog,
										int which) {
								}
							})
					.setPositiveButton(R.string.confirm,
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog,
										int whichButton) {
									mTencent.logout(cont);
									finish();
									System.exit(0);
								}
							}).show();
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}

	public void ShareSelector(JSONObject prms) throws JSONException {
		Log.v("ShareSelector", "传过来的参数是 : " + prms.toString());
		//Bitmap tempmap = getImageFromAssetsFile("screenshot/test.png");
		//Bitmap tempmap = BitmapFactory.decodeResource(getResources(), R.screenshot.fish_screenshot.png);
		String path = "/fish_screenshot.png";
		//saveBitmap(tempmap, path);
		shareMsg(cont, getTitle().toString(), "椰岛麻将分享", "快来挑战我", Environment
				.getExternalStorageDirectory().getAbsolutePath() + path);
		JSONObject json= new JSONObject();
		json.put("android", "截屏分享成功");
		AndroidNDKHelper.SendMessageWithParameters("ShareSelector",
				json );
	}

	/**
	 * 分享功能
	 * 
	 * @param context
	 *            上下文
	 * @param activityTitle
	 *            Activity的名字
	 * @param msgTitle
	 *            消息标题
	 * @param msgText
	 *            消息内容
	 * @param imgPath
	 *            图片路径，不分享图片则传null
	 */
	public static void shareMsg(Context context, String activityTitle,
			String msgTitle, String msgText, String imgPath) {
		Intent intent = new Intent(Intent.ACTION_SEND);
		if (imgPath == null || imgPath.equals("")) {
			intent.setType("text/plain"); // 纯文本
		} else {
			File f = new File(imgPath);
			if (f != null && f.exists() && f.isFile()) {
				intent.setType("image/png");
				Uri u = Uri.fromFile(f);
				intent.putExtra(Intent.EXTRA_STREAM, u);
			}
		}
		intent.putExtra(Intent.EXTRA_SUBJECT, msgTitle);
		intent.putExtra(Intent.EXTRA_TEXT, msgText);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		context.startActivity(Intent.createChooser(intent, activityTitle));
	}

	/**
	 * 从Assets中读取图片
	 */
	private Bitmap getImageFromAssetsFile(String fileName) {
		Bitmap image = null;
		AssetManager am = getResources().getAssets();
		try {
			InputStream is = am.open(fileName);
			image = BitmapFactory.decodeStream(is);
			is.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		return image;

	}

	/** 保存方法 */
	public void saveBitmap(Bitmap bm, String picName) {
		Log.e("tupian", "保存图片");
		File f = new File(Environment.getExternalStorageDirectory()
				.getAbsolutePath(), picName);
		if (f.exists()) {
			f.delete();
		}
		try {
			FileOutputStream out = new FileOutputStream(f);
			bm.compress(Bitmap.CompressFormat.PNG, 90, out);
			out.flush();
			out.close();
			//f.delete();
			Log.i("tupian", "已经保存");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
