package hiscene.com.hiscenegesture.api;

/**
 * Created by leon on 17-3-22.
 */

public interface IAlgWrapper {
    /* get the ready status for the caller*/
    boolean isReady();

    /* setting the image height and width*/
    void setImageParam(int height, int width);

    /* send data to AlgWrapper from camera, Non-blocking call*/
    void sendImage(byte[] data);

    /* register notify callback function for recognize results*/
    void registerCallback(INotify notify);
}
