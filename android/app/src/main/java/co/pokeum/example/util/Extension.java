package co.pokeum.example.util;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

public class Extension {

    public static void showToast(Activity activity, CharSequence text, int duration) {
        activity.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(activity.getBaseContext(), text, duration).show();
            }
        });
    }

    public static void copyToClipboard(Context context, String label, String text) {
//        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.HONEYCOMB) {
//            android.text.ClipboardManager clipboard = (android.text.ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
//            clipboard.setText(text);
//        } else {
            android.content.ClipboardManager clipboard = (android.content.ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
            android.content.ClipData clip = android.content.ClipData.newPlainText(label, text);
            clipboard.setPrimaryClip(clip);
//        }
    }
}