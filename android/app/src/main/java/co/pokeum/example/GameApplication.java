package co.pokeum.example;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.concurrent.atomic.AtomicBoolean;

import co.pokeum.example.util.Logger;

public class GameApplication extends Application implements Application.ActivityLifecycleCallbacks {

    private static final Logger Log = new Logger();

    private static State state = State.UNKNOWN;

    private final AtomicBoolean launched = new AtomicBoolean(false);
    private final AtomicBoolean foregrounded = new AtomicBoolean(false);

    private int activityCreatedCount = 0;
    private int activityStartCount = 0;

    public static boolean isAppInBackground() {
        return (state == State.BACKGROUNDED);
    }

    @Override
    public void onCreate() {
        super.onCreate();
        registerActivityLifecycleCallbacks(this);
    }

    @Override
    public void onActivityCreated(@NonNull Activity activity, @Nullable Bundle bundle) {
        activityCreatedCount++;
        if (launched.get() &&
                !foregrounded.get() &&
                !activity.isChangingConfigurations()
        ) {
            foregrounded.set(true);
            updateState(State.FOREGROUNDED);
        } else if (activityCreatedCount == 1 &&
                !launched.getAndSet(true) &&
                !foregrounded.getAndSet(true) &&
                !activity.isChangingConfigurations()
        ) {
            updateState(State.LAUNCHED);
        }
    }

    @Override
    public void onActivityStarted(@NonNull Activity activity) {
        activityStartCount++;
    }

    @Override
    public void onActivityResumed(@NonNull Activity activity) {
        if (launched.get() &&
                !foregrounded.getAndSet(true) &&
                !activity.isChangingConfigurations()
        ) {
            updateState(State.FOREGROUNDED);
        }
    }

    @Override
    public void onActivityPaused(@NonNull Activity activity) {

    }

    @Override
    public void onActivityStopped(@NonNull Activity activity) {
        activityStartCount--;
        if (activityStartCount <= 0 &&
                foregrounded.get() &&
                !activity.isChangingConfigurations()
        ) {
            foregrounded.set(false);
            updateState(State.BACKGROUNDED);
        }
    }

    @Override
    public void onActivitySaveInstanceState(@NonNull Activity activity, @NonNull Bundle bundle) {

    }

    @Override
    public void onActivityDestroyed(@NonNull Activity activity) {
        activityCreatedCount--;
        if (activityCreatedCount <= 0 && !activity.isChangingConfigurations()) {
            updateState(State.STOPPED);
        }
    }

    private void updateState(State state) {
        GameApplication.state = state;
        Log.info("state={" + state.name() + "}");
    }

    private enum State { UNKNOWN, LAUNCHED, FOREGROUNDED, BACKGROUNDED, STOPPED }

    // Load library here!!!
    static {
        System.loadLibrary("unreal_notifications");
    }
}