package hiscene.com.hiscenegesture.base;

/**
 * Created by leon on 17-3-22.
 */

public class BaseBox {
    public int m_x;
    public int m_y;
    public int m_width;
    public int m_height;

    BaseBox()
    {
        m_x = 0;
        m_y = 0;
        m_width=0;
        m_height=0;
    }

    BaseBox(int x, int y, int height, int width)
    {
        m_x = x;
        m_y = y;
        m_height = height;
        m_width = width;
    }
}
