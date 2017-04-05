package hiscene.com.hiscenegesture.JNI.tradition;

import hiscene.com.hiscenegesture.base.HisceneEvent;

/**
 * Created by leon on 17-3-22.
 */

public class TraditionManager {
    private static TraditionManager mInstance = null;

    private TraditionManager(){}
    public static TraditionManager getInstance(){
        if(null == mInstance){
            mInstance = new TraditionManager();
        }
        return  mInstance;
    }
    static {
        System.loadLibrary("tradition");
    }

    public native void init(String assetFolder);
    public native void setParam(int height, int width);
    public native HisceneEvent detect(byte[] data);
    public native void destory();
}
