if (Test-Path "./log.log")
{
    & del log.log
}
& adb logcat -c
#& adb logcat | Select-String "Scribble"
& adb logcat > log.log