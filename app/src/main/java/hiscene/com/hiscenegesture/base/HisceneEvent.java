package hiscene.com.hiscenegesture.base;

import java.util.ArrayList;

/**
 * Created by leon on 17-3-22.
 */

public class HisceneEvent extends BaseEvent {
    public ArrayList<BaseBox> m_HeadList;
    public ArrayList<BaseBox> m_HandList;

    public HisceneEvent()
    {
        m_HeadList = new ArrayList<>();
        m_HandList = new ArrayList<>();
    }
    public void addHandBox(int x, int y, int height, int width)
    {
        BaseBox box = new BaseBox(x,y,height,width);
        m_HandList.add(box);
    }

    public void addHeadBox(int x, int y, int height, int width)
    {
        BaseBox box = new BaseBox(x,y,height,width);
        m_HeadList.add(box);
    }

    public int HandBoxCount()
    {
        return m_HandList.size();
    }

    public int HeadBoxCount()
    {
        return m_HeadList.size();
    }

    public int count()
    {
        return HandBoxCount() + HeadBoxCount();
    }

    public void clearHand()
    {
        m_HandList.clear();
    }

    public void clearHead()
    {
        m_HeadList.clear();
    }

    public void clear()
    {
        m_HandList.clear();
        m_HeadList.clear();
    }

}
