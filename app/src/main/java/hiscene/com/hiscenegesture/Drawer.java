package hiscene.com.hiscenegesture;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.PorterDuff;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;

import java.util.ArrayList;
import java.util.List;

import hiscene.com.hiscenegesture.api.IDrawer;
import hiscene.com.hiscenegesture.api.INotify;
import hiscene.com.hiscenegesture.base.AlgWrapper;
import hiscene.com.hiscenegesture.base.BaseBox;
import hiscene.com.hiscenegesture.base.BaseEvent;
import hiscene.com.hiscenegesture.base.HisceneEvent;

/**
 * Created by leon on 17-3-22.
 */

public class Drawer extends SurfaceView implements SurfaceHolder.Callback, Runnable,IDrawer,INotify {
    private static String TAG = "Drawer";

    private SurfaceHolder mHolder;
    /**
     * 画布
     */
    private Canvas mCanvas;
    private Thread mThread;
    private boolean mIsRunning  = false;
    private Paint mPaint;
    private List<BaseEvent> m_events = new ArrayList<>();
    private Object mutex = new Object();
    // default width and height for the screen
    private float mScalar_width = (float)(1920*1.0f/1280);
    private float mScalar_height = (float)(1080*1.0f/720);
    public Drawer(Context context) {
        this(context,null);
    }

    public Drawer(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        mHolder= getHolder();
        mHolder.addCallback(this);
        mHolder.setFormat(PixelFormat.TRANSPARENT);

        // get the screen size
        WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics dm = new DisplayMetrics();
        wm.getDefaultDisplay().getMetrics(dm);
        mScalar_width = (float)(dm.widthPixels*1.0f/1280);
        mScalar_height = (float)(dm.heightPixels*1.0f/720);
    }

    @Override
    public void run() {
        while (!Thread.currentThread().isInterrupted()){

            if(mIsRunning){
                long start = System.currentTimeMillis();
                synchronized (mHolder){
                    try {
                            //锁定画布
                            mCanvas = mHolder.lockCanvas();
                            if (mCanvas == null) {
                                return;
                            }
                            draw();

                    }catch (Exception e){
                        e.printStackTrace();
                    }finally {
                            mHolder.unlockCanvasAndPost(mCanvas);
                    }
                }
                //绘制后的毫秒值
                long end = System.currentTimeMillis();
                //如果绘制时间不到10000毫秒，让线程休眠到100毫秒
//                if (end - start < 100&&(Thread.currentThread().isInterrupted() ==true)) {
//                    try {
//                        Thread.sleep(100 - (end - start));
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//              }
            }
        }
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        //设置画笔
        mPaint = new Paint();
        mPaint.setAntiAlias(true);
        mPaint.setDither(true);
        mPaint.setStyle(Paint.Style.STROKE);
        mPaint.setStrokeWidth(5.0f);
        //不启动启动线程
        mIsRunning = true;
        mThread = new Thread(this);
        AlgWrapper.getInstance().registerCallback(this);
        mThread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        //关闭线程的开关
        mIsRunning = false;
//        mThread.interrupt();
//        mThread = null;
    }

    private void draw()
    {
        synchronized (mutex){
            if(m_events.size() !=0){
                //draw the newest event
                draw(m_events.get((m_events.size()-1)));
                //m_events.clear();
            }
        }
    }

    public void draw(BaseEvent event)
    {    mCanvas.save();
        //每次绘制清屏
        mCanvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);//绘制透明色
        HisceneEvent e = (HisceneEvent)event;
        if(e.HandBoxCount() != 0)
        {
            mPaint.setColor(Color.GREEN);
            for(BaseBox box: e.m_HandList)
            {
                mCanvas.save();
                mCanvas.drawRect((float)(box.m_x)*mScalar_width,(float)(box.m_y)*mScalar_height,
                        (float)(box.m_x+box.m_width)*mScalar_width,(float)(box.m_y+box.m_height)*mScalar_height,mPaint);
                mCanvas.restore();
            }
        }

        if(e.HeadBoxCount() !=0)
        {
            mPaint.setColor(Color.RED);

            for(BaseBox box: e.m_HeadList)
            {
                mCanvas.save();
                mCanvas.drawRect((float)(box.m_x)*mScalar_width,(float)(box.m_y)*mScalar_height,
                            (float)(box.m_x+box.m_width)*mScalar_width,(float)(box.m_y+box.m_height)*mScalar_height,mPaint);
                mCanvas.restore();
            }
        }
        mIsRunning = false;
        mCanvas.restore();
    }

    public void callback(BaseEvent event)
    {
        mIsRunning = true;
        synchronized (mCanvas)
        {
            m_events.clear();
            m_events.add(event);
        }
    }

}
