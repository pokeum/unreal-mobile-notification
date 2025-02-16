object Versions {

    private const val MAJOR_NUMBER = 1
    private const val MINOR_NUMBER = 0
    private const val PATCH_NUMBER = 0

    const val VERSION_CODE = MAJOR_NUMBER * 1_000_000 + MINOR_NUMBER * 1_000 + PATCH_NUMBER
    const val VERSION_NAME = "$MAJOR_NUMBER.$MINOR_NUMBER.$PATCH_NUMBER"

    const val ANDROID_GRADLE_PLUGIN = "7.0.2"
    const val GOOGLE_SERVICE_PLUGIN = "4.3.10"

    const val COMPILE_SDK   = 33
    const val TARGET_SDK    = 33
    const val MIN_SDK       = 21

    const val KOTLIN = "1.8.0"

    const val ANDROIDX_ACTIVITY             = "1.7.0"
    const val ANDROIDX_APPCOMPAT            = "1.4.1"
    const val ANDROIDX_CONSTRAINT_LAYOUT    = "2.1.4"

    const val MATERIAL      = "1.6.0"
    const val GSON          = "2.11.0"

    const val UE4_FIREBASE_CORE         = "11.8.0"
    const val UE4_FIREBASE_MESSAGING    = "11.8.0"

    const val UE5_FIREBASE_CORE         = "21.1.1"
    const val UE5_FIREBASE_MESSAGING    = "23.0.8"
}