
$zip = $env:qmodName + ".zip"
$qmod = $env:qmodName + ".qmod"

Compress-Archive -Path  "./libs/arm64-v8a/libbeatsaber-hook_1_3_5.so",`
                        "./extern/libbeatsaber-hook_1_3_3.so",`
                        "./libs/arm64-v8a/libcustompillows.so",`
                        "./libs/arm64-v8a/libbs-utils.so",`
                        "./libs/arm64-v8a/libcodegen_0_9_0.so",`
                        "./libs/arm64-v8a/libquestui.so",`
                        "./libs/arm64-v8a/libcustom-types.so",`
                        "./cover.png",`
                        "./ExtraFiles/container.pillows",`
                        "./ExtraFiles/BMBF.png",`
                        "./ExtraFiles/BSMG.png",`
                        "./ExtraFiles/Cubes.png",`
                        "./ExtraFiles/simple.json",`
                        "./ExtraFiles/default.json",`
                        "./ExtraFiles/loss.json",`
                        "./ExtraFiles/linedup.json",`
                        "./mod.json" -DestinationPath $zip -Update

& move-item -Force $zip $qmod