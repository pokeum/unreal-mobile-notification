@file:Suppress("UnstableApiUsage")

plugins {
    id("com.android.application")
    id("com.google.gms.google-services")
}

android {
    namespace   = "co.pokeum.example"
    compileSdk  = Versions.COMPILE_SDK

    externalNativeBuild {
        cmake {
            path = file("src/main/jni/CMakeLists.txt")
        }
    }

    defaultConfig {
        applicationId   = "co.pokeum.example"
        minSdk          = Versions.MIN_SDK
        targetSdk       = Versions.TARGET_SDK
        versionCode     = Versions.VERSION_CODE
        versionName     = Versions.VERSION_NAME

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    flavorDimensions += "ue"
    productFlavors {
        create("ueV4") { dimension = "ue" }
        create("ueV5") { dimension = "ue" }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    buildFeatures {
        viewBinding = true
    }
}

dependencies {

    implementation(Libs.KOTLIN_STDLIB)

    implementation(Libs.ANDROIDX_ACTIVITY)
    implementation(Libs.ANDROIDX_APPCOMPAT)
    implementation(Libs.ANDROIDX_CONSTRAINT_LAYOUT)

    implementation(Libs.MATERIAL)
    implementation(Libs.GSON)

    "ueV4Implementation"(Libs.UE4_FIREBASE_CORE)
    "ueV4Implementation"(Libs.UE4_FIREBASE_MESSAGING)

    "ueV5Implementation"(Libs.UE5_FIREBASE_CORE)
    "ueV5Implementation"(Libs.UE5_FIREBASE_MESSAGING)
}