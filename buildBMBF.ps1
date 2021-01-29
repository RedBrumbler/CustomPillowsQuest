# Builds a .zip file for loading with BMBF
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
Compress-Archive -Path  "./libs/arm64-v8a/libmenupillowquest.so",`
                        "./bmbfmod.json",`
                        "./extern/libbeatsaber-hook_1_0_12.so",`
                        "./extern/libbs-utils.so",`
                        "./extern/libquestui.so",`
                        "./ExtraFiles/container.pillows",`
                        "./ExtraFiles/BeatTogether.png",`
                        "./ExtraFiles/BMBF.png",`
                        "./ExtraFiles/BSMG.png",`
                        "./ExtraFiles/Cubes.png",`
                        "./ExtraFiles/Qounters-.png",`
                        "./ExtraFiles/RichPresence.png",`
                        "./ExtraFiles/simple.json",`
                        "./ExtraFiles/busy.json",`
                        "./extern/libcustom-types.so" -DestinationPath "./MenuPillowQuest.zip" -Update
