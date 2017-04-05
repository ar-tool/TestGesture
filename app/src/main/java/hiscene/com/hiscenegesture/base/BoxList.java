package hiscene.com.hiscenegesture.base;

import java.util.ArrayList;

/**
 * Created by leon on 17-3-22.
 */

public class BoxList {
    public ArrayList<BaseBox> m_boxs;

    public BoxList()
    {
        m_boxs = new ArrayList<>();
    }

    void add(int x, int y, int height, int width)
    {
        BaseBox box = new BaseBox(x,y,height,width);
        m_boxs.add(box);
    }

    int count()
    {
        return m_boxs.size();
    }

    void clear()
    {
        m_boxs.clear();
    }
}
