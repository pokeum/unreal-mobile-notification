package co.pokeum.example.activity;

import android.widget.Toast;

import co.pokeum.example.util.Extension;
import co.pokeum.example.util.Logger;

public class GameActivity extends UPL {

    private static final Logger Log = new Logger();

    @Override
    protected void initUI() {

        binding.btnGetFirebaseToken.setOnClickListener(view -> binding.tvFirebaseToken.setText(getFirebaseToken()));

        binding.btnCopyFirebaseToken.setOnClickListener(view -> {
            String token = binding.tvFirebaseToken.getText().toString();
            if (token.isEmpty()) {
                Extension.showToast(this, "Nothing to copy!", Toast.LENGTH_SHORT);
            } else {
                Extension.copyToClipboard(this, "Firebase Token", token);
                Extension.showToast(this, "Copied to clipboard!", Toast.LENGTH_SHORT);
            }
        });

        binding.btnDeleteFirebaseToken.setOnClickListener(view -> {
            deleteFirebaseToken();
            binding.tvFirebaseToken.setText("");
        });
    }
}