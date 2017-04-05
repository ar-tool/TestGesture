package hiscene.com.hiscenegesture.base;

import java.util.ArrayList;
import java.util.List;

import hiscene.com.hiscenegesture.JNI.tradition.TraditionManager;
import hiscene.com.hiscenegesture.api.IAlgWrapper;
import hiscene.com.hiscenegesture.api.INotify;

/**
 * Created by leon on 17-3-22.
 */

public class AlgWrapper implements IAlgWrapper {
    private static final String TAG = "AlgWrapper";
    private boolean m_running_flag;
    private int m_height;
    private int m_width;
    private boolean m_status;
    private List<INotify> m_notifyList;
    private static AlgWrapper mInstance;

    public static AlgWrapper getInstance()
    {
        if(mInstance == null){
            mInstance = new AlgWrapper();
        }
        return mInstance;
    }

    private AlgWrapper()
    {
        m_height = 0;
        m_width = 0;
        m_status = true;
        m_notifyList = new ArrayList<>();
        TraditionManager.getInstance().init("");
    }

    /* get the ready status for the caller*/
    public boolean isReady()
    {
        return m_status;
    }

    /* setting the image height and width*/
    public void setImageParam(int height, int width)
    {
        m_height = height;
        m_width = width;
        TraditionManager.getInstance().setParam(height, width);

    }

    /* send data to AlgWrapper from camera, Non-blocking call*/
    public void sendImage(byte[] data)
    {
        m_status = false;
        // call the jni lib
        HisceneEvent event = TraditionManager.getInstance().detect(data);
        if(event != null) {
            processEvent(event);
        }
        m_status = true;
    }

    /* register notify callback function for recognize results*/
    public void registerCallback(INotify notify)
    {
        m_notifyList.add(notify);
    }

    private void processEvent(BaseEvent event)
    {
        if(m_notifyList != null) {
            for (INotify notify : m_notifyList) {
                notify.callback(event);
            }
        }
    }
}
