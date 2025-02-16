// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using System.Text;
using UnrealBuildTool;

public class MobileNotification : ModuleRules
{
	class FirebaseSettings
	{
		public bool FirebaseEnabled = false;
		public string FirebaseService = "";                             // for Android
		public bool AutoRegisterForRemoteNotificationsEnabled = false;  // for iOS
		public string ProjectName = "";                                 // for iOS

		public override string ToString()
		{
			return new StringBuilder()
				.Append("FirebaseSettings: ")
				.AppendFormat("FirebaseEnabled={{{0}}}, ", FirebaseEnabled)
				.AppendFormat("FirebaseService={{{0}}}, ", FirebaseService)
				.AppendFormat("AutoRegisterForRemoteNotificationsEnabled={{{0}}}, ", AutoRegisterForRemoteNotificationsEnabled)
				.AppendFormat("ProjectName={{{0}}}", ProjectName)
				.ToString();
		}
	}
	
	public MobileNotification(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "Engine" });

		PublicDefinitions.Add("WITH_FIREBASE=1");
		string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
		
		// Read Firebase Settings
		FirebaseSettings firebaseSettings = new FirebaseSettings();
		ReadFirebaseSettingsConfig(ref firebaseSettings);
		Console.WriteLine("Mobile Notification: {0}", firebaseSettings);
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.Add("Launch");

			if (OrLater(5, 1, 1))
			{
				CopyAndroidUPL("UPL_Android.v5.1.1.xml");
			}
			else if (OrLater(5, 0, 0))
			{
				CopyAndroidUPL("UPL_Android.v5.xml");
			}
			else
			{
				CopyAndroidUPL("UPL_Android.v4.xml");
			}
			
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "MobileNotification_UPL_Android.xml"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			if (firebaseSettings.AutoRegisterForRemoteNotificationsEnabled)
			{
				PublicDefinitions.Add("AUTO_REGISTER_FOR_REMOTE_NOTIFICATIONS");
			}
			
			PublicDefinitions.Add("WITH_FIREBASE_IOS=1");
			PublicDefinitions.Add("WITH_NOTIFICATIONS=1");
			string FirebaseBaseIOSDir = Path.Combine(ModuleDirectory, "Firebase/iOS/");
			
			PublicSystemIncludePaths.AddRange(new string[] { FirebaseBaseIOSDir + "include", });

			// Firebase frameworks for cloud messaging (notifications)
			PublicAdditionalFrameworks.Add(
				new Framework(
					"FIRAnalyticsConnector",
					Path.Combine(FirebaseBaseIOSDir, "FIRAnalyticsConnector.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"FirebaseAnalytics",
					Path.Combine(FirebaseBaseIOSDir, "FirebaseAnalytics.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"FirebaseCore",
					Path.Combine(FirebaseBaseIOSDir, "FirebaseCore.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"FirebaseCoreDiagnostics",
					Path.Combine(FirebaseBaseIOSDir, "FirebaseCoreDiagnostics.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"FirebaseInstanceID",
					Path.Combine(FirebaseBaseIOSDir, "FirebaseInstanceID.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"FirebaseMessaging",
					Path.Combine(FirebaseBaseIOSDir, "FirebaseMessaging.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"GoogleAppMeasurement",
					Path.Combine(FirebaseBaseIOSDir, "GoogleAppMeasurement.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"GoogleUtilities",
					Path.Combine(FirebaseBaseIOSDir, "GoogleUtilities.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"nanopb",
					Path.Combine(FirebaseBaseIOSDir, "nanopb.framework.zip"),
					""
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"Protobuf",
					Path.Combine(FirebaseBaseIOSDir, "Protobuf.framework.zip"),
					""
				)
			);
            
			PublicIncludePathModuleNames.Add("Launch");
			
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "MobileNotification_UPL_IOS.xml"));
            
			PrivateIncludePaths.Add("MobileNotification/Private/Platforms/iOS");
		}
	}
	
	private void ReadFirebaseSettingsConfig(ref FirebaseSettings Settings)
	{
		// Read from config
		ConfigHierarchy Ini = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, Target.ProjectFile.Directory, Target.Platform);

		string SettingsSection = "Firebase";
		Ini.GetBool(SettingsSection, "FirebaseEnabled", out Settings.FirebaseEnabled);
		Ini.GetString(SettingsSection, "FirebaseService", out Settings.FirebaseService);
		Ini.GetBool(SettingsSection, "AutoRegisterForRemoteNotificationsEnabled", out Settings.AutoRegisterForRemoteNotificationsEnabled);
		Ini.GetString(SettingsSection, "ProjectName", out Settings.ProjectName);
	}
    
	private void CopyAndroidUPL(string filename)
	{
		try
		{
			string source = Path.Combine(ModuleDirectory, "Firebase/UPL", filename);
			string destination = Path.Combine(ModuleDirectory, "MobileNotification_UPL_Android.xml");
            
			File.Copy(source, destination, true);
			Console.WriteLine("Mobile Notification: Copied Android UPL file. ({0})", filename);
		}
		catch (Exception e)
		{
			Console.WriteLine("Mobile Notification: Something broken while copying Android UPL: {0}", e.Message);
		}
	}
	
	private bool OrLater(int major, int minor, int patch)
	{
		return GetVersionCode(
			Target.Version.MajorVersion,
			Target.Version.MinorVersion,
			Target.Version.PatchVersion
		) >= GetVersionCode(major, minor, patch);
	}

	private int GetVersionCode(int major, int minor, int patch)
	{
		return major * 1_000_000 + minor * 1_000 + patch;
	}
}