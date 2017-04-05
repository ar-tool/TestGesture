package hiscene.com.hiscenegesture;

import android.content.Context;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by leon on 17-3-23.
 */

public class FileUtil {
    public static void copyAssetsFileToSDCard(Context context, String sourceFile, String destinationFile, boolean needRefresh) {
        if (!needRefresh) {
            File destination = new File(destinationFile);
            if (destination.exists()) return;
        }
        try {
            InputStream inputStream = context.getAssets().open(sourceFile);
            OutputStream outputStream = new FileOutputStream(destinationFile);
            // Transfer bytes from in to out
            byte[] buf = new byte[2048];
            int len;
            while ((len = inputStream.read(buf)) > 0) {
                outputStream.write(buf, 0, len);
            }
            inputStream.close();
            outputStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
