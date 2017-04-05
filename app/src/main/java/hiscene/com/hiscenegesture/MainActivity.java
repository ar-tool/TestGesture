package hiscene.com.hiscenegesture;

import android.Manifest;
import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.FrameLayout;

import java.io.File;

import hiscene.com.hiscenegesture.JNI.tradition.TraditionManager;

public class MainActivity extends AppCompatActivity {
    private HisceneSurfaceView mSurfaceView;
    private FrameLayout mFrameLayout;
    private Drawer mDrawer;
    private PermissionsChecker mPermissionsChecker; // 权限检测器
    private static final int REQUEST_CODE = 0; // 请求码

    // 所需的全部权限
    static final String[] PERMISSIONS = new String[]{
            Manifest.permission.CAMERA,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mFrameLayout = new FrameLayout(this);
        mSurfaceView = new HisceneSurfaceView(this);
        mDrawer = new Drawer(this);

        mFrameLayout.addView(mDrawer);
        mFrameLayout.addView(mSurfaceView);
        setContentView(mFrameLayout);

        //copy the asset
        AssetManager manager = getAssets();
        try{
            String[] files= manager.list("model");
            String path = getExternalCacheDir().getPath();
            for(String p:files){
                FileUtil.copyAssetsFileToSDCard(this,"model"+ File.separator+p,path+File.separator+p,false);
            }
        }catch (Exception e){

        }
        mPermissionsChecker = new PermissionsChecker(this);
    }


    @Override
    protected void onResume() {
        super.onResume();

        // 缺少权限时, 进入权限配置页面
        if (mPermissionsChecker.lacksPermissions(PERMISSIONS)) {
            PermissionsActivity.startActivityForResult(this, REQUEST_CODE, PERMISSIONS);
        }
    }
    @Override protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        // 拒绝时, 关闭页面, 缺少主要权限, 无法运行
        if (requestCode == REQUEST_CODE && resultCode == PermissionsActivity.PERMISSIONS_DENIED) {
            finish();
        }
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        TraditionManager.getInstance().destory();
    }
}
