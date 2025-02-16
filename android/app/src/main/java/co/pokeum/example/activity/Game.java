package co.pokeum.example.activity;

import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import co.pokeum.example.databinding.ActivityMainBinding;
import co.pokeum.example.util.IntentLogger;

public abstract class Game extends AppCompatActivity {

    protected ActivityMainBinding binding;

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        gameActivityOnActivityResultAdditions(requestCode, resultCode, data);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Read metadata from AndroidManifest.xml
        try {
            ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            gameActivityReadMetadata(bundle);
        }
        catch (Throwable ignore) { }

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        initUI();

        gameActivityOnCreateAdditions();
    }

    @Override
    protected void onStart() {
        super.onStart();
        gameActivityOnStartAdditions();
    }

    @Override
    protected void onResume() {
        super.onResume();
        IntentLogger.logFullContent(getIntent());

        gameActivityOnResumeAdditions();
    }

    @Override
    protected void onPause() {
        super.onPause();
        gameActivityOnPauseAdditions();
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        setIntent(intent);

        gameActivityOnNewIntentAdditions(intent);
    }

    @Override
    protected void onStop() {
        super.onStop();
        gameActivityOnStopAdditions();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        gameActivityOnDestroyAdditions();
    }

    //=========================================================================================================//

    protected abstract void gameActivityReadMetadata(Bundle bundle);
    protected abstract void gameActivityOnCreateAdditions();
    protected abstract void gameActivityOnDestroyAdditions();
    protected abstract void gameActivityOnStartAdditions();
    protected abstract void gameActivityOnStopAdditions();
    protected abstract void gameActivityOnPauseAdditions();
    protected abstract void gameActivityOnResumeAdditions();
    protected abstract void gameActivityOnNewIntentAdditions(Intent newIntent);
    protected abstract void gameActivityOnActivityResultAdditions(int requestCode, int resultCode, Intent data);

    //=========================================================================================================//

    protected abstract void initUI();

    public static int LocalNotificationGetID(Context context) { return 0; }
}