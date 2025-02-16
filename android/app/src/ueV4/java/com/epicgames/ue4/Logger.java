package com.epicgames.ue4;

import android.util.Log;

public class Logger {

    private final String tag;

    public Logger(String tag) {
        this.tag = tag;
    }

    public void verbose(String message) {
        Log.v(tag, message);
    }

    public void verbose(String message, Throwable throwable) {
        Log.v(tag, message, throwable);
    }

    public void debug(String message) {
        Log.d(tag, message);
    }

    public void debug(String message, Throwable throwable) {
        Log.d(tag, message, throwable);
    }

    public void info(String message) {
        Log.i(tag, message);
    }

    public void info(String message, Throwable throwable) {
        Log.i(tag, message, throwable);
    }

    public void warn(String message) {
        Log.w(tag, message);
    }

    public void warn(String message, Throwable throwable) {
        Log.w(tag, message, throwable);
    }

    public void error(String message) {
        Log.e(tag, message);
    }

    public void error(String message, Throwable throwable) {
        Log.e(tag, message, throwable);
    }
}
