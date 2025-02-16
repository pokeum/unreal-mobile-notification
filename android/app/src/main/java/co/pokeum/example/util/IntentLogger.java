package co.pokeum.example.util;

import android.content.Intent;
import android.os.Bundle;

import java.util.Set;

public class IntentLogger {

    private static final Logger Log = new Logger("IntentLogger");

    private static final String KEY_PACKAGE     = "Package     : ";
    private static final String KEY_ACTION      = "Action      : ";
    private static final String KEY_TYPE        = "Type        : ";
    private static final String KEY_CATEGORIES  = "Categories  : ";
    private static final String KEY_COMPONENT   = "Component   : ";
    private static final String KEY_DATA_STRING = "Data String : ";
    private static final String KEY_EXTRAS      = "Extras      : ";

    private static final String BORDER_LINE     = "-".repeat(100);

    public static void logFullContent(Intent intent) {

        Log.verbose(BORDER_LINE);
        Log.verbose(KEY_PACKAGE + intent.getPackage());
        Log.verbose(KEY_ACTION + intent.getAction());
        Log.verbose(KEY_TYPE + intent.getType());
        printCategories(intent.getCategories());
        Log.verbose(KEY_COMPONENT + intent.getComponent());
        Log.verbose(KEY_DATA_STRING + intent.getDataString());
        printExtras(intent.getExtras());
        Log.verbose(BORDER_LINE);
    }

    private static void printCategories(Set<String> categories) {
        StringBuilder value = new StringBuilder();
        if (categories == null) {
            value.append("null");
        } else if (categories.isEmpty()) {
            value.append("-");
        } else {
            for (String category : categories) {
                if (!value.toString().isEmpty()) value.append(", ");
                value.append(category);
            }
        }
        Log.verbose(KEY_CATEGORIES + value);
    }

    private static void printExtras(Bundle extras) {
        StringBuilder value = new StringBuilder();
        if (extras == null) {
            value.append("null");
        } else if (extras.isEmpty()) {
            value.append("-");
        } else {
            value.append(JsonUtil.toPrettyJsonString(extras));
        }
        Log.verbose(KEY_EXTRAS + value);
    }
}