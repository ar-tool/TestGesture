package hiscene.com.hiscenegesture;

import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.util.Log;
import android.view.SurfaceHolder;

import java.io.IOException;
import java.util.List;

import hiscene.com.hiscenegesture.base.AlgWrapper;

/**
 * Created by leon on 17-3-22.
 */

public class CameraPreview implements Camera.PreviewCallback {

    final static String TAG = "CameraPreview";

    private int num = 5;
    private int preWidth;
    private int preHeight;
    private String mFocusMode;
    private Camera camera;
    private static CameraPreview instance;
    private boolean isPreviewing = false;

    private CameraPreview() {
        mFocusMode = Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO;
    }

    public static CameraPreview getInstance(){
        if(null ==instance){
            instance = new CameraPreview();
        }
        return instance;
    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        if(data !=null){
            if(AlgWrapper.getInstance().isReady())
                AlgWrapper.getInstance().sendImage(data);

        }
        camera.addCallbackBuffer(data);
    }

    public int open(int direction) {
        try {
            if (camera != null) {
                camera.release();
            }
            camera = Camera.open();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    //与surfaceView关联
    public boolean start(SurfaceHolder holder) {
        if(isPreviewing){
            camera.stopPreview();
            return false;
        }

        if(holder == null){
            return false;
        }
        Camera.Parameters para = camera.getParameters();


        para.setPreviewFormat(ImageFormat.NV21);
        para.setPreviewSize(1280,720);
        List<String> focusModes = para.getSupportedFocusModes();
        if (focusModes.contains(mFocusMode)) {
            para.setFocusMode(mFocusMode);
        }

        // if return 0 isNotSupported
        int min = para.getMinExposureCompensation();
        int max = para.getMaxExposureCompensation();
        //设置自动曝光锁
        if(para.isAutoExposureLockSupported()){
            para.setAutoExposureLock(false);
        }
        //设置曝光补偿指数
        if(para.getMinExposureCompensation() !=0 &&para.getMaxExposureCompensation() !=0){
            para.setExposureCompensation(-12);
        }
        camera.setParameters(para);

//        Log.i("ExposureMinValue",""+min);
//        Log.e("ExposureMaxValue",""+max);
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                while (Thread.interrupted() == false){
//                    Camera.Parameters para1 = camera.getParameters();
//                    int index =para1.getExposureCompensation();
//                   boolean status =  para1.isAutoExposureLockSupported();
//                    Log.e("ExposureIndexValue",""+index+"status:"+String.valueOf(status));
//                }
//            }
//        }).start();

        Camera.Parameters paras = camera.getParameters();
        int pixelformat = paras.getPreviewFormat();
        PixelFormat pixelinfo = new PixelFormat();
        PixelFormat.getPixelFormatInfo(pixelformat, pixelinfo);
        Camera.Size preSize = paras.getPreviewSize();
        preWidth = preSize.width;
        preHeight = preSize.height;
        AlgWrapper.getInstance().setImageParam(preHeight,preWidth);

        int bufSize = preWidth * preHeight * pixelinfo.bitsPerPixel / 8;

        for (int i = 0; i < 5; i++) {
            camera.addCallbackBuffer(new byte[bufSize]);
        }
        camera.setPreviewCallbackWithBuffer(this);

        try {
            camera.setPreviewDisplay(holder);
            camera.startPreview();

        } catch (Exception e) {
            e.printStackTrace();
        }
        isPreviewing = true;
        return true;
    }

    public boolean stop() {
        if (camera != null) {
            camera.stopPreview();
            try {
                camera.setPreviewDisplay(null);
            } catch (IOException e) {
                e.printStackTrace();
            }
            camera.release();
            camera = null;
        }
        return true;
    }

}