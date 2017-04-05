package hiscene.com.hiscenegesture;

import android.content.Context;
import android.graphics.PixelFormat;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by leon on 17-3-22.
 */

public class HisceneSurfaceView extends SurfaceView implements SurfaceHolder.Callback{
    private SurfaceHolder mHolder;
    private int m_direction;

    public HisceneSurfaceView(Context context) {
        this(context,null);
    }

    public HisceneSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        m_direction = 1;
        mHolder = getHolder();
        mHolder.addCallback(this);
        mHolder.setFormat(PixelFormat.TRANSPARENT);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if (0 != CameraPreview.getInstance().open(m_direction)) {
            return;
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        CameraPreview.getInstance().start(mHolder);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        CameraPreview.getInstance().stop();
    }
}
