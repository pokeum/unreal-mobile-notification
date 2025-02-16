package co.pokeum.example.util;

import android.os.Bundle;

import androidx.annotation.NonNull;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.util.HashMap;
import java.util.Map;

public class JsonUtil {

    public static String toPrettyJsonString(Object src) {
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        return gson.toJson(src);
    }

    public static String toPrettyJsonString(@NonNull Bundle bundle) {
        return toPrettyJsonString(bundleToMap(bundle));
    }

    private static Map<String, Object> bundleToMap(@NonNull Bundle bundle) {
        Map<String, Object> map = new HashMap<>();
        for (String key : bundle.keySet()) {
            map.put(key, bundle.get(key));
        }
        return map;
    }
}
