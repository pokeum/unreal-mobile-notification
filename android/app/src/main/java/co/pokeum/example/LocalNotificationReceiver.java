package co.pokeum.example;

import android.annotation.SuppressLint;
import android.content.Context;

public class LocalNotificationReceiver {

    public static final String KEY_LOCAL_NOTIFICATION_ID        = "local-notification-ID";
    public static final String KEY_LOCAL_NOTIFICATION_TITLE     = "local-notification-title";
    public static final String KEY_LOCAL_NOTIFICATION_BODY      = "local-notification-body";
    public static final String KEY_LOCAL_NOTIFICATION_ACTION    = "local-notification-action";

    public static int getNotificationIconID(Context context) {
        int notificationIconID = getDrawableResourceByName(context, "ic_notification_simple");
        if (notificationIconID == 0) {
            notificationIconID = getDrawableResourceByName(context, "ic_notification");
        }
        if (notificationIconID == 0) {
            notificationIconID = getDrawableResourceByName(context, "icon");
        }
        return notificationIconID;
    }

    @SuppressLint("DiscouragedApi")
    private static int getDrawableResourceByName(Context context, String name) {
        return context.getResources().getIdentifier(name, "drawable", context.getPackageName());
    }
}
