buildscript {
    repositories {
        google()
        mavenCentral()
    }
    dependencies {
        classpath(Libs.ANDROID_GRADLE_PLUGIN)
        classpath(Libs.GOOGLE_SERVICE_PLUGIN)
    }
}

allprojects {
    repositories {
        google()
        mavenCentral()
    }
}