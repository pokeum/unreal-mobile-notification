package co.pokeum.example.activity;

import android.content.Intent;
import android.os.Bundle;

import com.epicgames.unreal.notifications.EpicFirebaseMessagingService;
import com.google.firebase.messaging.FirebaseMessaging;

public abstract class UPL extends Game {

//================================================================================================================//

    public String getFirebaseToken() {
        return EpicFirebaseMessagingService.getFirebaseToken(this);
    }

    public void deleteFirebaseToken() {
        FirebaseMessaging.getInstance().deleteToken()
                .addOnCompleteListener(task -> FirebaseMessaging.getInstance().getToken());
    }

//================================================================================================================//

    @Override protected void gameActivityReadMetadata(Bundle bundle) { }
    @Override protected void gameActivityOnCreateAdditions() { }
    @Override protected void gameActivityOnDestroyAdditions() { }
    @Override protected void gameActivityOnStartAdditions() { }
    @Override protected void gameActivityOnStopAdditions() { }
    @Override protected void gameActivityOnPauseAdditions() { }
    @Override protected void gameActivityOnResumeAdditions() { }
    @Override protected void gameActivityOnNewIntentAdditions(Intent newIntent) { }
    @Override protected void gameActivityOnActivityResultAdditions(int requestCode, int resultCode, Intent data) { }
}
