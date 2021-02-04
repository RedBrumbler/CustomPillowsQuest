# Builds a .zip file for loading with BMBF
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
Compress-Archive -Path  "./libs/arm64-v8a/libcustompillowsquest.so",`
                        "./bmbfmod.json",`
                        "./cover.png",`
                        "./libs/arm64-v8a/libbeatsaber-hook_1_0_12.so",`
                        "./ExtraFiles/container.pillows",`
                        "./ExtraFiles/BMBF.png",`
                        "./ExtraFiles/BSMG.png",`
                        "./ExtraFiles/Cubes.png",`
                        "./ExtraFiles/simple.json",`
                        "./ExtraFiles/default.json",`
                        "./ExtraFiles/loss.json",`
                        "./ExtraFiles/linedup.json" -DestinationPath "./CustomPillowsQuest.zip" -Update
