object Libs {

    const val ANDROID_GRADLE_PLUGIN = "com.android.tools.build:gradle:${Versions.ANDROID_GRADLE_PLUGIN}"
    const val GOOGLE_SERVICE_PLUGIN = "com.google.gms:google-services:${Versions.GOOGLE_SERVICE_PLUGIN}"

    const val KOTLIN_STDLIB = "org.jetbrains.kotlin:kotlin-stdlib-jdk8:${Versions.KOTLIN}"

    const val ANDROIDX_ACTIVITY             = "androidx.activity:activity:${Versions.ANDROIDX_ACTIVITY}"
    const val ANDROIDX_APPCOMPAT            = "androidx.appcompat:appcompat:${Versions.ANDROIDX_APPCOMPAT}"
    const val ANDROIDX_CONSTRAINT_LAYOUT    = "androidx.constraintlayout:constraintlayout:${Versions.ANDROIDX_CONSTRAINT_LAYOUT}"

    const val MATERIAL      = "com.google.android.material:material:${Versions.MATERIAL}"
    const val GSON          = "com.google.code.gson:gson:${Versions.GSON}"

    private const val FIREBASE_CORE         = "com.google.firebase:firebase-core"
    private const val FIREBASE_MESSAGING    = "com.google.firebase:firebase-messaging"

    const val UE4_FIREBASE_CORE             = "$FIREBASE_CORE:${Versions.UE4_FIREBASE_CORE}"
    const val UE4_FIREBASE_MESSAGING        = "$FIREBASE_MESSAGING:${Versions.UE4_FIREBASE_MESSAGING}"

    const val UE5_FIREBASE_CORE             = "$FIREBASE_CORE:${Versions.UE5_FIREBASE_CORE}"
    const val UE5_FIREBASE_MESSAGING        = "$FIREBASE_MESSAGING:${Versions.UE5_FIREBASE_MESSAGING}"
}